#ifndef STONE_CORE_DECL_H
#define STONE_CORE_DECL_H

#include "stone/Core/ASTNode.h"
#include "stone/Core/DeclCtx.h"
#include "stone/Core/DeclName.h"
#include "stone/Core/Identifier.h"
#include "stone/Core/LLVM.h"
#include "stone/Core/SrcLoc.h"

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

namespace stone {
class BraceStmt;
class DeclCtx;
class ASTCtx;

enum class DeclKind { Fun };

class alignas(8) Decl : public ASTNode {

protected:
  /// Allocate memory for a deserialized declaration.
  ///
  /// This routine must be used to allocate memory for any declaration that is
  /// deserialized from a module file.
  ///
  /// \param Size The size of the allocated object.
  /// \param Ctx The context in which we will allocate memory.
  /// \param ID The global ID of the deserialized declaration.
  /// \param Extra The amount of extra space to allocate after the object.
  void *operator new(std::size_t size, const ASTCtx &astCtx, unsigned ID,
                     std::size_t extra = 0);

  /// Allocate memory for a non-deserialized declaration.
  void *operator new(std::size_t size, const ASTCtx &astCtx,
                     DeclCtx *parentDeclCtx, std::size_t extra = 0);

public:
  Decl() = delete;
  Decl(const Decl &) = delete;
  Decl(Decl &&) = delete;
  Decl &operator=(const Decl &) = delete;
  Decl &operator=(Decl &&) = delete;

  friend class DeclContext;

  struct MultipleDeclCtx {
    DeclCtx *semanticDeclCtx;
    DeclCtx *lexicalDeclCtx;
  };

  llvm::PointerUnion<DeclCtx *, MultipleDeclCtx *> declCtx;
};

class NamedDecl : public Decl {
  /// The name of this declaration, which is typically a normal
  /// identifier but may also be a special kind of name (C++
  /// constructor, etc.)
  // DeclName name;
  /// Get the identifier that names this declaration, if there is one.
  ///
  /// This will return NULL if this declaration has no name (e.g., for
  /// an unnamed class) or if the name is a special name (C++ constructor,
  /// Objective-C selector, etc.).
  // Identifier *GetIdentifier() const { return name.GetAsIdentifier(); }
};

/*
class ValueDecl : public NamedDecl {
};

class VarDecl : public ValueDecl {};

class ParamDecl : public VarDecl {};

class AbstractFunctionDecl : public ValueDecl, public DeclContext {
protected:
  // If a function has a body at all, we have either a parsed body AST node or
  // we have saved the end location of the unparsed body.
  union {
    BraceStmt *body;
  };

public:
  void SetParams(ASTContext &ac, llvm::ArrayRef<ParamDecl *> params);
  BraceStmt *GetBody(bool canSynthesize = true) const;
  /// Set a new body for the function.
  void SetBody(BraceStmt *stmt BodyKind NewBodyKind);
};
class FunDecl final : public AbstractFunctionDecl {
public:
  static FunDecl *Create(ASTContext &ac, DeclContext *dc, SrcLoc startLoc);
};

*/

} // namespace stone
#endif
