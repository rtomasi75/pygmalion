namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool bsr(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		using R = typename intrinsics::detail::bsr_traits<COUNT_BITS>::intType;
		str << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> bitscan reverse" << std::endl;
		str << std::endl;
		str << "    " << U() << std::endl;
		str << "    " << U::bitscanReverse_Intrinsic << std::endl;
		str << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		str << "    generating " << countIterations << "x uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		U* m_Input = new U[countIterations];
		R* m_RefInput = new R[countIterations];
		R* m_BaseInput = new R[countIterations];
		size_t* m_Bits = new size_t[countIterations];
		size_t* m_RefBits = new size_t[countIterations];
		size_t* m_BaseBits = new size_t[countIterations];
		bool* m_Rets = new bool[countIterations];
		bool* m_RefRets = new bool[countIterations];
		bool* m_BaseRets = new bool[countIterations];
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input[i] = U::sparse();
			m_RefInput[i] = static_cast<R>(m_Input[i]);
			m_BaseInput[i] = static_cast<R>(m_Input[i]);
			m_Bits[i] = 0;
			m_RefBits[i] = 0;
			m_BaseBits[i] = 0;
		}
		profiler profileCount;
		profiler profileBase;
		profiler profileRef;
		profiler profileGeneric;
		str << "    scanning bits (uint_t)..." << std::endl;
		profileCount.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Rets[i] = m_Input[i].bitscanReverse(m_Bits[i]);
		profileCount.stop();
		const auto durationCount{ profileCount.duration() };
		const auto speedCount{ profileCount.computeSpeed(countIterations, "op") };
		str << "    scanning bits (baseline)..." << std::endl;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_BaseRets[i] = intrinsics::detail::bsr_traits<COUNT_BITS>::baseline(m_BaseInput[i], m_BaseBits[i]);
		profileBase.stop();
		const auto durationBase{ profileBase.duration() };
		const auto speedBase{ profileBase.computeSpeed(countIterations, "op") };
		str << "    scanning bits (reference)..." << std::endl;
		profileRef.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefRets[i] = intrinsics::detail::bsr_traits<COUNT_BITS>::reference(m_RefInput[i], m_RefBits[i]);
		profileRef.stop();
		const auto durationRef{ profileRef.duration() };
		const auto speedRef{ profileRef.computeSpeed(countIterations, "op") };
		profileGeneric.start();
		for (size_t i = 0; i < countIterations; i++)
			m_BaseRets[i] |= intrinsics::detail::bsr_traits<COUNT_BITS>::generic(m_BaseInput[i], m_BaseBits[i]);
		profileGeneric.stop();
		const auto durationGeneric{ profileGeneric.duration() };
		const auto speedGeneric{ profileGeneric.computeSpeed(countIterations, "op") };
		str << "      implementation: " << parser::durationToString(durationCount) << " -> " << speedCount << std::endl;
		str << "      baseline:       " << parser::durationToString(durationBase) << " -> " << speedBase << std::endl;
		str << "      generic:        " << parser::durationToString(durationGeneric) << " -> " << speedGeneric << std::endl;
		str << "      reference:      " << parser::durationToString(durationRef) << " -> " << speedRef << std::endl;
		str << "    verifying..." << std::endl;
		str << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			if ((m_Bits[i] != m_RefBits[i]) || (m_Bits[i] != m_BaseBits[i]) || (m_Rets[i] != m_RefRets[i]) || (m_Rets[i] != m_BaseRets[i]))
			{
				str << "    FAILED:" << std::endl;
				str << "      failing uint_t<" << COUNT_BITS << "," << COMPACT << ">: " << static_cast<std::uintmax_t>(m_Input[i]) << std::endl;
				str << std::endl;
				size_t bit{ 0 };
				const bool count{ m_Input[i].bitscanReverse(bit) };
				delete[] m_RefInput;
				delete[] m_BaseInput;
				delete[] m_Input;
				delete[] m_Rets;
				delete[] m_RefRets;
				delete[] m_BaseRets;
				delete[] m_Bits;
				delete[] m_RefBits;
				delete[] m_BaseBits;
				return false;
			}
		}
		duration += durationCount;
		operations += countIterations;
		str << "  PASSED" << std::endl;
		str << std::endl;
		delete[] m_RefInput;
		delete[] m_BaseInput;
		delete[] m_Input;
		delete[] m_Rets;
		delete[] m_RefRets;
		delete[] m_BaseRets;
		delete[] m_Bits;
		delete[] m_RefBits;
		delete[] m_BaseBits;
		return true;
	}
	bool bsr(std::ostream& str) noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		str << "_________________________________" << std::endl;
		str << "TESTSUITE: uint_t bitscan reverse" << std::endl;
		str << std::endl;
		result &= intrinsics::test::bsr<0, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<1, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<2, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<4, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<8, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<16, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<32, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<64, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<3, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<5, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<7, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<11, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<13, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<17, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<19, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<23, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<29, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<31, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<37, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<41, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<43, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<47, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<53, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<59, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<61, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsr<0, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<1, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<2, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<4, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<8, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<16, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<32, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<64, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<3, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<5, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<7, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<11, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<13, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<17, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<19, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<23, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<29, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<31, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<37, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<41, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<43, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<47, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<53, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<59, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsr<61, true>(str, durationCompact, operationsCompact);
		str << "  Performace: " << std::endl;
		str << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		str << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		str << std::endl;
		if (result)
			str << "ALL PASSED" << std::endl;
		else
			str << "SOME FAILED" << std::endl;
		str << "_________________________________" << std::endl;
		str << std::endl;
		return result;
	}
}