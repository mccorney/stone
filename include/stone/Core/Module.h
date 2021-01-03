#ifndef STONE_CORE_MODULE_H
#define STONE_CORE_MODULE_H

#include "stone/Core/Decl.h"

namespace stone {
namespace syntax {

class ModuleUnit {
public:
  enum class Kind { Source, Builtin };
};

class SourceUnit final : public ModuleUnit {
public:
};

class BuiltinUnit final : public ModuleUnit {
public:
};

class Module final : public DeclContext, public TypeDecl {
public:
};
} // namespace syntax
} // namespace stone

#endif
