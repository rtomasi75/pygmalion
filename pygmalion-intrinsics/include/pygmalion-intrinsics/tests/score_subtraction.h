namespace intrinsics::test
{
	template<size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	bool score_subtraction(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		bool result{ true };
		using S = score<MANTISSA, SHIFT, MAXDIST>;
		str << "  TEST: score<" << MANTISSA << "," << SHIFT << "," << MAXDIST << "> -> binary subtraction operator" << std::endl;
		str << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		str << "    generating " << countIterations << " pairs of doubles..." << std::endl;
		double* m_Input1 = new double[countIterations];
		double* m_Input2 = new double[countIterations];
		double* m_Output = new double[countIterations];
		S* m_ValuesI1 = new S[countIterations];
		S* m_ValuesI2 = new S[countIterations];
		S* m_ValuesO = new S[countIterations];
		for (size_t i = 0; i < countIterations; i++)
		{
			const double max{ static_cast<double>(S::WINNINGVALUE / 2 - 1) / static_cast<double>(1 << SHIFT) };
			const double min{ static_cast<double>(S::LOSINGVALUE / 2 + 1) / static_cast<double>(1 << SHIFT) };
			const double delta{ max - min };
			const double step{ 1.0 / static_cast<double>(1 << SHIFT) };
			const int steps = static_cast<int>(std::floor(delta / step));
			m_Input1[i] = static_cast<double>(std::rand() % steps) * step + min;
			m_ValuesI1[i] = static_cast<S>(m_Input1[i]);
		}
		for (size_t i = 0; i < countIterations; i++)
		{
			const double max{ static_cast<double>(S::WINNINGVALUE / 2 - 1) / static_cast<double>(1 << SHIFT) };
			const double min{ static_cast<double>(S::LOSINGVALUE / 2 + 1) / static_cast<double>(1 << SHIFT) };
			const double delta{ max - min };
			const double step{ 1.0 / static_cast<double>(1 << SHIFT) };
			const int steps = static_cast<int>(std::floor(delta / step));
			m_Input2[i] = static_cast<double>(std::rand() % steps) * step + min;
			m_ValuesI2[i] = static_cast<S>(m_Input2[i]);
		}
		profiler profile;
		str << "    subtracting..." << std::endl;
		profile.start();
		for (size_t i = 0; i < countIterations; i++)
			m_ValuesO[i] = m_ValuesI1[i] - m_ValuesI2[i];
		profile.stop();
		const auto durationCastTo{ profile.duration() };
		const auto speedTo{ profile.computeSpeed(countIterations, "op") };
		str << "      " << parser::durationToString(durationCastTo) << " -> " << speedTo << std::endl;
		str << "    verifying..." << std::endl;
		str << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Output[i] = static_cast<double>(m_ValuesO[i]);
			if ((m_Input1[i] - m_Input2[i]) != m_Output[i])
			{
				str << "    FAILED:" << std::endl;
				str << "      failing operation: " << m_ValuesI1[i] << " - " << m_ValuesI2[i] << " = " << m_ValuesO[i] << std::endl;
				str << std::endl;
				const double input1{ m_Input1[i] };
				const double input2{ m_Input2[i] };
				S value1;
				value1 = static_cast<S>(input1);
				S value2;
				value2 = static_cast<S>(input2);
				const double output{ static_cast<double>(value1 + value2) };
				delete[] m_Input1;
				delete[] m_Input2;
				delete[] m_Output;
				delete[] m_ValuesI1;
				delete[] m_ValuesI2;
				delete[] m_ValuesO;
				return false;
			}
		}
		duration += durationCastTo;
		operations += countIterations;
		str << "  PASSED" << std::endl;
		str << std::endl;
		delete[] m_Input1;
		delete[] m_Input2;
		delete[] m_Output;
		delete[] m_ValuesI1;
		delete[] m_ValuesI2;
		delete[] m_ValuesO;
		return result;
	}
	bool score_subtraction(std::ostream& str) noexcept
	{
		typename profiler::durationType duration{ 0 };
		size_t operations(0);
		bool result{ true };
		str << "____________________________________________" << std::endl;
		str << "TESTSUITE: score binary subtraction operator" << std::endl;
		str << std::endl;
		result &= intrinsics::test::score_subtraction<4, 2, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<4, 4, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<6, 4, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<8, 4, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<12, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<12, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<12, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<16, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<16, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<16, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<20, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<20, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<20, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<24, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<24, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<24, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<28, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<28, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<28, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<32, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<32, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_subtraction<32, 12, 4>(str, duration, operations);
		str << "  Performace: " << std::endl;
		str << "    Total: " << profiler::speed(operations, duration, "op") << std::endl;
		str << std::endl;
		if (result)
			str << "ALL PASSED" << std::endl;
		else
			str << "SOME FAILED" << std::endl;
		str << "____________________________________________" << std::endl;
		str << std::endl;
		return result;
	}
}