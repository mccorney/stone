set(stone_include_files
	${STONE_SOURCE_DIR}/include/stone/Core/*.h
	${STONE_SOURCE_DIR}/include/stone/Analyze/*.h
	${STONE_SOURCE_DIR}/include/stone/System/*.h
	${STONE_SOURCE_DIR}/include/stone/Gen/*.h
)
set(stone_lib_files
	${STONE_SOURCE_DIR}/lib/Core/*.cpp
	${STONE_SOURCE_DIR}/lib/Analyze/*.cpp
	${STONE_SOURCE_DIR}/lib/System/*.cpp
	${STONE_SOURCE_DIR}/lib/Gen/*.cpp
)
find_program(CLANG_FORMAT clang-format)

if(CLANG_FORMAT)

	add_custom_target(
		stone-fmt
		clang-format
		-i
		-style=llvm
		${stone_lib_files}
		${stone_include_files}
		)

endif()
