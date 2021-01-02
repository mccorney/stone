#include "stone/Core/LLVMContext.h"
#include "llvm/Support/ManagedStatic.h"

static llvm::ManagedStatic<llvm::LLVMContext> llvmCtx;

llvm::LLVMContext &Stone::GetLLVMContext() { return *llvmCtx; }
