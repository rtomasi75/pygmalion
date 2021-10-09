cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-evaluation)

set (pygmalion-chess-evaluation_VERSION_MAJOR 1)
set (pygmalion-chess-evaluation_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-evaluation/*.h)

add_library(pygmalion-chess-evaluation ${SOURCES} ${HEADERS} "include/pygmalion-chess-evaluation.h")
target_include_directories(pygmalion-chess-evaluation PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-chess-evaluation PUBLIC pygmalion-evaluation pygmalion-chess-dynamics)

if(BUILD_MODULE_ENGINES)
       
message("-- building chess evaluation engine")

add_executable(pygmalion-chess-evaluation-engine "test/engine.cpp")
target_link_libraries(pygmalion-chess-evaluation-engine pygmalion-chess-evaluation)

else()
endif()

install(TARGETS pygmalion-chess-evaluation EXPORT pygmalion-chess-evaluationConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-chess-evaluationConfig DESTINATION share/pygmalion-chess-evaluation/cmake)

export(TARGETS pygmalion-chess-evaluation FILE pygmalion-chess-evaluationConfig.cmake)

