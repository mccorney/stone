#include "stone/System/ToolChain.h"

using namespace stone;

UnixToolChain::UnixToolChain(const System &system, const llvm::Triple &triple)
    : ToolChain(system, triple) {}

LinuxToolChain::LinuxToolChain(const System &system, const llvm::Triple &triple)
    : UnixToolChain(system, triple) {}

FreeBSDToolChain::FreeBSDToolChain(const System &system,
                                   const llvm::Triple &triple)
    : UnixToolChain(system, triple) {}

OpenBSDToolChain::OpenBSDToolChain(const System &system,
                                   const llvm::Triple &triple)
    : UnixToolChain(system, triple) {}
