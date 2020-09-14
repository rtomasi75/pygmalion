namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool bsf(typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		using R = typename detail::bsf_traits<COUNT_BITS>::intType;
		std::cout << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> bitscan forward" << std::endl;
		std::cout << std::endl;
		std::cout << "    " << U() << std::endl;
		std::cout << "    " << U::bitscanForward_Intrinsic << std::endl;
		std::cout << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		U* m_Input = new U[countIterations];
		R* m_RefInput = new R[countIterations];
		R* m_BaseInput = new R[countIterations];
		size_t* m_Bits = new size_t[countIterations];
		size_t* m_RefBits = new size_t[countIterations];
		size_t* m_BaseBits = new size_t[countIterations];
		bool* m_Rets = new bool[countIterations];
		bool* m_RefRets = new bool[countIterations];
		bool* m_BaseRets = new bool[countIterations];
		std::cout << "    generating " << countIterations << "x uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input[i] = U::sparse();
			m_RefInput[i] = m_Input[i];
			m_BaseInput[i] = m_Input[i];
			m_Bits[i] = 0;
			m_RefBits[i] = 0;
			m_BaseBits[i] = 0;
		}
		profiler profileCount;
		profiler profileBase;
		profiler profileRef;
		profiler profileGeneric;
		std::cout << "    scanning bits (uint_t)..." << std::endl;
		profileCount.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Rets[i] = m_Input[i].bitscanForward(m_Bits[i]);
		profileCount.stop();
		const auto durationCount{ profileCount.duration() };
		const auto speedCount{ profileCount.computeSpeed(countIterations, "op") };
		std::cout << "    scanning bits (baseline)..." << std::endl;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_BaseRets[i] = detail::bsf_traits<COUNT_BITS>::baseline(m_BaseInput[i], m_BaseBits[i]);
		profileBase.stop();
		const auto durationBase{ profileBase.duration() };
		const auto speedBase{ profileBase.computeSpeed(countIterations, "op") };
		std::cout << "    scanning bits (reference)..." << std::endl;
		profileRef.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefRets[i] = detail::bsf_traits<COUNT_BITS>::reference(m_RefInput[i], m_RefBits[i]);
		profileRef.stop();
		const auto durationRef{ profileRef.duration() };
		const auto speedRef{ profileRef.computeSpeed(countIterations, "op") };
		profileGeneric.start();
		for (size_t i = 0; i < countIterations; i++)
			m_BaseRets[i] |= detail::bsf_traits<COUNT_BITS>::generic(m_BaseInput[i], m_BaseBits[i]);
		profileGeneric.stop();
		const auto durationGeneric{ profileGeneric.duration() };
		const auto speedGeneric{ profileGeneric.computeSpeed(countIterations, "op") };
		std::cout << "      implementation: " << parser::durationToString(durationCount) << " -> " << speedCount << std::endl;
		std::cout << "      baseline:       " << parser::durationToString(durationBase) << " -> " << speedBase << std::endl;
		std::cout << "      generic:        " << parser::durationToString(durationGeneric) << " -> " << speedGeneric << std::endl;
		std::cout << "      reference:      " << parser::durationToString(durationRef) << " -> " << speedRef << std::endl;
		std::cout << "    verifying..." << std::endl;
		std::cout << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			if ((m_Bits[i] != m_RefBits[i]) || (m_Bits[i] != m_BaseBits[i]) || (m_Rets[i] != m_RefRets[i]) || (m_Rets[i] != m_BaseRets[i]))
			{
				std::cout << "    FAILED:" << std::endl;
				std::cout << "      failing uint_t<" << COUNT_BITS << "," << COMPACT << ">: " << static_cast<std::uintmax_t>(m_Input[i]) << std::endl;
				std::cout << std::endl;
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
		std::cout << "  PASSED" << std::endl;
		std::cout << std::endl;
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
	bool bsf() noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		std::cout << "_________________________________" << std::endl;
		std::cout << "TESTSUITE: uint_t bitscan forward" << std::endl;
		std::cout << std::endl;
		result &= intrinsics::test::bsf<0, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<1, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<2, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<4, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<8, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<16, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<32, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<64, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<3, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<5, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<7, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<11, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<13, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<17, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<19, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<23, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<29, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<31, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<37, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<41, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<43, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<47, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<53, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<59, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<61, false>(durationFast, operationsFast);
		result &= intrinsics::test::bsf<0, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<1, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<2, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<4, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<8, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<16, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<32, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<64, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<3, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<5, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<7, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<11, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<13, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<17, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<19, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<23, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<29, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<31, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<37, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<41, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<43, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<47, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<53, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<59, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::bsf<61, true>(durationCompact, operationsCompact);
		std::cout << "  Performace: " << std::endl;
		std::cout << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		std::cout << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		std::cout << std::endl;
		if (result)
			std::cout << "ALL PASSED" << std::endl;
		else
			std::cout << "SOME FAILED" << std::endl;
		std::cout << "_________________________________" << std::endl;
		std::cout << std::endl;
		return result;
	}
}