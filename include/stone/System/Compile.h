#ifndef STONE_SYSTEM_COMPILE_H
#define STONE_SYSTEM_COMPILE_H

#include "llvm/ADT/ArrayRef.h"

namespace stone {

	class Pipeline; 
	int Compile(llvm::ArrayRef<const char *> Args, const char *Arg0, void *MainAddr, 
			Pipeline *P = nullptr);
}
#endif 
