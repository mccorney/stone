#ifndef STONE_SYSTEM_PROCESS_H
#define STONE_SYSTEM_PROCESS_H

namespace stone {
class Step;
class Driver;

class Process final {
  Step &trigger;
  Driver &driver;

public:
  Process(Step &trigger, Driver &driver) : trigger(trigger), driver(driver) {}

public:
  void AsyncRun();
  void SyncRun();
  Step &GetStep() { return trigger; }

public:
  // llvm::SmallVector<Process *, 10> deps;
};
} // namespace stone
#endif
