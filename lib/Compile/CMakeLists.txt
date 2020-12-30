
set(stone_compile_sources
	Analysis.cpp
	Backend.cpp
	Check.cpp
	Checker.cpp
	Compile.cpp
	CompileFile.cpp
	Compiler.cpp
	Gen.cpp
	Lexer.cpp
	Parse.cpp
	Parser.cpp
	Transformer.cpp
	
	LINK_LIBS
	StoneCore
	StoneSession
)
add_stone_library(StoneCompile
	${stone_compile_sources}
)



