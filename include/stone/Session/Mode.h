#ifndef STONE_SESSION_MODE_H
#define STONE_SESSION_MODE_H

namespace stone {

class Mode final {
  friend class Session;
  unsigned mid = 0;
  llvm::StringRef name;

public:
  bool IsValid() const { return mid != 0; }
  unsigned GetID() const { return mid; }
  llvm::StringRef GetName() const { return name; }

  void SetID(unsigned v) { mid = v; }
  void SetName(llvm::StringRef v) { name = v; }

private:
  Mode(unsigned mid) : mid(mid) {}
};
} // namespace stone
#endif