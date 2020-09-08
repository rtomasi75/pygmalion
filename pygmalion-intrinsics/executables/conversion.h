namespace intrinsics::test
{
	template<size_t COUNT_BITS1, bool COMPACT1, size_t COUNT_BITS2, bool COMPACT2, typename = typename std::enable_if<(COUNT_BITS1 <= 64) && (COUNT_BITS2 <= 64)>::type>
	bool conversion(typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using T1 = typename detail::popcnt_traits<COUNT_BITS1>::intType;
		using T2 = typename detail::popcnt_traits<COUNT_BITS2>::intType;
		using U1 = uint_t<COUNT_BITS1, COMPACT1>;
		using U2 = uint_t<COUNT_BITS2, COMPACT2>;
		std::cout << "  TEST: uint_t<" << COUNT_BITS1 << "," << COMPACT1 << "> -> uint_t<" << COUNT_BITS2 << "," << COMPACT2 << "> conversions" << std::endl;
		std::cout << std::endl;
		std::cout << "    " << U1() << std::endl;
		std::cout << "    " << U2() << std::endl;
		std::cout << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		U1* m_Input = new U1[countIterations];
		T1* m_RefInput = new T1[countIterations];
		U2* m_Output = new U2[countIterations];
		T2* m_RefOutput = new T2[countIterations];
		std::cout << "    generating " << countIterations << "x uint_t<" << COUNT_BITS1 << "," << COMPACT1 << ">..." << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input[i] = U1::random();
			m_RefInput[i] = m_Input[i];
		}
		profiler profile;
		std::cout << "    casting to uint_t<" << COUNT_BITS2 << "," << COMPACT2 << ">..." << std::endl;
		profile.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i] = U2(m_Input[i]);
		profile.stop();
		const auto durationCastTo{ profile.duration() };
		const auto speedTo{ profile.computeSpeed(countIterations, "op") };
		std::cout << "      " << parser::durationToString(durationCastTo) << " -> " << speedTo << std::endl;
		std::cout << "    generating reference baseline..." << std::endl;
		T2 mask{ 0 };
		if constexpr (COUNT_BITS2 >= (sizeof(T2) * CHAR_BIT))
			mask = static_cast<T2>(~T2(0));
		else
			mask = static_cast<T2>((T2(1) << COUNT_BITS2) - T2(1));
		profile.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefOutput[i] = static_cast<T1>(static_cast<T2>(m_RefInput[i]) & mask);
		profile.stop();
		const auto durationBase{ profile.duration() };
		const auto speedBase{ profile.computeSpeed(countIterations, "op") };
		std::cout << "      " << parser::durationToString(durationBase) << " -> " << speedBase << std::endl;
		std::cout << "    verifying..." << std::endl;
		std::cout << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			if (static_cast<T2>(m_Output[i]) != m_RefOutput[i])
			{
				std::cout << "    FAILED:" << std::endl;
				std::cout << "      failing uint_t: " << m_Input[i] << std::endl;
				std::cout << "      converted to:   " << m_Output[i] << std::endl;
				std::cout << std::endl;
				const U1 input{ m_Input[i] };
				const U2 output{ U2(input) };
				delete[] m_Output;
				delete[] m_RefOutput;
				delete[] m_Input;
				delete[] m_RefInput;
				return false;
			}
		}
		duration += durationCastTo;
		operations += countIterations;
		std::cout << "  PASSED" << std::endl;
		std::cout << std::endl;
		delete[] m_Output;
		delete[] m_RefOutput;
		delete[] m_Input;
		delete[] m_RefInput;
		return true;
	}
	bool conversion() noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		std::cout << "_____________________________" << std::endl;
		std::cout << "TESTSUITE: uint_t conversions" << std::endl;
		std::cout << std::endl;
		result &= intrinsics::test::conversion<0, false, 61, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<1, false, 59, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<2, false, 53, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<4, false, 47, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<8, false, 43, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<16, false, 41, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<32, false, 37, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<64, false, 31, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<3, false, 29, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<5, false, 23, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<7, false, 19, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<11, false, 17, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<13, false, 13, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<17, false, 11, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<19, false, 7, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<23, false, 5, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<29, false, 3, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<31, false, 0, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<37, false, 1, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<41, false, 2, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<43, false, 4, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<47, false, 8, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<53, false, 16, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<59, false, 32, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<61, false, 64, false>(durationFast, operationsFast);
		result &= intrinsics::test::conversion<0, true, 61, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<1, true, 59, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<2, true, 53, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<4, true, 47, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<8, true, 43, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<16, true, 41, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<32, true, 37, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<64, true, 31, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<3, true, 29, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<5, true, 23, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<7, true, 19, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<11, true, 17, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<13, true, 13, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<17, true, 11, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<19, true, 7, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<23, true, 5, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<29, true, 3, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<31, true, 0, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<37, true, 1, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<41, true, 2, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<43, true, 4, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<47, true, 8, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<53, true, 16, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<59, true, 32, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::conversion<61, true, 64, true>(durationCompact, operationsCompact);
		std::cout << "  Performace: " << std::endl;
		std::cout << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		std::cout << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		std::cout << std::endl;
		if (result)
			std::cout << "ALL PASSED" << std::endl;
		else
			std::cout << "SOME FAILED" << std::endl;
		std::cout << "_____________________________" << std::endl;
		std::cout << std::endl;
		return result;
	}
}