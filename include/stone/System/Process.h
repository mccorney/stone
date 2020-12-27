#ifndef STONE_SYSTEM_PROCESS_H
#define STONE_SYSTEM_PROCESS_H

namespace stone {
class Task;
class Driver;

class Process final {
  Task &trigger;
  Driver &driver;

public:
  Process(Task &trigger, Driver &driver) : trigger(trigger), driver(driver) {}

public:
  // llvm::SmallVector<Process *, 10> deps;
};
} // namespace stone
#endif
