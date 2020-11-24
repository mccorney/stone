set( LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
	BitReader
	BinaryFormat
  BitstreamReader
  ProfileData
  Support
  Analysis
  CodeGen
  Core
  IPO
  AggressiveInstCombine
  InstCombine
  Instrumentation
  MC
  MCParser
  Option
  ScalarOpts
  Support
  TransformUtils
  Vectorize
  )

set(stone_system_sources
	Action.cpp
	Compile.cpp
	CompileTest.cpp
	Compiler.cpp
	CompilerAction.cpp
	CompileProcess.cpp
	Compiler.cpp
	CompilerConsumer.cpp
	CompilerFile.cpp
	Help.cpp
	LangStd.cpp
	Link.cpp
	LinkProcess.cpp
	Options.cpp
	Process.cpp
	ProcessAction.cpp
	Run.cpp
	System.cpp
	ToolChain.cpp
	Work.cpp

	LINK_LIBS
	StoneAnalyze
	StoneGen
)
add_stone_library(StoneSystem
	${stone_system_sources}
)



