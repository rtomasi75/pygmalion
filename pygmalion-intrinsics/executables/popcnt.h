namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool popcnt(typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		std::cout << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> population counts" << std::endl;
		std::cout << std::endl;
		std::cout << "    " << U() << std::endl;
		std::cout << "    " << U::populationCount_Intrinsic << std::endl;
		std::cout << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		U* m_Input = new U[countIterations];
		size_t* m_Counts = new size_t[countIterations];
		std::cout << "    generating " << countIterations << "x uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		for (size_t i = 0; i < countIterations; i++)
			m_Input[i] = U::random();
		profiler profile;
		std::cout << "    counting bits..." << std::endl;
		profile.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Counts[i] = m_Input[i].populationCount();
		profile.stop();
		const auto durationCount{ profile.duration() };
		std::cout << "      " << parser::durationToString(durationCount) << " -> " << profile.computeSpeed(countIterations, "op") << std::endl;
		std::cout << "    verifying..." << std::endl;
		std::cout << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			std::uintmax_t test{ m_Input[i] };
			size_t count{ 0 };
			for (size_t i = 0; i < (sizeof(test) * CHAR_BIT); i++)
			{
				std::uintmax_t mask{ std::uintmax_t(1) << i };
				if (test & mask)
					count++;
			}
			if (m_Counts[i] != count)
			{
				std::cout << "    FAILED:" << std::endl;
				std::cout << "      failing uint_t<" << COUNT_BITS << "," << COMPACT << ">: " << static_cast<std::uintmax_t>(m_Input[i]) << std::endl;
				std::cout << std::endl;
				count = m_Input[i].populationCount();
				delete[] m_Input;
				delete[] m_Counts;
				return false;
			}
		}
		duration += durationCount;
		operations += countIterations;
		std::cout << "  PASSED" << std::endl;
		std::cout << std::endl;
		delete[] m_Input;
		delete[] m_Counts;
		return true;
	}
	bool popcnt() noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		std::cout << "___________________________________" << std::endl;
		std::cout << "TESTSUITE: uint_t population counts" << std::endl;
		std::cout << std::endl;
		result &= intrinsics::test::popcnt<1, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<2, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<4, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<8, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<16, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<32, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<64, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<3, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<5, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<7, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<11, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<13, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<17, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<19, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<23, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<29, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<31, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<37, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<41, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<43, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<47, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<53, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<59, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<61, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<1, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<2, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<4, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<8, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<16, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<32, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<64, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<3, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<5, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<7, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<11, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<13, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<17, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<19, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<23, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<29, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<31, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<37, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<41, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<43, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<47, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<53, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<59, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<61, true>(durationCompact, operationsCompact);
		std::cout << "  Performace: " << std::endl;
		std::cout << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		std::cout << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		std::cout << std::endl;
		if (result)
			std::cout << "ALL PASSED" << std::endl;
		else
			std::cout << "SOME FAILED" << std::endl;
		std::cout << "___________________________________" << std::endl;
		std::cout << std::endl;
		return result;
	}
}