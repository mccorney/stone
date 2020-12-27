#ifndef STONE_GEN_GEN_H
#define STONE_GEN_GEN_H

namespace stone {
class ASTContext;
class Pipeline;
struct GenOptions;
class ModuleDecl;
class Context;

// May want to pass Module instead
int Gen(stone::ModuleDecl *moduleDecl, const stone::Context &ctx,
        const GenOptions &genOpts, Pipeline *pipeline = nullptr);
} // namespace stone

#endif
