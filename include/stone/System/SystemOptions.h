namespace stone {

class SystemOptions final : public BaseOptions {
	public:
		void override Build(llvm::ArrayRef<const char*> Args); 
};

}
