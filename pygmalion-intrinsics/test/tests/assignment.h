namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT, typename = typename std::enable_if<(COUNT_BITS <= 64)>::type>
	bool assignment(typename profiler::durationType& durationTo, size_t& operationsTo, typename profiler::durationType& durationFrom, size_t& operationsFrom) noexcept
	{
		using T = typename intrinsics::detail::popcnt_traits<COUNT_BITS>::intType;
		using U = uint_t<COUNT_BITS, COMPACT>;
		std::cout << "  TEST: uint_t<" << COUNT_BITS << "," << COMPACT << "> -> " << (sizeof(T) * CHAR_BIT) << "bit assignments" << std::endl;
		std::cout << std::endl;
		std::cout << "    " << U() << std::endl;
		std::cout << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		std::cout << "    generating " << countIterations << " unsigned " << COUNT_BITS << "bit integers..." << std::endl;
		T* m_Input = new T[countIterations];
		T* m_Output = new T[countIterations];
		U* m_Values = new U[countIterations];
		T mask{ 0 };
		for (size_t i = 0; i < countIterations; i++)
		{
			if constexpr (COUNT_BITS == 0)
			{
				m_Input[i] = false;
			}
			else if constexpr (COUNT_BITS >= (sizeof(T) * CHAR_BIT))
			{
				mask = ~T(0);
				m_Input[i] = static_cast<T>(std::rand() % mask);
			}
			else
			{
				mask = static_cast<T>((T(1) << COUNT_BITS) - T(1));
				m_Input[i] = static_cast<T>(std::rand() % std::min<T>(mask, std::numeric_limits<T>::max()));
			}
		}
		profiler profile;
		std::cout << "    casting to uint_t <" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		profile.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Values[i] = m_Input[i];
		profile.stop();
		const auto durationCastTo{ profile.duration() };
		const auto speedTo{ profile.computeSpeed(countIterations, "op") };
		std::cout << "      " << parser::durationToString(durationCastTo) << " -> " << speedTo << std::endl;
		std::cout << "    casting from uint_t <" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		profile.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i] = static_cast<T>(m_Values[i]);
		profile.stop();
		const auto durationCastFrom{ profile.duration() };
		const auto speedFrom{ profile.computeSpeed(countIterations, "op") };
		std::cout << "      " << parser::durationToString(durationCastTo) << " -> " << speedFrom << std::endl;
		std::cout << "    verifying..." << std::endl;
		std::cout << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			if (m_Input[i] != m_Output[i])
			{
				std::cout << "    FAILED:" << std::endl;
				std::cout << "      failing unsigned " << (sizeof(T) * CHAR_BIT) << "bit integer: " << static_cast<std::uintmax_t>(m_Input[i]) << std::endl;
				std::cout << std::endl;
				const T input{ m_Input[i] };
				U value;
				value = input;
				const T output{ value };
				delete[] m_Input;
				delete[] m_Output;
				delete[] m_Values;
				return false;
			}
		}
		durationFrom += durationCastFrom;
		durationTo += durationCastTo;
		operationsFrom += countIterations;
		operationsTo += countIterations;
		std::cout << "  PASSED" << std::endl;
		std::cout << std::endl;
		delete[] m_Input;
		delete[] m_Output;
		delete[] m_Values;
		return true;
	}
	bool assignment() noexcept
	{
		typename profiler::durationType durationToCompact{ 0 };
		size_t operationsToCompact(0);
		typename profiler::durationType durationFromCompact{ 0 };
		size_t operationsFromCompact(0);
		typename profiler::durationType durationToFast{ 0 };
		size_t operationsToFast(0);
		typename profiler::durationType durationFromFast{ 0 };
		size_t operationsFromFast(0);
		bool result{ true };
		std::cout << "_____________________________" << std::endl;
		std::cout << "TESTSUITE: uint_t assignments" << std::endl;
		std::cout << std::endl;
		result &= intrinsics::test::assignment<0, false, std::uint_fast8_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<1, false, std::uint_fast8_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<2, false, std::uint_fast8_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<4, false, std::uint_fast8_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<8, false, std::uint_fast8_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<16, false, std::uint_fast16_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<32, false, std::uint_fast32_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<64, false, std::uint_fast64_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<3, false, std::uint_fast8_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<5, false, std::uint_fast8_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<7, false, std::uint_fast8_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<11, false, std::uint_fast16_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<13, false, std::uint_fast16_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<17, false, std::uint_fast32_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<19, false, std::uint_fast32_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<23, false, std::uint_fast32_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<29, false, std::uint_fast32_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<31, false, std::uint_fast32_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<37, false, std::uint_fast64_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<41, false, std::uint_fast64_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<43, false, std::uint_fast64_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<47, false, std::uint_fast64_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<53, false, std::uint_fast64_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<59, false, std::uint_fast64_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<61, false, std::uint_fast64_t>(durationToFast, operationsToFast, durationFromFast, operationsFromFast);
		result &= intrinsics::test::assignment<0, true, std::uint_fast8_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<1, true, std::uint_fast8_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<2, true, std::uint_fast8_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<4, true, std::uint_fast8_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<8, true, std::uint_fast8_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<16, true, std::uint_fast16_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<32, true, std::uint_fast32_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<64, true, std::uint_fast64_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<3, true, std::uint_fast8_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<5, true, std::uint_fast8_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<7, true, std::uint_fast8_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<11, true, std::uint_fast16_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<13, true, std::uint_fast16_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<17, true, std::uint_fast32_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<19, true, std::uint_fast32_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<23, true, std::uint_fast32_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<29, true, std::uint_fast32_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<31, true, std::uint_fast32_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<37, true, std::uint_fast64_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<41, true, std::uint_fast64_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<43, true, std::uint_fast64_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<47, true, std::uint_fast64_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<53, true, std::uint_fast64_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<59, true, std::uint_fast64_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		result &= intrinsics::test::assignment<61, true, std::uint_fast64_t>(durationToCompact, operationsToCompact, durationFromCompact, operationsFromCompact);
		std::cout << "  Performace: " << std::endl;
		std::cout << "    Compact:  -> " << profiler::speed(operationsToCompact, durationToCompact, "op") << std::endl;
		std::cout << "              <- " << profiler::speed(operationsFromCompact, durationFromCompact, "op") << std::endl;
		std::cout << "    Fast:     -> " << profiler::speed(operationsToFast, durationToFast, "op") << std::endl;
		std::cout << "              <- " << profiler::speed(operationsFromFast, durationFromFast, "op") << std::endl;
		std::cout << std::endl;
		if (result)
			std::cout << "ALL PASSED" << std::endl;
		else
			std::cout << "SOME FAILED" << std::endl;
		std::cout << "_____________________________" << std::endl;
		std::cout << std::endl;
		return result;
	}

}