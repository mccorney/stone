#ifndef STONE_CORE_DECL_H
#define STONE_CORE_DECL_H

#include "stone/Core/ASTNode.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/PointerIntPair.h"
#include "llvm/ADT/PointerUnion.h"
#include "llvm/ADT/iterator.h"
#include "llvm/ADT/iterator_range.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/VersionTuple.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>


namespace stone{
class alignas(8) Decl : public ASTNode {
public:
  enum Kind {
  };
public:
  Decl() = delete;
  Decl(const Decl&) = delete;
  Decl(Decl &&) = delete;
  Decl &operator=(const Decl&) = delete;
  Decl &operator=(Decl&&) = delete;

};
}
#endif 
