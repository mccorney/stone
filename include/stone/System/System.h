#ifndef STONE_SYSTEM_SYSTEM_H
#define STONE_SYSTEM_SYSTEM_H

#include "stone/System/Action.h"
#include "stone/System/SystemOptions.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/PriorityQueue.h"

namespace stone {
class Process;

class System final {
public:
  SystemOptions systemOpts;
  llvm::PriorityQueue<Process *> queue;

private:
  void BuildTasks();
  void BuildProcs();
  void BuildQueue();

private:
  void BuildOpts(llvm::ArrayRef<const char *> Args);

public:
  System();
  void Init(llvm::ArrayRef<const char *> args);

public:
  int Run();
};

} // namespace stone
#endif
