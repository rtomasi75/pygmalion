cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-intrinsics)

set (pygmalion-intrinsics_VERSION_MAJOR 1)
set (pygmalion-intrinsics_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-intrinsics/*.h)

add_library(pygmalion-intrinsics ${SOURCES} ${HEADERS} include/pygmalion-intrinsics.h)
target_include_directories(pygmalion-intrinsics PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)

add_executable(pygmalion-intrinsics-main "executables/main.cpp")
target_link_libraries(pygmalion-intrinsics-main pygmalion-intrinsics)
#target_compile_options(pygmalion-intrinsics-main PRIVATE /FAs)

add_executable(pygmalion-intrinsics-test "executables/unit.cpp")
target_link_libraries(pygmalion-intrinsics-test pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test pygmalion-intrinsics-test)

install(TARGETS pygmalion-intrinsics EXPORT pygmalion-intrinsicsConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-intrinsicsConfig DESTINATION share/pygmalion-intrinsics/cmake)

export(TARGETS pygmalion-intrinsics FILE pygmalion-intrinsicsConfig.cmake)

 