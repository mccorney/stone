#ifndef STONE_SYSTEM_COMPILE_H
#define STONE_SYSTEM_COMPILE_H

#include "llvm/ADT/ArrayRef.h"

namespace stone {

	class CompilerConsumer; 
	int Compile(llvm::ArrayRef<const char *> Args, const char *Arg0, void *MainAddr, 
			CompilerConsumer *Consumer = nullptr);
}
#endif 
