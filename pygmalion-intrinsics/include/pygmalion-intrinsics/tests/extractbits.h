namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool extractbits(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		constexpr const size_t start{ COUNT_BITS / 3 };
		constexpr const size_t len{ COUNT_BITS / 2 };
		using U = uint_t<COUNT_BITS, COMPACT>;
		using U2 = uint_t<len, COMPACT>;
		using R = typename intrinsics::detail::popcnt_traits<COUNT_BITS>::intType;
		str << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> extract range of bits" << std::endl;
		str << std::endl;
		str << "    " << U() << std::endl;
		str << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		str << "    generating " << countIterations << "x uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		U* m_Input = new U[countIterations];
		U2* m_Output = new U2[countIterations];
		R* m_RefInput = new R[countIterations];
		R* m_RefOutput = new R[countIterations];
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input[i] = U::random();
			m_Output[i] = U2::random();
			m_RefInput[i] = static_cast<R>(m_Input[i]);
			m_RefOutput[i] = static_cast<R>(m_Output[i]);
		}
		profiler profileImplementation;
		str << "    extracting bits (uint_t)..." << std::endl;
		profileImplementation.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i] = m_Input[i].template extractBits<start, len>();
		profileImplementation.stop();
		const auto durationImplementation{ profileImplementation.duration() };
		const auto speedImplementation{ profileImplementation.computeSpeed(countIterations, "op") };
		str << "    extracting bits (baseline)..." << std::endl;
		R mask{ 0 };
		if constexpr (len >= (sizeof(R) * CHAR_BIT))
			mask = static_cast<R>(~R(0));
		else
			mask = static_cast<R>((((R(1) << len) - R(1)) << start));
		profiler profileBase;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefOutput[i] = static_cast<R>((m_RefInput[i] & mask) >> start);
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
				const U I{ m_Input[i] };
				U2 O{ m_Output[i] };
				O = I.template extractBits<start, len>();
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
	bool extractbits(std::ostream& str) noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		str << "_______________________________________" << std::endl;
		str << "TESTSUITE: uint_t extract range of bits" << std::endl;
		str << std::endl;
		result &= intrinsics::test::extractbits<0, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<1, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<2, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<4, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<8, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<16, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<32, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<64, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<3, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<5, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<7, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<11, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<13, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<17, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<19, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<23, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<29, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<31, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<37, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<41, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<43, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<47, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<53, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<59, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<61, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::extractbits<0, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<1, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<2, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<4, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<8, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<16, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<32, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<64, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<3, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<5, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<7, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<11, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<13, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<17, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<19, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<23, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<29, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<31, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<37, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<41, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<43, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<47, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<53, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<59, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::extractbits<61, true>(str, durationCompact, operationsCompact);
		str << "  Performace: " << std::endl;
		str << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		str << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		str << std::endl;
		if (result)
			str << "ALL PASSED" << std::endl;
		else
			str << "SOME FAILED" << std::endl;
		str << "_______________________________________" << std::endl;
		str << std::endl;
		return result;
	}
}
