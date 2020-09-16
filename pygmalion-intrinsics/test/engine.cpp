
#include <pygmalion-intrinsics.h>

#include <iostream>

using namespace pygmalion;
using namespace pygmalion::intrinsics;

int main(int argc, char* argv[])
{
	engine eng(std::cin, std::cout);
	eng.run();
	return 0;
}