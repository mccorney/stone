#ifndef STONE_CORE_DECLNAME_H
#define STONE_CORE_DECLNAME_H
#include "stone/Core/Identifier.h"
namespace Stone {
namespace Syntax {

class DeclNameLoc {};
class DeclName {
public:
  // TODO:
  bool IsIdentifier() const { return false; }
  // TODO:
  Identifier *GetAsIdentifier() const {}
};
} // namespace Syntax
} // namespace Stone
#endif
