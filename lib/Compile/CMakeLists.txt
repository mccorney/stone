set( LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
	BitReader
	BinaryFormat
  BitstreamReader
  Support
  Core
  IPO
  Option
  )
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
	Optimize.cpp
	Parse.cpp
	Parser.cpp
	Transformer.cpp
	
	LINK_LIBS
	stoneCore
	stoneSession
)
add_stone_library(stoneCompile
	${stone_compile_sources}
)



