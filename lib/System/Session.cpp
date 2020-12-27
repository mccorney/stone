#include "stone/System/Session.h"
#include "llvm/Support/FileSystem.h"

using namespace stone;

Session::Session(SessionOptions &sessionOpts)
    : sessionOpts(sessionOpts), fileSystem(llvm::vfs::getRealFileSystem()) {}

Session::~Session() {}

std::unique_ptr<llvm::opt::InputArgList>
Session::BuildArgList(llvm::ArrayRef<const char *> args) {

  std::unique_ptr<llvm::opt::InputArgList> argList =
      llvm::make_unique<llvm::opt::InputArgList>(
          sessionOpts.GetOptTable().ParseArgs(
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
