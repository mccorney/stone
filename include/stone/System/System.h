#ifndef STONE_SYSTEM_SYSTEM_H
#define STONE_SYSTEM_SYSTEM_H

#include "llvm/ADT/ArrayRef.h"

namespace stone {
class System final {
	//Compilation 
	public:
		//SystemOptions SysOpts;
	public:
		//Action *A; // The action that creates the work 
	// llvm::PriorityQueue<Process*> ProcessQueue;
	// llvm::PriorityQueue<Work> WorkQueue;
	private:
		//void BuildOpts(llvm::ArrayRef<const char*> Args);
		void BuildWorkQueue(); 
	public:
		System();
		void Init(llvm::ArrayRef<const char*> args);
	public:
		int Run(); 
};

}
#endif
