cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-dynamics)

set (pygmalion-tictactoe-dynamics_VERSION_MAJOR 1)
set (pygmalion-tictactoe-dynamics_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-dynamics/*.h)

add_library(pygmalion-tictactoe-dynamics ${SOURCES} ${HEADERS} "include/pygmalion-tictactoe-dynamics.h")
target_include_directories(pygmalion-tictactoe-dynamics PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-tictactoe-dynamics PUBLIC pygmalion-dynamics pygmalion-tictactoe-mechanics)

if(BUILD_MODULE_ENGINES)
       
message("-- building tic tac toe dynamics engine")

add_executable(pygmalion-tictactoe-dynamics-engine "test/engine.cpp")
target_link_libraries(pygmalion-tictactoe-dynamics-engine pygmalion-tictactoe-dynamics)

else()
endif()

install(TARGETS pygmalion-tictactoe-dynamics EXPORT pygmalion-tictactoe-dynamicsConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-tictactoe-dynamicsConfig DESTINATION share/pygmalion-tictactoe-dynamics/cmake)

export(TARGETS pygmalion-tictactoe-dynamics FILE pygmalion-tictactoe-dynamicsConfig.cmake)

