#ifndef STONE_CORE_MODULE_H
#define STONE_CORE_MODULE_H

#include "stone/Core/Decl.h"

#include "llvm/ADT/SmallVector.h"

namespace stone {
namespace syntax {

class ModuleUnit {
public:
  enum class Kind { Source, Builtin };

public:
};

class SourceUnit final : public ModuleUnit {
public:
  enum class Kind { Stone };
public:
};

class BuiltinUnit final : public ModuleUnit {
public:
};

class Module final : public DeclContext, public TypeDecl {
public:
  llvm::SmallVector<ModuleUnit *, 2> units;

public:
  llvm::ArrayRef<ModuleUnit *> GetUnits() {
    assert(!units.empty());
    return units;
  }
  llvm::ArrayRef<const ModuleUnit *> GetUnits() const {
    return {units.begin(), units.size()};
  }
  void AddUnit(ModuleUnit &unit);
};
} // namespace syntax
} // namespace stone

#endif
