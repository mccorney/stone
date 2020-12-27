#include "stone/System/ToolChain.h"

using namespace stone;

WinToolChain::WinToolChain(const Driver &driver, const llvm::Triple &triple)
    : ToolChain(driver, triple) {}
