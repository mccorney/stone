#ifndef STONE_CORE_STATS_H
#define STONE_CORE_STATS_H

#include "stone/Core/Mem.h"
#include <iostream>

namespace Stone {

class Stats {
protected:
  llvm::raw_ostream &os;

public:
  Stats() : os(llvm::outs()) {}
  virtual ~Stats() {}

public:
  virtual void Print() const = 0;
};

class StatEngine {
public:
  StatEngine();
  /// Owns the Stats
  void AddStats(std::unique_ptr<Stats> stats);
  ///
  void Print();
};
} // namespace Stone

#endif
