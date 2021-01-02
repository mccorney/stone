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
class CompilePipeline;
class GenOptions;
class Context;
class Analysis;

namespace Syntax {
class ModuleDecl;
class ASTContext;
} // namespace Syntax

/// Parse a source file
int Parse(Analysis &analysis, CompilePipeline *pipeline = nullptr);

/// Perform type checking
int Check(Analysis &analysis, CompilePipeline *pipeline = nullptr);

/// May want to pass Module instead
llvm::Module *GenIR(Stone::Syntax::ModuleDecl *moduleDecl,
                    const Stone::Context &ctx, const GenOptions &genOpts,
                    llvm::StringRef outputModulename);

/// TODO:
void OptimizeIR(llvm::Module *llvmModule, const GenOptions &genOpts,
                llvm::TargetMachine *targetMachine);

} // namespace Stone
#endif
