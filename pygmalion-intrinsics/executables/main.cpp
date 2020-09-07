
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
	result &= intrinsics::test::conjunction<53,true>(durationFast, operationsFast);
	return !result;
}