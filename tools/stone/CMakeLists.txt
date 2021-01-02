
add_stone_tool(stone
  stone.cpp
)
target_link_libraries(stone
	PRIVATE
	stoneCompile
	stoneDriver
)
