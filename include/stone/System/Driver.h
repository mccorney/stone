#ifndef STONE_SYSTEM_DRIVER_H
#define STONE_SYSTEM_DRIVER_H

#include "stone/Core/Mem.h"
#include "stone/System/Action.h"
#include "stone/System/Compilation.h"
#include "stone/System/DriverOptions.h"
#include "stone/System/Session.h"

#include "llvm/Support/StringSaver.h"
#include "llvm/Support/VirtualFileSystem.h"

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
class ToolChain;

struct DriverOutput {
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

class Driver final : public Session {
public:
  DriverOptions driverOpts;
  llvm::PriorityQueue<Process *> queue;

public:
  /// The name the driver was invoked as.
  std::string driverName;

  /// Driver title to use with help.
  std::string driverTitle;

  /// The path the driver executable was in, as invoked from the
  /// command line.
  std::string driverDir;

  /// The original path to the stone executable.
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

private:
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

private:
  void BuildTasks();
  void BuildProcs();
  void BuildQueue();
  void BuildOpts(llvm::ArrayRef<const char *> args);

  /// This uses a std::unique_ptr instead of returning a toolchain by value
  /// because ToolChain has virtual methods.
  std::unique_ptr<ToolChain>
  BuildToolChain(const llvm::opt::InputArgList &argList);

  std::unique_ptr<Compilation>
  BuildCompilation(const ToolChain &toolChain,
                   const llvm::opt::InputArgList &argList);

public:
  Driver(llvm::StringRef executablePath);

  /// Parse the given list of strings into an InputArgList.
  bool Build(llvm::ArrayRef<const char *> args) override;

  int Run() override;
  ///
  void PrintCycle() override;

  ///
  void PrintHelp() override;

  ///
  // void PrintTasks();

  ///
  // void PrintProcs();

public:
  const std::string &GetConfigFile() const { return cfgFile; }

  bool GetCheckInputFilesExist() const { return checkInputFilesExist; }
  void SetCheckInputFilesExist(bool v) { checkInputFilesExist = v; }

  const std::string &GetDriverTitle() { return driverTitle; }
  void SetDriverTitle(std::string v) { driverTitle = std::move(v); }

  /// Get the path to where the clang executable was installed.
  const char *GetInstalledDir() const {
    if (!installedDir.empty())
      return installedDir.c_str();
    return driverDir.c_str();
  }
  void SetInstalledDir(llvm::StringRef v) { installedDir = std::string(v); }
};

} // namespace stone
#endif
