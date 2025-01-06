cmake_minimum_required(VERSION 3.12)
project(facefull_desktop_wx_example)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} main.cpp main.h frame.cpp frame.h)

find_package(wxWidgets COMPONENTS webview core base)
include(${wxWidgets_USE_FILE})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} -static-libgcc -static-libstdc++)

target_link_libraries(${PROJECT_NAME} facefull-bridge_static)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(SAMPLE_INSTALL_DIR ${CMAKE_SOURCE_DIR}/dist/bin)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${SAMPLE_INSTALL_DIR})

if (WIN32)
    install(FILES ${CMAKE_SOURCE_DIR}/3rdparty/win64/WebView2Loader.dll DESTINATION ${SAMPLE_INSTALL_DIR})
endif()
