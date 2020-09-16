cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-state)

set (pygmalion-state_VERSION_MAJOR 1)
set (pygmalion-state_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-state/*.h)

add_library(pygmalion-state ${SOURCES} ${HEADERS} "include/pygmalion-state.h")
target_include_directories(pygmalion-state PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-state PUBLIC pygmalion-intrinsics)

add_executable(pygmalion-state-engine "test/engine.cpp")
target_link_libraries(pygmalion-state-engine pygmalion-state)

install(TARGETS pygmalion-state EXPORT pygmalion-stateConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-stateConfig DESTINATION share/pygmalion-state/cmake)

export(TARGETS pygmalion-state FILE pygmalion-stateConfig.cmake)

 