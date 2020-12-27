#include "stone/Core/Context.h"

using namespace stone;

// TODO:
Context::Context() : diagEngine(diagOpts, nullptr, false), os(llvm::outs()) {}
