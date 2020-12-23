#ifndef STONE_CORE_DECLNAME_H
#define STONE_CORE_DECLNAME_H
#include "stone/Core/Identifier.h"
namespace stone {

class DeclName {
public:
  // TODO:
  bool IsIdentifier() const { return false; }
  // TODO:
  Identifier *GetAsIdentifier() const {}
};

} // namespace stone
#endif
