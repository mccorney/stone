#ifndef STONE_SYSTEM_PROCESSQUEUE_H
#define STONE_SYSTEM_PROCESSQUEUE_H

#include "stone/System/Process.h"

#include "llvm/ADT/PriorityQueue.h"

namespace stone {
namespace driver {
class Process;
class ProcessQueue final {
  llvm::PriorityQueue<Process *> queue;

public:
  ProcessQueue();
  ~ProcessQueue();
};
} // namespace driver
} // namespace stone
#endif
