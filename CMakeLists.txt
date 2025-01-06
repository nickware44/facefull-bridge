cmake_minimum_required(VERSION 3.12)
project(facefull-bridge VERSION 1.5.0 DESCRIPTION "Facefull bridge library")

set(CMAKE_CXX_STANDARD 14)

set(TARGET_SOURCE
        src/interface.cpp
        include/facefull/bridge/interface.h
        include/facefull/bridge/wx.hpp
        include/facefull/bridge/qt5webkit.hpp)

add_library(objlib OBJECT ${TARGET_SOURCE})
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE ON)

OPTION(FFB_EXAMPLES_BUILD "Build Facefull bridge examples" ON)

function(build_ffb LIBTYPE)
    message("Building ${LIBTYPE} variant")

    if(${LIBTYPE} STREQUAL shared)
        set(LIBTYPE "")
        add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:objlib>)
    elseif(${LIBTYPE} STREQUAL static)
        set(LIBTYPE "_static")
        add_library(${PROJECT_NAME}${LIBTYPE} STATIC $<TARGET_OBJECTS:objlib>)
    endif()

    set_target_properties(${PROJECT_NAME}${LIBTYPE} PROPERTIES
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR})

    include_directories(include/)
#    include_directories(3rdparty/)
endfunction()

build_ffb(shared)
build_ffb(static)

if (WIN32)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/dist/lib NAMELINK_COMPONENT)
else()
    install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/dist/lib NAMELINK_COMPONENT)
endif()

install(TARGETS ${PROJECT_NAME}_static ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/dist/lib NAMELINK_COMPONENT)
install(DIRECTORY include DESTINATION ${CMAKE_SOURCE_DIR}/dist)

if (FFB_EXAMPLES_BUILD)
    set(SAMPLE_INSTALL_DIR ${CMAKE_SOURCE_DIR}/dist/bin)

    install(DIRECTORY deps/facefull/dist/ DESTINATION ${SAMPLE_INSTALL_DIR}/../ui/facefull)
    add_subdirectory(examples/wxwidgets)
    if (NOT WIN32)
        add_subdirectory(examples/qt5)
    endif()
endif()