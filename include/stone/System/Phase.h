#ifndef STONE_SYSTEM_PHASE_H
#define STONE_SYSTEM_PHASE_H

#include "stone/Core/LLVM.h"
#include "llvm/ADT/SmallVector.h"

namespace stone {

enum class PhaseType {
  Compile,
  Backend,
  Assemble,
  Link,
};
class Phase final {
public:
  llvm::SmallVector<Phase *, 10> deps;
};

} // namespace stone
#endif
