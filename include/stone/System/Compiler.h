
class Compiler final {
	public: 
		CompilerOptions Opts; 
	//std::unique_ptr<Analysis> A; 
	public:
		//llvm::PriorityQueue<Action*> ActionQueue;
	public:
		BuildOpts(llvm::ArrayRef<const char*> Args);

	void Run(); 
};

