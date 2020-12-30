#ifndef STONE_SESSION_EXECUTABLEPATH_H
#define STONE_SESSION_EXECUTABLEPATH_H

#include "stone/Core/Context.h"
#include "stone/Session/FileType.h"
#include "stone/Session/Mode.h"
#include "stone/Session/SessionOptions.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include "llvm/ADT/PriorityQueue.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Arg.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Support/Chrono.h"
#include "llvm/Support/VirtualFileSystem.h"

#include "llvm/ADT/Triple.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/Program.h"
#include "llvm/Support/StringSaver.h"
#include "llvm/Support/TargetSelect.h"

namespace stone {
inline std::string GetExecutablePath(const char *arg0) {
  void *mainPath = (void *)(intptr_t)stone::GetExecutablePath;
  return llvm::sys::fs::getMainExecutable(arg0, mainPath);
}
} // namespace stone
#endif
