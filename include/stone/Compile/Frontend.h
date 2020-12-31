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

namespace stone {
class ModuleDecl;
class Analysis;
class GenOptions;
class Context;
class ASTContext;
class CompilePipeline;

/// Parse a source file
int Parse(Analysis &analysis, CompilePipeline *pipeline = nullptr);

/// Perform type checking
int Check(Analysis &analysis, CompilePipeline *pipeline = nullptr);

/// May want to pass Module instead
llvm::Module *GenIR(stone::ModuleDecl *moduleDecl, const stone::Context &ctx,
                    const GenOptions &genOpts,
                    llvm::StringRef outputModulename);

/// TODO:
void OptimizeIR(llvm::Module *llvmModule, const GenOptions &genOpts,
                llvm::TargetMachine *targetMachine);

} // namespace stone
#endif
