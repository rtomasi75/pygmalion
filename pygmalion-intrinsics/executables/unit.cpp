
#include <pygmalion-intrinsics.h>
#include "tests.h"

#include <iostream>

using namespace intrinsics;

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
	result &= intrinsics::test::disjunction();
	result &= intrinsics::test::conjunction();
	result &= intrinsics::test::exclusion();
	result &= intrinsics::test::popcnt();
	result &= intrinsics::test::bsf();
	result &= intrinsics::test::addition();
	result &= intrinsics::test::subtraction();
	result &= intrinsics::test::multiplication();
	std::cout << "================" << std::endl;
	if (result)
		std::cout << "PASSED UNIT TEST" << std::endl;
	else
		std::cout << "FAILED UNIT TEST" << std::endl;
	std::cout << "================" << std::endl;
	return !result;
}