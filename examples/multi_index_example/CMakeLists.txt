include(ExternalProject)
# if no cdt root is given use default path
if(AGRIO_CDT_ROOT STREQUAL "" OR NOT AGRIO_CDT_ROOT)
   find_package(agrio.cdt)
endif()

ExternalProject_Add(
   multi_index_example_project
   SOURCE_DIR ${CMAKE_SOURCE_DIR}/src
   BINARY_DIR ${CMAKE_BINARY_DIR}/multi_index_example
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${AGRIO_CDT_ROOT}/lib/cmake/agrio.cdt/AgrioWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)