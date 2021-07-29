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
				result &= intrinsics::test::assignment(this->output());
				result &= intrinsics::test::conversion(this->output());
				result &= intrinsics::test::clearbits(std::cout);
				result &= intrinsics::test::setbits(std::cout);
				result &= intrinsics::test::extractbits(std::cout);
				result &= intrinsics::test::storebits(std::cout);
				result &= intrinsics::test::equality(this->output());
				result &= intrinsics::test::inequality(this->output());
				result &= intrinsics::test::greater(this->output());
				result &= intrinsics::test::lesser(this->output());
				result &= intrinsics::test::greater_equal(this->output());
				result &= intrinsics::test::lesser_equal(this->output());
				result &= intrinsics::test::leftshift(this->output());
				result &= intrinsics::test::rightshift(this->output());
				result &= intrinsics::test::leftshift_inplace(this->output());
				result &= intrinsics::test::rightshift_inplace(this->output());
				result &= intrinsics::test::complement(this->output());
				result &= intrinsics::test::disjunction(this->output());
				result &= intrinsics::test::conjunction(this->output());
				result &= intrinsics::test::exclusion(this->output());
				result &= intrinsics::test::disjunction_inplace(this->output());
				result &= intrinsics::test::conjunction_inplace(this->output());
				result &= intrinsics::test::exclusion_inplace(this->output());
				result &= intrinsics::test::popcnt(this->output());
				result &= intrinsics::test::bsf(this->output());
				result &= intrinsics::test::bsr(this->output());
				result &= intrinsics::test::prefix_increment(this->output());
				result &= intrinsics::test::prefix_decrement(this->output());
				result &= intrinsics::test::postfix_increment(this->output());
				result &= intrinsics::test::postfix_decrement(this->output());
				result &= intrinsics::test::addition(this->output());
				result &= intrinsics::test::negation(this->output());
				result &= intrinsics::test::subtraction(this->output());
				result &= intrinsics::test::multiplication(this->output());
				result &= intrinsics::test::division(this->output());
				result &= intrinsics::test::modulus(this->output());
				result &= intrinsics::test::addition_inplace(this->output());
				result &= intrinsics::test::subtraction_inplace(this->output());
				result &= intrinsics::test::multiplication_inplace(this->output());
				result &= intrinsics::test::division_inplace(this->output());
				result &= intrinsics::test::modulus_inplace(this->output());
				result &= intrinsics::test::bittest(this->output());
				result &= intrinsics::test::bitset(this->output());
				result &= intrinsics::test::bitclear(this->output());
				result &= intrinsics::test::pext(this->output());
				result &= intrinsics::test::pdep(this->output());
				output() << std::endl;
			}
			else if (token == "assignment")
				result &= intrinsics::test::assignment(this->output());
			else if (token == "conversion")
				result &= intrinsics::test::conversion(this->output());
			else if (token == "clearbits")
				result &= intrinsics::test::clearbits(this->output());
			else if (token == "setbits")
				result &= intrinsics::test::setbits(this->output());
			else if (token == "extractbits")
				result &= intrinsics::test::extractbits(this->output());
			else if (token == "storebits")
				result &= intrinsics::test::storebits(this->output());
			else if (token == "equality")
				result &= intrinsics::test::equality(this->output());
			else if (token == "inequality")
				result &= intrinsics::test::inequality(this->output());
			else if (token == "greater")
				result &= intrinsics::test::greater(this->output());
			else if (token == "lesser")
				result &= intrinsics::test::lesser(this->output());
			else if (token == "greater_equal")
				result &= intrinsics::test::greater_equal(this->output());
			else if (token == "lesser_equal")
				result &= intrinsics::test::lesser_equal(this->output());
			else if (token == "leftshift")
				result &= intrinsics::test::leftshift(this->output());
			else if (token == "rightshift")
				result &= intrinsics::test::rightshift(this->output());
			else if (token == "leftshift_inplace")
				result &= intrinsics::test::leftshift_inplace(this->output());
			else if (token == "rightshift_inplace")
				result &= intrinsics::test::rightshift_inplace(this->output());
			else if (token == "complement")
				result &= intrinsics::test::complement(this->output());
			else if (token == "disjunction")
				result &= intrinsics::test::disjunction(this->output());
			else if (token == "conjunction")
				result &= intrinsics::test::conjunction(this->output());
			else if (token == "exclusion")
				result &= intrinsics::test::exclusion(this->output());
			else if (token == "disjunction_inplace")
				result &= intrinsics::test::disjunction_inplace(this->output());
			else if (token == "conjunction_inplace")
				result &= intrinsics::test::conjunction_inplace(this->output());
			else if (token == "exclusion_inplace")
				result &= intrinsics::test::exclusion_inplace(this->output());
			else if (token == "popcnt")
				result &= intrinsics::test::popcnt(this->output());
			else if (token == "bsf")
				result &= intrinsics::test::bsf(this->output());
			else if (token == "bsr")
				result &= intrinsics::test::bsr(this->output());
			else if (token == "prefix_increment")
				result &= intrinsics::test::prefix_increment(this->output());
			else if (token == "prefix_decrement")
				result &= intrinsics::test::prefix_decrement(this->output());
			else if (token == "postfix_increment")
				result &= intrinsics::test::postfix_increment(this->output());
			else if (token == "postfix_decrement")
				result &= intrinsics::test::postfix_decrement(this->output());
			else if (token == "addition")
				result &= intrinsics::test::addition(this->output());
			else if (token == "negation")
				result &= intrinsics::test::negation(this->output());
			else if (token == "subtraction")
				result &= intrinsics::test::subtraction(this->output());
			else if (token == "multiplication")
				result &= intrinsics::test::multiplication(this->output());
			else if (token == "division")
				result &= intrinsics::test::division(this->output());
			else if (token == "modulus")
				result &= intrinsics::test::modulus(this->output());
			else if (token == "addition_inplace")
				result &= intrinsics::test::addition_inplace(this->output());
			else if (token == "subtraction_inplace")
				result &= intrinsics::test::subtraction_inplace(this->output());
			else if (token == "multiplication_inplace")
				result &= intrinsics::test::multiplication_inplace(this->output());
			else if (token == "division_inplace")
				result &= intrinsics::test::division_inplace(this->output());
			else if (token == "modulus_inplace")
				result &= intrinsics::test::modulus_inplace(this->output());
			else if (token == "bittest")
				result &= intrinsics::test::bittest(this->output());
			else if (token == "bitset")
				result &= intrinsics::test::bitset(this->output());
			else if (token == "bitclear")
				result &= intrinsics::test::bitclear(this->output());
			else if (token == "pext")
				result &= intrinsics::test::pext(this->output());
			else if (token == "pdep")
				result &= intrinsics::test::pdep(this->output());
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

	std::string command_debugIntrinsics::help() noexcept
	{
		return "DEBUG-INTRINSICS";
	}
}