#ifndef STONE_SYSTEM_MODE_H
#define STONE_SYSTEM_MODE_H

namespace stone {

class ModeID final {
  friend class Session;
  friend class Compiler;
  friend class Driver;
  unsigned mid = 0;

public:
  bool IsValid() const { return mid != 0; }
  unsigned GetID() const { return mid; }

private:
  ModeID(unsigned mid) : mid(mid) {}

private:
  void SetID(unsigned v) { mid = v; }
};
} // namespace stone
#endif
