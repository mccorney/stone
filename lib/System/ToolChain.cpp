#include "stone/System/ToolChain.h"

using namespace stone;

ToolChain::ToolChain(const System &system, const llvm::Triple &triple)
    : system(system), triple(triple) {}
