set( LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
  Analysis
  CodeGen
  Core
  IPO
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


# Support plugins. This must be before add_stone_executable as it reads
# LLVM_NO_DEAD_STRIP.
if(STONE_PLUGIN_SUPPORT)
  set(LLVM_NO_DEAD_STRIP 1)
endif()

if(NOT STONE_BUILT_STANDALONE)
  set(tablegen_deps intrinsics_gen)
endif()

add_stone_tool(stone
  stone.cpp
  DEPENDS
  ${tablegen_deps}

)
target_link_libraries(stone
	PRIVATE
	StoneSystem 
)
