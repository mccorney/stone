#ifndef STONE_SYSTEM_SESSION_H
#define STONE_SYSTEM_SESSION_H

#include "stone/Core/Context.h"
#include "stone/System/FileType.h"
#include "stone/System/Mode.h"
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

  /// The mode id for this session
  SessionOptions &sessionOpts;
  llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> fileSystem;

protected:
  Mode mode;
  /// Bit flags for OptTable
  unsigned includedFlagsBitmask = 0;

  /// This bit flag will ensure the correct mode for the session
  unsigned excludedFlagsBitmask = 0;
  unsigned missingArgIndex;
  unsigned missingArgCount;

  /// Default target triple.
  std::string targetTriple;

  /// An input argument from the command line and its inferred type.
  using InputPair = std::pair<file::FileType, const llvm::opt::Arg *>;

  /// Type used for a list of input arguments.
  using InputFiles = llvm::SmallVector<InputPair, 16>;

  /// The original (untranslated) input argument list.
  // llvm::opt::InputArgList *originalArgs;

  /// The driver translated arguments. Note that toolchains may perform their
  /// own argument translation.
  // llvm::opt::DerivedArgList *translatedArgs;

public:
  void SetFS(llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> fs) {
    fileSystem = fs;
  }
  llvm::vfs::FileSystem &GetFS() const { return *fileSystem; }
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
  virtual void PrintHelp(bool showHidden) = 0;

  void SetTargetTriple(const llvm::Triple &triple);

  void SetTargetTriple(llvm::StringRef triple);

  llvm::StringRef GetTargetTriple() const { return langOpts.target.str(); }

  // virtual llvm::StringRef GetName() = 0;
  //
protected:
  // Compute the mode id -- TODO: virtual
  virtual void ComputeMode(const llvm::opt::DerivedArgList &args);
  /// TranslateInputArgs - Create a new derived argument list from the input
  /// arguments, after applying the standard argument translations.
  virtual llvm::opt::DerivedArgList *
  TranslateInputArgs(const llvm::opt::InputArgList &args) const;

  Mode &GetMode();
};

} // namespace stone
#endif
