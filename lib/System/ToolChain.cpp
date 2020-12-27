#include "stone/System/ToolChain.h"

using namespace stone;

ToolChain::ToolChain(const Driver &driver, const llvm::Triple &triple)
    : driver(driver), triple(triple) {}
