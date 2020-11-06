

class CompilerAction;

class CompilerAction {
	public: 
		std::vector<CompilerAction*> Deps; 
		std::vector<CompilerAction*> Consumers;
	public:
		CompilerAction(Compiler* C); 

};
