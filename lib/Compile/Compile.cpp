#include "stone/Compile/Compile.h"
#include "stone/Compile/Analysis.h"
#include "stone/Compile/Compiler.h"
#include "stone/Compile/Gen.h"
#include "stone/Core/Ret.h"
#include "stone/SubSystem.h"

using namespace stone;

int stone::Compile(llvm::ArrayRef<const char *> args, const char *arg0,
                   void *mainAddr, Pipeline *pipeline) {

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
  return stone::Gen(compiler.GetAnalysis().GetMainModule(), compiler,
                    compiler.compileOpts.genOpts, pipeline);

  return ret::ok;
}
