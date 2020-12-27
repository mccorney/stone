#include "stone/System/Driver.h"
#include "stone/Core/Ret.h"
#include "stone/System/ToolChain.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallSet.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/Config/llvm-config.h"
#include "llvm/Option/Arg.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Option/OptSpecifier.h"
#include "llvm/Option/OptTable.h"
#include "llvm/Option/Option.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/Program.h"
#include "llvm/Support/StringSaver.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"

using namespace stone;

Driver::Driver(llvm::StringRef stoneExecutable)
    : Session(driverOpts), driverOpts(langOpts),
      stoneExecutablePath(stoneExecutablePath),
      /*sysRoot(DEFAULT_SYSROOT),*/
      driverTitle("Stone Compiler"), strSaver(bumpAlloc),
      checkInputFilesExist(true) {}
/// Parse the given list of strings into an InputArgList.
bool Driver::Build(llvm::ArrayRef<const char *> args) {

  excludedFlagsBitmask = opts::NoDriverOption;
  auto argList = BuildArgList(args);
  return true;
}

std::unique_ptr<ToolChain>
Driver::BuildToolChain(const llvm::opt::InputArgList &argList) {

  if (const llvm::opt::Arg *arg = argList.getLastArg(opts::Target)) {
    targetTriple = llvm::Triple::normalize(arg->getValue());
  }
  llvm::Triple target(targetTriple);

  switch (target.getOS()) {

  case llvm::Triple::Darwin:
  case llvm::Triple::MacOSX: {
    llvm::Optional<llvm::Triple> targetVariant;
    if (const llvm::opt::Arg *A = argList.getLastArg(opts::TargetVariant)) {
      targetVariant = llvm::Triple(llvm::Triple::normalize(A->getValue()));
    }
    return llvm::make_unique<DarwinToolChain>(*this, target, targetVariant);
  }
  case llvm::Triple::Linux:
    return llvm::make_unique<LinuxToolChain>(*this, target);
  case llvm::Triple::FreeBSD:
    return llvm::make_unique<FreeBSDToolChain>(*this, target);
  case llvm::Triple::OpenBSD:
    return llvm::make_unique<OpenBSDToolChain>(*this, target);
  case llvm::Triple::Win32:
    return llvm::make_unique<WinToolChain>(*this, target);
  default:
    os << "D(SourceLoc(),"
       << "msg::error_unknown_target,"
       << "ArgList.getLastArg(options::OPT_target)->getValue());" << '\n';
    break;
  }
}

std::unique_ptr<Compilation>
Driver::BuildCompilation(const ToolChain &toolChain,
                         const llvm::opt::InputArgList &argList) {}

void Driver::PrintCycle() {}

void Driver::PrintHelp() {}

int Driver::Run() {
  // Perform a quick help check
  if (driverOpts.GetAction()->GetKind() == ActionKind::Help) {
    PrintHelp();
  }
}
