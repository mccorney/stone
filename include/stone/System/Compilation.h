#ifndef STONE_SYSTEM_COMPILATION_H
#define STONE_SYSTEM_COMPILATION_H

#include "stone/Core/LLVM.h"
#include "stone/System/Action.h"
#include "stone/System/ProcessQueue.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Option.h"

#include <cassert>
#include <iterator>
#include <map>
#include <memory>
#include <utility>
#include <vector>

namespace llvm {
namespace opt {
class DerivedArgList;
class InputArgList;
} // namespace opt
} // namespace llvm
namespace stone {
class Driver;
class ToolChain;

class Compilation final {

  /// The System we were created by.
  const Driver &driver;

  // TODO: Move to DriverProfile
  /// The default tool chain.
  const ToolChain &tc;

  /// Temporary files which should be removed on exit.
  llvm::opt::ArgStringList tempFiles;

  /// True if temporary files should not be deleted.
  const bool saveTempFiles = false;

  /// Result files which should be removed on failure.
  // ArgStringMap resultFiles;

  /// Result files which are generated correctly on failure, and which should
  /// only be removed if we crash.
  // ArgStringMap failureResultFiles;

  Steps steps;

  Processes procs;

public:
  Compilation(Driver &driver, const ToolChain &tc);
  ~Compilation();

public:
  /// Creates a new Action owned by this Compilation.
  ///
  /// The new Action is *not* added to the list returned by getActions().
  template <typename T, typename... Args> T *CreateStep(Args &&...arg) {
    auto step = new T(std::forward<Args>(arg)...);
    steps.Add(std::unique_ptr<Step>(step));
    return step;
  }

  Steps &GetSteps() { return steps; }
  const Steps &GetSteps() const { return steps; }

  Processes &GetProcs() { return procs; }
  const Processes &GetProcs() const { return procs; }

  void AddProc(std::unique_ptr<Process> proc) { procs.Add(std::move(proc)); }

  /// addTempFile - Add a file to remove on exit, and returns its
  /// argument.
  const char *AddTempFile(const char *name) {
    tempFiles.push_back(name);
    return name;
  }

  /// PurgeFile - Delete a given file.
  ///
  /// \param IssueErrors - Report failures as errors.
  /// \return Whether the file was removed successfully.
  bool PurgeFile(const char *name, bool issueErrors = false) const;

  /// PurgeFiles - Remove the files in the given list.
  ///
  /// \param IssueErrors - Report failures as errors.
  /// \return Whether all files were removed successfully.
  bool PurgeFiles(const llvm::opt::ArgStringList &files,
                  bool issueErrors = false) const;

  // bool ExecuteProcs(std::unique_ptr<stone::ProcessQueue> &&queue);
  /// ExecuteProc - Execute an actual command.
  ///
  /// \param fallBackProc - For non-zero results, this will be set to the
  /// Command which failed, if any.
  /// \return The result code of the subprocess.
  int ExecuteProc(const Process &proc, const Process *&fallBackProc) const;

  /// ExecuteProc - Execute a single job.
  ///
  /// \param fallBackProc - For non-zero results, this will be a vector of
  /// failing commands and their associated result code.
  void ExecuteProcs(const Processes &procs,
                    llvm::SmallVectorImpl<std::pair<int, const Process *>>
                        &fallBackProcs) const;

  ToolChain const &GetToolChain() const { return tc; }
};

} // namespace stone
#endif
