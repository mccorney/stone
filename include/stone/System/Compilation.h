#ifndef STONE_SYSTEM_COMPILATION_H
#define STONE_SYSTEM_COMPILATION_H


#include "stone/Core/LLVM.h"
#include "stone/System/Action.h"
#include "stone/System/Process.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Option.h"


#include <cassert>
#include <iterator>
#include <map>
#include <memory>
#include <utility>
#include <vector>

namespace llvm {
namespace opt {
class DerivedArgList;
class InputArgList;
} // namespace opt
} // namespace llvm
namespace stone {
class System;
class ToolChain; 

class Compilation final {

	/// The System we were created by.
  const System &system;

  /// The default tool chain.
  const ToolChain &toolChain;

  /// The original (untranslated) input argument list.
  llvm::opt::InputArgList *args;

  /// The driver translated arguments. Note that toolchains may perform their
  /// own argument translation.
  llvm::opt::DerivedArgList *translatedArgs;

public:
	int Execute();
};
} // namespace stone
#endif
