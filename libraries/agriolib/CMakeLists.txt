file(GLOB HEADERS "*.hpp"
                  "*.h")

add_library(agrio
            agriolib.cpp
            crypto.cpp
            ${HEADERS})

target_include_directories(agrio PUBLIC
                                 "$<BUILD_INTERFACE:${STANDARD_INCLUDES}>"
                                 $<INSTALL_INTERFACE:${CMAKE_INSTALL_FULL_INCLUDEDIR}>)

target_link_libraries( agrio c c++ )

install(TARGETS agrio EXPORT AgrioLib
   LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
   ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../agriolib DESTINATION ${CMAKE_BINARY_DIR}/include FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
add_custom_command( TARGET agrio POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:agrio> ${CMAKE_BINARY_DIR}/lib )
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../agriolib DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
