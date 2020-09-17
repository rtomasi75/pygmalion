
#include <pygmalion-intrinsics.h>
#include <pygmalion-intrinsics/tests.h>

#include <iostream>

using namespace pygmalion;

int main(int argc, char* argv[])
{
	typename profiler::durationType durationCompact{ 0 };
	size_t operationsCompact(0);
	typename profiler::durationType durationFast{ 0 };
	size_t operationsFast(0);

	bool result{ true };
	result &= intrinsics::test::extractbits(std::cout);
	//result &= intrinsics::test::extractbits<53, true>(std::cout, durationFast, operationsFast);
/*


	std::cout << "===============================" << std::endl;
	std::cout << "UNIT TEST: pygmalion-intrinsics" << std::endl;
	std::cout << "===============================" << std::endl;
	result &= intrinsics::test::assignment(std::cout);
	result &= intrinsics::test::conversion(std::cout);
	result &= intrinsics::test::clearbits(std::cout);
	result &= intrinsics::test::equality(std::cout);
	result &= intrinsics::test::inequality(std::cout);
	result &= intrinsics::test::greater(std::cout);
	result &= intrinsics::test::lesser(std::cout);
	result &= intrinsics::test::greater_equal(std::cout);
	result &= intrinsics::test::lesser_equal(std::cout);
	result &= intrinsics::test::leftshift(std::cout);
	result &= intrinsics::test::rightshift(std::cout);
	result &= intrinsics::test::leftshift_inplace(std::cout);
	result &= intrinsics::test::rightshift_inplace(std::cout);
	result &= intrinsics::test::complement(std::cout);
	result &= intrinsics::test::disjunction(std::cout);
	result &= intrinsics::test::conjunction(std::cout);
	result &= intrinsics::test::exclusion(std::cout);
	result &= intrinsics::test::disjunction_inplace(std::cout);
	result &= intrinsics::test::conjunction_inplace(std::cout);
	result &= intrinsics::test::exclusion_inplace(std::cout);
	result &= intrinsics::test::popcnt(std::cout);
	result &= intrinsics::test::bsf(std::cout);
	result &= intrinsics::test::bsr(std::cout);
	result &= intrinsics::test::prefix_increment(std::cout);
	result &= intrinsics::test::prefix_decrement(std::cout);
	result &= intrinsics::test::postfix_increment(std::cout);
	result &= intrinsics::test::postfix_decrement(std::cout);
	result &= intrinsics::test::addition(std::cout);
	result &= intrinsics::test::negation(std::cout);
	result &= intrinsics::test::subtraction(std::cout);
	result &= intrinsics::test::multiplication(std::cout);
	result &= intrinsics::test::division(std::cout);
	result &= intrinsics::test::modulus(std::cout);
	result &= intrinsics::test::addition_inplace(std::cout);
	result &= intrinsics::test::subtraction_inplace(std::cout);
	result &= intrinsics::test::multiplication_inplace(std::cout);
	result &= intrinsics::test::division_inplace(std::cout);
	result &= intrinsics::test::modulus_inplace(std::cout);
	result &= intrinsics::test::bittest(std::cout);
	result &= intrinsics::test::bitset(std::cout);
	result &= intrinsics::test::bitclear(std::cout);
	result &= intrinsics::test::pext(std::cout);
	result &= intrinsics::test::pdep(std::cout);
	std::cout << "================" << std::endl;
	if (result)
		std::cout << "PASSED UNIT TEST" << std::endl;
	else
		std::cout << "FAILED UNIT TEST" << std::endl;
	std::cout << "================" << std::endl;*/
	return !result;
}