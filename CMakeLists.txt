cmake_minimum_required(VERSION 3.15)
project(Stone)

# Make sure that our source directory is on the current cmake module path so that
# we can include cmake files from this directory.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")


include(CMakeParseArguments)

include(StoneCore)
include(StoneTblGen)
include(StoneFormat)
#include(StoneUnitTests)



set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(StoneCommon)
stone_common_unified_build_config(STONE)

if(NOT EXISTS "${CLANG_MAIN_INCLUDE_DIR}/clang/AST/Decl.h")
	#message(FATAL_ERROR "Clang is missing from llvm/tools subdirectory.")
endif()

set(STONE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(STONE_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(STONE_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
set(STONE_MAIN_INCLUDE_DIR "${STONE_SOURCE_DIR}/include")
set(STONE_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/include")

# If STONE_VERSION_* is specified, use it, if not use LLVM_VERSION_*.
if(NOT DEFINED STONE_VERSION_MAJOR)
  set(STONE_VERSION_MAJOR 0)
endif()
if(NOT DEFINED STONE_VERSION_MINOR)
  set(STONE_VERSION_MINOR 1)
endif()
if(NOT DEFINED STONE_VERSION_PATCHLEVEL)
  set(STONE_VERSION_PATCHLEVEL 0)
endif()
# Unlike PACKAGE_VERSION, STONE_VERSION does not include LLVM_VERSION_SUFFIX.
set(STONE_VERSION "${STONE_VERSION_MAJOR}.${STONE_VERSION_MINOR}.${STONE_VERSION_PATCHLEVEL}")
message(STATUS "Stone version: ${STONE_VERSION}")

if (NOT LLVM_INSTALL_TOOLCHAIN_ONLY)
  install(DIRECTORY include/stone 
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.def"
    PATTERN "*.h"
    PATTERN "config.h" EXCLUDE
	)

  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/stone
    DESTINATION include
    FILES_MATCHING
    PATTERN "CMakeFiles" EXCLUDE
    PATTERN "*.inc"
    PATTERN "*.h"
    )

  install(PROGRAMS utils/bash-autocomplete.sh
    DESTINATION share/stone
    )
endif()

add_definitions( -D_GNU_SOURCE )

option(STONE_BUILD_TOOLS
  "Build the Stone tools. If OFF, just generate build targets." ON)

add_subdirectory(include)

add_subdirectory(lib)
add_subdirectory(tools)
#add_subdirectory(tests)

