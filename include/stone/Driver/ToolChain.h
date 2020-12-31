#ifndef STONE_DRIVER_TOOLCHAIN_H
#define STONE_DRIVER_TOOLCHAIN_H

#include "stone/Core/LLVM.h"
#include "stone/Core/Mem.h"
#include "stone/Driver/Process.h"
#include "stone/Session/FileType.h"
#include "stone/Session/Options.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Option/Option.h"

namespace stone {

class ToolChain {
  const Driver &driver;
  const llvm::Triple triple;

protected:
  ToolChain(const Driver &driver, const llvm::Triple &triple);

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
};

class UnixToolChain : public ToolChain {
public:
  UnixToolChain(const Driver &driver, const llvm::Triple &triple);
  ~UnixToolChain() = default;
};

class DarwinToolChain final : public ToolChain {
  const llvm::Optional<llvm::Triple> &targetVariant;

public:
  DarwinToolChain(const Driver &driver, const llvm::Triple &triple,
                  const llvm::Optional<llvm::Triple> &targetVariant);
  ~DarwinToolChain() = default;
};

class LinuxToolChain final : public UnixToolChain {
public:
  LinuxToolChain(const Driver &driver, const llvm::Triple &triple);
  ~LinuxToolChain() = default;
};

class FreeBSDToolChain final : public UnixToolChain {
public:
  FreeBSDToolChain(const Driver &driver, const llvm::Triple &triple);
  ~FreeBSDToolChain() = default;
};
class OpenBSDToolChain final : public UnixToolChain {
public:
  OpenBSDToolChain(const Driver &driver, const llvm::Triple &triple);
  ~OpenBSDToolChain() = default;
};

class WinToolChain : public ToolChain {
public:
  WinToolChain(const Driver &driver, const llvm::Triple &triple);
  ~WinToolChain() = default;
};

} // namespace stone
#endif