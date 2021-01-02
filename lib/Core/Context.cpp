#include "stone/Core/Context.h"

using namespace Stone;

// TODO:
Context::Context() : de(diagOpts, nullptr, false), os(llvm::outs()) {}
