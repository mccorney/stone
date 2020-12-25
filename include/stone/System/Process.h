#ifndef STONE_SYSTEM_PROCESS_H
#define STONE_SYSTEM_PROCESS_H

#include "stone/System/Phase.h"

namespace stone {
class Task;
class System;

class Process final {
  Task &trigger;
  System &system;

public:
  Process(Task &trigger, System &system) : trigger(trigger), system(system) {}

public:
  // llvm::SmallVector<Process *, 10> deps;
};
} // namespace stone
#endif
