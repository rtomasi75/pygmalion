cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-dynamics)

set (pygmalion-dynamics_VERSION_MAJOR 1)
set (pygmalion-dynamics_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-dynamics/*.h)

add_library(pygmalion-dynamics ${SOURCES} ${HEADERS} "include/pygmalion-dynamics.h")
target_include_directories(pygmalion-dynamics PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-dynamics PUBLIC pygmalion-mechanics)

install(TARGETS pygmalion-dynamics EXPORT pygmalion-dynamicsConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-dynamicsConfig DESTINATION share/pygmalion-dynamics/cmake)

export(TARGETS pygmalion-dynamics FILE pygmalion-dynamicsConfig.cmake)

 