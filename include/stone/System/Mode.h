#ifndef STONE_SYSTEM_MODE_H
#define STONE_SYSTEM_MODE_H

namespace stone {

/*
enum class ModeID {
  None,
  Parse,
  Check,
  EmitModuleOnly, ///< Emit module only
  MergeModules,   ///< Merge modules only
  EmitIR,
  EmitBC,
  EmitExecutable,
  EmitObject,
  EmitLibrary,
  EmitAssembly,
  PrintVersion, ///< Print version information.
  PrintFeature, ///< Print supported feature of this compiler
};
*/

class ModeID final {
  friend class Session;
  unsigned mid = 0;

public:
  bool IsValid() const { return mid != 0; }
  unsigned GetID() const { return mid; }

private:
  ModeID(unsigned mid) : mid(mid) {}

private:
  void SetID(unsigned v) { mid = v; }
};
} // namespace stone
#endif
