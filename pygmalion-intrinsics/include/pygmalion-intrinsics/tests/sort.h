namespace intrinsics::test
{
	template<typename VALUE, typename SCORE, size_t LENGTH>
	bool sort(std::ostream& str, typename profiler::durationType& duration, size_t& operations) noexcept
	{
		const size_t reps{ 1024 * 32 };
		str << "  TEST: sort<" << CHAR_BIT * sizeof(VALUE) << "," << CHAR_BIT * sizeof(SCORE) << "> with n=" << LENGTH << std::endl;
		str << std::endl;
		std::default_random_engine generator;
		str << "    generating " << reps * LENGTH << " std::uint" << CHAR_BIT * sizeof(VALUE) << "_t" << std::endl;
		std::uniform_int_distribution<unsigned long long> distributionV(0, VALUE(1) << (sizeof(VALUE) * CHAR_BIT - 1));
		VALUE* m_Value = new VALUE[reps * LENGTH];
		VALUE* m_ValueRef = new VALUE[reps * LENGTH];
		for (size_t i = 0; i < reps * LENGTH; i++)
		{
			m_Value[i] = distributionV(generator);
			m_ValueRef[i] = m_Value[i];
		}
		str << "    generating " << reps * LENGTH << " std::int" << CHAR_BIT * sizeof(SCORE) << "_t" << std::endl;
		std::uniform_int_distribution<long long> distributionS(-(SCORE(1) << (sizeof(SCORE) * CHAR_BIT - 2)), SCORE(1) << (sizeof(SCORE) * CHAR_BIT - 2));
		SCORE* m_Score = new SCORE[reps * LENGTH];
		SCORE* m_ScoreRef = new SCORE[reps * LENGTH];
		for (size_t i = 0; i < reps * LENGTH; i++)
		{
			m_Score[i] = distributionS(generator);
			m_ScoreRef[i] = m_Score[i];
		}
		profiler profileImplementation;
		str << "    sorting..." << std::endl;
		profileImplementation.start();
		for (size_t i = 0; i < reps; i++)
			pygmalion::sort<VALUE, SCORE>::sortValues(m_Value + i * LENGTH, m_Score + i * LENGTH, LENGTH);
		profileImplementation.stop();
		const auto durationImplementation{ profileImplementation.duration() };
		const auto speedImplementation{ profileImplementation.computeSpeed(reps * LENGTH, "op") };
		str << "      duration: " << parser::durationToString(durationImplementation) << std::endl;
		str << "      speed:    " << speedImplementation << std::endl;
		str << "    verifying..." << std::endl;
		str << std::endl;
		for (size_t j = 0; j < reps; j++)
		{
			for (size_t i = 1; i < LENGTH; i++)
			{
				if (m_Score[i + j * LENGTH] > m_Score[i + j * LENGTH - 1])
				{
					str << "    FAILED" << std::endl;
					delete[] m_Value;
					delete[] m_Score;
					delete[] m_ValueRef;
					delete[] m_ScoreRef;
					return false;
				}
			}
			for (size_t i = 0; i < LENGTH; i++)
			{
				size_t countV{ 0 };
				size_t countVRef{ 0 };
				size_t countS{ 0 };
				size_t countSRef{ 0 };
				for (size_t k = 0; k < LENGTH; k++)
				{
					if (m_Value[i + j * LENGTH] == m_Value[k + j * LENGTH])
						countV++;
					if (m_Value[i + j * LENGTH] == m_ValueRef[k + j * LENGTH])
						countVRef++;
					if (m_Score[i + j * LENGTH] == m_Score[k + j * LENGTH])
						countS++;
					if (m_Score[i + j * LENGTH] == m_ScoreRef[k + j * LENGTH])
						countSRef++;
				}
				if (countV != countVRef)
				{
					str << "    FAILED" << std::endl;
					delete[] m_Value;
					delete[] m_Score;
					delete[] m_ValueRef;
					delete[] m_ScoreRef;
					return false;
				}
				if (countS != countSRef)
				{
					str << "    FAILED" << std::endl;
					delete[] m_Value;
					delete[] m_Score;
					delete[] m_ValueRef;
					delete[] m_ScoreRef;
					return false;
				}
			}
		}
		duration += durationImplementation;
		operations += reps * LENGTH;
		str << "  PASSED" << std::endl;
		str << std::endl;
		delete[] m_Value;
		delete[] m_Score;
		delete[] m_ValueRef;
		delete[] m_ScoreRef;
		return true;
	}
	template<typename VALUE, typename SCORE>
	bool sort(std::ostream& str) noexcept
	{
		typename profiler::durationType duration{ 0 };
		size_t operations(0);
		bool result{ true };
		str << "_______________" << std::endl;
		str << "TESTSUITE: sort" << std::endl;
		str << std::endl;
		result &= intrinsics::test::sort<VALUE, SCORE, 0>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 1>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 2>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 3>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 4>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 5>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 6>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 7>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 8>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 9>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 10>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 11>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 12>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 13>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 14>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 15>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 16>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 17>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 18>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 19>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 20>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 21>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 22>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 23>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 24>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 25>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 26>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 27>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 28>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 29>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 30>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 31>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 32>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 63>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 127>(str, duration, operations);
		result &= intrinsics::test::sort<VALUE, SCORE, 255>(str, duration, operations);
		str << "  Performace: " << std::endl;
		str << "    Global: " << profiler::speed(operations, duration, "op") << std::endl;
		str << std::endl;
		if (result)
			str << "ALL PASSED" << std::endl;
		else
			str << "SOME FAILED" << std::endl;
		str << "__________________________________________" << std::endl;
		str << std::endl;
		return result;
	}
	bool sort(std::ostream& str) noexcept
	{
		typename profiler::durationType duration{ 0 };
		size_t operations(0);
		bool result{ true };
		/*result &= intrinsics::test::sort<std::uint8_t, std::int8_t>(str);
		result &= intrinsics::test::sort<std::uint8_t, std::int16_t>(str);
		result &= intrinsics::test::sort<std::uint8_t, std::int32_t>(str);
		result &= intrinsics::test::sort<std::uint8_t, std::int64_t>(str);
		result &= intrinsics::test::sort<std::uint16_t, std::int8_t>(str);
		result &= intrinsics::test::sort<std::uint16_t, std::int16_t>(str);*/
		result &= intrinsics::test::sort<std::uint16_t, std::int32_t>(str);
		/*result &= intrinsics::test::sort<std::uint16_t, std::int64_t>(str);
		result &= intrinsics::test::sort<std::uint32_t, std::int8_t>(str);
		result &= intrinsics::test::sort<std::uint32_t, std::int16_t>(str);
		result &= intrinsics::test::sort<std::uint32_t, std::int32_t>(str);
		result &= intrinsics::test::sort<std::uint32_t, std::int64_t>(str);
		result &= intrinsics::test::sort<std::uint64_t, std::int8_t>(str);
		result &= intrinsics::test::sort<std::uint64_t, std::int16_t>(str);
		result &= intrinsics::test::sort<std::uint64_t, std::int32_t>(str);
		result &= intrinsics::test::sort<std::uint64_t, std::int64_t>(str);*/
		str << "__________________________________________" << std::endl;
		if (result)
			str << "ALL PASSED" << std::endl;
		else
			str << "SOME FAILED" << std::endl;
		str << "__________________________________________" << std::endl;
		str << std::endl;
		return result;
	}
}