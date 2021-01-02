#include "stone/Driver/ToolChain.h"

using namespace stone;
using namespace stone::driver;

Tool::Tool(llvm::StringRef fullName, llvm::StringRef shortName,
           const ToolChain &toolChain)
    : fullName(fullName), shortName(shortName), toolChain(toolChain) {
  canEmitIR = false;
}

Tool::~Tool() {}

ClangTool::ClangTool(llvm::StringRef fullName, llvm::StringRef shortName,
                     const ToolChain &toolChain)
    : Tool(fullName, shortName, toolChain) {
  canEmitIR = true;
}

ClangTool::~ClangTool() {}

stoneTool::stoneTool(llvm::StringRef fullName, llvm::StringRef shortName,
                     const ToolChain &toolChain)
    : Tool(fullName, shortName, toolChain) {
  canEmitIR = true;
}
stoneTool::~stoneTool() {}

GCCTool::GCCTool(llvm::StringRef fullName, llvm::StringRef shortName,
                 const ToolChain &toolChain)
    : Tool(fullName, shortName, toolChain) {}
GCCTool::~GCCTool() {}

DynamicLinkTool::DynamicLinkTool(llvm::StringRef fullName,
                                 llvm::StringRef shortName,
                                 const ToolChain &toolChain)
    : Tool(fullName, shortName, toolChain) {}
DynamicLinkTool::~DynamicLinkTool() {}

StaticLinkTool::StaticLinkTool(llvm::StringRef fullName,
                               llvm::StringRef shortName,
                               const ToolChain &toolChain)
    : Tool(fullName, shortName, toolChain) {}

StaticLinkTool::~StaticLinkTool() {}

AssembleTool::AssembleTool(llvm::StringRef fullName, llvm::StringRef shortName,
                           const ToolChain &toolChain)
    : Tool(fullName, shortName, toolChain) {}
AssembleTool::~AssembleTool() {}

ToolChain::ToolChain(const Driver &driver, const llvm::Triple &triple)
    : driver(driver), triple(triple) {}

std::unique_ptr<Process> ToolChain::CreateProc(/*const JobAction &JA, Compilation &C,
                                    SmallVectorImpl<const Job *> &&inputs,
                                    ArrayRef<const Action *> inputActions,
                                    std::unique_ptr<CommandOutput> output,
																		const OutputInfo &OI*/) const {
  return nullptr;
}

Tool *ToolChain::PickTool(const CompilationEvent &event) const {

  switch (event.GetKind()) {
  case Event::Kind::DynamicLink:
    return nullptr;
  default:
    return nullptr;
  }
  return nullptr;
}
