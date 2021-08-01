cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-evaluation)

set (pygmalion-evaluation_VERSION_MAJOR 1)
set (pygmalion-evaluation_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp) 
file(GLOB HEADERS include/pygmalion-evaluation/*.h)

add_library(pygmalion-evaluation ${SOURCES} ${HEADERS} "include/pygmalion-evaluation.h")
target_include_directories(pygmalion-evaluation PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-evaluation PUBLIC pygmalion-chess-dynamics)

install(TARGETS pygmalion-evaluation EXPORT pygmalion-evaluationConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-evaluationConfig DESTINATION share/pygmalion-evaluation/cmake)

export(TARGETS pygmalion-evaluation FILE pygmalion-evaluationConfig.cmake)

 