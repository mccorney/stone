#ifndef STONE_SYSTEM_SESSION_H
#define STONE_SYSTEM_SESSION_H

#include "stone/Core/Context.h"
#include "stone/System/SessionOptions.h"

#include "llvm/ADT/ArrayRef.h"

#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include "llvm/ADT/PriorityQueue.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Arg.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Support/Chrono.h"
#include "llvm/Support/VirtualFileSystem.h"

namespace stone {

class Session : public Context {

  SessionOptions &sessionOpts;
  llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> vfs;

protected:
  /// Bit flags for OptTable
  unsigned includedFlagsBitmask = 0;
  unsigned excludedFlagsBitmask = 0;
  unsigned missingArgIndex;
  unsigned missingArgCount;

  /// Default target triple.
  std::string targetTriple;

public:
  llvm::vfs::FileSystem &GetVFS() const { return *vfs; }
  //
  /// When the session was started.
  ///
  /// This should be as close as possible to when the driver was invoked, since
  /// it's used as a lower bound.
  llvm::sys::TimePoint<> startTime;

  /// The time of the last build.
  ///
  /// If unknown, this will be some time in the past.
  llvm::sys::TimePoint<> endTime = llvm::sys::TimePoint<>::min();

public:
  Session(SessionOptions &sessionOpts);
  ~Session();

protected:
  std::unique_ptr<llvm::opt::InputArgList>
  BuildArgList(llvm::ArrayRef<const char *> args);

public:
  ///
  virtual bool Build(llvm::ArrayRef<const char *> args) = 0;
  ///
  virtual int Run() = 0;
  ///
  virtual void PrintCycle() = 0;
  ///
  virtual void PrintHelp() = 0;

  void SetTargetTriple(const llvm::Triple &triple);

  void SetTargetTriple(llvm::StringRef triple);

  llvm::StringRef GetTargetTriple() const { return langOpts.target.str(); }

 const llvm::opt::OptTable &GetOptTable() const {
    return sessionOpts.GetOptTable();
  }

  // virtual llvm::StringRef GetName() = 0;
};

} // namespace stone
#endif
