cmake_minimum_required(VERSION 3.12)
project(facefull_desktop_web_bridge_example)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++)

target_link_libraries(${PROJECT_NAME} facefull-bridge_static)
include_directories(${CMAKE_SOURCE_DIR}/include)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${INSTALL_DIR}/bin)
