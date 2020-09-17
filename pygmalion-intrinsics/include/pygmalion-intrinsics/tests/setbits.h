namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool setbits(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		using R = typename intrinsics::detail::popcnt_traits<COUNT_BITS>::intType;
		str << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> set range of bits" << std::endl;
		str << std::endl;
		str << "    " << U() << std::endl;
		str << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		str << "    generating " << countIterations << "x uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		U* m_Input = new U[countIterations];
		U* m_Output = new U[countIterations];
		R* m_RefInput = new R[countIterations];
		R* m_RefOutput = new R[countIterations];
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input[i] = U::random();
			m_Output[i] = m_Input[i];
			m_RefInput[i] = static_cast<R>(m_Input[i]);
			m_RefOutput[i] = m_RefInput[i];
		}
		constexpr const size_t start{ COUNT_BITS / 3 };
		constexpr const size_t len{ COUNT_BITS / 2 };
		profiler profileImplementation;
		str << "    setting bits (uint_t)..." << std::endl;
		profileImplementation.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i].template setBits<start, len>();
		profileImplementation.stop();
		const auto durationImplementation{ profileImplementation.duration() };
		const auto speedImplementation{ profileImplementation.computeSpeed(countIterations, "op") };
		str << "    setting bits (baseline)..." << std::endl;
		R mask{ 0 };
		if constexpr (len >= (sizeof(R) * CHAR_BIT))
			mask = static_cast<R>(~R(0));
		else
			mask = static_cast<R>((((R(1) << len) - R(1)) << start));
		profiler profileBase;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefOutput[i]|=mask;
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
				const R I{ m_Input[i] };
			    U O{ m_Output[i] };
				O.template clearBits<start, len>();
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
	bool setbits(std::ostream& str) noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		str << "_____________________________________" << std::endl;
		str << "TESTSUITE: uint_t clear range of bits" << std::endl;
		str << std::endl;
		result &= intrinsics::test::setbits<0, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<1, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<2, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<4, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<8, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<16, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<32, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<64, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<3, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<5, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<7, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<11, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<13, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<17, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<19, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<23, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<29, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<31, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<37, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<41, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<43, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<47, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<53, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<59, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<61, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::setbits<0, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<1, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<2, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<4, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<8, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<16, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<32, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<64, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<3, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<5, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<7, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<11, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<13, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<17, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<19, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<23, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<29, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<31, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<37, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<41, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<43, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<47, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<53, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<59, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::setbits<61, true>(str, durationCompact, operationsCompact);
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
