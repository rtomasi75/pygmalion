cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-mechanics)

set (pygmalion-chess-mechanics_VERSION_MAJOR 1)
set (pygmalion-chess-mechanics_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-mechanics/*.h)

add_library(pygmalion-chess-mechanics ${SOURCES} ${HEADERS} "include/pygmalion-chess-mechanics.h")
target_include_directories(pygmalion-chess-mechanics PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-chess-mechanics PUBLIC pygmalion-mechanics pygmalion-chess-state)

add_executable(pygmalion-chess-mechanics-test "test/main.cpp")
target_link_libraries(pygmalion-chess-mechanics-test pygmalion-chess-mechanics)

install(TARGETS pygmalion-chess-mechanics EXPORT pygmalion-chess-mechanicsConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-chess-mechanicsConfig DESTINATION share/pygmalion-chess-mechanics/cmake)

export(TARGETS pygmalion-chess-mechanics FILE pygmalion-chess-mechanicsConfig.cmake)

