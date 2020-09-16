#include <pygmalion-intrinsics.h>
#include <pygmalion-intrinsics/tests.h>

namespace pygmalion::intrinsics
{
	bool command_debugIntrinsics::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-intrinsics")
		{
			bool result{ true };
			parser::parseToken(remainder, token, remainder);
			if (token == "all")
			{
				output() << std::endl;
				result &= intrinsics::test::assignment();
				result &= intrinsics::test::conversion();
				result &= intrinsics::test::equality();
				result &= intrinsics::test::inequality();
				result &= intrinsics::test::greater();
				result &= intrinsics::test::lesser();
				result &= intrinsics::test::greater_equal();
				result &= intrinsics::test::lesser_equal();
				result &= intrinsics::test::leftshift();
				result &= intrinsics::test::rightshift();
				result &= intrinsics::test::leftshift_inplace();
				result &= intrinsics::test::rightshift_inplace();
				result &= intrinsics::test::complement();
				result &= intrinsics::test::disjunction();
				result &= intrinsics::test::conjunction();
				result &= intrinsics::test::exclusion();
				result &= intrinsics::test::disjunction_inplace();
				result &= intrinsics::test::conjunction_inplace();
				result &= intrinsics::test::exclusion_inplace();
				result &= intrinsics::test::popcnt();
				result &= intrinsics::test::bsf();
				result &= intrinsics::test::bsr();
				result &= intrinsics::test::prefix_increment();
				result &= intrinsics::test::prefix_decrement();
				result &= intrinsics::test::postfix_increment();
				result &= intrinsics::test::postfix_decrement();
				result &= intrinsics::test::addition();
				result &= intrinsics::test::negation();
				result &= intrinsics::test::subtraction();
				result &= intrinsics::test::multiplication();
				result &= intrinsics::test::division();
				result &= intrinsics::test::modulus();
				result &= intrinsics::test::addition_inplace();
				result &= intrinsics::test::subtraction_inplace();
				result &= intrinsics::test::multiplication_inplace();
				result &= intrinsics::test::division_inplace();
				result &= intrinsics::test::modulus_inplace();
				result &= intrinsics::test::bittest();
				result &= intrinsics::test::bitset();
				result &= intrinsics::test::bitclear();
				result &= intrinsics::test::pext();
				result &= intrinsics::test::pdep();
				output() << std::endl;
			}
			else if (token == "assignment")
				result &= intrinsics::test::assignment();
			else if (token == "conversion")
				result &= intrinsics::test::conversion();
			else if (token == "equality")
				result &= intrinsics::test::equality();
			else if (token == "inequality")
				result &= intrinsics::test::inequality();
			else if (token == "greater")
				result &= intrinsics::test::greater();
			else if (token == "lesser")
				result &= intrinsics::test::lesser();
			else if (token == "greater_equal")
				result &= intrinsics::test::greater_equal();
			else if (token == "lesser_equal")
				result &= intrinsics::test::lesser_equal();
			else if (token == "leftshift")
				result &= intrinsics::test::leftshift();
			else if (token == "rightshift")
				result &= intrinsics::test::rightshift();
			else if (token == "leftshift_inplace")
				result &= intrinsics::test::leftshift_inplace();
			else if (token == "rightshift_inplace")
				result &= intrinsics::test::rightshift_inplace();
			else if (token == "complement")
				result &= intrinsics::test::complement();
			else if (token == "disjunction")
				result &= intrinsics::test::disjunction();
			else if (token == "conjunction")
				result &= intrinsics::test::conjunction();
			else if (token == "exclusion")
				result &= intrinsics::test::exclusion();
			else if (token == "disjunction_inplace")
				result &= intrinsics::test::disjunction_inplace();
			else if (token == "conjunction_inplace")
				result &= intrinsics::test::conjunction_inplace();
			else if (token == "exclusion_inplace")
				result &= intrinsics::test::exclusion_inplace();
			else if (token == "popcnt")
				result &= intrinsics::test::popcnt();
			else if (token == "bsf")
				result &= intrinsics::test::bsf();
			else if (token == "bsr")
				result &= intrinsics::test::bsr();
			else if (token == "prefix_increment")
				result &= intrinsics::test::prefix_increment();
			else if (token == "prefix_decrement")
				result &= intrinsics::test::prefix_decrement();
			else if (token == "postfix_increment")
				result &= intrinsics::test::postfix_increment();
			else if (token == "postfix_decrement")
				result &= intrinsics::test::postfix_decrement();
			else if (token == "addition")
				result &= intrinsics::test::addition();
			else if (token == "negation")
				result &= intrinsics::test::negation();
			else if (token == "subtraction")
				result &= intrinsics::test::subtraction();
			else if (token == "multiplication")
				result &= intrinsics::test::multiplication();
			else if (token == "division")
				result &= intrinsics::test::division();
			else if (token == "modulus")
				result &= intrinsics::test::modulus();
			else if (token == "addition_inplace")
				result &= intrinsics::test::addition_inplace();
			else if (token == "subtraction_inplace")
				result &= intrinsics::test::subtraction_inplace();
			else if (token == "multiplication_inplace")
				result &= intrinsics::test::multiplication_inplace();
			else if (token == "division_inplace")
				result &= intrinsics::test::division_inplace();
			else if (token == "modulus_inplace")
				result &= intrinsics::test::modulus_inplace();
			else if (token == "bittest")
				result &= intrinsics::test::bittest();
			else if (token == "bitset")
				result &= intrinsics::test::bitset();
			else if (token == "bitclear")
				result &= intrinsics::test::bitclear();
			else if (token == "pext")
				result &= intrinsics::test::pext();
			else if (token == "pdep")
				result &= intrinsics::test::pdep();
			else
			{
				output() << std::endl;
				output() << "illegal test: " << token << std::endl;
				output() << std::endl;
				return true;
			}
			output() << "================" << std::endl;
			if (result)
				output() << "PASSED ALL TESTS" << std::endl;
			else
				output() << "FAILED ALL TESTS" << std::endl;
			output() << "================" << std::endl;
			return true;
		}
		else
			return false;
	}
}