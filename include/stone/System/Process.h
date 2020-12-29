#ifndef STONE_SYSTEM_PROCESS_H
#define STONE_SYSTEM_PROCESS_H

#include "stone/Core/List.h"
#include "stone/System/Crash.h"
#include "stone/System/Event.h"

#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Arg.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Support/StringSaver.h"

using namespace stone::driver;

namespace stone {
class Driver;
namespace driver {
// class ProcessOutput {
//};

class Process {
  friend class Compilation;
  Event &trigger;
  Driver &driver;
  /// The input file list in case we need to emit a file list instead of a
  /// proper response file
  llvm::opt::ArgStringList inputFiles;

public:
  Process(Event &trigger, Driver &driver) : trigger(trigger), driver(driver) {}
  virtual ~Process();

public:
  Event &GetTrigger() { return trigger; }

  virtual void Print(llvm::raw_ostream &os, const char *terminator, bool quote,
                     Crash *crash = nullptr) const;

  virtual int
  AsyncExecute(llvm::ArrayRef<llvm::Optional<llvm::StringRef>> redirects,
               std::string *errMsg, bool *failed) const;

  virtual int
  SyncExecute(llvm::ArrayRef<llvm::Optional<llvm::StringRef>> redirects,
              std::string *errMsg, bool *failed) const;

public:
  // llvm::SmallVector<Process *, 10> deps;
  //
  /// Set an input file list, necessary if you specified an RF_FileList response
  /// file support.
  void SetInputFiles(llvm::opt::ArgStringList files) {
    inputFiles = std::move(files);
  }
};

class SyncProcess : public Process {};
class AsyncProcess : public Process {};

class ProcessList final : public List<Process> {
public:
  void Print() const;
};
} // namespace driver
} // namespace stone
#endif
