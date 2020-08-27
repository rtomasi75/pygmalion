cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-core)

set (pygmalion-core_VERSION_MAJOR 1)
set (pygmalion-core_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-core/*.h)

add_library(pygmalion-core ${SOURCES} ${HEADERS} include/pygmalion-core.h)
target_include_directories(pygmalion-core PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)

add_executable(pygmalion-core-test "test/main.cpp")
target_link_libraries(pygmalion-core-test pygmalion-core)

install(TARGETS pygmalion-core EXPORT pygmalion-coreConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-coreConfig DESTINATION share/pygmalion-core/cmake)

export(TARGETS pygmalion-core FILE pygmalion-coreConfig.cmake)

 