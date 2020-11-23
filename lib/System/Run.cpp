#include "stone/System/System.h"
#include "stone/System/Compile.h"
#include "stone/System/Run.h"
#include "stone/System/Help.h"
#include "stone/Core/LLVM.h"
#include "stone/Core/Ret.h"

#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Option/OptTable.h"
#include "llvm/Option/Option.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/Program.h"
#include "llvm/Support/Regex.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/StringSaver.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/raw_ostream.h"

#include <memory>
#include <set>
#include <system_error>

using namespace stone;
using namespace llvm::opt;

std::string GetExecutablePath(const char *Arg0) {
  void *Path = (void *)(intptr_t)GetExecutablePath;
  return llvm::sys::fs::getMainExecutable(Arg0, Path);
}

namespace stone {
int Run(llvm::ArrayRef<const char*> Args) {	
	if(Args.size()  == 0) {
		return ret::err; 
	}
	if(Args.size()  == 1) {
		return stone::Help(HelpMode::System);
	}
	if (llvm::sys::Process::FixupStandardFileDescriptors())
    return  ret::err;

  llvm::InitializeAllTargets();
  //auto TargetAndMode = ToolChain::GetTargetAndModeFromProgramName(argv[0]);
	// -compile ?
  auto Arg0 = Args[1]; 
	if(Arg0 == "-compile") {
		//return stone::Compile(llvm::makeArrayRef(Args.data() +2,
                                                //Args.data() + Args.size()), Arg0) 
	}	

	//System S;
	//S.Init(Args); 
	//return S.Run();
	return ret::ok;	
}

}
int stone::Run(const int argc, const char** args) {

	//llvm::InitLLVM LLVM(argc, args);

	llvm::SmallVector<const char *, 256> InitialArgs(args, args + argc);
	llvm::BumpPtrAllocator A;
  llvm::StringSaver Saver(A);

	llvm::cl::ExpandResponseFiles(
      Saver,
      llvm::Triple(llvm::sys::getProcessTriple()).isOSWindows()
          ? llvm::cl::TokenizeWindowsCommandLine
          : llvm::cl::TokenizeGNUCommandLine, InitialArgs);

	llvm::ArrayRef<const char *> Args(InitialArgs);

	return stone::Run(Args); 
}





