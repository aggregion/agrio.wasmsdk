file(GLOB HEADERS "*.hpp"
                  "*.h")

add_library(agrio
            agriolib.cpp
            crypto.cpp
            ${HEADERS})

add_library(agrio_malloc
            malloc.cpp
            ${HEADERS})

add_library(agrio_dsm
            simple_malloc.cpp
            ${HEADERS})

add_library(agrio_cmem
            memory.cpp
            ${HEADERS})

add_native_library(native_agrio
                   agriolib.cpp
                   crypto.cpp
                   malloc.cpp
                   ${HEADERS})

set_target_properties(agrio_malloc PROPERTIES LINKER_LANGUAGE C)

target_include_directories(agrio PUBLIC
                                 ${CMAKE_SOURCE_DIR}/libc/musl/include
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/internal
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/crypt
                                 ${CMAKE_SOURCE_DIR}/libc/musl/arch/agr
                                 ${CMAKE_SOURCE_DIR}/libcxx/include
                                 ${CMAKE_SOURCE_DIR}
                                 ${CMAKE_SOURCE_DIR}/boost/include)

target_link_libraries( agrio c c++ )
add_dependencies( native_agrio agrio )

add_custom_command( TARGET agrio POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:agrio> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET agrio_malloc POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:agrio_malloc> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET agrio_dsm POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:agrio_dsm> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET agrio_cmem POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:agrio_cmem> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET native_agrio POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:native_agrio> ${BASE_BINARY_DIR}/lib )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../agriolib DESTINATION ${BASE_BINARY_DIR}/include FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
