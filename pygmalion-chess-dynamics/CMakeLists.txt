cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-dynamics)

set (pygmalion-chess-dynamics_VERSION_MAJOR 1)
set (pygmalion-chess-dynamics_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-dynamics/*.h)

add_library(pygmalion-chess-dynamics ${SOURCES} ${HEADERS} "include/pygmalion-chess-dynamics.h")
target_include_directories(pygmalion-chess-dynamics PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-chess-dynamics PUBLIC pygmalion-dynamics pygmalion-chess-mechanics)

add_executable(pygmalion-chess-dynamics-test "test/main.cpp")
target_link_libraries(pygmalion-chess-dynamics-test pygmalion-chess-dynamics)

install(TARGETS pygmalion-chess-dynamics EXPORT pygmalion-chess-dynamicsConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-chess-dynamicsConfig DESTINATION share/pygmalion-chess-dynamics/cmake)

export(TARGETS pygmalion-chess-dynamics FILE pygmalion-chess-dynamicsConfig.cmake)

