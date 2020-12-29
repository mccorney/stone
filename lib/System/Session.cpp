#include "stone/System/Session.h"
#include "llvm/Support/FileSystem.h"

using namespace stone;
using namespace llvm::opt;

Session::Session(SessionOptions &sessionOpts)
    : sessionOpts(sessionOpts), mode(0),
      targetTriple(llvm::sys::getDefaultTargetTriple()),
      fileSystem(llvm::vfs::getRealFileSystem()) {

  startTime = std::chrono::system_clock::now();
}

Session::~Session() {}

std::unique_ptr<llvm::opt::InputArgList>
Session::BuildArgList(llvm::ArrayRef<const char *> args) {

  std::unique_ptr<llvm::opt::InputArgList> argList =
      llvm::make_unique<llvm::opt::InputArgList>(
          sessionOpts.GetOpts().ParseArgs(args, missingArgIndex,
                                          missingArgCount, includedFlagsBitmask,
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
    return nullptr;
  }
  return argList;
}

void Session::SetTargetTriple(const llvm::Triple &triple) {
  // TODO: langOpts.SetTarget(triple);
}
void Session::SetTargetTriple(llvm::StringRef triple) {
  SetTargetTriple(llvm::Triple(triple));
}

void Session::ComputeMode(const llvm::opt::DerivedArgList &args) {

  assert(mode.GetID() > 0 && "mode id already computed");
  const llvm::opt::Arg *const modeArg = args.getLastArg(opts::ModeGroup);

  switch (modeArg->getOption().getID()) {
  case opts::Parse:
    mode.SetID(opts::Parse);
    break;
  case opts::Check:
    mode.SetID(opts::Check);
    break;
  case opts::EmitIR:
    mode.SetID(opts::EmitIR);
    break;
  case opts::EmitBC:
    mode.SetID(opts::EmitBC);
    break;
  case opts::EmitObject:
    mode.SetID(opts::EmitObject);
    break;
  case opts::EmitAssembly:
    mode.SetID(opts::EmitAssembly);
    break;
  default:
    break;
  }
  if (mode.GetID() > 0) {
    mode.SetName(modeArg->getAsString(args));
  }
}
llvm::opt::DerivedArgList *
Session::TranslateInputArgs(const llvm::opt::InputArgList &args) const {

  DerivedArgList *dArgList = new DerivedArgList(args);
  for (Arg *arg : args) {
    dArgList->append(arg);
  }
  return dArgList;
}

Mode &Session::GetMode() {
  assert(mode.IsValid() && "did not find a mid");
  return mode;
}
