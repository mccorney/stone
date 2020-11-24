set(LLVM_LINK_COMPONENTS
  Core
  Support
)
add_stone_unittest(StoneGenTests
	GenTest.cpp
)
target_link_libraries(StoneGenTests
  PRIVATE
	StoneCore
)

