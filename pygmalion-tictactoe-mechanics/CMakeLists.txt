cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-mechanics)

set (pygmalion-tictactoe-mechanics_VERSION_MAJOR 1)
set (pygmalion-tictactoe-mechanics_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-mechanics/*.h)

add_library(pygmalion-tictactoe-mechanics ${SOURCES} ${HEADERS} "include/pygmalion-tictactoe-mechanics.h")
target_include_directories(pygmalion-tictactoe-mechanics PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-tictactoe-mechanics PUBLIC pygmalion-mechanics pygmalion-tictactoe-state)

add_executable(pygmalion-tictactoe-mechanics-test "test/main.cpp")
target_link_libraries(pygmalion-tictactoe-mechanics-test pygmalion-tictactoe-mechanics)

install(TARGETS pygmalion-tictactoe-mechanics EXPORT pygmalion-tictactoe-mechanicsConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-tictactoe-mechanicsConfig DESTINATION share/pygmalion-tictactoe-mechanics/cmake)

export(TARGETS pygmalion-tictactoe-mechanics FILE pygmalion-tictactoe-mechanicsConfig.cmake)

