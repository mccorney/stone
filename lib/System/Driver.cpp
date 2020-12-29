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
  auto toolChain = BuildToolChain(*clOptions);

  compilation = BuildCompilation(*toolChain, *clOptions);

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

/// Check that the file referenced by \p Input exists. If it doesn't,
/// issue a diagnostic and return false.
static bool DoesInputExist(Driver &driver, const DerivedArgList &args,
                           DiagnosticEngine &de, llvm::StringRef input) {

  // TODO:
  // if (!driver.GetCheckInputFilesExist())
  //  return true;

  // stdin always exists.
  if (input == "-")
    return true;

  if (file::Exists(input))
    return true;

  driver.Out() << "de.D(SourceLoc(),"
               << "diag::error_no_such_file_or_directory, Input);" << '\n';

  return false;
}
// TODO: May move to session
void Driver::BuildInputs(const ToolChain &tc, const DerivedArgList &args,
                         InputFiles &inputs) {

  llvm::DenseMap<llvm::StringRef, llvm::StringRef> seenSourceFiles;

  for (Arg *arg : args) {

    if (arg->getOption().getKind() == Option::InputClass) {
      llvm::StringRef argValue = arg->getValue();
      file::FileType ft = file::FileType::INVALID;
      // stdin must be handled specially.
      if (argValue.equals("-")) {
        // By default, treat stdin as Swift input.
        ft = file::FileType::Stone;
      } else {
        // Otherwise lookup by extension.
        ft = file::GetTypeByExt(llvm::sys::path::extension(argValue));

        if (ft == file::FileType::INVALID) {
          // By default, treat inputs with no extension, or with an
          // extension that isn't recognized, as object files.
          ft = file::FileType::Object;
        }
      }

      if (DoesInputExist(*this, args, de, argValue)) {
        inputs.push_back(std::make_pair(ft, arg));
      }

      if (ft == file::FileType::Stone) {
        auto basename = llvm::sys::path::filename(argValue);
        if (!seenSourceFiles.insert({basename, argValue}).second) {
          Out() << "de.D(SourceLoc(),"
                << "diag::error_two_files_same_name,"
                << "basename, seenSourceFiles[basename], argValue);" << '\n';
          Out() << " de.D(SourceLoc(), "
                << "diag::note_explain_two_files_"
                   "same_name);"
                << '\n';
        }
      }
    }
  }
}

static void BuildStep(Driver &driver) {}
void Driver::BuildSteps() {}

static void BuildProc(Driver &driver) {}
void Driver::BuildProcs() {}

std::unique_ptr<Compilation>
Driver::BuildCompilation(const ToolChain &tc,
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
  if (!HandleImmediateArgs(*dArgList, tc)) {
    return nullptr;
  }

  // Construct the list of inputs.
  InputFiles inputs;
  BuildInputs(tc, *dArgList, inputs);

  if (de.HasError())
    return nullptr;

  ComputeMID(*dArgList);

  // TODO: ComputeCompileMod()
  //
  // About to move argument list, so capture some flags that will be needed
  // later.
  // const bool DriverPrintActions =
  //    ArgList->hasArg(options::OPT_driver_print_actions);

  // const bool DriverPrintDerivedOutputFileMap =
  //    ArgList->hasArg(options::OPT_driver_print_derived_output_file_map);

  // const bool ContinueBuildingAfterErrors =
  //    computeContinueBuildingAfterErrors(BatchMode, ArgList.get());

  driverOpts.showCycle = argList.hasArg(opts::ShowCycle);

  std::unique_ptr<Compilation> compilation(new Compilation(*this, tc));
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
