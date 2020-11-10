
set(stone_core_sources
	AST.cpp
	ASTState.cpp
	ASTConsumer.cpp
	ASTScope.cpp
	Builtins.cpp
	Decl.cpp
	Diag.cpp
	Expr.cpp
	FileMgr.cpp
	Module.cpp
	Source.cpp
	SrcLoc.cpp
	SrcMgr.cpp
	Stmt.cpp
	Visitor.cpp
	Walker.cpp
)
add_stone_library(StoneCore
	${stone_core_sources}
)



