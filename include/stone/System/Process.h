#ifndef STONE_SYSTEM_PROCESS_H
#define STONE_SYSTEM_PROCESS_H

#include "stone/System/Phase.h"
#include "stone/System/System.h"

namespace stone {
class Process final {
  Phase &trigger;
  System &system;

public:
  Process(Phase &trigger, System &system) : trigger(trigger), system(system) {}

public:
  // llvm::SmallVector<Process *, 10> deps;
};
} // namespace stone
#endif
