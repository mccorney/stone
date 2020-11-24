#ifndef STONE_CORE_EXPR_H
#define STONE_CORE_EXPR_H

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
class Expr  {
public:
  enum Kind {
  };
public:
  Expr() = delete;
  Expr(const Expr&) = delete;
  Expr(Expr &&) = delete;
  Expr &operator=(const Expr&) = delete;
  Expr &operator=(Expr&&) = delete;

};
}
#endif 
