namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool subtraction(typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		using R = typename detail::popcnt_traits<COUNT_BITS>::intType;
		std::cout << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> binary subtraction operator" << std::endl;
		std::cout << std::endl;
		std::cout << "    " << U() << std::endl;
		std::cout << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		U* m_Input1 = new U[countIterations];
		U* m_Input2 = new U[countIterations];
		U* m_Output = new U[countIterations];
		R* m_RefInput1 = new R[countIterations];
		R* m_RefInput2 = new R[countIterations];
		R* m_RefOutput = new R[countIterations];
		size_t* m_Counts = new size_t[countIterations];
		size_t* m_RefCounts = new size_t[countIterations];
		size_t* m_BaseCounts = new size_t[countIterations];
		std::cout << "    generating " << countIterations << " pairs of uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input1[i] = U::random();
			m_Input2[i] = U::random();
			m_RefInput1[i] = m_Input1[i];
			m_RefInput2[i] = m_Input2[i];
		}
		profiler profileImplementation;
		std::cout << "    subtracting (uint_t)..." << std::endl;
		profileImplementation.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i] = m_Input1[i] - m_Input2[i];
		profileImplementation.stop();
		const auto durationImplementation{ profileImplementation.duration() };
		const auto speedImplementation{ profileImplementation.computeSpeed(countIterations, "op") };
		std::cout << "    subtracting (baseline)..." << std::endl;
		R mask{ 0 };
		if constexpr (COUNT_BITS >= (sizeof(R) * CHAR_BIT))
			mask = static_cast<R>(~R(0));
		else
			mask = static_cast<R>((R(1) << COUNT_BITS) - R(1));
		profiler profileBase;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefOutput[i] = static_cast<R>((m_RefInput1[i] - m_RefInput2[i]) & mask);
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
				std::cout << "      pair of uint_t<" << COUNT_BITS << "," << COMPACT << ">: " << std::endl;
				std::cout << "        " << static_cast<std::uintmax_t>(m_Input1[i]) << " - " << static_cast<std::uintmax_t>(m_Input2[i]) << " = " << static_cast<std::uintmax_t>(m_Output[i]) << " (!?)" << std::endl;
				std::cout << std::endl;
				const R I1{ m_Input1[i] };
				const R I2{ m_Input2[i] };
				const R O{ m_Output[i] };
				const U sum{ m_Input1[i] - m_Input2[i] };
				delete[] m_Input1;
				delete[] m_Input2;
				delete[] m_Output;
				delete[] m_RefInput1;
				delete[] m_RefInput2;
				delete[] m_RefOutput;
				return false;
			}
		}
		duration += durationImplementation;
		operations += countIterations;
		std::cout << "  PASSED" << std::endl;
		std::cout << std::endl;
		delete[] m_Input1;
		delete[] m_Input2;
		delete[] m_Output;
		delete[] m_RefInput1;
		delete[] m_RefInput2;
		delete[] m_RefOutput;
		return true;
	}
	bool subtraction() noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		std::cout << "_____________________________________________" << std::endl;
		std::cout << "TESTSUITE: uint_t binary subtraction operator" << std::endl;
		std::cout << std::endl;
		result &= intrinsics::test::subtraction<0, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<1, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<2, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<4, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<8, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<16, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<32, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<64, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<3, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<5, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<7, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<11, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<13, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<17, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<19, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<23, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<29, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<31, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<37, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<41, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<43, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<47, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<53, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<59, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<61, false>(durationFast, operationsFast);
		result &= intrinsics::test::subtraction<0, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<1, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<2, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<4, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<8, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<16, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<32, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<64, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<3, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<5, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<7, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<11, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<13, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<17, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<19, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<23, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<29, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<31, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<37, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<41, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<43, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<47, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<53, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<59, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::subtraction<61, true>(durationCompact, operationsCompact);
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