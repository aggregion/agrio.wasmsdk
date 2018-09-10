cmake_minimum_required(VERSION 3.5)
project(abigen_test_example VERSION 1.0.0)

# if no wasm root is given use default path
if(AGRIO_CDT_ROOT STREQUAL "" OR NOT AGRIO_CDT_ROOT)
   set(AGRIO_CDT_ROOT "/usr/local/agrio.cdt")
endif()

# append the path to the module to include
list(APPEND CMAKE_MODULE_PATH ${AGRIO_CDT_ROOT}/lib/cmake)

#include the toolchain cmake
include(AgrioWasmToolchain)

set(CMAKE_CXX_FLAGS " -abigen ${CMAKE_CXX_FLAGS} ")
add_executable( test.wasm test.cpp )
