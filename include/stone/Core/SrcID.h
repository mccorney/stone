#ifndef STONE_CORE_SRCID_H
#define STONE_CORE_SRCID_H
/// An opaque identifier used by SrcMgr which refers to a
/// source file (MemoryBuffer) along with its \#include path and \#line data.
///
namespace stone{
class SrcMgr; 
class SrcID final {
  /// A mostly-opaque identifier, where 0 is "invalid", >0 is
  /// this module, and <-1 is something loaded from another module.
  int ID = 0;
public:
  bool isValid() const { return ID != 0; }
  bool isInvalid() const { return ID == 0; }

  bool operator==(const SrcID &RHS) const { return ID == RHS.ID; }
  bool operator<(const SrcID &RHS) const { return ID < RHS.ID; }
  bool operator<=(const SrcID &RHS) const { return ID <= RHS.ID; }
  bool operator!=(const SrcID &RHS) const { return !(*this == RHS); }
  bool operator>(const SrcID &RHS) const { return RHS < *this; }
  bool operator>=(const SrcID &RHS) const { return RHS <= *this; }

  static SrcID getSentinel() { return GetSrcID(-1); }
  unsigned getHashValue() const { return static_cast<unsigned>(ID); }

private:
  friend class SrcMgr;
  static SrcID GetSrcID(int ID) {
    SrcID S;
    S.ID = ID;
    return S;
  }
  int getOpaqueValue() const { return ID; }
};
}
#endif 
