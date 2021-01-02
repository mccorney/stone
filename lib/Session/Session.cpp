#include "stone/Session/Session.h"
#include "llvm/Support/FileSystem.h"

using namespace Stone;
using namespace llvm::opt;

AbstractSession::AbstractSession(SessionOptions &sessionOpts)
    : sessionOpts(sessionOpts), mode(0),
      targetTriple(llvm::sys::getDefaultTargetTriple()),
      fileSystem(llvm::vfs::getRealFileSystem()) {

  startTime = std::chrono::system_clock::now();
}

AbstractSession::~AbstractSession() {}

std::unique_ptr<llvm::opt::InputArgList>
AbstractSession::BuildArgList(llvm::ArrayRef<const char *> args) {

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
  for (const llvm::opt::Arg *arg : argList->filtered(Options::UNKNOWN)) {
    os << "D(SourceLoc(), "
       << "msg::error_unknown_arg,"
       << "arg->getAsString(*ArgList));" << '\n';
    return nullptr;
  }
  return argList;
}

void AbstractSession::SetTargetTriple(const llvm::Triple &triple) {
  // TODO: langOpts.SetTarget(triple);
}
void AbstractSession::SetTargetTriple(llvm::StringRef triple) {
  SetTargetTriple(llvm::Triple(triple));
}

void AbstractSession::ComputeMode(const llvm::opt::DerivedArgList &args) {

  assert(mode.GetID() == 0 && "mode id already computed");
  const llvm::opt::Arg *const modeArg = args.getLastArg(Options::ModeGroup);

  // TODO: may have to claim
  if (modeArg) {
    switch (modeArg->getOption().getID()) {
    case Options::Parse:
      mode.SetID(Options::Parse);
      break;
    case Options::Check:
      mode.SetID(Options::Check);
      break;
    case Options::EmitIR:
      mode.SetID(Options::EmitIR);
      break;
    case Options::EmitBC:
      mode.SetID(Options::EmitBC);
      break;
    case Options::EmitObject:
      mode.SetID(Options::EmitObject);
      break;
    case Options::EmitAssembly:
      mode.SetID(Options::EmitAssembly);
      break;
    case Options::EmitLibrary:
      mode.SetID(Options::EmitLibrary);
      break;
    default:
      break;
    }
  }
  if (mode.GetID() > 0) {
    mode.SetName(modeArg->getAsString(args));
  }
}
bool AbstractSession::IsModeOutput() {

  switch (mode.GetID()) {
  case Options::EmitIR:
  case Options::EmitBC:
  case Options::EmitObject:
  case Options::EmitAssembly:
  case Options::EmitLibrary:
    return true;
  default:
    return false;
  }
}
llvm::opt::DerivedArgList *
AbstractSession::TranslateInputArgs(const llvm::opt::InputArgList &args) const {

  DerivedArgList *dArgList = new DerivedArgList(args);
  for (Arg *arg : args) {
    dArgList->append(arg);
  }
  return dArgList;
}

Mode &AbstractSession::GetMode() {
  assert(mode.IsValid() && "did not find a mid");
  return mode;
}

void AbstractSession::Purge() {}

void AbstractSession::Finish() {
  Purge();
  PrintDiagnostics();
  PrintStatistics();
}
void AbstractSession::PrintDiagnostics() {}
void AbstractSession::PrintStatistics() {}

// TODO:
ModeType Mode::GetType() {
  /*
          switch (mode.GetID()) {
    case Options::EmitIR:
                  return MdodeType::EmitIR;
    case Options::EmitBC:
                  return ModeType:EmitBC;
    case Options::EmitObject:
                  return ModeType::EmitObject;
    case Options::EmitAssembly:
                  return ModeType::EmitAssembly;
    case Options::EmitLibrary:
                  return ModeType::EmitLibrary;
    default:
      return ModeType::None;
    }
          */
  return ModeType::None;
}
