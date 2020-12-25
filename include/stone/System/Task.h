#ifndef STONE_SYSTEM_TASK_H
#define STONE_SYSTEM_TASK_H

#include "llvm/ADT/SmallVector.h"

namespace stone {

class Task {
  llvm::SmallVector<Task *, 10> deps;
};

} // namespace stone
#endif
