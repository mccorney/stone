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
using namespace llvm::opt;

Driver::Driver(llvm::StringRef stoneExecutable, std::string driverName)
    : Session(driverOpts), driverOpts(langOpts),
      stoneExecutablePath(stoneExecutablePath), driverName(driverName),
      /*sysRoot(DEFAULT_SYSROOT),*/
      driverTitle("Stone Compiler"), strSaver(bumpAlloc),
      checkInputFilesExist(true) {}
/// Parse the given list of strings into an InputArgList.
bool Driver::Build(llvm::ArrayRef<const char *> args) {

  excludedFlagsBitmask = opts::NoDriverOption;
  auto clOptions = BuildArgList(args);
  //auto toolChain = BuildToolChain(*clOptions);

  // auto compilation = BuildCompilation(*toolChain, *clOptions);

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

llvm::opt::DerivedArgList *
Driver::TranslateInputArgs(const llvm::opt::InputArgList &args) const {

  DerivedArgList *dArgList = new DerivedArgList(args);

  for (Arg *arg : args) {
    dArgList->append(arg);
  }
  return dArgList;
}

bool Driver::HandleImmediateArgs(const ArgList &args, const ToolChain &tc) {

  if (args.hasArg(opts::Help)) {
    PrintHelp(false);
    return false;
  }
  return true;
}
std::unique_ptr<Compilation>
Driver::BuildCompilation(const ToolChain &toolChain,
                         const llvm::opt::InputArgList &argList) {

  llvm::PrettyStackTraceString CrashInfo("Compilation construction");

  startTime = std::chrono::system_clock::now();

  // TODO:
  // workingDirectory = ComputeWorkingDirectory(argList.get());

  std::unique_ptr<DerivedArgList> dArgList(TranslateInputArgs(argList));

  // Perform toolchain specific args validation.
  // toolChain.ValidateArguments(de, *dArgList, targetTriple);
  //
  if (de.HasError()) {
    return nullptr;
  }
  if (!HandleImmediateArgs(*dArgList, toolChain)) {
    return nullptr;
  }
}

void Driver::PrintCycle() {}

void Driver::PrintHelp(bool showHidden) {
  excludedFlagsBitmask = opts::NoDriverOption;
  // if (!showHidden)
  //  excludedFlagsBitmask |= HelpHidden;

  driverOpts.GetOpts().PrintHelp(Out(), driverName.c_str(), "Stone Compiler",
                                 includedFlagsBitmask, excludedFlagsBitmask,
                                 /*ShowAllAliases*/ false);
}
int Driver::Run() {
  // Perform a quick help check
  if (driverOpts.showHelp) {
    // PrintHelp();
  }
  return 0;
}
