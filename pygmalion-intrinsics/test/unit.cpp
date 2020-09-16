
#include <pygmalion-intrinsics.h>
#include <pygmalion-intrinsics/tests.h>

#include <iostream>

using namespace pygmalion;

int main(int argc, char* argv[])
{
	bool result{ true };
	std::cout << "===============================" << std::endl;
	std::cout << "UNIT TEST: pygmalion-intrinsics" << std::endl;
	std::cout << "===============================" << std::endl;
	result &= intrinsics::test::assignment();
	result &= intrinsics::test::conversion();
	result &= intrinsics::test::equality();
	result &= intrinsics::test::inequality();
	result &= intrinsics::test::greater();
	result &= intrinsics::test::lesser();
	result &= intrinsics::test::greater_equal();
	result &= intrinsics::test::lesser_equal();
	result &= intrinsics::test::leftshift();
	result &= intrinsics::test::rightshift();
	result &= intrinsics::test::leftshift_inplace();
	result &= intrinsics::test::rightshift_inplace();
	result &= intrinsics::test::complement();
	result &= intrinsics::test::disjunction();
	result &= intrinsics::test::conjunction();
	result &= intrinsics::test::exclusion();
	result &= intrinsics::test::disjunction_inplace();
	result &= intrinsics::test::conjunction_inplace();
	result &= intrinsics::test::exclusion_inplace();
	result &= intrinsics::test::popcnt();
	result &= intrinsics::test::bsf();
	result &= intrinsics::test::bsr();
	result &= intrinsics::test::prefix_increment();
	result &= intrinsics::test::prefix_decrement();
	result &= intrinsics::test::postfix_increment();
	result &= intrinsics::test::postfix_decrement();
	result &= intrinsics::test::addition();
	result &= intrinsics::test::negation();
	result &= intrinsics::test::subtraction();
	result &= intrinsics::test::multiplication();
	result &= intrinsics::test::division();
	result &= intrinsics::test::modulus();
	result &= intrinsics::test::addition_inplace();
	result &= intrinsics::test::subtraction_inplace();
	result &= intrinsics::test::multiplication_inplace();
	result &= intrinsics::test::division_inplace();
	result &= intrinsics::test::modulus_inplace();
	result &= intrinsics::test::bittest();
	result &= intrinsics::test::bitset();
	result &= intrinsics::test::bitclear();
	result &= intrinsics::test::pext();
	result &= intrinsics::test::pdep();
	std::cout << "================" << std::endl;
	if (result)
		std::cout << "PASSED UNIT TEST" << std::endl;
	else
		std::cout << "FAILED UNIT TEST" << std::endl;
	std::cout << "================" << std::endl;
	return !result;
}