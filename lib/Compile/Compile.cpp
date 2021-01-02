#include "stone/Compile/Compile.h"
#include "stone/Compile/Analysis.h"
#include "stone/Compile/Backend.h"
#include "stone/Compile/Compiler.h"
#include "stone/Compile/Frontend.h"
#include "stone/Core/Ret.h"
#include "stone/Public.h"
#include "stone/Session/Options.h"

using namespace Stone;
using namespace Stone::Syntax;
using namespace Stone::Analysis;
using namespace Stone::Backend;

int Stone::Compile(llvm::ArrayRef<const char *> args, const char *arg0,
                   void *mainAddr, CompilePipeline *pipeline) {

  Compiler compiler(pipeline);
  // TODO: cleanup
  if (compiler.Build(args)) {
    compiler.Run();
    compiler.Finish();
    if (compiler.GetDiagEngine().HasError()) {
      return ret::err;
    }
  }
  /*
          switch(compiler.GetMode().GetID()){
                  case opts::Parse:{
                          break;
                  }
                  case opts::Check: {
                          break;
                  }
                  default:
                          break;
          }

  */

  // We are not passing the compiler directly, we are pass Stone::Context
  auto llvmModule = Stone::Analysis::GenIR(
      compiler.GetAnalysisContext().GetMainModule(), compiler,
      compiler.compileOpts.genOpts, /*TODO*/ {});

  bool status = Stone::Backend::GenObject(
      llvmModule, compiler.compileOpts.genOpts,
      compiler.GetAnalysisContext().GetASTContext(), /*TODO*/ {});

  return ret::ok;
}
