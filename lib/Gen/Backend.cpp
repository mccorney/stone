#include "stone/Gen/Backend.h"
#include "stone/Core/Ret.h"
#include "stone/SubSystem.h"
#include "llvm/IR/Module.h"


using namespace stone;

int Backend::ToObj(llvm::Module* Module, Pipeline *P) {
	return ret::ok;
}
