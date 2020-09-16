namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool lesser_equal(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		using R = typename intrinsics::detail::popcnt_traits<COUNT_BITS>::intType;
		str << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> lesser or equal than relation" << std::endl;
		str << std::endl;
		str << "    " << U() << std::endl;
		str << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		str << "    generating " << countIterations << " pairs of uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		U* m_Input1 = new U[countIterations];
		U* m_Input2 = new U[countIterations];
		bool* m_Output = new bool[countIterations];
		R* m_RefInput1 = new R[countIterations];
		R* m_RefInput2 = new R[countIterations];
		bool* m_RefOutput = new bool[countIterations];
		size_t* m_Counts = new size_t[countIterations];
		size_t* m_RefCounts = new size_t[countIterations];
		size_t* m_BaseCounts = new size_t[countIterations];
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input1[i] = U::random();
			m_Input2[i] = (std::rand() % 2) ? U::random() : m_Input1[i];
			m_RefInput1[i] = static_cast<R>(m_Input1[i]);
			m_RefInput2[i] = static_cast<R>(m_Input2[i]);
		}
		profiler profileImplementation;
		str << "    comparing (uint_t)..." << std::endl;
		profileImplementation.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i] = (m_Input1[i] <= m_Input2[i]);
		profileImplementation.stop();
		const auto durationImplementation{ profileImplementation.duration() };
		const auto speedImplementation{ profileImplementation.computeSpeed(countIterations, "op") };
		str << "    comparing (baseline)..." << std::endl;
		R mask{ 0 };
		if constexpr (COUNT_BITS >= (sizeof(R) * CHAR_BIT))
			mask = static_cast<R>(~R(0));
		else
			mask = static_cast<R>((R(1) << COUNT_BITS) - R(1));
		profiler profileBase;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefOutput[i] = (m_RefInput1[i] <= m_RefInput2[i]);
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
				str << "        " << static_cast<std::uintmax_t>(m_Input1[i]) << " <= " << static_cast<std::uintmax_t>(m_Input2[i]) << " = " << (m_Output[i] ? "true" : "false") << " (!?)" << std::endl;
				str << std::endl;
				const R I1{ m_Input1[i] };
				const R I2{ m_Input2[i] };
				const R O{ m_Output[i] };
				const bool result{ m_Input1[i] <= m_Input2[i] };
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
	bool lesser_equal(std::ostream& str) noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		str << "_______________________________________________" << std::endl;
		str << "TESTSUITE: uint_t lesser or equal than relation" << std::endl;
		str << std::endl;
		result &= intrinsics::test::lesser_equal<0, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<1, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<2, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<4, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<8, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<16, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<32, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<64, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<3, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<5, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<7, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<11, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<13, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<17, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<19, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<23, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<29, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<31, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<37, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<41, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<43, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<47, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<53, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<59, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<61, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::lesser_equal<0, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<1, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<2, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<4, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<8, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<16, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<32, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<64, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<3, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<5, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<7, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<11, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<13, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<17, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<19, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<23, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<29, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<31, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<37, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<41, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<43, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<47, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<53, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<59, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::lesser_equal<61, true>(str, durationCompact, operationsCompact);
		str << "  Performace: " << std::endl;
		str << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		str << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		str << std::endl;
		if (result)
			str << "ALL PASSED" << std::endl;
		else
			str << "SOME FAILED" << std::endl;
		str << "_______________________________________________" << std::endl;
		str << std::endl;
		return result;
	}
}