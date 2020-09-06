
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
	constexpr const bool compact{ true };
	using T = uint_least_t<len>;
	T v1{ uint_t<len,compact>::random() };
	T v2 = ~v1;
	T v3 = v1 & v2;
	T v4 = v1 | v2;
	T v5{ 128 };
	T v6{ v5+v5 };
	std::int8_t s;
	std::cout << sizeof(long ) << std::endl;
	std::cout << "popc: " << T::populationCount_Intrinsic << std::endl;
	std::cout << "popc: " << T::populationCount_Intrinsic << std::endl;
	std::cout << "bits: " << v1 << std::endl;
	std::cout << "popc: " << v1.populationCount() << std::endl;
	std::cout << "bits: " << v5 << std::endl;
	std::cout << "sum2: " << v6 << std::endl;
	std::cout << "notb: " << v2 << std::endl;
	std::cout << "all0: " << v3 << std::endl;
	std::cout << "all0: " << v3 << std::endl;
	std::cout << "all1: " << v4 << std::endl;
	v4 ^= v1;
	std::cout << "bits: " << v4 << std::endl;
	std::cout << "size: " << sizeof(v1) << std::endl;
	std::cout << "bitc: " << v1.countBits << std::endl;
	std::cout << "word: " << v1.countBitsPerWord << std::endl;
	return 0;
	}