#include "stone/Compile/Analysis.h"
#include "stone/Core/Mem.h"

using namespace Stone;
using namespace Stone::Syntax;
using namespace Stone::Analysis;

AnalysisContext::AnalysisContext(const Context &ctx,
                                 const CompileOptions &compileOpts, SrcMgr &sm)
    : ctx(ctx), compileOpts(compileOpts), sm(sm) {

  ac.reset(new ASTContext(ctx, compileOpts.spOpts, sm));
}

ModuleDecl *AnalysisContext::GetMainModule() const {
  assert(mainModule && "Null Main Module.");
  return mainModule;
}

void AnalysisContext::SetMainModule(ModuleDecl *moduleDecl) {}
