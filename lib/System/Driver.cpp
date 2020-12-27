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

Driver::Driver(llvm::StringRef stoneExecutable, llvm::StringRef targetTriple,
               llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> vfs)
    : driverOpts(GetLangOptions()), vfs(std::move(vfs)),
      stoneExecutablePath(stoneExecutablePath),
      /*sysRoot(DEFAULT_SYSROOT),*/
      driverTitle("Stone Compiler"), targetTriple(targetTriple),
      strSaver(bumpAlloc), checkInputFilesExist(true) {

  // Provide a sane fallback if no VFS is specified.
  if (!this->vfs)
    this->vfs = llvm::vfs::getRealFileSystem();
}

std::unique_ptr<llvm::opt::InputArgList>
Driver::BuildArgList(llvm::ArrayRef<const char *> args) {

  unsigned includedFlagsBitmask = 0;
  unsigned excludedFlagsBitmask = opts::NoDriverOption;
  unsigned missingArgIndex, missingArgCount;

  std::unique_ptr<llvm::opt::InputArgList> argList =
      llvm::make_unique<llvm::opt::InputArgList>(
          driverOpts.GetOptTable().ParseArgs(
              args, missingArgIndex, missingArgCount, includedFlagsBitmask,
              excludedFlagsBitmask));

  assert(argList && "No input argument list.");

  // Check for missing argument error.
  if (missingArgCount) {
    os << "D(SrcLoc(),"
       << "msg::error_missing_arg_value,"
       << "argList->getArgString(missingArgIndex),"
       << "missingArgCount" << '\n';
    return nullptr;
  }

  // Check for unknown arguments.
  for (const llvm::opt::Arg *arg : argList->filtered(opts::UNKNOWN)) {
    os << "D(SourceLoc(), "
       << "msg::error_unknown_arg,"
       << "arg->getAsString(*ArgList));" << '\n';
  }

  return argList;
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

int Driver::Run() {}
