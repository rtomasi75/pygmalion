namespace intrinsics::test
{
	template<size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	bool score_addition_inplace(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		bool result{ true };
		using S = score<MANTISSA, SHIFT, MAXDIST>;
		str << "  TEST: score<" << MANTISSA << "," << SHIFT << "," << MAXDIST << "> -> unary addition operator" << std::endl;
		str << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		str << "    generating " << countIterations << " pairs of doubles..." << std::endl;
		double* m_Input1 = new double[countIterations];
		double* m_Input2 = new double[countIterations];
		double* m_Output = new double[countIterations];
		S* m_ValuesI1 = new S[countIterations];
		S* m_ValuesI2 = new S[countIterations];
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
		str << "    adding..." << std::endl;
		profile.start();
		for (size_t i = 0; i < countIterations; i++)
			m_ValuesI1[i] += m_ValuesI2[i];
		profile.stop();
		const auto durationCastTo{ profile.duration() };
		const auto speedTo{ profile.computeSpeed(countIterations, "op") };
		str << "      " << parser::durationToString(durationCastTo) << " -> " << speedTo << std::endl;
		str << "    verifying..." << std::endl;
		str << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Output[i] = static_cast<double>(m_ValuesI1[i]);
			if ((m_Input1[i] + m_Input2[i]) != m_Output[i])
			{
				str << "    FAILED:" << std::endl;
				str << "      failing operation: " << m_Input1[i] << " + " << m_Input2[i] << " = " << m_ValuesI2[i] << std::endl;
				str << std::endl;
				const double input1{ m_Input1[i] };
				const double input2{ m_Input2[i] };
				S value1;
				value1 = static_cast<S>(input1);
				S value2;
				value2 = static_cast<S>(input2);
				value1 += value2;
				const double output{ static_cast<double>(value1) };
				delete[] m_Input1;
				delete[] m_Input2;
				delete[] m_Output;
				delete[] m_ValuesI1;
				delete[] m_ValuesI2;
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
		return result;
	}
	bool score_addition_inplace(std::ostream& str) noexcept
	{
		typename profiler::durationType duration{ 0 };
		size_t operations(0);
		bool result{ true };
		str << "________________________________________" << std::endl;
		str << "TESTSUITE: score unary addition operator" << std::endl;
		str << std::endl;
		result &= intrinsics::test::score_addition_inplace<4, 2, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<4, 4, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<6, 4, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<8, 4, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<12, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<12, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<12, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<16, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<16, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<16, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<20, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<20, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<20, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<24, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<24, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<24, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<28, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<28, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<28, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<32, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<32, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_addition_inplace<32, 12, 4>(str, duration, operations);
		str << "  Performace: " << std::endl;
		str << "    Total: " << profiler::speed(operations, duration, "op") << std::endl;
		str << std::endl;
		if (result)
			str << "ALL PASSED" << std::endl;
		else
			str << "SOME FAILED" << std::endl;
		str << "________________________________________" << std::endl;
		str << std::endl;
		return result;
	}
}