set(LLVM_LINK_COMPONENTS
	Option
)

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
	Compilation.cpp
	Compiler.cpp
	CompileProcess.cpp
	Compiler.cpp
	CompileFile.cpp
	DarwinToolChain.cpp
	FileType.cpp
	Help.cpp
	Link.cpp
	LinkProcess.cpp
	Options.cpp
	Phase.cpp
	Process.cpp
	Run.cpp
	System.cpp
	ToolChain.cpp
	UnixToolChain.cpp
	WinToolChain.cpp
	Task.cpp

	LINK_LIBS
	StoneAnalyze
	StoneGen
)
add_stone_library(StoneSystem
	${stone_system_sources}

	DEPENDS
	StoneOptions
)



