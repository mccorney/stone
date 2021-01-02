#ifndef STONE_CORE_MEM_H
#define STONE_CORE_MEM_H

#include "llvm/Support/raw_ostream.h"

#include <memory>
#include <stdio.h>

namespace Stone {
namespace mem {
///
void Allocate();
///
void DeAllocate();
} // namespace mem
} // namespace Stone
#endif
