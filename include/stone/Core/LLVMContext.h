#ifndef STONE_CORE_LLVMCTX_H
#define STONE_CORE_LLVMCTX_H

#include "llvm/IR/LLVMContext.h"

namespace Stone {
llvm::LLVMContext &GetLLVMContext();
} // namespace Stone

#endif
