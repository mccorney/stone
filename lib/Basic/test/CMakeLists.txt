set(LLVM_LINK_COMPONENTS
  Core
  Support
)

add_stone_unittest(StoneBasicTests
	SrcMgrTest.cpp
)
target_link_libraries(StoneBasicTests
  PRIVATE
	StoneBasic
	StoneCore
)

