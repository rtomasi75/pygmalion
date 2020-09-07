
#include <pygmalion-intrinsics.h>
#include "tests.h"

#include <iostream>

using namespace intrinsics;

int main(int argc, char* argv[])
{
	bool result{ true };
	result &= intrinsics::test::assignments();
	return !result;
}