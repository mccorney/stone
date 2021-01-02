#ifndef STONE_SESSION_MODE_H
#define STONE_SESSION_MODE_H

namespace Stone {

enum class ModeType { None, Parse, Check };
class Mode final {
  friend class Session;
  unsigned mid = 0;
  llvm::StringRef name;

public:
  bool IsValid() const { return mid != 0; }
  unsigned GetID() const { return mid; }
  llvm::StringRef GetName() const { return name; }
  ModeType GetType();

  void SetID(unsigned v) { mid = v; }
  void SetName(llvm::StringRef v) { name = v; }

private:
  Mode(unsigned mid) : mid(mid) {}
};
} // namespace Stone
#endif
