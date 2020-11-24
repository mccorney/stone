#include "stone/Gen/Backend.h"
#include "stone/Core/Ret.h"
#include "stone/SubSystem.h"
#include "llvm/IR/Module.h"
#include "stone/Gen/GenOptions.h"



using namespace stone;

int Backend::ToNative(ASTContext& AC, llvm::Module* Module,
		const GenOptions& GenOpts, Pipeline *P) {

	return ret::ok;
}
