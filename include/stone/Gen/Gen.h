#ifndef STONE_GEN_GEN_H
#define STONE_GEN_GEN_H

namespace stone {
class ASTContext;
class Pipeline;
struct GenOptions;
class Module;
class Transformation;

// May want to pass Module instead
int Gen(stone::Module &langModule, const GenOptions &genOpts,
        Pipeline *pipeline = nullptr);

int Gen(Transformation &transformation, const GenOptions &genOpts,
        Pipeline *pipeline = nullptr);

} // namespace stone

#endif
