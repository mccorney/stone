namespace stone {

struct CompilerOptions final : public BuildOptions {
	GenOptions			GenOpts; 
	AnalysisOptions AnalysisOpts;  
};

}
