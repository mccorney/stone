#include "stone/System/ToolChain.h"

using namespace stone;

DarwinToolChain::DarwinToolChain(
    const System &system, const llvm::Triple &triple,
    const llvm::Optional<llvm::Triple> &targetVariant)
    : ToolChain(system, triple), targetVariant(targetVariant) {}
