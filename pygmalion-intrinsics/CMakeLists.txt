cmake_minimum_required (VERSION 3.16)
include(GNUInstallDirs)

project (pygmalion-intrinsics)

set (pygmalion-intrinsics_VERSION_MAJOR 1)
set (pygmalion-intrinsics_VERSION_MINOR 0)

find_package (Threads REQUIRED)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/pygmalion-intrinsics/*.h)

add_library(pygmalion-intrinsics ${SOURCES} ${HEADERS} "include/pygmalion-intrinsics.h")
target_include_directories(pygmalion-intrinsics PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)
target_link_libraries(pygmalion-intrinsics PUBLIC Threads::Threads)

if(BUILD_TESTS)
    
message("-- building intrinsics tests")

add_executable(pygmalion-intrinsics-test-assignment "test/assignment.cpp")
target_link_libraries(pygmalion-intrinsics-test-assignment pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-assignment pygmalion-intrinsics-test-assignment)

add_executable(pygmalion-intrinsics-test-conversion "test/conversion.cpp")
target_link_libraries(pygmalion-intrinsics-test-conversion pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-conversion pygmalion-intrinsics-test-conversion)

add_executable(pygmalion-intrinsics-test-clearbits "test/clearbits.cpp")
target_link_libraries(pygmalion-intrinsics-test-clearbits pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-clearbits pygmalion-intrinsics-test-clearbits)

add_executable(pygmalion-intrinsics-test-setbits "test/setbits.cpp")
target_link_libraries(pygmalion-intrinsics-test-setbits pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-setbits pygmalion-intrinsics-test-setbits)

add_executable(pygmalion-intrinsics-test-extractbits "test/extractbits.cpp")
target_link_libraries(pygmalion-intrinsics-test-extractbits pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-extractbits pygmalion-intrinsics-test-extractbits)

add_executable(pygmalion-intrinsics-test-storebits "test/storebits.cpp")
target_link_libraries(pygmalion-intrinsics-test-storebits pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-storebits pygmalion-intrinsics-test-storebits)

add_executable(pygmalion-intrinsics-test-equality "test/equality.cpp")
target_link_libraries(pygmalion-intrinsics-test-equality pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-equality pygmalion-intrinsics-test-equality)

add_executable(pygmalion-intrinsics-test-inequality "test/inequality.cpp")
target_link_libraries(pygmalion-intrinsics-test-inequality pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-inequality pygmalion-intrinsics-test-inequality)

add_executable(pygmalion-intrinsics-test-lesser "test/lesser.cpp")
target_link_libraries(pygmalion-intrinsics-test-lesser pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-lesser pygmalion-intrinsics-test-lesser)

add_executable(pygmalion-intrinsics-test-greater_equal "test/greater_equal.cpp")
target_link_libraries(pygmalion-intrinsics-test-greater_equal pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-greater_equal pygmalion-intrinsics-test-greater_equal)

add_executable(pygmalion-intrinsics-test-lesser_equal "test/lesser_equal.cpp")
target_link_libraries(pygmalion-intrinsics-test-lesser_equal pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-lesser_equal pygmalion-intrinsics-test-lesser_equal)

add_executable(pygmalion-intrinsics-test-leftshift "test/leftshift.cpp")
target_link_libraries(pygmalion-intrinsics-test-leftshift pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-leftshift pygmalion-intrinsics-test-leftshift)

add_executable(pygmalion-intrinsics-test-rightshift "test/rightshift.cpp")
target_link_libraries(pygmalion-intrinsics-test-rightshift pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-rightshift pygmalion-intrinsics-test-rightshift)

add_executable(pygmalion-intrinsics-test-leftshift_inplace "test/leftshift_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-leftshift_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-leftshift_inplace pygmalion-intrinsics-test-leftshift_inplace)

add_executable(pygmalion-intrinsics-test-rightshift_inplace "test/rightshift_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-rightshift_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-rightshift_inplace pygmalion-intrinsics-test-rightshift_inplace)

add_executable(pygmalion-intrinsics-test-complement "test/complement.cpp")
target_link_libraries(pygmalion-intrinsics-test-complement pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-complement pygmalion-intrinsics-test-complement)

add_executable(pygmalion-intrinsics-test-disjunction "test/disjunction.cpp")
target_link_libraries(pygmalion-intrinsics-test-disjunction pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-disjunction pygmalion-intrinsics-test-disjunction)

add_executable(pygmalion-intrinsics-test-conjunction "test/conjunction.cpp")
target_link_libraries(pygmalion-intrinsics-test-conjunction pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-conjunction pygmalion-intrinsics-test-conjunction)

add_executable(pygmalion-intrinsics-test-exclusion "test/exclusion.cpp")
target_link_libraries(pygmalion-intrinsics-test-exclusion pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-exclusion pygmalion-intrinsics-test-exclusion)

add_executable(pygmalion-intrinsics-test-disjunction_inplace "test/disjunction_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-disjunction_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-disjunction_inplace pygmalion-intrinsics-test-disjunction_inplace)

add_executable(pygmalion-intrinsics-test-conjunction_inplace "test/conjunction_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-conjunction_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-conjunction_inplace pygmalion-intrinsics-test-conjunction_inplace)

add_executable(pygmalion-intrinsics-test-exclusion_inplace "test/exclusion_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-exclusion_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-exclusion_inplace pygmalion-intrinsics-test-exclusion_inplace)

add_executable(pygmalion-intrinsics-test-popcnt "test/popcnt.cpp")
target_link_libraries(pygmalion-intrinsics-test-popcnt pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-popcnt pygmalion-intrinsics-test-popcnt)

add_executable(pygmalion-intrinsics-test-bsf "test/bsf.cpp")
target_link_libraries(pygmalion-intrinsics-test-bsf pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-bsf pygmalion-intrinsics-test-bsf)

add_executable(pygmalion-intrinsics-test-bsr "test/bsr.cpp")
target_link_libraries(pygmalion-intrinsics-test-bsr pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-bsr pygmalion-intrinsics-test-bsr)

add_executable(pygmalion-intrinsics-test-prefix_increment "test/prefix_increment.cpp")
target_link_libraries(pygmalion-intrinsics-test-prefix_increment pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-prefix_increment pygmalion-intrinsics-test-prefix_increment)

add_executable(pygmalion-intrinsics-test-prefix_decrement "test/prefix_decrement.cpp")
target_link_libraries(pygmalion-intrinsics-test-prefix_decrement pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-prefix_decrement pygmalion-intrinsics-test-prefix_decrement)

add_executable(pygmalion-intrinsics-test-postfix_increment "test/postfix_increment.cpp")
target_link_libraries(pygmalion-intrinsics-test-postfix_increment pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-postfix_increment pygmalion-intrinsics-test-postfix_increment)

add_executable(pygmalion-intrinsics-test-postfix_decrement "test/postfix_decrement.cpp")
target_link_libraries(pygmalion-intrinsics-test-postfix_decrement pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-postfix_decrement pygmalion-intrinsics-test-postfix_decrement)

add_executable(pygmalion-intrinsics-test-addition "test/addition.cpp")
target_link_libraries(pygmalion-intrinsics-test-addition pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-addition pygmalion-intrinsics-test-addition)

add_executable(pygmalion-intrinsics-test-negation "test/negation.cpp")
target_link_libraries(pygmalion-intrinsics-test-negation pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-negation pygmalion-intrinsics-test-negation)

add_executable(pygmalion-intrinsics-test-subtraction "test/subtraction.cpp")
target_link_libraries(pygmalion-intrinsics-test-subtraction pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-subtraction pygmalion-intrinsics-test-subtraction)

add_executable(pygmalion-intrinsics-test-multiplication "test/multiplication.cpp")
target_link_libraries(pygmalion-intrinsics-test-multiplication pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-multiplication pygmalion-intrinsics-test-multiplication)

add_executable(pygmalion-intrinsics-test-division "test/division.cpp")
target_link_libraries(pygmalion-intrinsics-test-division pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-division pygmalion-intrinsics-test-division)

add_executable(pygmalion-intrinsics-test-modulus "test/modulus.cpp")
target_link_libraries(pygmalion-intrinsics-test-modulus pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-modulus pygmalion-intrinsics-test-modulus)

add_executable(pygmalion-intrinsics-test-addition_inplace "test/addition_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-addition_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-addition_inplace pygmalion-intrinsics-test-addition_inplace)

add_executable(pygmalion-intrinsics-test-subtraction_inplace "test/subtraction_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-subtraction_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-subtraction_inplace pygmalion-intrinsics-test-subtraction_inplace)

add_executable(pygmalion-intrinsics-test-multiplication_inplace "test/multiplication_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-multiplication_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-multiplication_inplace pygmalion-intrinsics-test-multiplication_inplace)

add_executable(pygmalion-intrinsics-test-division_inplace "test/division_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-division_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-division_inplace pygmalion-intrinsics-test-division_inplace)

add_executable(pygmalion-intrinsics-test-modulus_inplace "test/modulus_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-modulus_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-modulus_inplace pygmalion-intrinsics-test-modulus_inplace)

add_executable(pygmalion-intrinsics-test-bittest "test/bittest.cpp")
target_link_libraries(pygmalion-intrinsics-test-bittest pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-bittest pygmalion-intrinsics-test-bittest)

add_executable(pygmalion-intrinsics-test-bitset "test/bitset.cpp")
target_link_libraries(pygmalion-intrinsics-test-bitset pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-bitset pygmalion-intrinsics-test-bitset)

add_executable(pygmalion-intrinsics-test-bitclear "test/bitclear.cpp")
target_link_libraries(pygmalion-intrinsics-test-bitclear pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-bitclear pygmalion-intrinsics-test-bitclear)

add_executable(pygmalion-intrinsics-test-pext "test/pext.cpp")
target_link_libraries(pygmalion-intrinsics-test-pext pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-pext pygmalion-intrinsics-test-pext)

add_executable(pygmalion-intrinsics-test-pdep "test/pdep.cpp")
target_link_libraries(pygmalion-intrinsics-test-pdep pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-pdep pygmalion-intrinsics-test-pdep)

add_executable(pygmalion-intrinsics-test-score_assignment "test/score_assignment.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_assignment pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_assignment pygmalion-intrinsics-test-score_assignment)

add_executable(pygmalion-intrinsics-test-score_conversion "test/score_conversion.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_conversion pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_conversion pygmalion-intrinsics-test-score_conversion)

add_executable(pygmalion-intrinsics-test-score_equality "test/score_equality.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_equality pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_equality pygmalion-intrinsics-test-score_equality)

add_executable(pygmalion-intrinsics-test-score_inequality "test/score_inequality.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_inequality pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_inequality pygmalion-intrinsics-test-score_inequality)

add_executable(pygmalion-intrinsics-test-score_greater "test/score_greater.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_greater pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_greater pygmalion-intrinsics-test-score_greater)

add_executable(pygmalion-intrinsics-test-score_less "test/score_less.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_less pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_less pygmalion-intrinsics-test-score_less)

add_executable(pygmalion-intrinsics-test-score_greaterequal "test/score_greaterequal.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_greaterequal pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_greaterequal pygmalion-intrinsics-test-score_greaterequal)

add_executable(pygmalion-intrinsics-test-score_lessequal "test/score_lessequal.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_lessequal pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_lessequal pygmalion-intrinsics-test-score_lessequal)

add_executable(pygmalion-intrinsics-test-score_addition "test/score_addition.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_addition pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_addition pygmalion-intrinsics-test-score_addition)

add_executable(pygmalion-intrinsics-test-score_subtraction "test/score_subtraction.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_subtraction pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_subtraction pygmalion-intrinsics-test-score_subtraction)

add_executable(pygmalion-intrinsics-test-score_addition_inplace "test/score_addition_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_addition_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_addition_inplace pygmalion-intrinsics-test-score_addition_inplace)

add_executable(pygmalion-intrinsics-test-score_subtraction_inplace "test/score_subtraction_inplace.cpp")
target_link_libraries(pygmalion-intrinsics-test-score_subtraction_inplace pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-score_subtraction_inplace pygmalion-intrinsics-test-score_subtraction_inplace)

add_executable(pygmalion-intrinsics-test-sort "test/sort.cpp")
target_link_libraries(pygmalion-intrinsics-test-sort pygmalion-intrinsics)
add_test(pygmalion-intrinsics-test-sort pygmalion-intrinsics-test-sort)

else()
endif()

install(TARGETS pygmalion-intrinsics EXPORT pygmalion-intrinsicsConfig
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT pygmalion-intrinsicsConfig DESTINATION share/pygmalion-intrinsics/cmake)

export(TARGETS pygmalion-intrinsics FILE pygmalion-intrinsicsConfig.cmake)

 