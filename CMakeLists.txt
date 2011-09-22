cmake_minimum_required(VERSION 2.8)
project(libgpnread)

option(BUILD_SHARED_LIBS "Build a shared library. When off, a static library is built." ON)

find_package(Boost 1.40 COMPONENTS unit_test_framework REQUIRED)

###################
# library sources #
###################

set(sources
  src/gpnread.cpp
  src/master_data.cpp
  src/utils.cpp
)
include_directories(${Boost_INCLUDE_DIRS})
add_library(gpnread ${sources})

#########
# tests #
#########

set(test_sources
  tests/utils.cpp
)
include_directories(${PROJECT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
add_executable(tests ${test_sources})
target_link_libraries(tests gpnread ${Boost_LIBRARIES})

