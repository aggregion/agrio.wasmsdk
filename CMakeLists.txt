cmake_minimum_required(VERSION 3.5)
project(agrio_cdt)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 4)
set(VERSION_PATCH 1)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
   message(WARNING "CMAKE_INSTALL_PREFIX is set to default path of ${CMAKE_INSTALL_PREFIX}, resetting to ${CMAKE_INSTALL_PREFIX}/agrio.cdt")
   set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/agrio.cdt")
elseif ("${CMAKE_INSTALL_PREFIX}" STREQUAL "/usr/local")
   message(WARNING "CMAKE_INSTALL_PREFIX is explicitly set to /usr/local. This is not recommended.")
endif()

include(GNUInstallDirs)

include(ClangExternalProject.txt)
include(ToolsExternalProject.txt)

add_subdirectory(external)

set(WASM_SDK_BUILD true)

### Configure the AgrioWasmToolchain.cmakes
set(CDT_ROOT_DIR ${CMAKE_BINARY_DIR})
configure_file(${CMAKE_SOURCE_DIR}/modules/agrio.cdt-config.cmake ${CMAKE_BINARY_DIR}/lib/cmake/agrio.cdt/agrio.cdt-config.cmake @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/modules/AgrioWasmToolchain.cmake.in ${CMAKE_BINARY_DIR}/lib/cmake/agrio.cdt/AgrioWasmToolchain.cmake @ONLY)

set(CDT_ROOT_DIR ${CMAKE_INSTALL_PREFIX})
configure_file(${CMAKE_SOURCE_DIR}/modules/agrio.cdt-config.cmake ${CMAKE_BINARY_DIR}/modules/agrio.cdt-config.cmake @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/modules/agrio.cdt-config.cmake DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/agrio.cdt)
configure_file(${CMAKE_SOURCE_DIR}/modules/AgrioWasmToolchain.cmake.in ${CMAKE_BINARY_DIR}/modules/AgrioWasmToolchain.cmake @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/modules/AgrioWasmToolchain.cmake DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/agrio.cdt)

set(CDT_ROOT_DIR "_PREFIX_")
configure_file(${CMAKE_SOURCE_DIR}/modules/AgrioWasmToolchain.cmake.in ${CMAKE_BINARY_DIR}/modules/AgrioWasmToolchainPackage.cmake @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/modules/agrio.cdt-config.cmake ${CMAKE_BINARY_DIR}/modules/agrio.cdt-config.cmake.package @ONLY)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/lib/cmake/agrio.cdt")
include(AgrioWasmToolchain)

add_subdirectory(libraries)

include(InstallClang.txt)

configure_file(${CMAKE_SOURCE_DIR}/agrio.imports.in ${CMAKE_BINARY_DIR}/agrio.imports COPYONLY)
install(FILES ${CMAKE_BINARY_DIR}/agrio.imports DESTINATION ${CMAKE_INSTALL_PREFIX})

configure_file(${CMAKE_SOURCE_DIR}/scripts/ricardagr/ricardagr.py ${CMAKE_BINARY_DIR}/scripts/ricardagr.py COPYONLY)
install(FILES ${CMAKE_BINARY_DIR}/scripts/ricardagr.py DESTINATION ${CMAKE_INSTALL_PREFIX}/scripts)

set(VENDOR "block.one")
set(PROJECT_NAME "agrio.cdt")
set(DESC "Toolchain and supporting tools for the AGR.IO platform")
set(URL "https://github.com/aggregion/agrio.cdt")
set(EMAIL "support@block.one")
configure_file(${CMAKE_SOURCE_DIR}/scripts/generate_package.sh.in ${CMAKE_BINARY_DIR}/packages/generate_package.sh @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/scripts/generate_deb.sh ${CMAKE_BINARY_DIR}/packages/generate_deb.sh COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/scripts/generate_bottle.sh ${CMAKE_BINARY_DIR}/packages/generate_bottle.sh COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/scripts/generate_rpm.sh ${CMAKE_BINARY_DIR}/packages/generate_rpm.sh COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/scripts/generate_tarball.sh ${CMAKE_BINARY_DIR}/packages/generate_tarball.sh COPYONLY)

# add licenses
configure_file(${CMAKE_SOURCE_DIR}/agrio_llvm/LICENSE.TXT ${CMAKE_BINARY_DIR}/licenses/llvm.license COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/libraries/boost/boost.license ${CMAKE_BINARY_DIR}/licenses/boost.license COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/external/wabt/LICENSE ${CMAKE_BINARY_DIR}/licenses/wabt.license COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/tools/jsoncons/LICENSE ${CMAKE_BINARY_DIR}/licenses/jsoncons.license COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/LICENSE ${CMAKE_BINARY_DIR}/licenses/agrio.cdt.license COPYONLY)
