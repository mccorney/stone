#ifndef STONE_CORE_SRC_FILE_H
#define STONE_CORE_SRC_FILE_H

#include "stone/Core/FileSystem.h"
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
class FileMgr; 
class Directory; 

/// Cached information about one file (either on disk
/// or in the virtual file system).
///
/// If the 'File' member is valid, then this SrcFile has an open file
/// descriptor for the file.
class SrcFile {
  friend class FileMgr;

  llvm::StringRef fileName;             // Name of the file.
  std::string realPathName;   // Real path to the file; could be empty.
  off_t fileSize;                 // File size in bytes.
  time_t modificationTime;             // Modification time of file.
  const Directory *dir;  // Directory file lives in.
  unsigned UID;               // A unique (small) ID for the file.
  llvm::sys::fs::UniqueID uniqueID;
  bool isNamedPipe;
  bool isValid;               // Is this \c SrcFile initialized and valid?

  /// The open file, if it is owned by the \p SrcFile.
  mutable std::unique_ptr<llvm::vfs::File> file;

public:
  SrcFile()
      : uniqueID(0, 0), isNamedPipe(false), isValid(false)
  {}

  SrcFile(const SrcFile &) = delete;
  SrcFile &operator=(const SrcFile &) = delete;

  llvm::StringRef GetName() const { return fileName; }
  llvm::StringRef TryGetRealPathName() const { return realPathName; }
  bool IsValid() const { return isValid; }
  off_t GetSize() const { return fileSize; }
  unsigned GetUID() const { return UID; }
  const llvm::sys::fs::UniqueID &GetUniqueID() const { return uniqueID; }
  time_t GetModificationTime() const { return modificationTime; }

  /// Return the directory the file lives in.
  const Directory *GetDir() const { return dir; }

  bool operator<(const SrcFile &RHS) const { return uniqueID < RHS.uniqueID; }

  /// Check whether the file is a named pipe (and thus can't be opened by
  /// the native FileMgr methods).
  bool IsNamedPipe() const { return isNamedPipe; }

  void CloseFile() const {
    file.reset(); // rely on destructor to close File
  }

  // Only for use in tests to see if deferred opens are happening, rather than
  // relying on RealPathName being empty.
  bool IsOpenForTests() const { return file != nullptr; }
};

}
#endif

