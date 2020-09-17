namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool storebits(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		constexpr const size_t start{ COUNT_BITS / 3 };
		constexpr const size_t len{ COUNT_BITS / 2 };
		using U = uint_t<COUNT_BITS, COMPACT>;
		using U2 = uint_t<len, COMPACT>;
		using R = typename intrinsics::detail::popcnt_traits<COUNT_BITS>::intType;
		str << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> store range of bits" << std::endl;
		str << std::endl;
		str << "    " << U() << std::endl;
		str << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		str << "    generating " << countIterations << "x uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		U2* m_Input = new U2[countIterations];
		U* m_Output = new U[countIterations];
		R* m_RefInput = new R[countIterations];
		R* m_RefOutput = new R[countIterations];
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input[i] = U2::random();
			m_Output[i] = U::random();
			m_RefInput[i] = static_cast<R>(m_Input[i]);
			m_RefOutput[i] = static_cast<R>(m_Output[i]);
		}
		profiler profileImplementation;
		str << "    storing bits (uint_t)..." << std::endl;
		profileImplementation.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i].template storeBits<start, len>(m_Input[i]);
		profileImplementation.stop();
		const auto durationImplementation{ profileImplementation.duration() };
		const auto speedImplementation{ profileImplementation.computeSpeed(countIterations, "op") };
		str << "    storing bits (baseline)..." << std::endl;
		R mask{ 0 };
		if constexpr (len >= (sizeof(R) * CHAR_BIT))
			mask = static_cast<R>(~R(0));
		else
			mask = static_cast<R>((((R(1) << len) - R(1)) << start));
		profiler profileBase;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
		{
			m_RefOutput[i] &= ~mask;
			m_RefOutput[i] |= m_RefInput[i] << start;
		}
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
				str << "      offending uint_t<" << COUNT_BITS << "," << COMPACT << ">: " << std::endl;
				str << "        " << static_cast<std::uintmax_t>(m_Input[i]) << std::endl;
				str << std::endl;
				const U2 I{ m_Input[i] };
				U O{ m_Output[i] };
				O.template storeBits<start, len>(I);
				delete[] m_Input;
				delete[] m_Output;
				delete[] m_RefInput;
				delete[] m_RefOutput;
				return false;
			}
		}
		duration += durationImplementation;
		operations += countIterations;
		str << "  PASSED" << std::endl;
		str << std::endl;
		delete[] m_Input;
		delete[] m_Output;
		delete[] m_RefInput;
		delete[] m_RefOutput;
		return true;
	}
	bool storebits(std::ostream& str) noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		str << "_____________________________________" << std::endl;
		str << "TESTSUITE: uint_t store range of bits" << std::endl;
		str << std::endl;
		result &= intrinsics::test::storebits<0, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<1, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<2, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<4, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<8, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<16, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<32, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<64, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<3, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<5, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<7, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<11, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<13, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<17, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<19, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<23, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<29, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<31, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<37, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<41, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<43, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<47, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<53, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<59, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<61, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::storebits<0, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<1, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<2, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<4, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<8, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<16, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<32, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<64, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<3, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<5, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<7, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<11, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<13, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<17, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<19, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<23, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<29, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<31, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<37, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<41, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<43, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<47, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<53, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<59, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::storebits<61, true>(str, durationCompact, operationsCompact);
		str << "  Performace: " << std::endl;
		str << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		str << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		str << std::endl;
		if (result)
			str << "ALL PASSED" << std::endl;
		else
			str << "SOME FAILED" << std::endl;
		str << "_____________________________________" << std::endl;
		str << std::endl;
		return result;
	}
}
