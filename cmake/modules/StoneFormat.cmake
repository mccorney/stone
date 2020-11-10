set(clang_include_files
	${CLANG_SOURCE_DIR}/include/clang/Parser/*.h
)
set(clang_lib_files
	${CLANG_SOURCE_DIR}/lib/Parser/*.cpp
)

find_program(CLANG_FORMAT clang-format)

if(CLANG_FORMAT)
	add_custom_target(clang-fmt
		clang-format
		-i
		-style=llvm
		${clang_lib_files}
		${clang_include_files}
	)

endif()
