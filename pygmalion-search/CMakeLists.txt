cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-search)

set (pygmalion-search_VERSION_MAJOR 1)
set (pygmalion-search_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp) 
file(GLOB HEADERS include/pygmalion-search/*.h)

add_library(pygmalion-search ${SOURCES} ${HEADERS} "include/pygmalion-search.h")
target_include_directories(pygmalion-search PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-search PUBLIC pygmalion-evaluation)

install(TARGETS pygmalion-search EXPORT pygmalion-searchConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-searchConfig DESTINATION share/pygmalion-search/cmake)

export(TARGETS pygmalion-search FILE pygmalion-searchConfig.cmake)

 