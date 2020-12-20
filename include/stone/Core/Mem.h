#ifndef STONE_CORE_MEM_H
#define STONE_CORE_MEM_H

#include <memory>

#include "llvm/Support/raw_ostream.h"
#include <stdio.h>

namespace stone {
namespace mem {
///
void Allocate();
///
void DeAllocate();
} // namespace mem
} // namespace stone
#endif
