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
include(StoneTests)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_stone_properties(STONE)

set_stone_version()
message(STATUS "stone compiler version: ${STONE_VERSION}")

install_stone()


add_definitions( -D_GNU_SOURCE )

option(STONE_BUILD_TOOLS
  "Build the Stone tools. If OFF, just generate build targets." ON)


#add_definitions( -D_GNU_SOURCE )

#add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(tools)
#add_subdirectory(tests)

