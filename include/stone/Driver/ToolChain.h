#ifndef STONE_DRIVER_TOOLCHAIN_H
#define STONE_DRIVER_TOOLCHAIN_H

#include "stone/Core/LLVM.h"
#include "stone/Core/Mem.h"
#include "stone/Driver/CompilationTool.h"
#include "stone/Driver/Process.h"
#include "stone/Session/FileType.h"
#include "stone/Session/Mode.h"
#include "stone/Session/Options.h"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Triple.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Option/Option.h"
#include "llvm/Support/VersionTuple.h"
#include "llvm/Target/TargetOptions.h"

#include <cassert>
#include <climits>
#include <memory>
#include <string>
#include <utility>

namespace llvm {
namespace opt {
class Arg;
class ArgList;
class DerivedArgList;

} // namespace opt
namespace vfs {
class FileSystem;
} // namespace vfs
} // namespace llvm
namespace stone {

class ToolChain {
  const Driver &driver;
  const llvm::Triple triple;

  /// A special name used to identify the 'stone' executable itself.
  constexpr static const char *const StoneExecutableName = "stone";

public:
  using Paths = llvm::SmallVector<std::string, 16>;

protected:
  ToolChain(const Driver &driver, const llvm::Triple &triple);

private:
  /// The list of toolchain specific path prefixes to search for libraries.
  Paths libraryPaths;

  /// The list of toolchain specific path prefixes to search for files.
  Paths filePaths;

  /// The list of toolchain specific path prefixes to search for programs.
  Paths programPaths;

public:
  virtual ~ToolChain() = default;

  const Driver &GetDriver() const { return driver; }
  const llvm::Triple &GetTriple() const { return triple; }

  /// Construct a Process for the action \p JA, taking the given information
  /// into account.
  ///
  /// This method dispatches to the various \c constructInvocation methods,
  /// which may be overridden by platform-specific subclasses.
  std::unique_ptr<Process> CreateProc(/*const JobAction &JA, Compilation &C,
                                    SmallVectorImpl<const Job *> &&inputs,
                                    ArrayRef<const Action *> inputActions,
                                    std::unique_ptr<CommandOutput> output,
                                    const OutputInfo &OI*/) const;

  std::unique_ptr<ClangTool> GetClangTool();
  std::unique_ptr<LinkTool> GetLinkTool();
  std::unique_ptr<AssembleTool> GetAssembleTool();
  std::unique_ptr<GCCTool> GetGCCTool();
  std::unique_ptr<StoneTool> GetStoneTool();

  Paths &GetLibraryPaths() { return libraryPaths; }
  const Paths &GetLibraryPaths() const { return libraryPaths; }

  Paths &GetFilePaths() { return filePaths; }
  const Paths &GetFilePaths() const { return filePaths; }

  Paths &GetProgramPaths() { return programPaths; }
  const Paths &GetProgramPaths() const { return programPaths; }

  /// Pick a tool to use to handle the compilation event \p event.
  ///
  /// This can be overridden when a particular ToolChain needs to use
  /// a compiler other than Clang.
  virtual CompilationTool *PickTool(const CompilationEvent &event) const;

public:
  virtual CompilationTool *BuildAssembleTool() const;
  virtual CompilationTool *BuildLinkTool() const;
  virtual CompilationTool *BuildStaticLibTool() const;
  virtual CompilationTool *BuildDynamicLibTool() const;
  virtual CompilationTool *GetCompilationTool(ModeType modeType) const;
};

/*
class UnixToolChain : public ToolChain {
public:
  UnixToolChain(const Driver &driver, const llvm::Triple &triple);
  ~UnixToolChain() = default;
};
*/

class DarwinToolChain final : public ToolChain {
  const llvm::Optional<llvm::Triple> &targetVariant;

public:
  DarwinToolChain(const Driver &driver, const llvm::Triple &triple,
                  const llvm::Optional<llvm::Triple> &targetVariant);
  ~DarwinToolChain() = default;

public:
  CompilationTool *BuildAssembleTool() const override;
  CompilationTool *BuildLinkTool() const override;
  CompilationTool *BuildStaticLibTool() const override;
  CompilationTool *BuildDynamicLibTool() const override;
  CompilationTool *GetCompilationTool(ModeType modeType) const override;
};

/*
class LinuxToolChain final : public UnixToolChain {
public:
  LinuxToolChain(const Driver &driver, const llvm::Triple &triple);
  ~LinuxToolChain() = default;

public:
  CompilationTool *BuildAssembleTool() override const;
  CompilationTool *BuildLinkTool() override const;
  CompilationTool *BuildStaticLibTool() override const;
  CompilationTool *BuildDynamicLibTool() override const;
  CompilationTool *GetCompilationTool(ModeType modeType) override const;
};

class FreeBSDToolChain final : public UnixToolChain {
public:
  FreeBSDToolChain(const Driver &driver, const llvm::Triple &triple);
  ~FreeBSDToolChain() = default;

public:
  CompilationTool *BuildAssembleTool() override const;
  CompilationTool *BuildLinkTool() override const;
  CompilationTool *BuildStaticLibTool() override const;
  CompilationTool *BuildDynamicLibTool() override const;
  CompilationTool *GetCompilationTool(ModeType modeType) override const;
};
class OpenBSDToolChain final : public UnixToolChain {
public:
  OpenBSDToolChain(const Driver &driver, const llvm::Triple &triple);
  ~OpenBSDToolChain() = default;

public:
  CompilationTool *BuildAssembleTool() override const;
  CompilationTool *BuildLinkTool() override const;
  CompilationTool *BuildStaticLibTool() override const;
  CompilationTool *BuildDynamicLibTool() override const;
  CompilationTool *GetCompilationTool(ModeType modeType) override const;
};

class WinToolChain : public ToolChain {
public:
  WinToolChain(const Driver &driver, const llvm::Triple &triple);
  ~WinToolChain() = default;

public:
  CompilationTool *BuildAssembleTool() override const;
  CompilationTool *BuildLinkTool() override const;
  CompilationTool *BuildStaticLibTool() override const;
  CompilationTool *BuildDynamicLibTool() override const;
  CompilationTool *GetCompilationTool(ModeType modeType) override const;
};
*/

} // namespace stone
#endif
