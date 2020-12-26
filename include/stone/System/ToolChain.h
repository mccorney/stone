#ifndef STONE_SYSTEM_TOOLCHAIN_H
#define STONE_SYSTEM_TOOLCHAIN_H

#include "stone/Core/LLVM.h"
#include "stone/Core/Mem.h"
#include "stone/System/Action.h"
#include "stone/System/FileType.h"
#include "stone/System/Options.h"
#include "stone/System/Process.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Option/Option.h"

namespace stone {

class ToolChain {
  const System &system;
  const llvm::Triple triple;

protected:
  ToolChain(const System &system, const llvm::Triple &triple);
};

class UnixToolChain : public ToolChain {
public:
  UnixToolChain(const System &system, const llvm::Triple &triple);
  ~UnixToolChain() = default;
};

class DarwinToolChain final : public ToolChain {
  const llvm::Optional<llvm::Triple> &targetVariant;

public:
  DarwinToolChain(const System &system, const llvm::Triple &triple,
                  const llvm::Optional<llvm::Triple> &targetVariant);
  ~DarwinToolChain() = default;
};

class LinuxToolChain final : public UnixToolChain {
public:
  LinuxToolChain(const System &system, const llvm::Triple &triple);
  ~LinuxToolChain() = default;
};

class FreeBSDToolChain final : public UnixToolChain {
public:
  FreeBSDToolChain(const System &system, const llvm::Triple &triple);
  ~FreeBSDToolChain() = default;
};
class OpenBSDToolChain final : public UnixToolChain {
public:
  OpenBSDToolChain(const System &system, const llvm::Triple &triple);
  ~OpenBSDToolChain() = default;
};

class WinToolChain : public ToolChain {
public:
  WinToolChain(const System &system, const llvm::Triple &triple);
  ~WinToolChain() = default;
};

} // namespace stone
#endif
