#include "stone/Driver/ToolChain.h"

using namespace stone;

DarwinToolChain::DarwinToolChain(
    const Driver &driver, const llvm::Triple &triple,
    const llvm::Optional<llvm::Triple> &targetVariant)
    : ToolChain(driver, triple), targetVariant(targetVariant) {}

CompilationTool *DarwinToolChain::BuildAssembleTool() const { return nullptr; }
CompilationTool *DarwinToolChain::BuildLinkTool() const { return nullptr; }
CompilationTool *DarwinToolChain::BuildStaticLibTool() const { return nullptr; }
CompilationTool *DarwinToolChain::BuildDynamicLibTool() const {
  return nullptr;
}

CompilationTool *DarwinToolChain::GetCompilationTool(ModeType modeType) const {

  return nullptr;
}
