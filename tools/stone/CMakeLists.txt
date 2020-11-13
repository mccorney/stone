
add_stone_tool(stone
  stone.cpp
	#DEPENDS
	#${tablegen_deps}

)
target_link_libraries(stone
	PRIVATE
	StoneSystem 
)
