
set(stone_core_sources
	AST.cpp
	ASTConsumer.cpp
	ASTScope.cpp
	Builtins.cpp
	Decl.cpp
	Diag.cpp
	Expr.cpp
	FileMgr.cpp
	Module.cpp
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



