#ifndef STONE_GEN_GEN_H
#define STONE_GEN_GEN_H

namespace stone{
class ASTContext;
class Pipeline;
struct GenOptions;

	// May want to pass Module instead
int Gen(ASTContext& AC, const GenOptions& GenOpts, Pipeline* P = nullptr);

}

#endif 
