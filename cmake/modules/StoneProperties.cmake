@CLANG_CONFIG_CODE@

find_package(LLVM REQUIRED CONFIG
             HINTS "@CLANG_CONFIG_LLVM_CMAKE_DIR@")

set(CLANG_EXPORTED_TARGETS "@CLANG_EXPORTS@")
set(CLANG_CMAKE_DIR "@CLANG_CONFIG_CMAKE_DIR@")
set(CLANG_INCLUDE_DIRS "@CLANG_CONFIG_INCLUDE_DIRS@")

# Provide all our library targets to users.
include("@CLANG_CONFIG_EXPORTS_FILE@")


file(GLOB_RECURSE
	ALL_CXX_SOURCE_FILES
	*.[chi]pp *.[chi]xx *.cpp *.cc *.h *.hh *.[CHI]
)


macro(stone_properties product)

  set(PATH_TO_LLVM_SOURCE "${CMAKE_SOURCE_DIR}")
  set(PATH_TO_LLVM_BUILD "${CMAKE_BINARY_DIR}")
  set(${product}_PATH_TO_CLANG_BUILD "${CMAKE_BINARY_DIR}")
  set(PATH_TO_CLANG_BUILD "${CMAKE_BINARY_DIR}")
  #set(CLANG_MAIN_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/tools/clang/include")
  #set(CLANG_BUILD_INCLUDE_DIR "${CMAKE_BINARY_DIR}/tools/clang/include")
  set(${product}_NATIVE_LLVM_TOOLS_PATH "${CMAKE_BINARY_DIR}/bin")
  set(${product}_NATIVE_CLANG_TOOLS_PATH "${CMAKE_BINARY_DIR}/bin")
  set(LLVM_PACKAGE_VERSION ${PACKAGE_VERSION})
  set(LLVM_CMAKE_DIR "${CMAKE_SOURCE_DIR}/cmake/modules")
 
  include_directories(${CLANG_BUILD_INCLUDE_DIR})
  include_directories(${CLANG_MAIN_INCLUDE_DIR})
	
	include(StoneTableGen) # This imports TableGen from LLVM.

  check_cxx_compiler_flag("-Werror -Wnested-anon-types" CXX_SUPPORTS_NO_NESTED_ANON_TYPES_FLAG)
  if(CXX_SUPPORTS_NO_NESTED_ANON_TYPES_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nested-anon-types")
  endif()
endmacro()

