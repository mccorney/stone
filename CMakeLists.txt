cmake_minimum_required(VERSION 3.15)
project(Stone)

# Make sure that our source directory is on the current cmake module path so that
# we can include cmake files from this directory.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

include(CMakeParseArguments)
include(StoneProperties)
include(StoneCore)
include(StoneTblGen)
include(StoneFormat)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_stone_build_properties(STONE)

message(STATUS "Stone version: 0.0.1")

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


#add_definitions( -D_GNU_SOURCE )

#add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(tools)
#add_subdirectory(tests)

