#ifndef STONE_DRIVER_COMPILATIONTOOL_H
#define STONE_DRIVER_COMPILATIONTOOL_H

#include "llvm/ADT/StringRef.h"

namespace stone {
class ToolChain;
class CompilationTool {
  /// The tool name (for debugging).
  llvm::StringRef fullName;
  /// The human readable name for the tool, for use in diagnostics.
  llvm::StringRef shortName;
  /// The tool chain this tool is a part of.
  const ToolChain &toolChain;

public:
  CompilationTool(llvm::StringRef fullName, llvm::StringRef shortName,
                  const ToolChain &toolChain);

public:
  virtual ~CompilationTool();

public:
  virtual bool HasAssembler() const { return false; }
};

class LinkTool final : public CompilationTool {};

class AssembleTool final : public CompilationTool {};

class ClangTool final : public CompilationTool {};

class StoneTool final : public CompilationTool {};

class GCCTool final : public CompilationTool {};

} // namespace stone

#endif
