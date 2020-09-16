namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool rightshift(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		using R = typename intrinsics::detail::popcnt_traits<COUNT_BITS>::intType;
		str << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> binary rightshift operator" << std::endl;
		str << std::endl;
		str << "    " << U() << std::endl;
		str << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		str << "    generating " << countIterations << " pairs of uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		U* m_Input1 = new U[countIterations];
		size_t* m_Input2 = new size_t[countIterations];
		U* m_Output = new U[countIterations];
		R* m_RefInput1 = new R[countIterations];
		size_t* m_RefInput2 = new size_t[countIterations];
		R* m_RefOutput = new R[countIterations];
		size_t* m_Counts = new size_t[countIterations];
		size_t* m_RefCounts = new size_t[countIterations];
		size_t* m_BaseCounts = new size_t[countIterations];
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input1[i] = U::random();
			m_Input2[i] = std::rand() % (2 * COUNT_BITS + 1);
			m_RefInput1[i] = static_cast<R>(m_Input1[i]);
			m_RefInput2[i] = static_cast<R>(m_Input2[i]);
		}
		profiler profileImplementation;
		str << "    shifting (uint_t)..." << std::endl;
		profileImplementation.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i] = m_Input1[i] >> m_Input2[i];
		profileImplementation.stop();
		const auto durationImplementation{ profileImplementation.duration() };
		const auto speedImplementation{ profileImplementation.computeSpeed(countIterations, "op") };
		str << "    shifting (baseline)..." << std::endl;
		R mask{ 0 };
		if constexpr (COUNT_BITS >= (sizeof(R) * CHAR_BIT))
			mask = static_cast<R>(~R(0));
		else
			mask = static_cast<R>((R(1) << COUNT_BITS) - R(1));
		profiler profileBase;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefOutput[i] = static_cast<R>((m_RefInput2[i] >= (sizeof(R) * CHAR_BIT)) ? 0 : ((m_RefInput1[i] >> m_RefInput2[i]) & mask));
		profileBase.stop();
		const auto speedBase{ profileBase.computeSpeed(countIterations, "op") };
		const auto durationBase{ profileBase.duration() };
		str << "      implementation: " << parser::durationToString(durationImplementation) << " -> " << speedImplementation << std::endl;
		str << "      baseline:       " << parser::durationToString(durationBase) << " -> " << speedBase << std::endl;
		str << "    verifying..." << std::endl;
		str << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			if (R(m_Output[i]) != m_RefOutput[i])
			{
				str << "    FAILED:" << std::endl;
				str << "      pair of uint_t<" << COUNT_BITS << "," << COMPACT << ">: " << std::endl;
				str << "        " << static_cast<std::uintmax_t>(m_Input1[i]) << " << " << static_cast<std::uintmax_t>(m_Input2[i]) << " = " << static_cast<std::uintmax_t>(m_Output[i]) << " (!?)" << std::endl;
				str << std::endl;
				const R I1{ m_Input1[i] };
				const size_t I2{ m_Input2[i] };
				const R O{ m_Output[i] };
				const U sum{ m_Input1[i] >> m_Input2[i] };
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
		str << "  PASSED" << std::endl;
		str << std::endl;
		delete[] m_Input1;
		delete[] m_Input2;
		delete[] m_Output;
		delete[] m_RefInput1;
		delete[] m_RefInput2;
		delete[] m_RefOutput;
		return true;
	}
	bool rightshift(std::ostream& str) noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		str << "____________________________________________" << std::endl;
		str << "TESTSUITE: uint_t binary rightshift operator" << std::endl;
		str << std::endl;
		result &= intrinsics::test::rightshift<0, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<1, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<2, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<4, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<8, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<16, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<32, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<64, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<3, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<5, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<7, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<11, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<13, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<17, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<19, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<23, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<29, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<31, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<37, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<41, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<43, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<47, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<53, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<59, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<61, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::rightshift<0, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<1, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<2, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<4, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<8, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<16, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<32, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<64, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<3, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<5, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<7, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<11, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<13, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<17, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<19, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<23, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<29, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<31, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<37, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<41, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<43, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<47, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<53, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<59, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::rightshift<61, true>(str, durationCompact, operationsCompact);
		str << "  Performace: " << std::endl;
		str << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		str << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		str << std::endl;
		if (result)
			str << "ALL PASSED" << std::endl;
		else
			str << "SOME FAILED" << std::endl;
		str << "____________________________________________" << std::endl;
		str << std::endl;
		return result;
	}
}