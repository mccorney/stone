set(LLVM_LINK_COMPONENTS
  Core
  Support
)

add_stone_unittest(StoneCoreTests
  DiagTest.cpp
	FileMgrTest.cpp
	SrcMgrTest.cpp
)
target_link_libraries(StoneCoreTests
  PRIVATE
	StoneCore
)

