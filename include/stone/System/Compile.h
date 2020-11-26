#ifndef STONE_SYSTEM_COMPILE_H
#define STONE_SYSTEM_COMPILE_H

#include "llvm/ADT/ArrayRef.h"

namespace stone {

class Pipeline; 
int Compile(llvm::ArrayRef<const char *> args, const char *arg0, 
		void *mainAddr, Pipeline *pipeline = nullptr);
}
#endif 
