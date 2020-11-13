namespace stone {

class Process; 
class ProcessQueue; 

class Process final {
	System *S; 
	public:
		llvm::SmallVector<Process*> Deps; 
};

class ProcessQueue {
};

}
