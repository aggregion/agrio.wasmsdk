cmake_minimum_required(VERSION 3.5)
project(hello_example VERSION 1.0.0)

# if no wasm root is given use default path
if(AGRIO_CDT_ROOT STREQUAL "" OR NOT AGRIO_CDT_ROOT)
   set(AGRIO_CDT_ROOT ${CMAKE_INSTALL_PREFIX}/agrio.cdt)
endif()

# append the path to the module to include
list(APPEND CMAKE_MODULE_PATH ${AGRIO_CDT_ROOT}/lib/cmake)

#include the toolchain cmake
include(AgrioWasmToolchain)

add_executable( hello.wasm hello.cpp )
