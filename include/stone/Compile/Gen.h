#ifndef STONE_COMPILE_GEN_H
#define STONE_COMPILE_GEN_H

namespace stone {
class ASTContext;
class Pipeline;
class GenOptions;
class ModuleDecl;
class Context;

// May want to pass Module instead
int Gen(stone::ModuleDecl *moduleDecl, const stone::Context &ctx,
        const GenOptions &genOpts, Pipeline *pipeline = nullptr);
} // namespace stone

#endif
