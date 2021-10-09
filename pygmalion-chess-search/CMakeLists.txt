cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-search)

set (pygmalion-chess-search_VERSION_MAJOR 1)
set (pygmalion-chess-search_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-search/*.h)

add_library(pygmalion-chess-search ${SOURCES} ${HEADERS} "include/pygmalion-chess-search.h")
target_include_directories(pygmalion-chess-search PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-chess-search PUBLIC pygmalion-search pygmalion-chess-evaluation)


if(BUILD_MODULE_ENGINES)
       
message("-- building chess search engine")

add_executable(pygmalion-chess-search-engine "test/engine.cpp")
target_link_libraries(pygmalion-chess-search-engine pygmalion-chess-search)

else()
endif()

install(TARGETS pygmalion-chess-search EXPORT pygmalion-chess-searchConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-chess-searchConfig DESTINATION share/pygmalion-chess-search/cmake)

export(TARGETS pygmalion-chess-search FILE pygmalion-chess-searchConfig.cmake)

