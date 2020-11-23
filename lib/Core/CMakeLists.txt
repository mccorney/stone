set(LLVM_LINK_COMPONENTS
  BinaryFormat
  Core
  Support
  )
set(stone_core_sources
	ASTContext.cpp
	ASTConsumer.cpp
	ASTScope.cpp
	Builtins.cpp
	Decl.cpp
	DeclContext.cpp
	Diag.cpp
	Expr.cpp
	FileMgr.cpp
	Identifier.cpp
	Module.cpp
	SrcFile.cpp
	SrcLoc.cpp
	SrcMgr.cpp
	Stats.cpp
	Stmt.cpp
	Visitor.cpp
	Walker.cpp
)
add_stone_library(StoneCore
	${stone_core_sources}
)



