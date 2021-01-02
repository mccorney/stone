#ifndef STONE_DRIVER_PROCESS_H
#define STONE_DRIVER_PROCESS_H

#include "stone/Core/List.h"
#include "stone/Driver/CrashCondition.h"
#include "stone/Driver/Event.h"

#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Arg.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Support/StringSaver.h"

namespace Stone {
namespace Driver {

class Driver;
// class ProcessOutput {
//};

class Process {
  friend class Compilation;

  Driver &driver;
  CompilationEvent &trigger;
  /// The input file list in case we need to emit a file list instead of a
  /// proper response file
  llvm::opt::ArgStringList inputFiles;

public:
  Process(CompilationEvent &trigger, Driver &driver)
      : trigger(trigger), driver(driver) {}
  virtual ~Process();

public:
  CompilationEvent &GetTrigger() { return trigger; }

  virtual void Print(llvm::raw_ostream &os, const char *terminator, bool quote,
                     CrashCondition *crash = nullptr) const;

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

} // namespace Driver
} // namespace Stone
#endif
