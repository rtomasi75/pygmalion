cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-frontend)

set (pygmalion-frontend_VERSION_MAJOR 1)
set (pygmalion-frontend_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp) 
file(GLOB HEADERS include/pygmalion-frontend/*.h)

add_library(pygmalion-frontend ${SOURCES} ${HEADERS} "include/pygmalion-frontend.h" "include/pygmalion-frontend/commands/command_option.h")
target_include_directories(pygmalion-frontend PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-frontend PUBLIC pygmalion-search)

install(TARGETS pygmalion-frontend EXPORT pygmalion-frontendConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-frontendConfig DESTINATION share/pygmalion-frontend/cmake)

export(TARGETS pygmalion-frontend FILE pygmalion-frontendConfig.cmake)

 