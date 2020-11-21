
set(stone_gen_sources
	Backend.cpp
	Gen.cpp
	Transformer.cpp


	LINK_LIBS
	StoneCore
)
add_stone_library(StoneGen
	${stone_gen_sources}
)



