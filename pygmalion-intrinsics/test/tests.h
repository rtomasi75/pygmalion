namespace intrinsics::test
{
	template<size_t COUNT_BITS, bool COMPACT, typename T, typename = typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<bool, T>::value>::type>
	bool assignment() noexcept
	{
		using U = uint_t<COUNT_BITS, COMPACT>;
		std::cout << "  TEST: uint_t <" << COUNT_BITS << "," << COMPACT << "> -> " << (sizeof(T) * CHAR_BIT) << "bit assignments" << std::endl;
		std::cout << std::endl;
		std::cout << "    "<< U() << std::endl;
		std::cout << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		T* m_Input = new T[countIterations];
		T* m_Output = new T[countIterations];
		U* m_Values = new U[countIterations];
		std::cout << "    generating " << countIterations << " unsigned " << COUNT_BITS << "bit integers..." << std::endl;
		T mask{ 0 };
		for (size_t i = 0; i < countIterations; i++)
		{
			if constexpr (COUNT_BITS >= (sizeof(T) * CHAR_BIT))
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
		std::cout << "    casting to uint_t <" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		for (size_t i = 0; i < countIterations; i++)
			m_Values[i] = m_Input[i];
		std::cout << "    casting from uint_t <" << COUNT_BITS << "," << COMPACT << ">..." << std::endl;
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i] = m_Values[i];
		std::cout << "    verifying..." << std::endl;
		std::cout << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			if (m_Input[i] != m_Output[i])
			{
				std::cout << "    FAILED:" << std::endl;
				std::cout << "      failing " << countIterations << " unsigned " << (sizeof(T) * CHAR_BIT) << "bit integer: " << static_cast<std::uintmax_t>(m_Input[i]) << std::endl;
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
		std::cout << "  PASSED" << std::endl;
		std::cout << std::endl;
		delete[] m_Input;
		delete[] m_Output;
		delete[] m_Values;
		return true;
	}
	bool assignments() noexcept
	{
		bool result{ true };
		std::cout << "_____________________________" << std::endl;
		std::cout << "TESTSUITE: uint_t assignments" << std::endl;
		std::cout << "_____________________________" << std::endl;
		std::cout << std::endl;
		result &= intrinsics::test::assignment<1, false, std::uint_least8_t>();
		result &= intrinsics::test::assignment<2, false, std::uint_least8_t>();
		result &= intrinsics::test::assignment<4, false, std::uint_least8_t>();
		result &= intrinsics::test::assignment<8, false, std::uint_least8_t>();
		result &= intrinsics::test::assignment<16, false, std::uint_least16_t>();
		result &= intrinsics::test::assignment<32, false, std::uint_least32_t>();
		result &= intrinsics::test::assignment<64, false, std::uint_least64_t>();
		result &= intrinsics::test::assignment<3, false, std::uint_least8_t>();
		result &= intrinsics::test::assignment<5, false, std::uint_least8_t>();
		result &= intrinsics::test::assignment<7, false, std::uint_least8_t>();
		result &= intrinsics::test::assignment<11, false, std::uint_least16_t>();
		result &= intrinsics::test::assignment<13, false, std::uint_least16_t>();
		result &= intrinsics::test::assignment<17, false, std::uint_least32_t>();
		result &= intrinsics::test::assignment<19, false, std::uint_least32_t>();
		result &= intrinsics::test::assignment<23, false, std::uint_least32_t>();
		result &= intrinsics::test::assignment<29, false, std::uint_least32_t>();
		result &= intrinsics::test::assignment<31, false, std::uint_least32_t>();
		result &= intrinsics::test::assignment<37, false, std::uint_least64_t>();
		result &= intrinsics::test::assignment<41, false, std::uint_least64_t>();
		result &= intrinsics::test::assignment<43, false, std::uint_least64_t>();
		result &= intrinsics::test::assignment<47, false, std::uint_least64_t>();
		result &= intrinsics::test::assignment<53, false, std::uint_least64_t>();
		result &= intrinsics::test::assignment<59, false, std::uint_least64_t>();
		result &= intrinsics::test::assignment<61, false, std::uint_least64_t>();
		result &= intrinsics::test::assignment<1, true, std::uint_least8_t>();
		result &= intrinsics::test::assignment<2, true, std::uint_least8_t>();
		result &= intrinsics::test::assignment<4, true, std::uint_least8_t>();
		result &= intrinsics::test::assignment<8, true, std::uint_least8_t>();
		result &= intrinsics::test::assignment<16, true, std::uint_least16_t>();
		result &= intrinsics::test::assignment<32, true, std::uint_least32_t>();
		result &= intrinsics::test::assignment<64, true, std::uint_least64_t>();
		result &= intrinsics::test::assignment<3, true, std::uint_least8_t>();
		result &= intrinsics::test::assignment<5, true, std::uint_least8_t>();
		result &= intrinsics::test::assignment<7, true, std::uint_least8_t>();
		result &= intrinsics::test::assignment<11, true, std::uint_least16_t>();
		result &= intrinsics::test::assignment<13, true, std::uint_least16_t>();
		result &= intrinsics::test::assignment<17, true, std::uint_least32_t>();
		result &= intrinsics::test::assignment<19, true, std::uint_least32_t>();
		result &= intrinsics::test::assignment<23, true, std::uint_least32_t>();
		result &= intrinsics::test::assignment<29, true, std::uint_least32_t>();
		result &= intrinsics::test::assignment<31, true, std::uint_least32_t>();
		result &= intrinsics::test::assignment<37, true, std::uint_least64_t>();
		result &= intrinsics::test::assignment<41, true, std::uint_least64_t>();
		result &= intrinsics::test::assignment<43, true, std::uint_least64_t>();
		result &= intrinsics::test::assignment<47, true, std::uint_least64_t>();
		result &= intrinsics::test::assignment<53, true, std::uint_least64_t>();
		result &= intrinsics::test::assignment<59, true, std::uint_least64_t>();
		result &= intrinsics::test::assignment<61, true, std::uint_least64_t>();
		if(result)
			std::cout << "ALL PASSED" << std::endl;
		else
			std::cout << "SOME FAILED" << std::endl;
		std::cout << "_____________________________" << std::endl;
		std::cout << std::endl;
		return result;
	}

}