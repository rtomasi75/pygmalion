namespace intrinsics::test
{
	namespace detail
	{
		template<typename T>
		T pdep_reference(const T val, T mask) noexcept
		{
			T res{ T(0) };
			for (T bb = T(1); mask; bb += bb)
			{
				if (val & bb)
					res |= mask & -mask;
				mask &= mask - T(1);
			}
			return res;
		}
	}

	template<size_t COUNT_BITS, bool COMPACT>
	bool pdep(typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		using R = typename intrinsics::detail::popcnt_traits<COUNT_BITS>::intType;
		std::cout << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> masked deposition" << std::endl;
		std::cout << std::endl;
		std::cout << "    " << U() << std::endl;
		std::cout << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		std::cout << "    generating " << countIterations << " pairs of uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		U* m_Input1 = new U[countIterations];
		U* m_Input2 = new U[countIterations];
		U* m_Output = new U[countIterations];
		R* m_RefInput1 = new R[countIterations];
		R* m_RefInput2 = new R[countIterations];
		R* m_RefOutput = new R[countIterations];
		size_t* m_Counts = new size_t[countIterations];
		size_t* m_RefCounts = new size_t[countIterations];
		size_t* m_BaseCounts = new size_t[countIterations];
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Input1[i] = U::random();
			m_Input2[i] = U::random();
			m_Input1[i] &= (U::one() << m_Input2[i].populationCount()) - U::one();
			m_RefInput1[i] = static_cast<R>(m_Input1[i]);
			m_RefInput2[i] = static_cast<R>(m_Input2[i]);
		}
		profiler profileImplementation;
		std::cout << "    deposing (uint_t)..." << std::endl;
		profileImplementation.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i] = m_Input1[i].deposePattern(m_Input2[i]);
		profileImplementation.stop();
		const auto durationImplementation{ profileImplementation.duration() };
		const auto speedImplementation{ profileImplementation.computeSpeed(countIterations, "op") };
		std::cout << "    deposing (baseline)..." << std::endl;
		R mask{ 0 };
		if constexpr (COUNT_BITS >= (sizeof(R) * CHAR_BIT))
			mask = static_cast<R>(~R(0));
		else
			mask = static_cast<R>((R(1) << COUNT_BITS) - R(1));
		profiler profileBase;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefOutput[i] = detail::pdep_reference(m_RefInput1[i], m_RefInput2[i]);
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
				std::cout << "        " << m_Input1[i] << std::endl;
				std::cout << "        " << m_Input2[i] << std::endl;
				std::cout << "        " << m_Output[i] << std::endl;
				std::cout << std::endl;
				const R I1{ m_Input1[i] };
				const R I2{ m_Input2[i] };
				const R O{ m_Output[i] };
				const U sum{ m_Input1[i].deposePattern(m_Input2[i]) };
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
	bool pdep() noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		std::cout << "__________________________________________" << std::endl;
		std::cout << "TESTSUITE: uint_t masked deposition" << std::endl;
		std::cout << std::endl;
		result &= intrinsics::test::pdep<0, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<1, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<2, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<4, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<8, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<16, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<32, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<64, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<3, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<5, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<7, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<11, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<13, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<17, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<19, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<23, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<29, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<31, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<37, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<41, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<43, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<47, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<53, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<59, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<61, false>(durationFast, operationsFast);
		result &= intrinsics::test::pdep<0, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<1, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<2, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<4, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<8, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<16, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<32, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<64, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<3, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<5, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<7, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<11, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<13, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<17, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<19, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<23, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<29, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<31, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<37, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<41, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<43, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<47, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<53, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<59, true>(durationCompact, operationsCompact);
		result &= intrinsics::test::pdep<61, true>(durationCompact, operationsCompact);
		std::cout << "  Performace: " << std::endl;
		std::cout << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		std::cout << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		std::cout << std::endl;
		if (result)
			std::cout << "ALL PASSED" << std::endl;
		else
			std::cout << "SOME FAILED" << std::endl;
		std::cout << "__________________________________________" << std::endl;
		std::cout << std::endl;
		return result;
	}
}