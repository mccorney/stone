#include "stone/Driver/ToolChain.h"
#include "stone/Driver/CompilationTool.h"

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

CompilationTool *ToolChain::BuildAssembleTool() const { return nullptr; }
CompilationTool *ToolChain::BuildLinkTool() const { return nullptr; }
CompilationTool *ToolChain::BuildStaticLibTool() const { return nullptr; }
CompilationTool *ToolChain::BuildDynamicLibTool() const { return nullptr; }

CompilationTool *ToolChain::GetCompilationTool(ModeType modeType) const {
  return nullptr;
}
CompilationTool *ToolChain::PickTool(const CompilationEvent &event) const {

  switch (event.GetKind()) {
  case Event::Kind::DynamicLink:
    return nullptr;
  default:
    return nullptr;
  }
  return nullptr;
}
