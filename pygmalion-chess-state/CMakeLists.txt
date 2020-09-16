cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-state)

set (pygmalion-chess-state_VERSION_MAJOR 1)
set (pygmalion-chess-state_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-state/*.h)

add_library(pygmalion-chess-state ${SOURCES} ${HEADERS} "include/pygmalion-chess-state.h")
target_include_directories(pygmalion-chess-state PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-chess-state PUBLIC pygmalion-state)

add_executable(pygmalion-chess-state-test "test/main.cpp")
target_link_libraries(pygmalion-chess-state-test pygmalion-chess-state)

install(TARGETS pygmalion-chess-state EXPORT pygmalion-chess-stateConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-chess-stateConfig DESTINATION share/pygmalion-chess-state/cmake)

export(TARGETS pygmalion-chess-state FILE pygmalion-chess-stateConfig.cmake)

