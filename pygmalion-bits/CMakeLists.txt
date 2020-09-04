cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-bits)

set (pygmalion-bits_VERSION_MAJOR 1)
set (pygmalion-bits_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-bits/*.h)

add_library(pygmalion-bits ${SOURCES} ${HEADERS} include/pygmalion-bits.h)
target_include_directories(pygmalion-bits PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-bits PUBLIC pygmalion-intrinsics)

add_executable(pygmalion-bits-test "test/main.cpp")
target_link_libraries(pygmalion-bits-test pygmalion-bits)

install(TARGETS pygmalion-bits EXPORT pygmalion-bitsConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-bitsConfig DESTINATION share/pygmalion-bits/cmake)

export(TARGETS pygmalion-bits FILE pygmalion-bitsConfig.cmake)

 