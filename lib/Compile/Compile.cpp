#include "stone/Compile/Compile.h"
#include "stone/Compile/Analysis.h"
#include "stone/Compile/Backend.h"
#include "stone/Compile/Compiler.h"
#include "stone/Compile/Frontend.h"
#include "stone/Core/Defer.h"
#include "stone/Core/Ret.h"

#include "stone/Public.h"
#include "stone/Session/Options.h"

using namespace stone;
using namespace stone::syntax;
using namespace stone::analysis;
using namespace stone::backend;

int stone::Compile(llvm::ArrayRef<const char *> args, const char *arg0,
                   void *mainAddr, CompilePipeline *pipeline) {

  Compiler compiler(pipeline);
  if (compiler.Build(args)) {
    compiler.Run();
    compiler.Finish();
    if (compiler.GetDiagEngine().HasError()) {
      return ret::err;
    }
  }

  // We are not passing the compiler directly, we are pass stone::Context
  auto llvmModule = stone::analysis::GenIR(
      compiler.GetAnalysisContext().GetMainModule(), compiler,
      compiler.compileOpts.genOpts, /*TODO*/ {});

  bool status = stone::backend::GenObject(
      llvmModule, compiler.compileOpts.genOpts,
      compiler.GetAnalysisContext().GetASTContext(), /*TODO*/ {});

  STONE_DEFER{};

  return ret::ok;
}
