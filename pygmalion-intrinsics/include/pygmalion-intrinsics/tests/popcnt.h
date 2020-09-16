namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT>
	bool popcnt(typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		using R = typename intrinsics::detail::popcnt_traits<COUNT_BITS>::intType;
		std::cout << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> population counts" << std::endl;
		std::cout << std::endl;
		std::cout << "    " << U() << std::endl;
		std::cout << "    " << U::populationCount_Intrinsic << std::endl;
		std::cout << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		std::cout << "    generating " << countIterations << "x uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		U* m_Input = new U[countIterations];
		R* m_RefInput = new R[countIterations];
		R* m_BaseInput = new R[countIterations];
		size_t* m_Counts = new size_t[countIterations];
		size_t* m_RefCounts = new size_t[countIterations];
		size_t* m_BaseCounts = new size_t[countIterations];
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input[i] = U::random();
			m_RefInput[i] = static_cast<R>(m_Input[i]);
			m_BaseInput[i] = static_cast<R>(m_Input[i]);
		}
		profiler profileCount;
		profiler profileBase;
		profiler profileRef;
		profiler profileGeneric;
		std::cout << "    counting bits (uint_t)..." << std::endl;
		profileCount.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Counts[i] = m_Input[i].populationCount();
		profileCount.stop();
		const auto durationCount{ profileCount.duration() };
		const auto speedCount{ profileCount.computeSpeed(countIterations, "op") };
		std::cout << "    counting bits (baseline)..." << std::endl;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_BaseCounts[i] = intrinsics::detail::popcnt_traits<COUNT_BITS>::baseline(m_BaseInput[i]);
		profileBase.stop();
		const auto durationBase{ profileBase.duration() };
		const auto speedBase{ profileBase.computeSpeed(countIterations, "op") };
		std::cout << "    counting bits (reference)..." << std::endl;
		profileRef.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefCounts[i] = intrinsics::detail::popcnt_traits<COUNT_BITS>::reference(m_RefInput[i]);
		profileRef.stop();
		const auto durationRef{ profileRef.duration() };
		const auto speedRef{ profileRef.computeSpeed(countIterations, "op") };
		profileGeneric.start();
		for (size_t i = 0; i < countIterations; i++)
			m_BaseCounts[i] |= intrinsics::detail::popcnt_traits<COUNT_BITS>::generic(m_BaseInput[i]);
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
			if ((m_Counts[i] != m_RefCounts[i]) || (m_Counts[i] != m_BaseCounts[i]))
			{
				std::cout << "    FAILED:" << std::endl;
				std::cout << "      failing uint_t<" << COUNT_BITS << "," << COMPACT << ">: " << static_cast<std::uintmax_t>(m_Input[i]) << std::endl;
				std::cout << std::endl;
				const size_t count{ m_Input[i].populationCount() };
				delete[] m_RefInput;
				delete[] m_BaseInput;
				delete[] m_Input;
				delete[] m_Counts;
				delete[] m_RefCounts;
				delete[] m_BaseCounts;
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
		delete[] m_Counts;
		delete[] m_RefCounts;
		delete[] m_BaseCounts;
		return true;
	}
	bool popcnt() noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		std::cout << "___________________________________" << std::endl;
		std::cout << "TESTSUITE: uint_t population counts" << std::endl;
		std::cout << std::endl;
		result &= intrinsics::test::popcnt<0, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<1, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<2, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<4, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<8, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<16, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<32, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<64, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<3, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<5, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<7, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<11, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<13, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<17, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<19, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<23, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<29, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<31, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<37, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<41, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<43, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<47, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<53, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<59, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<61, false>(durationFast, operationsFast);
		result &= intrinsics::test::popcnt<0, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<1, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<2, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<4, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<8, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<16, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<32, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<64, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<3, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<5, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<7, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<11, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<13, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<17, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<19, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<23, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<29, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<31, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<37, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<41, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<43, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<47, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<53, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<59, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::popcnt<61, true>(durationCompact, operationsCompact);
		std::cout << "  Performace: " << std::endl;
		std::cout << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		std::cout << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		std::cout << std::endl;
		if (result)
			std::cout << "ALL PASSED" << std::endl;
		else
			std::cout << "SOME FAILED" << std::endl;
		std::cout << "___________________________________" << std::endl;
		std::cout << std::endl;
		return result;
	}
}