namespace stone {

class Process; 
class ProcessQueue; 


class Process final {
	public:
		llvm::SmallVector<Process*> Deps; 
};

class ProcessQueue {

};

}
