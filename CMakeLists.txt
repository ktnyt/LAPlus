cmake_minimum_required(VERSION 2.8)

option(test "Build all tests." OFF)

set(PROJECT_NAME LAPlus)
project(${PROJECT_NAME})
set(LAPLUS_VERSION_MAJOR 1)
set(LAPLUS_VERSION_MINOR 0)
set(LAPLUS_VERSION_PATCH 0)

# Enable C++11
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" STD_CXX11)
if(STD_CXX11)
  add_definitions("-std=c++11")
else()
  add_definitions("-std=c++0x")
endif()

# Include directories for LAPlus
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(external)
add_subdirectory(tests)

install(FILES include/laplus.hpp DESTINATION include)
