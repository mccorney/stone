#ifndef STONE_CORE_STATS_H
#define STONE_CORE_STATS_H

namespace stone {

class Stat {
public:
  virtual void Print() const = 0;
};

class StatEngine {};
} // namespace stone

#endif
