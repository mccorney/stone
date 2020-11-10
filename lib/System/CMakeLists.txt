set(LLVM_LINK_COMPONENTS
   Core
   Support
	 MC
)
set(stone_system_sources
Compiler.cpp
)
add_stone_library(StoneSystem
	${stone_system_sources}
)



