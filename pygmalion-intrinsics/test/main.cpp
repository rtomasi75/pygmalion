
#include <pygmalion-intrinsics.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace intrinsics;

int main(int argc, char* argv[])
{
	constexpr const intrinsics::compiler::flags comp{ intrinsics::compiler::computeFlags() };
	constexpr const intrinsics::cpu::flags cpu{ intrinsics::cpu::computeFlags() };
	std::srand(std::time(nullptr));
	constexpr const size_t len{ 56 };
	using T = uint_fast_t<len>;
	uint_fast_t<len> v1{ uint_fast_t<len>::random() };
	uint_least_t<len> v2{ uint_least_t<len>::random() };
	std::cout << "fast:  " << v1 << std::endl;
	std::cout << "least: " << v2 << std::endl;
	return 0;
	}