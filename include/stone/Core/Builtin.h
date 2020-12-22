#ifndef STONE_CORE_BUILTIN_H
#define STONE_CORE_BUILTIN_H

namespace stone {

class BuiltinCtx {};
class ASTCtx;

class Builtin final {

  BuiltinCtx builtinCtx;

  enum BuiltinID {
    None,
  };

  Builtin(const Builtin &) = delete;
  void operator=(const Builtin &) = delete;

  void InitType(ASTCtx &astCtx);
  void InitTypes(ASTCtx &astCtx);

  BuiltinID builtinID;

public:
  Builtin() = default;
  ~Builtin();

  void Init(ASTCtx &astCtx);
};

} // namespace stone
#endif
