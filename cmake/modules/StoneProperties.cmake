file(GLOB_RECURSE
	ALL_CXX_SOURCE_FILES
	*.[chi]pp *.[chi]xx *.cpp *.cc *.h *.hh *.[CHI]
)
macro(set_stone_build_properties product)

	#LLVM
  set(PATH_TO_LLVM_SOURCE "${CMAKE_SOURCE_DIR}")
  set(PATH_TO_LLVM_BUILD "${CMAKE_BINARY_DIR}")
	set(LLVM_PACKAGE_VERSION ${PACKAGE_VERSION})
  set(LLVM_CMAKE_DIR "${CMAKE_SOURCE_DIR}/cmake/modules")
  set(${product}_NATIVE_LLVM_TOOLS_PATH "${CMAKE_BINARY_DIR}/bin")

	#STONE
	set(STONE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
	set(STONE_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")
	set(STONE_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
	set(STONE_MAIN_INCLUDE_DIR "${STONE_SOURCE_DIR}/include")
	set(STONE_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/include")
	set(STONE_LIB_DIR "${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/lib/stone")
	set(STONE_STATIC_LIB_DIR "${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/lib/stone_static")

endmacro()
