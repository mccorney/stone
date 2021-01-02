#ifndef STONE_SESSION_EXECUTABLEPATH_H
#define STONE_SESSION_EXECUTABLEPATH_H

#include "llvm/Support/FileSystem.h"

namespace Stone {
inline std::string GetExecutablePath(const char *arg0) {
  void *mainPath = (void *)(intptr_t)Stone::GetExecutablePath;
  return llvm::sys::fs::getMainExecutable(arg0, mainPath);
}
} // namespace Stone
#endif
