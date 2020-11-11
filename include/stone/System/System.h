

namespace stone {

class System final {
	public:
		SystemOptions Opts;
	public:
		//Action *A; // The action that creates the work 
	// llvm::PriorityQueue<Process*> ProcessQueue;
	// llvm::PriorityQueue<Work> WorkQueue;
	private:
		void BuildOpts(llvm::ArrayRef<const char*> Args);
		void BuildWorkQueue(); 
	public:
		void Init(llvm::ArrayRef<const char*> Args);
	public:
		bool Run(); 
};

}

