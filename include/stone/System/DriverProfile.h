#ifndef STONE_SYSTEM_DRIVERPROFILE_H
#define STONE_SYSTEM_DRIVERPROFILE_H

namespace stone {

class DriverProfile final {
public:
  enum class DriverType {
    None,
  };
  enum class CompileType {
    /// Multiple compile invocations and -main-file.
    MultipleInvocation,
    /// A compilation using a single compile invocation without -main-file.
    SingleInvocation,
    /// Compile and execute the inputs immediately
    ImmediateInvocation,
  };

  CompileType compileType = CompileType::MultipleInvocation;

  enum class LinkType { None, Executable, DynamicLib, StaticLib };

  /// The number of threads for multi-threaded compilation.
  unsigned numThreads = 0;

  /// Returns true if multi-threading is enabled.
  bool IsMultiThreading() const { return numThreads > 0; }

  /// The name of the module which we are building.
  std::string moduleName;

  /// The path to the SDK against which to build.
  /// (If empty, this implies no SDK.)
  std::string sdkPath;

  // Whether or not the driver should generate a module.
  bool generateModule = false;

  /// Default linking kind
  LinkType linkType = LinkType::None;

  LinkType GetLinkType() { return linkType; }

  bool ShouldLink() { return linkType != LinkType::None; }
};

} // namespace stone
#endif
