#include "stone/Core/FileMgr.h"
#include "stone/Core/FileSystemStatCache.h"

#include "llvm/ADT/SmallString.h"
#include "llvm/Config/llvm-config.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/raw_ostream.h"


#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>

using namespace stone;

//===----------------------------------------------------------------------===//
// Common logic.
//===----------------------------------------------------------------------===//

FileMgr::FileMgr(const FileSystemOptions &fileSysOpts,
                         IntrusiveRefCntPtr<llvm::vfs::FileSystem> fileSys)
    : fileSysOpts(std::move(fileSysOpts)), fileSys(fileSys), seenDirs(64),
      seenFiles(64), nextFileUID(0) {

  numDirLookups = numFileLookups = 0;
  numDirCacheMisses = numFileCacheMisses = 0;

  // If the caller doesn't provide a virtual file system, just grab the real
  // file system.
  if (!this->fileSys)
    this->fileSys = llvm::vfs::getRealFileSystem();
}

FileMgr::~FileMgr() = default;

void FileMgr::SetStatCache(std::unique_ptr<FileSystemStatCache> cache) {
  assert(cache && "No stat cache provided?");
  statCache = std::move(cache);
}

void FileMgr::ClearStatCache() { statCache.reset(); }

/// Retrieve the directory that the given file name resides in.
/// Filename can point to either a real file or a virtual file.
static const Directory *GetDirFromFile(FileMgr &fileMgr,
                                                  StringRef Filename,
                                                  bool CacheFailure) {
  if (Filename.empty())
    return nullptr;

  if (llvm::sys::path::is_separator(Filename[Filename.size() - 1]))
    return nullptr; // If Filename is a directory.

  StringRef DirName = llvm::sys::path::parent_path(Filename);
  // Use the current directory if file has no path component.
  if (DirName.empty())
    DirName = ".";

  return fileMgr.GetDir(DirName, CacheFailure);
}

/// Add all ancestors of the given path (pointing to either a file or
/// a directory) as virtual directories.
void FileMgr::AddAncestorsAsVirtualDirs(StringRef Path) {
  StringRef DirName = llvm::sys::path::parent_path(Path);
  if (DirName.empty())
    DirName = ".";

  auto &NamedDirEnt = *seenDirs.insert({DirName, nullptr}).first;

  // When caching a virtual directory, we always cache its ancestors
  // at the same time.  Therefore, if DirName is already in the cache,
  // we don't need to recurse as its ancestors must also already be in
  // the cache (or it's a known non-virtual directory).
  if (NamedDirEnt.second)
    return;

  // Add the virtual directory to the cache.
  auto UDE = llvm::make_unique<Directory>();
  UDE->dirName = NamedDirEnt.first();
  NamedDirEnt.second = UDE.get();
  virtDirs.push_back(std::move(UDE));

  // Recursively add the other ancestors.
  AddAncestorsAsVirtualDirs(DirName);
}

const Directory *FileMgr::GetDir(StringRef DirName,
                                                bool CacheFailure) {
  // stat doesn't like trailing separators except for root directory.
  // At least, on Win32 MSVCRT, stat() cannot strip trailing '/'.
  // (though it can strip '\\')
  if (DirName.size() > 1 &&
      DirName != llvm::sys::path::root_path(DirName) &&
      llvm::sys::path::is_separator(DirName.back()))
    DirName = DirName.substr(0, DirName.size()-1);


#ifdef _WIN32
  // Fixing a problem with "clang C:test.c" on Windows.
  // Stat("C:") does not recognize "C:" as a valid directory
  std::string DirNameStr;
  if (DirName.size() > 1 && DirName.back() == ':' &&
      DirName.equals_lower(llvm::sys::path::root_name(DirName))) {
    DirNameStr = DirName.str() + '.';
    DirName = DirNameStr;
  }
#endif

  ++numDirLookups;

  // See if there was already an entry in the map.  Note that the map
  // contains both virtual and real directories.
  auto seenDirInsertResult = seenDirs.insert({DirName, nullptr});
  if (!seenDirInsertResult.second)
    return seenDirInsertResult.first->second;

  // We've not seen this before. Fill it in.
  ++numDirCacheMisses;
  auto &NamedDirEnt = *seenDirInsertResult.first;
  assert(!NamedDirEnt.second && "should be newly-created");

  // Get the null-terminated directory name as stored as the key of the
  // seenDirs map.
  StringRef InterndDirName = NamedDirEnt.first();

  // Check to see if the directory exists.
  llvm::vfs::Status Status;
  if (GetStatValue(InterndDirName, Status, false, nullptr /*directory lookup*/)) {
    // There's no real directory at the given path.
    if (!CacheFailure)
      seenDirs.erase(DirName);
    return nullptr;
  }

  // It exists.  See if we have already opened a directory with the
  // same inode (this occurs on Unix-like systems when one dir is
  // symlinked to another, for example) or the same path (on
  // Windows).
  Directory &UDE = uniqueRealDirs[Status.getUniqueID()];

  NamedDirEnt.second = &UDE;
  if (UDE.GetName().empty()) {
    // We don't have this directory yet, add it.  We use the string
    // key from the seenDirs map as the string.
    UDE.dirName  = InterndDirName;
  }

  return &UDE;
}

const SrcFile *FileMgr::GetFile(StringRef Filename, bool openFile,
                                      bool CacheFailure) {
  ++numFileLookups;

  // See if there is already an entry in the map.
  auto seenFileInsertResult = seenFiles.insert({Filename, nullptr});
  if (!seenFileInsertResult.second)
    return seenFileInsertResult.first->second;

  // We've not seen this before. Fill it in.
  ++numFileCacheMisses;
  auto &NamedFileEnt = *seenFileInsertResult.first;
  assert(!NamedFileEnt.second && "should be newly-created");

  // Get the null-terminated file name as stored as the key of the
  // seenFiles map.
  StringRef InterndFileName = NamedFileEnt.first();

  // Look up the directory for the file.  When looking up something like
  // sys/foo.h we'll discover all of the search directories that have a 'sys'
  // subdirectory.  This will let us avoid having to waste time on known-to-fail
  // searches when we go to find sys/bar.h, because all the search directories
  // without a 'sys' subdir will get a cached failure result.
  const Directory *DirInfo = GetDirFromFile(*this, Filename,
                                                       CacheFailure);
  if (DirInfo == nullptr) { // Directory doesn't exist, file can't exist.
    if (!CacheFailure)
      seenFiles.erase(Filename);

    return nullptr;
  }

  // FIXME: Use the directory info to prune this, before doing the stat syscall.
  // FIXME: This will reduce the # syscalls.

  // Check to see if the file exists.
  std::unique_ptr<llvm::vfs::File> F;
  llvm::vfs::Status Status;
  if (GetStatValue(InterndFileName, Status, true, openFile ? &F : nullptr)) {
    // There's no real file at the given path.
    if (!CacheFailure)
      seenFiles.erase(Filename);

    return nullptr;
  }

  assert((openFile || !F) && "undesired open file");

  // It exists.  See if we have already opened a file with the same inode.
  // This occurs when one dir is symlinked to another, for example.
  SrcFile &UFE = uniqueRealFiles[Status.getUniqueID()];

  NamedFileEnt.second = &UFE;

  // If the name returned by GetStatValue is different than Filename, re-intern
  // the name.
  if (Status.getName() != Filename) {
    auto &NamedFileEnt =
      *seenFiles.insert({Status.getName(), &UFE}).first;
    assert(NamedFileEnt.second == &UFE &&
           "filename from getStatValue() refers to wrong file");
    InterndFileName = NamedFileEnt.first().data();
  }

  if (UFE.IsValid()) { // Already have an entry with this inode, return it.

    // FIXME: this hack ensures that if we look up a file by a virtual path in
    // the VFS that the getDir() will have the virtual path, even if we found
    // the file by a 'real' path first. This is required in order to find a
    // module's structure when its headers/module map are mapped in the VFS.
    // We should remove this as soon as we can properly support a file having
    // multiple names.
    if (DirInfo != UFE.dir && Status.IsVFSMapped)
      UFE.dir = DirInfo;

    // Always update the name to use the last name by which a file was accessed.
    // FIXME: Neither this nor always using the first name is correct; we want
    // to switch towards a design where we return a FileName object that
    // encapsulates both the name by which the file was accessed and the
    // corresponding SrcFile.
    UFE.fileName = InterndFileName;

    return &UFE;
  }

  // Otherwise, we don't have this file yet, add it.
  UFE.fileName    = InterndFileName;
  UFE.fileSize    = Status.getSize();
  UFE.modificationTime = llvm::sys::toTimeT(Status.getLastModificationTime());
  UFE.dir     = DirInfo;
  UFE.UID     = nextFileUID++;
  UFE.uniqueID = Status.getUniqueID();
  UFE.isNamedPipe = Status.getType() == llvm::sys::fs::file_type::fifo_file;
  UFE.file = std::move(F);
  UFE.isValid = true;

  if (UFE.file) {
    if (auto PathName = UFE.file->getName())
      FillRealPathName(&UFE, *PathName);
  } else if (!openFile) {
    // We should still fill the path even if we aren't opening the file.
    FillRealPathName(&UFE, InterndFileName);
  }
  return &UFE;
}

const SrcFile *
FileMgr::GetVirtualFile(StringRef Filename, off_t Size,
                            time_t ModificationTime) {
  ++numFileLookups;

  // See if there is already an entry in the map for an existing file.
  auto &NamedFileEnt = *seenFiles.insert({Filename, nullptr}).first;
  if (NamedFileEnt.second)
    return NamedFileEnt.second;

  // We've not seen this before, or the file is cached as non-existent.
  ++numFileCacheMisses;
  AddAncestorsAsVirtualDirs(Filename);
  SrcFile *UFE = nullptr;

  // Now that all ancestors of Filename are in the cache, the
  // following call is guaranteed to find the Directory from the
  // cache.
  const Directory *DirInfo = GetDirFromFile(*this, Filename,
                                                       /*CacheFailure=*/true);
  assert(DirInfo &&
         "The directory of a virtual file should already be in the cache.");

  // Check to see if the file exists. If so, drop the virtual file
  llvm::vfs::Status Status;
  const char *InterndFileName = NamedFileEnt.first().data();
  if (GetStatValue(InterndFileName, Status, true, nullptr) == 0) {
    UFE = &uniqueRealFiles[Status.getUniqueID()];
    Status = llvm::vfs::Status(
      Status.getName(), Status.getUniqueID(),
      llvm::sys::toTimePoint(ModificationTime),
      Status.getUser(), Status.getGroup(), Size,
      Status.getType(), Status.getPermissions());

    NamedFileEnt.second = UFE;

    // If we had already opened this file, close it now so we don't
    // leak the descriptor. We're not going to use the file
    // descriptor anyway, since this is a virtual file.
    if (UFE->file)
      UFE->CloseFile();

    // If we already have an entry with this inode, return it.
    if (UFE->IsValid())
      return UFE;

    UFE->uniqueID = Status.getUniqueID();
    UFE->isNamedPipe = Status.getType() == llvm::sys::fs::file_type::fifo_file;
    FillRealPathName(UFE, Status.getName());
  } else {
    virtFiles.push_back(llvm::make_unique<SrcFile>());
    UFE = virtFiles.back().get();
    NamedFileEnt.second = UFE;
  }

  UFE->fileName    = InterndFileName;
  UFE->fileSize    = Size;
  UFE->modificationTime = ModificationTime;
  UFE->dir     = DirInfo;
  UFE->UID     = nextFileUID++;
  UFE->isValid = true;
  UFE->file.reset();
  return UFE;
}

bool FileMgr::FixupRelativePath(SmallVectorImpl<char> &path) const {
  StringRef pathRef(path.data(), path.size());

  if (fileSysOpts.workingDir.empty()
      || llvm::sys::path::is_absolute(pathRef))
    return false;

  SmallString<128> NewPath(fileSysOpts.workingDir);
  llvm::sys::path::append(NewPath, pathRef);
  path = NewPath;
  return true;
}

bool FileMgr::MakeAbsolutePath(SmallVectorImpl<char> &Path) const {
  bool Changed = FixupRelativePath(Path);

  if (!llvm::sys::path::is_absolute(StringRef(Path.data(), Path.size()))) {
    fileSys->makeAbsolute(Path);
    Changed = true;
  }

  return Changed;
}

void FileMgr::FillRealPathName(SrcFile *UFE, llvm::StringRef FileName) {
  llvm::SmallString<128> AbsPath(FileName);
  // This is not the same as `VFS::getRealPath()`, which resolves symlinks
  // but can be very expensive on real file systems.
  // FIXME: the semantic of RealPathName is unclear, and the name might be
  // misleading. We need to clean up the interface here.
  MakeAbsolutePath(AbsPath);
  llvm::sys::path::remove_dots(AbsPath, /*remove_dot_dot=*/true);
  UFE->realPathName = AbsPath.str();
}

llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>>
FileMgr::GetBufferForFile(const SrcFile *Entry, bool isVolatile,
                              bool ShouldCloseOpenFile) {
  uint64_t FileSize = Entry->GetSize();
  // If there's a high enough chance that the file have changed since we
  // got its size, force a stat before opening it.
  if (isVolatile)
    FileSize = -1;

  StringRef Filename = Entry->GetName();
  // If the file is already open, use the open file descriptor.
  if (Entry->file) {
    auto Result =
        Entry->file->getBuffer(Filename, FileSize,
                               /*RequiresNullTerminator=*/true, isVolatile);
    // FIXME: we need a set of APIs that can make guarantees about whether a
    // SrcFile is open or not.
    if (ShouldCloseOpenFile)
      Entry->CloseFile();
    return Result;
  }

  // Otherwise, open the file.

  if (fileSysOpts.workingDir.empty())
    return fileSys->getBufferForFile(Filename, FileSize,
                                /*RequiresNullTerminator=*/true, isVolatile);

  SmallString<128> FilePath(Entry->GetName());
  FixupRelativePath(FilePath);
  return fileSys->getBufferForFile(FilePath, FileSize,
                              /*RequiresNullTerminator=*/true, isVolatile);
}

llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>>
FileMgr::GetBufferForFile(StringRef Filename, bool isVolatile) {
  if (fileSysOpts.workingDir.empty())
    return fileSys->getBufferForFile(Filename, -1, true, isVolatile);

  SmallString<128> FilePath(Filename);
  FixupRelativePath(FilePath);
  return fileSys->getBufferForFile(FilePath.c_str(), -1, true, isVolatile);
}

/// getStatValue - Get the 'stat' information for the specified path,
/// using the cache to accelerate it if possible.  This returns true
/// if the path points to a virtual file or does not exist, or returns
/// false if it's an existent real file.  If FileDescriptor is NULL,
/// do directory look-up instead of file look-up.
bool FileMgr::GetStatValue(StringRef Path, llvm::vfs::Status &Status,
                               bool isFile,
                               std::unique_ptr<llvm::vfs::File> *file) {
  // FIXME: FileSystemOpts shouldn't be passed in here, all paths should be
  // absolute!
  if (fileSysOpts.workingDir.empty())
    return bool(FileSystemStatCache::Get(Path, Status, isFile, file,
                                         statCache.get(), *fileSys));

  SmallString<128> FilePath(Path);
  FixupRelativePath(FilePath);

  return bool(FileSystemStatCache::Get(FilePath.c_str(), Status, isFile, file,
                                       statCache.get(), *fileSys));
}

bool FileMgr::GetNoncachedStatValue(StringRef Path,
                                        llvm::vfs::Status &Result) {
  SmallString<128> FilePath(Path);
  FixupRelativePath(FilePath);

  llvm::ErrorOr<llvm::vfs::Status> S = fileSys->status(FilePath.c_str());
  if (!S)
    return true;
  Result = *S;
  return false;
}

void FileMgr::InvalidateCache(const SrcFile *Entry) {
  assert(Entry && "Cannot invalidate a NULL SrcFile");

  seenFiles.erase(Entry->GetName());

  // SrcFile invalidation should not block future optimizations in the file
  // caches. Possible alternatives are cache truncation (invalidate last N) or
  // invalidation of the whole cache.
  //
  // FIXME: This is broken. We sometimes have the same SrcFile* shared
  // betweeen multiple seenFiles, so this can leave dangling pointers.
  uniqueRealFiles.erase(Entry->GetUniqueID());
}

void FileMgr::GetUniqueIDMapping(
                   SmallVectorImpl<const SrcFile *> &UIDToFiles) const {
  UIDToFiles.clear();
  UIDToFiles.resize(nextFileUID);

  // Map file entries
  for (llvm::StringMap<SrcFile*, llvm::BumpPtrAllocator>::const_iterator
         FE = seenFiles.begin(), FEEnd = seenFiles.end();
       FE != FEEnd; ++FE)
    if (FE->getValue())
      UIDToFiles[FE->getValue()->GetUID()] = FE->getValue();

  // Map virtual file entries
  for (const auto &VFE : virtFiles)
    UIDToFiles[VFE->GetUID()] = VFE.get();
}

void FileMgr::ModifySrcFile(SrcFile *file, off_t fileSize, time_t modificationTime) {
	file->fileSize = fileSize;
  file->modificationTime = modificationTime;
}

StringRef FileMgr::GetCanonicalName(const Directory *Dir) {
  // FIXME: use llvm::sys::fs::canonical() when it gets implemented
  llvm::DenseMap<const Directory *, llvm::StringRef>::iterator Known
    = canonicalDirNames.find(Dir);
  if (Known != canonicalDirNames.end())
    return Known->second;

  StringRef CanonicalName(Dir->GetName());

  SmallString<4096> CanonicalNameBuf;
  if (!fileSys->getRealPath(Dir->GetName(), CanonicalNameBuf))
    CanonicalName = StringRef(CanonicalNameBuf).copy(canonicalNameStorage);

  canonicalDirNames.insert({Dir, CanonicalName});
  return CanonicalName;
}

void FileMgr::PrintStats() const {

  llvm::errs() << "\n*** File Manager Stats:\n";
  llvm::errs() << uniqueRealFiles.size() << " real files found, "
               << uniqueRealDirs.size() << " real dirs found.\n";
  llvm::errs() << virtFiles.size() << " virtual files found, "
               << virtDirs.size() << " virtual dirs found.\n";
  llvm::errs() << numDirLookups << " dir lookups, "
               << numDirCacheMisses << " dir cache misses.\n";
  llvm::errs() << numFileLookups << " file lookups, "
               << numFileCacheMisses << " file cache misses.\n";

  //llvm::errs() << PagesMapped << BytesOfPagesMapped << FSLookups;
}
