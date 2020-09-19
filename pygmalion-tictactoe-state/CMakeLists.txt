cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-state)

set (pygmalion-tictactoe-state_VERSION_MAJOR 1)
set (pygmalion-tictactoe-state_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-state/*.h)

add_library(pygmalion-tictactoe-state ${SOURCES} ${HEADERS} "include/pygmalion-tictactoe-state.h")
target_include_directories(pygmalion-tictactoe-state PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-tictactoe-state PUBLIC pygmalion-state)

add_executable(pygmalion-tictactoe-state-test "test/main.cpp")
target_link_libraries(pygmalion-tictactoe-state-test pygmalion-tictactoe-state)

install(TARGETS pygmalion-tictactoe-state EXPORT pygmalion-tictactoe-stateConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-tictactoe-stateConfig DESTINATION share/pygmalion-tictactoe-state/cmake)

export(TARGETS pygmalion-tictactoe-state FILE pygmalion-tictactoe-stateConfig.cmake)

