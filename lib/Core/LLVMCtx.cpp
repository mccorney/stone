#include "stone/Core/LLVMCtx.h"
#include "llvm/Support/ManagedStatic.h"

static llvm::ManagedStatic<llvm::LLVMContext> llvmCtx;

llvm::LLVMContext &stone::GetLLVMCtx() { return *llvmCtx; }
