configure_file(${CMAKE_CURRENT_SOURCE_DIR}/agrio-cc.cpp.in ${CMAKE_BINARY_DIR}/agrio-cc.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/agrio-cpp.cpp.in ${CMAKE_BINARY_DIR}/agrio-cpp.cpp)

add_tool(agrio-cc)
add_tool(agrio-cpp)
