cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-tictactoe)

set (pygmalion-tictactoe_VERSION_MAJOR 1)
set (pygmalion-tictactoe_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-tictactoe/*.h)

add_library(pygmalion-tictactoe ${SOURCES} ${HEADERS} include/pygmalion-tictactoe.h)
target_include_directories(pygmalion-tictactoe PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-tictactoe PUBLIC pygmalion-core)

add_executable(pygmalion-tictactoe-test "test/main.cpp")
target_link_libraries(pygmalion-tictactoe-test pygmalion-tictactoe)

install(TARGETS pygmalion-tictactoe EXPORT pygmalion-tictactoeConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-tictactoeConfig DESTINATION share/pygmalion-tictactoe/cmake)

export(TARGETS pygmalion-tictactoe FILE pygmalion-tictactoeConfig.cmake)

 