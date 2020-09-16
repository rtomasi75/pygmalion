namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool bsf(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		using R = typename intrinsics::detail::bsf_traits<COUNT_BITS>::intType;
		str << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> bitscan forward" << std::endl;
		str << std::endl;
		str << "    " << U() << std::endl;
		str << "    " << U::bitscanForward_Intrinsic << std::endl;
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
			m_Rets[i] = m_Input[i].bitscanForward(m_Bits[i]);
		profileCount.stop();
		const auto durationCount{ profileCount.duration() };
		const auto speedCount{ profileCount.computeSpeed(countIterations, "op") };
		str << "    scanning bits (baseline)..." << std::endl;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_BaseRets[i] = intrinsics::detail::bsf_traits<COUNT_BITS>::baseline(m_BaseInput[i], m_BaseBits[i]);
		profileBase.stop();
		const auto durationBase{ profileBase.duration() };
		const auto speedBase{ profileBase.computeSpeed(countIterations, "op") };
		str << "    scanning bits (reference)..." << std::endl;
		profileRef.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefRets[i] = intrinsics::detail::bsf_traits<COUNT_BITS>::reference(m_RefInput[i], m_RefBits[i]);
		profileRef.stop();
		const auto durationRef{ profileRef.duration() };
		const auto speedRef{ profileRef.computeSpeed(countIterations, "op") };
		profileGeneric.start();
		for (size_t i = 0; i < countIterations; i++)
			m_BaseRets[i] |= intrinsics::detail::bsf_traits<COUNT_BITS>::generic(m_BaseInput[i], m_BaseBits[i]);
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
				const bool count{ m_Input[i].bitscanForward(bit) };
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
	bool bsf(std::ostream& str) noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		str << "_________________________________" << std::endl;
		str << "TESTSUITE: uint_t bitscan forward" << std::endl;
		str << std::endl;
		result &= intrinsics::test::bsf<0, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<1, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<2, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<4, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<8, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<16, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<32, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<64, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<3, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<5, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<7, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<11, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<13, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<17, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<19, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<23, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<29, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<31, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<37, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<41, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<43, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<47, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<53, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<59, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<61, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::bsf<0, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<1, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<2, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<4, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<8, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<16, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<32, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<64, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<3, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<5, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<7, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<11, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<13, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<17, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<19, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<23, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<29, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<31, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<37, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<41, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<43, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<47, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<53, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<59, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<61, true>(str, durationCompact, operationsCompact);
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