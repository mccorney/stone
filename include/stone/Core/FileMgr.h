#ifndef STONE_CORE_FILEMGR_H
#define STONE_CORE_FILEMGR_H

#include "stone/Core/FileSystem.h"
#include "stone/Core/SrcFile.h"
#include "stone/Core/LLVM.h"

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Allocator.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/VirtualFileSystem.h"

#include <ctime>
#include <map>
#include <memory>
#include <string>

namespace llvm {
class MemoryBuffer;
} // end namespace llvm

namespace stone {

//class FileSysStatCache;

/// Cached information about one directory (either on disk or in
/// the virtual file system).
class Directory final {
  friend class FileMgr;
  StringRef dirName; // Name of the directory.
public:
  StringRef GetName() const { return dirName; }
};

/// Implements support for file system lookup, file system caching,
/// and directory search management.
///
/// This also handles more advanced properties, such as uniquing files based
/// on "inode", so that a file with two names (e.g. symlinked) will be treated
/// as a single file.
///
class FileMgr final : public RefCountedBase<FileMgr> {
  IntrusiveRefCntPtr<llvm::vfs::FileSystem> fileSys;
  FileSystemOptions fileSysOpts;

  /// Cache for existing real directories.
  std::map<llvm::sys::fs::UniqueID, Directory> uniqueRealDirs;

  /// Cache for existing real files.
  std::map<llvm::sys::fs::UniqueID, SrcFile> uniqueRealFiles;

  /// The virtual directories that we have allocated.
  ///
  /// For each virtual file (e.g. foo/bar/baz.cpp), we add all of its parent
  /// directories (foo/ and foo/bar/) here.
  SmallVector<std::unique_ptr<Directory>, 4> virtDirs;
  /// The virtual files that we have allocated.
  SmallVector<std::unique_ptr<SrcFile>, 4> virtFiles;

  /// A cache that maps paths to directory entries (either real or
  /// virtual) we have looked up
  ///
  /// The actual Entries for real directories/files are
  /// owned by UniqueRealDirs/UniqueRealFiles above, while the Entries
  /// for virtual directories/files are owned by
  /// VirtDirs/VirtSrcFiles above.
  ///
  llvm::StringMap<Directory*, llvm::BumpPtrAllocator> seenDirs;

  /// A cache that maps paths to file entries (either real or
  /// virtual) we have looked up.
  ///
  /// \see SeenDirEntries
  llvm::StringMap<SrcFile*, llvm::BumpPtrAllocator> seenFiles;

  /// The canonical names of directories.
  llvm::DenseMap<const Directory *, llvm::StringRef> canonicalDirNames;

  /// Storage for canonical names that we have computed.
  llvm::BumpPtrAllocator canonicalNameStorage;

  /// Each SrcFile we create is assigned a unique ID #.
  ///
  unsigned nextFileUID;

  // Statistics.
  unsigned numDirLookups;
	unsigned umFileLookups;
  unsigned numDirCacheMisses;
	unsigned numFileCacheMisses;

  // Caching.
  //std::unique_ptr<FileSysStatCache> StatCache;

  bool GetStatValue(StringRef Path, llvm::vfs::Status &status, bool isFile,
                    std::unique_ptr<llvm::vfs::File> *file);

  /// Add all ancestors of the given path (pointing to either a file
  /// or a directory) as virtual directories.
  void addAncestorsAsVirtualDirs(StringRef path);

  /// Fills the RealPathName in file entry.
  void fillRealPathName(SrcFile *UFE, llvm::StringRef fileName);

public:
  /// Construct a file manager, optionally with a custom VFS.
  ///
  /// \param FS if non-null, the VFS to use.  Otherwise uses
  /// llvm::vfs::getRealFileSystem().
  FileMgr(const FileSystemOptions &fileSysOpts,
              IntrusiveRefCntPtr<llvm::vfs::FileSystem> fileSys = nullptr);
  ~FileMgr();

  /// Installs the provided FileSystemStatCache object within
  /// the FileMgr.
  ///
  /// Ownership of this object is transferred to the FileMgr.
  ///
  /// \param statCache the new stat cache to install. Ownership of this
  /// object is transferred to the FileMgr.
  void setStatCache(std::unique_ptr<FileSystemStatCache> statCache);

  /// Removes the FileSystemStatCache object from the manager.
  void clearStatCache();

  /// Lookup, cache, and verify the specified directory (real or
  /// virtual).
  ///
  /// This returns NULL if the directory doesn't exist.
  ///
  /// \param CacheFailure If true and the file does not exist, we'll cache
  /// the failure to find this file.
  const Directory *GetDir(StringRef dirName, bool cacheFailure = true);

  /// Lookup, cache, and verify the specified file (real or
  /// virtual).
  ///
  /// This returns NULL if the file doesn't exist.
  ///
  /// \param OpenFile if true and the file exists, it will be opened.
  ///
  /// \param CacheFailure If true and the file does not exist, we'll cache
  /// the failure to find this file.
  const SrcFile *GetFile(StringRef filename, bool openFile = false,
                           bool cacheFailure = true);

  /// Returns the current file system options
  FileSystemOptions &GetFileSystemOpts() { return fileSysOpts; }
  const FileSystemOptions &GetFileSystemOpts() const { return fileSysOpts; }

  llvm::vfs::FileSystem &GetVirtualFileSystem() const { return *fileSys; }

  /// Retrieve a file entry for a "virtual" file that acts as
  /// if there were a file with the given name on disk.
  ///
  /// The file itself is not accessed.
  const SrcFile *GetVirtualFile(StringRef filename, off_t fileSize,
                                  time_t modificationTime);

  /// Open the specified file as a MemoryBuffer, returning a new
  /// MemoryBuffer if successful, otherwise returning null.
  llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>>
  GetBufferForFile(const SrcFile *srcFile, bool isVolatile = false,
                   bool ShouldCloseOpenFile = true);

  llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>>
  GetBufferForFile(StringRef filename, bool isVolatile = false);

  /// Get the 'stat' information for the given \p Path.
  ///
  /// If the path is relative, it will be resolved against the WorkingDir of the
  /// FileMgr's FileSystemOptions.
  ///
  /// \returns false on success, true on error.
  bool GetNoncachedStatValue(StringRef Path, llvm::vfs::Status &fesult);

  /// Remove the real file \p Entry from the cache.
  void invalidateCache(const SrcFile *srcFile);

  /// If path is not absolute and FileSystemOptions set the working
  /// directory, the path is modified to be relative to the given
  /// working directory.
  /// \returns true if \c path changed.
  bool FixupRelativePath(SmallVectorImpl<char> &path) const;

  /// Makes \c Path absolute taking into account FileSystemOptions and the
  /// working directory option.
  /// \returns true if \c Path changed to absolute.
  bool makeAbsolutePath(SmallVectorImpl<char> &path) const;

  /// Produce an array mapping from the unique IDs assigned to each
  /// file to the corresponding SrcFile pointer.
  void GetUniqueIDMapping(llvm::SmallVectorImpl<const SrcFile *> &uidToFiles) const;

  /// Modifies the size and modification time of a previously created
  /// SrcFile. Use with caution.
  static void modifySrcFile(SrcFile *srcFile, off_t fileSize, time_t modificationTime);

  /// Retrieve the canonical name for a given directory.
  ///
  /// This is a very expensive operation, despite its results being cached,
  /// and should only be used when the physical layout of the file system is
  /// required, which is (almost) never.
	llvm::StringRef GetCanonicalName(const Directory *directory);

  //void PrintStats() const;
};

} // end namespace stone

#endif
