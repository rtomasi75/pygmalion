cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-frontend)

set (pygmalion-chess-frontend_VERSION_MAJOR 1)
set (pygmalion-chess-frontend_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-frontend/*.h)

add_library(pygmalion-chess-frontend ${SOURCES} ${HEADERS} "include/pygmalion-chess-frontend.h")
target_include_directories(pygmalion-chess-frontend PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-chess-frontend PUBLIC pygmalion-frontend pygmalion-chess-search)

add_executable(pygmalion-chess-frontend-test "test/main.cpp")
target_link_libraries(pygmalion-chess-frontend-test pygmalion-chess-frontend)

install(TARGETS pygmalion-chess-frontend EXPORT pygmalion-chess-frontendConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-chess-frontendConfig DESTINATION share/pygmalion-chess-frontend/cmake)

export(TARGETS pygmalion-chess-frontend FILE pygmalion-chess-frontendConfig.cmake)

