#ifndef STONE_SYSTEM_SYSTEM_H
#define STONE_SYSTEM_SYSTEM_H

#include "stone/Core/Mem.h"
#include "stone/System/Action.h"
#include "stone/System/SystemOptions.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include "llvm/ADT/PriorityQueue.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Arg.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Support/Chrono.h"
#include "llvm/Support/StringSaver.h"

#include <list>
#include <map>
#include <string>
#include <vector>

namespace llvm {
class Triple;
namespace vfs {
class FileSystem;
}
namespace opt {
class Arg;
class ArgList;
class OptTable;
class InputArgList;
class DerivedArgList;
} // namespace opt
} // namespace llvm

namespace stone {

class Task;
class Process;
class Compilation;

struct SystemOutput {
  enum class CompileMode {
    /// Multiple compile invocations and -main-file.
    Multiple,
    /// A compilation using a single compile invocation without -main-file.
    Single,
    /// Compile and execute the inputs immediately
    Immediate,
  };
  /// The number of threads for multi-threaded compilation.
  unsigned numThreads = 0;

  /// Returns true if multi-threading is enabled.
  bool IsMultiThreading() const { return numThreads > 0; }

  /// The name of the module which we are building.
  std::string moduleName;

  /// The path to the SDK against which to build.
  /// (If empty, this implies no SDK.)
  std::string sdkPath;
};

class System final {
public:
  SystemOptions systemOpts;
  llvm::PriorityQueue<Process *> queue;

public:
  /// The name the driver was invoked as.
  std::string driverName;

  /// Driver title to use with help.
  std::string driverTitle;

  /// The path the driver executable was in, as invoked from the
  /// command line.
  std::string driverPath;

  /// The original path to the clang executable.
  std::string stoneExecutablePath;

  /// sysroot, if present
  std::string sysRoot;

  /// Dynamic loader prefix, if present
  std::string dyldPrefix;

  /// Information about the host which can be overridden by the user.
  std::string hostBits, hostMachine, hostSystem, hostRelease;

  /// Target and driver mode components extracted from clang executable name.
  // ParsedClangName ClangNameParts;

  /// The path to the installed stone directory, if any.
  std::string installedDir;

  /// The path to the compiler resource directory.
  std::string resourceDir;

  /// System directory for config files.
  std::string systemConfigDir;

  /// User directory for config files.
  std::string userConfigDir;

  llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> vfs;

private:
  /// Raw target triple.
  std::string targetTriple;

  /// Name of configuration file if used.
  std::string cfgFile;

  /// Whether to check that input files exist when constructing compilation
  /// processes.
  unsigned checkInputFilesExist : 1;

  /// Allocator for string saver.
  llvm::BumpPtrAllocator bumpAlloc;

  /// Object that stores strings read from configuration file.
  llvm::StringSaver strSaver;

  /// Arguments originated from configuration file.
  std::unique_ptr<llvm::opt::InputArgList> cfgOpts;

  /// Arguments originated from command line.
  std::unique_ptr<llvm::opt::InputArgList> clOpts;

  /// When the build was started.
  ///
  /// This should be as close as possible to when the driver was invoked, since
  /// it's used as a lower bound.
  llvm::sys::TimePoint<> buildStartTime;

  /// The time of the last build.
  ///
  /// If unknown, this will be some time in the past.
  llvm::sys::TimePoint<> buildEndTime = llvm::sys::TimePoint<>::min();

private:
  void BuildTasks();
  void BuildProcs();
  void BuildQueue();
  void BuildOpts(llvm::ArrayRef<const char *> args);

public:
  System(llvm::StringRef stoneExecutable, llvm::StringRef targetTriple,
         llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> vfs = nullptr);

  void Init(llvm::ArrayRef<const char *> args);
  Compilation &BuildCompilation();

public:
  const std::string &GetConfigFile() const { return cfgFile; }
  const llvm::opt::OptTable &GetOptTable() const {
    return systemOpts.GetOptTable();
  }

  // const DiagnosticsEngine &GetDiagEngine() const { return Diags; }
  llvm::vfs::FileSystem &GetVFS() const { return *vfs; }

  bool GetCheckInputFilesExist() const { return checkInputFilesExist; }
  void SetCheckInputFilesExist(bool v) { checkInputFilesExist = v; }

  const std::string &GetDriverTitle() { return driverTitle; }
  void SetDriverTitle(std::string v) { driverTitle = std::move(v); }

public:
  int Run();
};

} // namespace stone
#endif
