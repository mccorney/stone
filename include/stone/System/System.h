

namespace stone {

class System final {
	public:
		SystemOptions Opts;
	public:
		//Action *A; // The action that creates the work 
	// llvm::PriorityQueue<Process*> ProcessQueue;
	// llvm::PriorityQueue<Work> WorkQueue; 
	public:
		void BuildOpts(llvm::ArrayRef<const char*> Args);

	public:
		bool Run(); 
};

} 
