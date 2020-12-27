#include "stone/System/ToolChain.h"

using namespace stone;

DarwinToolChain::DarwinToolChain(
    const Driver &driver, const llvm::Triple &triple,
    const llvm::Optional<llvm::Triple> &targetVariant)
    : ToolChain(driver, triple), targetVariant(targetVariant) {}
