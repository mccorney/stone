
set(stone_system_sources
	Action.cpp
	Compile.cpp
	Compiler.cpp
	CompileProcess.cpp
	Compiler.cpp
	CompilerConsumer.cpp
	CompilerFile.cpp
	LangStd.cpp
	Link.cpp
	LinkProcess.cpp
	Options.cpp
	Process.cpp
	Run.cpp
	System.cpp
	ToolChain.cpp
	Work.cpp

	LINK_LIBS
	StoneAnalysis
	StoneGen
)
add_stone_library(StoneSystem
	${stone_system_sources}
)



