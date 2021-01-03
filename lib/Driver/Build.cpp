#include "stone/Core/Ret.h"
#include "stone/Driver/Driver.h"
#include "stone/Driver/ToolChain.h"

using namespace stone;
using namespace stone::driver; 


void Driver::BuildEvents() {
  llvm::PrettyStackTraceString CrashInfo("Building compilation events");

  if (mode.IsCompileOnly()) {
    return BuildCompileEvents(*compilation.get());
  } else {
    return BuildLinkEvent();
  }
}

void Driver::BuildCompileEvent(Compilation &compilation, Event *ie) {

  // if (profile.compileType == CompileType::MultipleInvocation) {
  //   } else if (profile.compileType == CompileType::SingleInvocation) {
  //}
  auto ce =
      compilation.CreateEvent<CompileEvent>(ie, profile.compilerOutputFileType);

  // Since we are here, let us build the jobs.
  BuildJobsForCompileEvent(compilation, ce);
}

void Driver::BuildCompileEvents(Compilation &compilation) {
  // Go through the files and build the compile events

  for (const InputPair &input : profile.inputFiles) {
    // BuildCompileEvent(input);
    file::FileType inputType = input.first;
    const llvm::opt::Arg *inputArg = input.second;
    auto ie = compilation.CreateEvent<InputEvent>(*inputArg, inputType);

    switch (inputType) {
    case file::FileType::Stone: {
      assert(file::IsPartOfCompilation(inputType));
      BuildCompileEvent(compilation, ie);
    }
    default:
      break;
    }
  }
}
void Driver::BuildJobsForCompileEvent(Compilation &compilation, const CompileEvent *ce) {


}

void Driver::BuildLinkEvent() {

  // BuildCompileEvents();
}
