#ifndef STONE_COMPILE_FRONTEND_H
#define STONE_COMPILE_FRONTEND_H

#include "llvm/ADT/ArrayRef.h"

namespace llvm {
class raw_pwrite_stream;
class GlobalVariable;
class MemoryBuffer;
class Module;
class TargetOptions;
class TargetMachine;
} // namespace llvm

namespace Stone {
class Context;
class CompilePipeline;
class GenOptions;

namespace Syntax {
class ModuleDecl;
class ASTContext;
} // namespace Syntax

namespace Analysis {
class AnalysisContext;

/// Parse a source file
int Parse(AnalysisContext &analysis, CompilePipeline *pipeline = nullptr);

/// Perform type checking
int Check(AnalysisContext &analysis, CompilePipeline *pipeline = nullptr);

/// May want to pass Module instead
llvm::Module *GenIR(Stone::Syntax::ModuleDecl *moduleDecl,
                    const Stone::Context &ctx, const GenOptions &genOpts,
                    llvm::StringRef outputModulename);

void OptimizeIR(llvm::Module *llvmModule, const GenOptions &genOpts,
                llvm::TargetMachine *targetMachine);
} // namespace Analysis
} // namespace Stone
#endif
