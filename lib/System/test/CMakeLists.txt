set(LLVM_LINK_COMPONENTS
  Core
  Support
)

add_stone_unittest(StoneSystemTests
  CompileTest.cpp
)
target_link_libraries(StoneSystemTests
  PRIVATE
	StoneCore
	StoneGen
	StoneAnalysis
)

