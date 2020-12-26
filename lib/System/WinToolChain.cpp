#include "stone/System/ToolChain.h"

using namespace stone;

WinToolChain::WinToolChain(const System &system, const llvm::Triple &triple)
    : ToolChain(system, triple) {}
