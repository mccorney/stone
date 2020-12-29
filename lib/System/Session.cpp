#include "stone/System/Session.h"
#include "llvm/Support/FileSystem.h"

using namespace stone;

Session::Session(SessionOptions &sessionOpts)
    : sessionOpts(sessionOpts), mid(0),
      targetTriple(llvm::sys::getDefaultTargetTriple()),
      fileSystem(llvm::vfs::getRealFileSystem()) {}

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

void Session::ComputeMID(const llvm::opt::DerivedArgList &args) {

  assert(mid.GetID() > 0 && "mode id already computed");
  const llvm::opt::Arg *const midArg = args.getLastArg(opts::ModeGroup);

  switch (midArg->getOption().getID()) {
  case opts::Parse:
    mid.SetID(opts::Parse);
    break;
  case opts::Check:
    mid.SetID(opts::Check);
    break;
  case opts::EmitIR:
    mid.SetID(opts::EmitIR);
    break;
  case opts::EmitBC:
    mid.SetID(opts::EmitBC);
		break;
  case opts::EmitExecutable:
    mid.SetID(opts::EmitExecutable);
    break;
  case opts::EmitObject:
    mid.SetID(opts::EmitObject);
    break;
  case opts::EmitAssembly:
    mid.SetID(opts::EmitAssembly);
		break;
  default:
    mid.SetID(opts::EmitExecutable);
  }
}

ModeID &Session::GetMID() {
  assert(mid.IsValid() && "did not find a mid");
  return mid;
}
