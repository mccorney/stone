set(LLVM_LINK_COMPONENTS
  Core
  Support
)

add_stone_unittest(StoneAnalysisContextTests
	LexerTest.cpp
	ParserTest.cpp
)
target_link_libraries(StoneAnalysisContextTests
  PRIVATE
	StoneCore
	StoneAnalysisContext
)

