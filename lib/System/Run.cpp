#include "stone/System/Run.h"
#include "stone/Core/Fmt.h"
#include "stone/Core/LLVM.h"
#include "stone/Core/Ret.h"
#include "stone/System/Compilation.h"
#include "stone/System/Compile.h"
#include "stone/System/Driver.h"
#include "stone/System/Help.h"
#include "stone/System/ToolChain.h"

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

std::string GetExecutablePath(const char *arg0) {
  void *mainPath = (void *)(intptr_t)GetExecutablePath;
  return llvm::sys::fs::getMainExecutable(arg0, mainPath);
}

namespace stone {

void SetInstallDir(llvm::ArrayRef<const char *> &argv, Driver &driver,
                   bool canonicalPrefixes) {
  // Attempt to find the original path used to invoke the driver, to determine
  // the installed path. We do this manually, because we want to support that
  // path being a symlink.
  llvm::SmallString<128> InstalledPath(argv[0]);

  // Do a PATH lookup, if there are no directory components.
  if (llvm::sys::path::filename(InstalledPath) == InstalledPath) {
    if (llvm::ErrorOr<std::string> Tmp = llvm::sys::findProgramByName(
            llvm::sys::path::filename(InstalledPath.str()))) {
      InstalledPath = *Tmp;
    }
  }

  // FIXME: We don't actually canonicalize this, we just make it absolute.
  if (canonicalPrefixes) {
    llvm::sys::fs::make_absolute(InstalledPath);
  }

  llvm::StringRef InstalledPathParent(
      llvm::sys::path::parent_path(InstalledPath));
  if (llvm::sys::fs::exists(InstalledPathParent)) {
    driver.SetInstalledDir(InstalledPathParent);
  }
}

int Run(llvm::ArrayRef<const char *> args) {

  if (args.size() == 0) {
    return ret::err;
  }

  if (args.size() == 1) {
    return stone::Help(HelpMode::Driver);
  }

  if (llvm::sys::Process::FixupStandardFileDescriptors())
    return ret::err;

  llvm::InitializeAllTargets();

  std::string executablePath = GetExecutablePath(args[0]);

  // auto TargetAndMode = ToolChain::GetTargetAndModeFromProgramName(argv[0]);
  // -compile ?
  auto arg0 = args[1];
  if (arg0 == "-compile") {
    // return stone::Compile(llvm::makeArrayRef(Args.data() +2,
    // Args.data() + Args.size()), Arg0)
  }

  bool canonicalPrefixes = false;

  Driver driver(executablePath, llvm::sys::getDefaultTargetTriple());
  stone::SetInstallDir(args, driver, canonicalPrefixes);

  // TODO: driver.SetTargetAndMode(TargetAndMode);
  if (driver.Build(args)) {

    return driver.Run();
  }
  // auto toolChain = driver.BuildToolChain(*argList.get());

  // auto compilation = driver.BuildCompilation(*toolChain.get(),
  // *argList.get());
  //
  return 0;
}

} // namespace stone
int stone::Run(int argc, const char **args) {

  llvm::InitLLVM initLLVM(argc, args);

  llvm::SmallVector<const char *, 256> argsToExpand(args, args + argc);
  llvm::BumpPtrAllocator ptrAlloc;
  llvm::StringSaver strSaver(ptrAlloc);

  llvm::cl::ExpandResponseFiles(
      strSaver,
      llvm::Triple(llvm::sys::getProcessTriple()).isOSWindows()
          ? llvm::cl::TokenizeWindowsCommandLine
          : llvm::cl::TokenizeGNUCommandLine,
      argsToExpand);

  llvm::ArrayRef<const char *> argsToProcess(argsToExpand);

  return stone::Run(argsToProcess);
}
