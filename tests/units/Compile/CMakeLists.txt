set(LLVM_LINK_COMPONENTS
  Core
  Support
)

add_stone_unittest(stoneAnalysisContextTests
	LexerTest.cpp
	ParserTest.cpp
)
target_link_libraries(stoneAnalysisContextTests
  PRIVATE
	stoneCore
	stoneAnalysisContext
)

