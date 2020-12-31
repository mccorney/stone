#ifndef STONE_DRIVER_DRIVER_H
#define STONE_DRIVER_DRIVER_H

#include "stone/Core/Mem.h"
#include "stone/Driver/Compilation.h"
#include "stone/Driver/DriverOptions.h"
#include "stone/Driver/DriverProfile.h"
#include "stone/Driver/ToolChain.h"
#include "stone/Session/Session.h"

#include "llvm/Support/StringSaver.h"
#include "llvm/Support/VirtualFileSystem.h"

#include <list>
#include <map>
#include <string>
#include <vector>

using namespace llvm::opt;
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

namespace driver {
class Event;
class Process;

} // namespace driver

class Compilation;
class ToolChain;

class Driver final : public Session {

  std::unique_ptr<Compilation> compilation;

public:
  DriverOptions driverOpts;

  DriverProfile profile;

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

  /// Cache of all the ToolChains in use by the driver.
  ///
  /// This maps from the string representation of a triple to a ToolChain
  /// created targeting that triple. The driver owns all the ToolChain objects
  /// stored in it, and will clean them up when torn down.
  mutable llvm::StringMap<std::unique_ptr<ToolChain>> toolChainCache;

  // BuildProfile buildProfile;

private:
  void BuildEvents();
  void BuildProcs();
  void BuildQueue();

  /// This uses a std::unique_ptr instead of returning a toolchain by value
  /// because ToolChain has virtual methods.
  std::unique_ptr<ToolChain>
  BuildToolChain(const llvm::opt::InputArgList &argList);

  void BuildInputs(const ToolChain &tc, const DerivedArgList &args,
                   InputFiles &inputs);

  std::unique_ptr<Compilation>
  BuildCompilation(const ToolChain &toolChain,
                   const llvm::opt::InputArgList &argList);

  bool HandleImmediateArgs(const ArgList &args, const ToolChain &tc);

public:
  Driver(llvm::StringRef executablePath, std::string driverName);

  /// Parse the given list of strings into an InputArgList.
  bool Build(llvm::ArrayRef<const char *> args) override;

  int Run() override;
  ///
  void PrintLifecycle() override;

  ///
  void PrintHelp(bool showHidden) override;

  ///
  // void PrintTasks();

  ///
  // void PrintProcs();
  //

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

  // const DriverProfile &GetProfile() const { return profile; }
  // DriverProfile &GetDriverProfile() { return profile; }

  // const BuildProfile &GetBuildProfile() const { return buildProfile; }
  // BuildProfile &GetBuildProfile() { return buildProfile; }

protected:
  void ComputeMode(const llvm::opt::DerivedArgList &args) override;

  /// TranslateInputArgs - Create a new derived argument list from the input
  /// arguments, after applying the standard argument translations.
  // llvm::opt::DerivedArgList *
  // TranslateInputArgs(const llvm::opt::InputArgList &args) override const;
};

} // namespace stone
#endif