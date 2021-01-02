#ifndef STONE_DRIVER_PROCESSQUEUE_H
#define STONE_DRIVER_PROCESSQUEUE_H

#include "stone/Driver/Process.h"

#include "llvm/ADT/PriorityQueue.h"

namespace Stone {
namespace Driver {
class Process;
class ProcessQueue final {
  llvm::PriorityQueue<Process *> queue;

public:
  ProcessQueue();
  ~ProcessQueue();
};
} // namespace Driver
} // namespace Stone
#endif
