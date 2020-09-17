cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-mechanics)

set (pygmalion-mechanics_VERSION_MAJOR 1)
set (pygmalion-mechanics_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-mechanics/*.h)

add_library(pygmalion-mechanics ${SOURCES} ${HEADERS} "include/pygmalion-mechanics.h")
target_include_directories(pygmalion-mechanics PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-mechanics PUBLIC pygmalion-state)

install(TARGETS pygmalion-mechanics EXPORT pygmalion-mechanicsConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-mechanicsConfig DESTINATION share/pygmalion-mechanics/cmake)

export(TARGETS pygmalion-mechanics FILE pygmalion-mechanicsConfig.cmake)

 