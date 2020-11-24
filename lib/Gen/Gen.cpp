#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"
#include "stone/Core/Ret.h"
#include "stone/SubSystem.h"
#include "stone/Gen/GenOptions.h"
#include "stone/Gen/Gen.h"
#include "stone/Gen/Transformer.h"
#include "stone/Gen/Backend.h"
#include "llvm/IR/Module.h"

using namespace stone; 

int stone::Gen(stone::Module& M , const GenOptions& GenOpts, Pipeline* P) {

	Transformer T;
	llvm::Module *LM = T.ToIR(M, P); 
	
	Backend B;
	//B.ToNative(M.GetASTContext(), M, P); 

	return ret::ok; 
}

