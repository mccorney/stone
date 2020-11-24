#include "stone/Core/Ret.h"
#include "stone/Core/ASTContext.h"
#include "stone/SubSystem.h"
#include "stone/Gen/GenOptions.h"
#include "stone/Gen/Gen.h"
#include "stone/Gen/Transformer.h"
#include "stone/Gen/Backend.h"
#include "llvm/IR/Module.h"


using namespace stone; 

int stone::Gen(ASTContext& AC, const GenOptions& GenOpts, Pipeline* P) {

	Transformer T;
	llvm::Module *M = T.ToLLVM(P); 
	
	Backend B;
	B.ToObj(M, P); 

	return ret::ok; 
}

