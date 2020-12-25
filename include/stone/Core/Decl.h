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

class Decl;
class BraceStmt;
class DeclCtx;
class ASTCtx;
class DeclContext;

class DeclStats final : public Stats {
  const Decl &declaration;

public:
  DeclStats(const Decl &declaration) : declaration(declaration) {}
  void Print() const override;
};

class alignas(8) Decl {

public:
  enum Kind {
#define DECL(Id, Parent) Id,
#define LAST_DECL(Id) LastDecl = Id,
#define DECL_RANGE(Id, FirstId, LastId)                                        \
  First##Id##Decl = FirstId, Last##Id##Decl = LastId,
#include "stone/Core/DeclKind.def"
  };

  friend DeclStats;
  Decl::Kind kind;
  SrcLoc loc;
  DeclCtx *dc;

protected:
  /// Allocate memory for a deserialized declaration.
  ///
  /// This routine must be used to allocate memory for any declaration that is
  /// deserialized from a module file.
  ///
  /// \param size The size of the allocated object.
  /// \param astCtx The context in which we will allocate memory.
  /// \param declID The global ID of the deserialized declaration.
  /// \param extra The amount of extra space to allocate after the object.
  void *operator new(std::size_t size, const ASTCtx &astCtx, unsigned declID,
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

protected:
  Decl(Decl::Kind kind, DeclCtx *dc, SrcLoc loc)
      : kind(kind), dc(dc), loc(loc) {}
};

class NamingDecl : public Decl {
  /// The name of this declaration, which is typically a normal
  /// identifier but may also be a special kind of name (C++
  /// constructor, etc.)
  DeclName name;

protected:
  NamingDecl(Decl::Kind kind, DeclCtx *dc, SrcLoc loc, DeclName name)
      : Decl(kind, dc, loc), name(name) {}

public:
  /// Get the identifier that names this declaration, if there is one.
  ///
  /// This will return NULL if this declaration has no name (e.g., for
  /// an unnamed class) or if the name is a special name such ast a C++
  /// constructor.
  Identifier *GetIdentifier() const { return name.GetAsIdentifier(); }

  /// Get the name of identifier for this declaration as a StringRef.
  ///
  /// This requires that the declaration have a name and that it be a simple
  /// identifier.
  llvm::StringRef GetName() const {
    // TODO: assert(name.IsIdentifier() && "Name is not a simple identifier");
    return GetIdentifier() ? GetIdentifier()->GetName() : "";
  }
};

class ValueDecl : public NamingDecl {
public:
};

class SpaceDecl : public NamingDecl {
public:
  SpaceDecl(DeclCtx *dc, SrcLoc loc, DeclName name)
      : NamingDecl(Decl::Kind::Space, dc, loc, name) {}
};

class FunctionDecl : public ValueDecl, public DeclCtx {};

class FunDecl : public FunctionDecl {};

class ConstructorInitializer final {
public:
};

class ConstructorDecl : public FunctionDecl {
public:
};

class DestructorDecl : public FunctionDecl {
public:
};

} // namespace stone
#endif
