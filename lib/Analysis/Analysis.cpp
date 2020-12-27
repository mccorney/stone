#include "stone/Analysis/Analysis.h"
#include "stone/Core/Mem.h"

using namespace stone;

Analysis::Analysis(const stone::Context &ctx, const SearchPathOptions &pathOpts,
                   SrcMgr &sm)
    : ctx(ctx), pathOpts(pathOpts), sm(sm) {

  ac.reset(new ASTContext(ctx, pathOpts, sm));
}

ModuleDecl *Analysis::GetMainModule() const { 
	assert(mainModule && "Null Main Module."); 
	return mainModule; 
}

void Analysis::SetMainModule(ModuleDecl *moduleDecl) {}
