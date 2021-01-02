#ifndef STONE_DRIVER_RUN_H
#define STONE_DRIVER_RUN_H
#include "llvm/ADT/ArrayRef.h"

namespace Stone {
int Run(llvm::ArrayRef<const char *> args, const char *arg0, void *mainAddr);
} // namespace Stone

#endif
