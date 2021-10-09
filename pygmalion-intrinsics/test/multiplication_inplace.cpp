
#include <pygmalion-intrinsics.h>
#include <pygmalion-intrinsics/tests.h>

#include <iostream>

using namespace pygmalion;

int main(int argc, char* argv[])
{
	std::cout << "===============================" << std::endl;
	std::cout << "UNIT TEST: pygmalion-intrinsics" << std::endl;
	std::cout << "===============================" << std::endl;
	bool result{ true };
	result &= intrinsics::test::multiplication_inplace(std::cout);
	std::cout << "================" << std::endl;
	if (result)
		std::cout << "PASSED UNIT TEST" << std::endl;
	else
		std::cout << "FAILED UNIT TEST" << std::endl;
	std::cout << "================" << std::endl;
	return !result;
}