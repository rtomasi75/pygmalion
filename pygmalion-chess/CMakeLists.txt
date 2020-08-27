cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-chess)

set (pygmalion-chess_VERSION_MAJOR 1)
set (pygmalion-chess_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-chess/*.h)

add_library(pygmalion-chess ${SOURCES} ${HEADERS} include/pygmalion-chess.h)
target_include_directories(pygmalion-chess PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-chess PUBLIC pygmalion-core)

add_executable(pygmalion-chess-test "test/main.cpp")
target_link_libraries(pygmalion-chess-test pygmalion-chess pygmalion-core)

install(TARGETS pygmalion-chess EXPORT pygmalion-chessConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-chessConfig DESTINATION share/pygmalion-chess/cmake)

export(TARGETS pygmalion-chess FILE pygmalion-chessConfig.cmake)

 