#include "stone/Compile/Compile.h"
#include "stone/Compile/Analysis.h"
#include "stone/Compile/Backend.h"
#include "stone/Compile/Compiler.h"
#include "stone/Compile/Frontend.h"
#include "stone/Core/Ret.h"
#include "stone/Public.h"

using namespace stone;

int stone::Compile(llvm::ArrayRef<const char *> args, const char *arg0,
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
  // We are not passing the compiler directly, we are pass stone::Context
  auto llvmModule =
      stone::GenIR(compiler.GetAnalysis().GetMainModule(), compiler,
                   compiler.compileOpts.genOpts, /*TODO*/ {});

  bool status =
      stone::GenObject(llvmModule, compiler.compileOpts.genOpts,
                       compiler.GetAnalysis().GetASTContext(), /*TODO*/ {});

  return ret::ok;
}
