
class Compiler final {
	public: 
	 CompilerOptions Opts; 
	 std::unique_ptr<Analysis> A; 
	public:
		//llvm::PriorityQueue<Action*> ActionQueue;
	public:
		void Init(llvm::ArrayRef<const char*> Args);
		bool Run();
	public:
		Analysis *GetAnalysis(); 
};
