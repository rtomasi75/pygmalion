namespace intrinsics::test
{
	template<size_t MANTISSA1, size_t SHIFT1, size_t MAXDIST1, size_t MANTISSA2, size_t SHIFT2, size_t MAXDIST2>
	bool score_conversion(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		bool result{ true };
		using S1 = score<MANTISSA1, SHIFT1, MAXDIST1>;
		using S2 = score<MANTISSA2, SHIFT2, MAXDIST2>;
		str << "  TEST: score<" << MANTISSA1 << "," << SHIFT1 << "," << MAXDIST1 << "> -> score<" << MANTISSA2 << "," << SHIFT2 << "," << MAXDIST2 << "> conversion" << std::endl;
		str << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		str << "    generating " << countIterations << " instances of score<" << MANTISSA1 << "," << SHIFT1 << "," << MAXDIST1 << ">..." << std::endl;
		double* m_Input = new double[countIterations];
		double* m_Output = new double[countIterations];
		S1* m_Values1 = new S1[countIterations];
		S2* m_Values2 = new S2[countIterations];
		for (size_t i = 0; i < countIterations; i++)
		{
			const double max1{ static_cast<double>(S1::WINNINGVALUE - 1) / static_cast<double>(1 << SHIFT1) };
			const double min1{ static_cast<double>(S1::LOSINGVALUE + 1) / static_cast<double>(1 << SHIFT1) };
			const double max2{ static_cast<double>(S2::WINNINGVALUE - 1) / static_cast<double>(1 << SHIFT2) };
			const double min2{ static_cast<double>(S2::LOSINGVALUE + 1) / static_cast<double>(1 << SHIFT2) };
			double max{ std::min(max1,max2) };
			double min{ std::max(min1,min2) };
			max -= std::remainder(max, 1.0 / static_cast<double>(1 << std::min(SHIFT1, SHIFT2)));
			min += (1.0 / static_cast<double>(1 << std::min(SHIFT1, SHIFT2))) - std::remainder(min, 1.0 / static_cast<double>(1 << std::min(SHIFT1, SHIFT2)));
			const double delta{ max - min };
			const double step{ 1.0 / static_cast<double>(1 << std::min(SHIFT1, SHIFT2)) };
			const int steps = static_cast<int>(std::floor(delta / step));
			m_Input[i] = static_cast<double>(std::rand() % steps) * step + min;
			m_Values1[i] = static_cast<S1>(m_Input[i]);
			assert(std::abs(m_Values1[i].get_Value()) < S1::WINNINGVALUE);
		}
		str << "    casting to score<" << MANTISSA2 << "," << SHIFT2 << "," << MAXDIST2 << ">..." << std::endl;
		profiler profile;
		profile.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Values2[i] = static_cast<S2>(m_Values1[i]);
		profile.stop();
		const auto durationCast{ profile.duration() };
		const auto speedFrom{ profile.computeSpeed(countIterations, "op") };
		str << "      " << parser::durationToString(durationCast) << " -> " << speedFrom << std::endl;
		str << "    verifying..." << std::endl;
		str << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			m_Output[i] = static_cast<double>(m_Values2[i]);
			if (m_Input[i] != m_Output[i])
			{
				str << "    FAILED:" << std::endl;
				str << "      failing double: " << m_Input[i] << std::endl;
				str << std::endl;
				const double input{ m_Input[i] };
				S1 value1;
				S2 value2;
				value1 = static_cast<S1>(input);
				value2 = static_cast<S2>(value1);
				const double output{ static_cast<double>(value2) };
				delete[] m_Input;
				delete[] m_Output;
				delete[] m_Values1;
				delete[] m_Values2;
				return false;
			}
		}
		duration += durationCast;
		operations += countIterations;
		str << "  PASSED" << std::endl;
		str << std::endl;
		delete[] m_Input;
		delete[] m_Output;
		delete[] m_Values1;
		delete[] m_Values2;
		return result;
	}
	bool score_conversion(std::ostream& str) noexcept
	{
		typename profiler::durationType duration{ 0 };
		size_t operations(0);
		bool result{ true };
		str << "___________________________" << std::endl;
		str << "TESTSUITE: score conversion" << std::endl;
		str << std::endl;
		result &= intrinsics::test::score_conversion<4, 2, 4, 32, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<4, 4, 4, 32, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<6, 4, 4, 32, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<8, 4, 4, 28, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<12, 6, 4, 28, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<12, 8, 4, 28, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<12, 12, 4, 24, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<16, 6, 4, 24, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<16, 8, 4, 24, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<16, 12, 4, 4, 2, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<20, 6, 4, 20, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<20, 8, 4, 20, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<20, 12, 4, 20, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<24, 6, 4, 16, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<24, 8, 4, 16, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<24, 12, 4, 16, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<28, 6, 4, 12, 12, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<28, 8, 4, 12, 8, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<28, 12, 4, 12, 6, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<32, 6, 4, 8, 4, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<32, 8, 4, 6, 4, 4>(str, duration, operations);
		result &= intrinsics::test::score_conversion<32, 12, 4, 4, 4, 4>(str, duration, operations);
		str << "  Performace: " << std::endl;
		str << "    Total: " << profiler::speed(operations, duration, "op") << std::endl;
		str << std::endl;
		if (result)
			str << "ALL PASSED" << std::endl;
		else
			str << "SOME FAILED" << std::endl;
		str << "___________________________" << std::endl;
		str << std::endl;
		return result;
	}
}