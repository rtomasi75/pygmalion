
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
	result &= intrinsics::test::assignments();
	result &= intrinsics::test::popcnt();
	std::cout << "================" << std::endl;
	if (result)
		std::cout << "PASSED UNIT TEST" << std::endl;
	else
		std::cout << "FAILED UNIT TEST" << std::endl;
	std::cout << "================" << std::endl;
	return !result;
}