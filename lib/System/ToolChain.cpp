#include "stone/System/ToolChain.h"

using namespace stone;

ToolChain::ToolChain(const Driver &driver, const llvm::Triple &triple)
    : driver(driver), triple(triple) {}

std::unique_ptr<Process> ToolChain::CreateProc(/*const JobAction &JA, Compilation &C,
                                    SmallVectorImpl<const Job *> &&inputs,
                                    ArrayRef<const Action *> inputActions,
                                    std::unique_ptr<CommandOutput> output,
																		const OutputInfo &OI*/) const {
  return nullptr;
}
