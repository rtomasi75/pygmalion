namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool complement(typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		using R = typename detail::popcnt_traits<COUNT_BITS>::intType;
		std::cout << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> bitwise complement operator" << std::endl;
		std::cout << std::endl;
		std::cout << "    " << U() << std::endl;
		std::cout << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		U* m_Input = new U[countIterations];
		U* m_Output = new U[countIterations];
		R* m_RefInput = new R[countIterations];
		R* m_RefOutput = new R[countIterations];
		std::cout << "    generating " << countIterations << "x uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input[i] = U::random();
			m_RefInput[i] = m_Input[i];
		}
		profiler profileImplementation;
		std::cout << "    computing complements (uint_t)..." << std::endl;
		profileImplementation.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i] = ~m_Input[i];
		profileImplementation.stop();
		const auto durationImplementation{ profileImplementation.duration() };
		const auto speedImplementation{ profileImplementation.computeSpeed(countIterations, "op") };
		std::cout << "    computing complements (baseline)..." << std::endl;
		R mask{ 0 };
		if constexpr (COUNT_BITS >= (sizeof(R) * CHAR_BIT))
			mask = static_cast<R>(~R(0));
		else
			mask = static_cast<R>((R(1) << COUNT_BITS) - R(1));
		profiler profileBase;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefOutput[i] = static_cast<R>((~m_RefInput[i]) & mask);
		profileBase.stop();
		const auto speedBase{ profileBase.computeSpeed(countIterations, "op") };
		const auto durationBase{ profileBase.duration() };
		std::cout << "      implementation: " << parser::durationToString(durationImplementation) << " -> " << speedImplementation << std::endl;
		std::cout << "      baseline:       " << parser::durationToString(durationBase) << " -> " << speedBase << std::endl;
		std::cout << "    verifying..." << std::endl;
		std::cout << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			if (R(m_Output[i]) != m_RefOutput[i])
			{
				std::cout << "    FAILED:" << std::endl;
				std::cout << "      offending uint_t<" << COUNT_BITS << "," << COMPACT << ">: " << std::endl;
				std::cout << "        " << static_cast<std::uintmax_t>(m_Input[i])<< std::endl;
				std::cout << std::endl;
				const R I{ m_Input[i] };
				const R O{ m_Output[i] };
				const U sum{ ~m_Input[i] };
				delete[] m_Input;
				delete[] m_Output;
				delete[] m_RefInput;
				delete[] m_RefOutput;
				return false;
			}
		}
		duration += durationImplementation;
		operations += countIterations;
		std::cout << "  PASSED" << std::endl;
		std::cout << std::endl;
		delete[] m_Input;
		delete[] m_Output;
		delete[] m_RefInput;
		delete[] m_RefOutput;
		return true;
	}
	bool complement() noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		std::cout << "_____________________________________________" << std::endl;
		std::cout << "TESTSUITE: uint_t bitwise complement operator" << std::endl;
		std::cout << std::endl;
		result &= intrinsics::test::complement<0, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<1, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<2, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<4, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<8, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<16, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<32, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<64, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<3, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<5, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<7, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<11, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<13, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<17, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<19, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<23, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<29, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<31, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<37, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<41, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<43, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<47, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<53, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<59, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<61, false>(durationFast, operationsFast);
		result &= intrinsics::test::complement<0, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<1, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<2, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<4, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<8, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<16, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<32, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<64, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<3, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<5, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<7, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<11, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<13, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<17, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<19, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<23, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<29, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<31, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<37, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<41, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<43, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<47, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<53, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<59, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::complement<61, true>(durationCompact, operationsCompact);
		std::cout << "  Performace: " << std::endl;
		std::cout << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		std::cout << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		std::cout << std::endl;
		if (result)
			std::cout << "ALL PASSED" << std::endl;
		else
			std::cout << "SOME FAILED" << std::endl;
		std::cout << "_____________________________________________" << std::endl;
		std::cout << std::endl;
		return result;
	}
}