namespace intrinsics::test
{
	template<size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	bool score_assignment(std::ostream& str, typename profiler::durationType& durationTo, size_t& operationsTo, typename profiler::durationType& durationFrom, size_t& operationsFrom) noexcept
	{
		bool result{ true };
		using S = score<MANTISSA, SHIFT, MAXDIST>;
		str << "  TEST: score<" << MANTISSA << "," << SHIFT << "," << MAXDIST << "> -> assignment" << std::endl;
		str << std::endl;
		const size_t countIterations{ size_t(1) << 24 };
		str << "    generating " << countIterations << " doubles..." << std::endl;
		double* m_Input = new double[countIterations];
		double* m_Output = new double[countIterations];
		S* m_Values = new S[countIterations];
		for (size_t i = 0; i < countIterations; i++)
		{
			const double max{ static_cast<double>(S::WINNINGVALUE - 1) / static_cast<double>(1 << SHIFT) };
			const double min{ static_cast<double>(S::LOSINGVALUE + 1) / static_cast<double>(1 << SHIFT) };
			const double delta{ max - min };
			const double step{ 1.0 / static_cast<double>(1 << SHIFT) };
			const int steps = static_cast<int>(std::floor(delta / step));
			m_Input[i] = static_cast<double>(std::rand() % steps) * step + min;
		}
		profiler profile;
		str << "    casting to score<" << MANTISSA << "," << SHIFT << "," << MAXDIST << ">..." << std::endl;
		profile.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Values[i] = static_cast<S>(m_Input[i]);
		profile.stop();
		const auto durationCastTo{ profile.duration() };
		const auto speedTo{ profile.computeSpeed(countIterations, "op") };
		str << "      " << parser::durationToString(durationCastTo) << " -> " << speedTo << std::endl;
		str << "    casting from score<" << MANTISSA << "," << SHIFT << "," << MAXDIST << ">..." << std::endl;
		profile.start();
		for (size_t i = 0; i < countIterations; i++)
			m_Output[i] = static_cast<double>(m_Values[i]);
		profile.stop();
		const auto durationCastFrom{ profile.duration() };
		const auto speedFrom{ profile.computeSpeed(countIterations, "op") };
		str << "      " << parser::durationToString(durationCastFrom) << " -> " << speedFrom << std::endl;
		str << "    verifying..." << std::endl;
		str << std::endl;
		for (size_t i = 0; i < countIterations; i++)
		{
			if (m_Input[i] != m_Output[i])
			{
				str << "    FAILED:" << std::endl;
				str << "      failing double: " << m_Input[i] << std::endl;
				str << std::endl;
				const double input{ m_Input[i] };
				S value;
				value = static_cast<S>(input);
				const double output{ static_cast<double>(value) };
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
		str << "  PASSED" << std::endl;
		str << std::endl;
		delete[] m_Input;
		delete[] m_Output;
		delete[] m_Values;
		return result;
	}
	bool score_assignment(std::ostream& str) noexcept
	{
		typename profiler::durationType durationTo{ 0 };
		size_t operationsTo(0);
		typename profiler::durationType durationFrom{ 0 };
		size_t operationsFrom(0);
		bool result{ true };
		str << "___________________________" << std::endl;
		str << "TESTSUITE: score assignment" << std::endl;
		str << std::endl;
		result &= intrinsics::test::score_assignment<4, 2, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<4, 4, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<6, 4, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<8, 4, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<12, 6, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<12, 8, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<12, 12, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<16, 6, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<16, 8, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<16, 12, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<20, 6, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<20, 8, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<20, 12, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<24, 6, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<24, 8, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<24, 12, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<28, 6, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<28, 8, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<28, 12, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<32, 6, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<32, 8, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		result &= intrinsics::test::score_assignment<32, 12, 4>(str, durationTo, operationsTo, durationFrom, operationsFrom);
		str << "  Performace: " << std::endl;
		str << "    -> " << profiler::speed(operationsTo, durationTo, "op") << std::endl;
		str << "    <- " << profiler::speed(operationsFrom, durationFrom, "op") << std::endl;
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