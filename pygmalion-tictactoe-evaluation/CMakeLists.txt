cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-evaluation)

set (pygmalion-tictactoe-evaluation_VERSION_MAJOR 1)
set (pygmalion-tictactoe-evaluation_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-evaluation/*.h)

add_library(pygmalion-tictactoe-evaluation ${SOURCES} ${HEADERS} "include/pygmalion-tictactoe-evaluation.h")
target_include_directories(pygmalion-tictactoe-evaluation PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-tictactoe-evaluation PUBLIC pygmalion-evaluation pygmalion-tictactoe-dynamics)

add_executable(pygmalion-tictactoe-evaluation-test "test/main.cpp")
target_link_libraries(pygmalion-tictactoe-evaluation-test pygmalion-tictactoe-evaluation)

install(TARGETS pygmalion-tictactoe-evaluation EXPORT pygmalion-tictactoe-evaluationConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-tictactoe-evaluationConfig DESTINATION share/pygmalion-tictactoe-evaluation/cmake)

export(TARGETS pygmalion-tictactoe-evaluation FILE pygmalion-tictactoe-evaluationConfig.cmake)

