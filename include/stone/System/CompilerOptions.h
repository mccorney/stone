namespace stone {

struct CompilerOptions final : public BaseOptions {
	GenOptions			GenOpts; 
	AnalysisOptions AnalysisOpts;  
};

}
