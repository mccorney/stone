#ifndef STONE_SYSTEM_COMPILER_OPTIONS_H
#define STONE_SYSTEM_COMPILER_OPTIONS_H

#include "stone/Gen/GenOptions.h"
#include "stone/Analyze/AnalyzeOptions.h"
#include "stone/System/BuildOptions.h"

namespace stone {

struct CompilerOptions final : public BuildOptions {
	GenOptions				genOpts; 
	AnalyzeOptions		analyzeOpts;  
};

}
#endif 
