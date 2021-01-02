#include "stone/Driver/Process.h"

using namespace Stone;

Process::~Process() {}

void Process::Print(llvm::raw_ostream &os, const char *terminator, bool quote,
                    CrashCondition *crash) const {}

int Process::AsyncExecute(
    llvm::ArrayRef<llvm::Optional<llvm::StringRef>> redirects,
    std::string *errMsg, bool *failed) const {
  return 0;
}

int Process::SyncExecute(
    llvm::ArrayRef<llvm::Optional<llvm::StringRef>> redirects,
    std::string *errMsg, bool *failed) const {

  return 0;
}
