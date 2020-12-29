#ifndef STONE_SYSTEM_MODE_H
#define STONE_SYSTEM_MODE_H

namespace stone {

class Mode final {
  friend class Session;
  friend class Compiler;
  friend class Driver;
  unsigned mid = 0;
  llvm::StringRef name;

public:
  bool IsValid() const { return mid != 0; }
  unsigned GetID() const { return mid; }
  llvm::StringRef GetName() const { return name; }

private:
  Mode(unsigned mid) : mid(mid) {}

private:
  void SetID(unsigned v) { mid = v; }
  void SetName(llvm::StringRef v) { name = v; }
};
} // namespace stone
#endif
