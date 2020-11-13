

class Action {
	Compiler *C; 
	public:
		AtionKind Kind; 

	public: 
		//std::vector<Action*> Deps; 
		//std::vector<Action*> Consumers;
	public:
		Action(Compiler* C); 
};
