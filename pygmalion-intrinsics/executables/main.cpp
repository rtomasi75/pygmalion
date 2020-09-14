
#include <pygmalion-intrinsics.h>
#include "tests.h"

#include <iostream>

using namespace intrinsics;

int main(int argc, char* argv[])
{
	typename profiler::durationType durationCompact{ 0 };
	size_t operationsCompact(0);
	typename profiler::durationType durationFast{ 0 };
	size_t operationsFast(0);
	bool result{ true };
	//result &= intrinsics::test::bsr<24, true>(durationCompact, operationsCompact);
	result &= intrinsics::test::negation();
	//result &= intrinsics::test::inequality();
	uint_t<8, true> x = 12;
	//std::cout << x << std::endl;
	size_t bit;
//	std::cout << (x.bitscanForward(bit) ? bit : -1) << std::endl;
//	std::cout << (x.bitscanReverse(bit) ? bit : -1) << std::endl;
	return !result;
}