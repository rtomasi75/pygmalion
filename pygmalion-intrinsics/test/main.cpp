
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
	constexpr const size_t len{ 16 };
	using T = uint_fast_t<len>;
	uint_least_t<len> v1{ 65535 };
	uint_least_t<len> v2{ 1 };
	uint_least_t<len> v3{ uint_fast_t<len>(v2) };
	std::cout << "v1:    " << v1 << " = " << (unsigned int)v1 << std::endl;
	std::cout << "v2:    " << v2 << " = " << (unsigned int)v2 << std::endl;
	std::cout << "v1+v2: " << (v1+v2) << " = " << (unsigned int)(v1 + v2) << std::endl;
	std::cout << (unsigned int)v1 << " + " << (unsigned int)v2 << " = " << (unsigned int)(v1+v2) << std::endl;
	return 0;
}