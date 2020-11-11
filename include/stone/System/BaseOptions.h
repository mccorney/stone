

class BaseOptions {
	public:
		ActionKind Action;
	public:
		void virtual Build(llvm::ArrayRef<const char*> Args) = 0;  
};
