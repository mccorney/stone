namespace stone {

class CompilerOptions final : public BaseOptions {
	public:
		GenOptions			GenOpts; 
		AnalysisOptions AnalysisOpts; 
	public:
		void override Build(llvm::ArrayRef<const char*> Args); 
};

}
