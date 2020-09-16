namespace intrinsics::test
{
	namespace detail
	{
		template<typename T>
		T pext_reference(const T val, T mask) noexcept
		{
			T res = 0;
			for (T bb = 1; mask; bb += bb)
			{
				if (val & mask & -mask)
					res |= bb;
				mask &= mask - 1;
			}
			return res;
			return res;
		}
	}

	template<size_t COUNT_BITS, bool COMPACT>
	bool pext(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		using R = typename intrinsics::detail::popcnt_traits<COUNT_BITS>::intType;
		str << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> masked extraction" << std::endl;
		str << std::endl;
		str << "    " << U() << std::endl;
		str << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		str << "    generating " << countIterations << " pairs of uint_t<" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
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
			m_RefInput1[i] = static_cast<R>(m_Input1[i]);
			m_RefInput2[i] = static_cast<R>(m_Input2[i]);
		}
		profiler profileImplementation;
		str << "    extracting (uint_t)..." << std::endl;
		profileImplementation.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i] = m_Input1[i].extractPattern(m_Input2[i]);
		profileImplementation.stop();
		const auto durationImplementation{ profileImplementation.duration() };
		const auto speedImplementation{ profileImplementation.computeSpeed(countIterations, "op") };
		str << "    extracting (baseline)..." << std::endl;
		R mask{ 0 };
		if constexpr (COUNT_BITS >= (sizeof(R) * CHAR_BIT))
			mask = static_cast<R>(~R(0));
		else
			mask = static_cast<R>((R(1) << COUNT_BITS) - R(1));
		profiler profileBase;
		profileBase.start();
		for (size_t i = 0; i < countIterations; i++)
			m_RefOutput[i] = detail::pext_reference(m_RefInput1[i], m_RefInput2[i]);
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
				str << "        " << static_cast<std::uintmax_t>(m_Input1[i]) << " + " << static_cast<std::uintmax_t>(m_Input2[i]) << " = " << static_cast<std::uintmax_t>(m_Output[i]) << " (!?)" << std::endl;
				str << std::endl;
				const R I1{ m_Input1[i] };
				const R I2{ m_Input2[i] };
				const R O{ m_Output[i] };
				const U sum{ m_Input1[i].extractPattern(m_Input2[i]) };
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
	bool pext(std::ostream& str) noexcept
	{
		typename profiler::durationType durationCompact{ 0 };
		size_t operationsCompact(0);
		typename profiler::durationType durationFast{ 0 };
		size_t operationsFast(0);
		bool result{ true };
		str << "__________________________________________" << std::endl;
		str << "TESTSUITE: uint_t masked extraction" << std::endl;
		str << std::endl;
		result &= intrinsics::test::pext<0, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<1, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<2, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<4, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<8, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<16, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<32, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<64, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<3, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<5, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<7, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<11, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<13, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<17, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<19, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<23, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<29, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<31, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<37, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<41, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<43, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<47, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<53, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<59, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<61, false>(str, durationFast, operationsFast);
		result &= intrinsics::test::pext<0, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<1, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<2, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<4, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<8, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<16, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<32, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<64, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<3, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<5, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<7, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<11, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<13, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<17, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<19, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<23, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<29, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<31, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<37, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<41, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<43, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<47, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<53, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<59, true>(str, durationCompact, operationsCompact);
		result &= intrinsics::test::pext<61, true>(str, durationCompact, operationsCompact);
		str << "  Performace: " << std::endl;
		str << "    Compact:  " << profiler::speed(operationsCompact, durationCompact, "op") << std::endl;
		str << "    Fast:     " << profiler::speed(operationsFast, durationFast, "op") << std::endl;
		str << std::endl;
		if (result)
			str << "ALL PASSED" << std::endl;
		else
			str << "SOME FAILED" << std::endl;
		str << "__________________________________________" << std::endl;
		str << std::endl;
		return result;
	}
}