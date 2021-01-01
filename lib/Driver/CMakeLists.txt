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

set(stone_driver_sources

	Compilation.cpp
	DarwinToolChain.cpp
	Driver.cpp
	Event.cpp
	Process.cpp
	ProcessQueue.cpp
	Run.cpp
	ToolChain.cpp
	UnixToolChain.cpp
	WinToolChain.cpp

	LINK_LIBS
	StoneCore
	StoneSession
)
add_stone_library(StoneDriver
	${stone_driver_sources}

	DEPENDS
	StoneOptions
)



