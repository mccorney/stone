#ifndef STONE_SYSTEM_BUILDPROFILE_H
#define STONE_SYSTEM_BUILDPROFILE_H

#include "stone/System/DriverProfile.h"

#include "llvm/ADT/StringRef.h"

namespace stone {
namespace driver {
class Event;
}
struct ModuleEncapsulation final {
public:
  /// The name of the module which we are building.
  std::string moduleName;

  ///  Whether or not the driver should generate a module.
  bool generateModule = false;

  /// The inputs for this module
  llvm::SmallVector<const driver::Event *, 2> inputs;
};
struct LinkerEncapsulation final {
public:
  llvm::SmallVector<const driver::Event *, 2> inputs;

  /// The linker type
  enum class LinkType { None, Executable, DynamicLib, StaticLib };

  /// Default link type
  LinkType linkType = LinkType::None;

  LinkType GetLinkType() { return linkType; }

  bool ShouldLink() { return linkType != LinkType::None; }
};
struct CompileEncapsulation final {
public:
  enum class CompileType {
    /// Multiple compile invocations and -main-file.
    MultipleInvocation,
    /// A compilation using a single compile invocation without -main-file.
    SingleInvocation,
    /// Compile and execute the inputs immediately
    ImmediateInvocation,
  };
  CompileType compileType = CompileType::MultipleInvocation;

  /// The number of threads for multi-threaded compilation.
  unsigned numThreads = 0;

  /// Returns true if multi-threading is enabled.
  bool IsMultiThreading() const { return numThreads > 0; }
};

class BuildProfile final {
public:
  /// The path to the SDK against which to build.
  /// (If empty, this implies no SDK.)
  std::string sdkPath;

  /// Whether to skip the SDK
  bool skipSDK = false;

  ModuleEncapsulation moduleEncap;
  LinkerEncapsulation linkerEncap;
  CompileEncapsulation compileEncap;
};

} // namespace stone
#endif
