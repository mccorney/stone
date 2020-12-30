#include "stone/Compile/Analysis.h"
#include "stone/Core/Mem.h"

using namespace stone;

Analysis::Analysis(const stone::Context &ctx, const CompileOptions &compileOpts,
                   SrcMgr &sm)
    : ctx(ctx), compileOpts(compileOpts), sm(sm) {

  ac.reset(new ASTContext(ctx, compileOpts.spOpts, sm));
}

ModuleDecl *Analysis::GetMainModule() const {
  assert(mainModule && "Null Main Module.");
  return mainModule;
}

void Analysis::SetMainModule(ModuleDecl *moduleDecl) {}
