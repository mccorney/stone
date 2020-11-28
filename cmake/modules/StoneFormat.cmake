set(stone_include_files
	${STONE_SOURCE_DIR}/include/stone/Core/*.h
	${STONE_SOURCE_DIR}/include/stone/Analyze/*.h
	${STONE_SOURCE_DIR}/include/stone/System/*.h
	${STONE_SOURCE_DIR}/include/stone/Gen/*.h
	${STONE_SOURCE_DIR}/include/stone/*.h

)
set(stone_lib_files
	${STONE_SOURCE_DIR}/lib/Core/*.cpp
	${STONE_SOURCE_DIR}/lib/Core/test/*.cpp
	${STONE_SOURCE_DIR}/lib/Analyze/*.cpp
	${STONE_SOURCE_DIR}/lib/Analyze/test/*.cpp
	${STONE_SOURCE_DIR}/lib/System/*.cpp
	${STONE_SOURCE_DIR}/lib/System/test/*.cpp
	${STONE_SOURCE_DIR}/lib/Gen/*.cpp
	${STONE_SOURCE_DIR}/lib/Gen/test/*.cpp
)
set(stone_def_files
	${STONE_SOURCE_DIR}/include/stone/*.def
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
		${stone_def_files}

	)
endif()
