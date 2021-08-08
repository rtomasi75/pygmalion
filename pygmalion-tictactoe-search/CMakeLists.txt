cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-search)

set (pygmalion-tictactoe-search_VERSION_MAJOR 1)
set (pygmalion-tictactoe-search_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-search/*.h)

add_library(pygmalion-tictactoe-search ${SOURCES} ${HEADERS} "include/pygmalion-tictactoe-search.h")
target_include_directories(pygmalion-tictactoe-search PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-tictactoe-search PUBLIC pygmalion-search pygmalion-tictactoe-evaluation)

add_executable(pygmalion-tictactoe-search-test "test/main.cpp")
target_link_libraries(pygmalion-tictactoe-search-test pygmalion-tictactoe-search)

install(TARGETS pygmalion-tictactoe-search EXPORT pygmalion-tictactoe-searchConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-tictactoe-searchConfig DESTINATION share/pygmalion-tictactoe-search/cmake)

export(TARGETS pygmalion-tictactoe-search FILE pygmalion-tictactoe-searchConfig.cmake)

