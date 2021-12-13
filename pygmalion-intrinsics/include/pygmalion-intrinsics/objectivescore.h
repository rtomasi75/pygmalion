namespace pygmalion
{
	template<typename SCORE, size_t COUNTPLAYERS>
	class objectivescore
	{
	public:
		using subjectiveType = SCORE;
		constexpr static inline const size_t countPlayers{ COUNTPLAYERS };
	private:
		std::array<subjectiveType, countPlayers> m_PlayerScores;
	public:
		constexpr PYGMALION_INLINE bool operator==(const objectivescore& other) const noexcept
		{
			for (size_t i = 0; i < countPlayers; i++)
			{
				if (this->m_PlayerScores[i] != other.m_PlayerScores[i])
					return false;
			}
			return true;
		}
		constexpr PYGMALION_INLINE bool operator!=(const objectivescore& other) const noexcept
		{
			for (size_t i = 0; i < countPlayers; i++)
			{
				if (this->m_PlayerScores[i] != other.m_PlayerScores[i])
					return true;
			}
			return false;
		}
		constexpr PYGMALION_INLINE objectivescore() noexcept :
			m_PlayerScores{ arrayhelper::template generate<countPlayers,subjectiveType>([](const size_t playerIndex) { constexpr const subjectiveType zero{subjectiveType::zero()}; return zero; }) }
		{
		}
		PYGMALION_INLINE ~objectivescore() noexcept = default;
		constexpr PYGMALION_INLINE objectivescore(const objectivescore&) noexcept = default;
		constexpr PYGMALION_INLINE objectivescore(objectivescore&&) noexcept = default;
		constexpr PYGMALION_INLINE objectivescore& operator=(const objectivescore&) noexcept = default;
		constexpr PYGMALION_INLINE objectivescore& operator=(objectivescore&&) noexcept = default;
		constexpr PYGMALION_INLINE const subjectiveType& player(const size_t playerIndex) const noexcept
		{
			return m_PlayerScores[playerIndex];
		}
		constexpr PYGMALION_INLINE subjectiveType& player(const size_t playerIndex) noexcept
		{
			return m_PlayerScores[playerIndex];
		}
		template<size_t PLAYER>
		constexpr PYGMALION_INLINE const subjectiveType& player() const noexcept
		{
			return m_PlayerScores[PLAYER];
		}
		template<size_t PLAYER>
		constexpr PYGMALION_INLINE subjectiveType& player() noexcept
		{
			return m_PlayerScores[PLAYER];
		}
		constexpr PYGMALION_INLINE objectivescore& operator+=(const objectivescore& other) noexcept
		{
			for (size_t i = 0; i < countPlayers; i++)
				m_PlayerScores[i] += other.m_PlayerScores[i];
			return *this;
		}
		constexpr PYGMALION_INLINE objectivescore& operator-=(const objectivescore& other) noexcept
		{
			for (size_t i = 0; i < countPlayers; i++)
				m_PlayerScores[i] -= other.m_PlayerScores[i];
			return *this;
		}
		constexpr PYGMALION_INLINE objectivescore operator+(const objectivescore& other) const
		{
			objectivescore accumulator{ *this };
			accumulator += other;
			return accumulator;
		}
		constexpr PYGMALION_INLINE objectivescore operator-(const objectivescore& other) const
		{
			objectivescore accumulator{ *this };
			accumulator -= other;
			return accumulator;
		}
		constexpr PYGMALION_INLINE objectivescore operator-() const
		{
			objectivescore accumulator;
			for (size_t i = 0; i < countPlayers; i++)
				accumulator.m_PlayerScores[i] = -m_PlayerScores[i];
			return accumulator;
		}
		constexpr PYGMALION_INLINE subjectiveType makeSubjective(const size_t playerIndex) const noexcept
		{
			constexpr const subjectiveType zero{ subjectiveType::zero() };
			subjectiveType subjective{ zero };
			for (size_t i = 0; i < countPlayers; i++)
				subjective += (i == playerIndex) ? m_PlayerScores[i] : -m_PlayerScores[i];
			return subjective;
		}
		template<size_t PLAYER>
		constexpr PYGMALION_INLINE subjectiveType makeSubjective() const noexcept
		{
			constexpr const subjectiveType zero{ subjectiveType::zero() };
			subjectiveType subjective{ zero };
			for (size_t i = 0; i < countPlayers; i++)
				subjective += (i == PLAYER) ? m_PlayerScores[i] : -m_PlayerScores[i];
			return subjective;
		}
		constexpr PYGMALION_INLINE static objectivescore makeObjective(const subjectiveType sc, const size_t playerIndex) noexcept
		{
			objectivescore result;
			result.m_PlayerScores[playerIndex] = sc;
			return result;
		}
		template<size_t PLAYER>
		constexpr PYGMALION_INLINE static objectivescore makeObjective(const subjectiveType sc) noexcept
		{
			objectivescore result;
			result.m_PlayerScores[PLAYER] = sc;
			return result;
		}
		constexpr PYGMALION_INLINE static inline objectivescore<SCORE, COUNTPLAYERS> zero() noexcept
		{
			constexpr const objectivescore<SCORE, COUNTPLAYERS> zro{ objectivescore<SCORE, COUNTPLAYERS>() };
			return zro;
		};
		std::string toString() const noexcept
		{
			return this->template makeSubjective<0>().toString();
		}
	};

	template<typename SCORE>
	class objectivescore<SCORE, 2>
	{
	public:
		using subjectiveType = SCORE;
		constexpr static inline const size_t countPlayers{ 2 };
	private:
		subjectiveType m_PlayerZeroScore;
	public:
		constexpr PYGMALION_INLINE bool operator==(const objectivescore& other) const noexcept
		{
			return this->m_PlayerZeroScore == other.m_PlayerZeroScore;
		}
		constexpr PYGMALION_INLINE bool operator!=(const objectivescore& other) const noexcept
		{
			return this->m_PlayerZeroScore != other.m_PlayerZeroScore;
		}
		constexpr PYGMALION_INLINE objectivescore() noexcept :
			m_PlayerZeroScore{ []() { constexpr const subjectiveType zero{subjectiveType::zero()}; return zero; }() }
		{
		}
		PYGMALION_INLINE ~objectivescore() noexcept = default;
		constexpr PYGMALION_INLINE objectivescore(const objectivescore&) noexcept = default;
		constexpr PYGMALION_INLINE objectivescore(objectivescore&&) noexcept = default;
		constexpr PYGMALION_INLINE objectivescore& operator=(const objectivescore&) noexcept = default;
		constexpr PYGMALION_INLINE objectivescore& operator=(objectivescore&&) noexcept = default;
		constexpr PYGMALION_INLINE const subjectiveType& player(const size_t playerIndex) const noexcept
		{
			return playerIndex == 0 ? m_PlayerZeroScore : -m_PlayerZeroScore;
		}
		template<size_t PLAYER>
		constexpr PYGMALION_INLINE const subjectiveType& player() const noexcept
		{
			if constexpr (PLAYER == 0)
				return m_PlayerZeroScore;
			else
				return -m_PlayerZeroScore;
		}
		constexpr PYGMALION_INLINE objectivescore& operator+=(const objectivescore& other) noexcept
		{
			m_PlayerZeroScore += other.m_PlayerZeroScore;
			return *this;
		}
		constexpr PYGMALION_INLINE objectivescore& operator-=(const objectivescore& other) noexcept
		{
			m_PlayerZeroScore -= other.m_PlayerZeroScore;
			return *this;
		}
		constexpr PYGMALION_INLINE objectivescore operator+(const objectivescore& other) const
		{
			objectivescore accumulator{ *this };
			accumulator += other;
			return accumulator;
		}
		constexpr PYGMALION_INLINE objectivescore operator-(const objectivescore& other) const
		{
			objectivescore accumulator{ *this };
			accumulator -= other;
			return accumulator;
		}
		constexpr PYGMALION_INLINE objectivescore operator-() const
		{
			objectivescore accumulator;
			accumulator.m_PlayerZeroScore = -m_PlayerZeroScore;
			return accumulator;
		}
		constexpr PYGMALION_INLINE subjectiveType makeSubjective(const size_t playerIndex) const noexcept
		{
			return playerIndex == 0 ? m_PlayerZeroScore : -m_PlayerZeroScore;
		}
		template<size_t PLAYER>
		constexpr PYGMALION_INLINE subjectiveType makeSubjective() const noexcept
		{
			if constexpr (PLAYER == 0)
				return m_PlayerZeroScore;
			else
				return -m_PlayerZeroScore;
		}
		constexpr PYGMALION_INLINE static objectivescore makeObjective(const subjectiveType sc, const size_t playerIndex) noexcept
		{
			objectivescore result;
			result.m_PlayerZeroScore= playerIndex == 0 ? sc : -sc;
			return result;
		}
		template<size_t PLAYER>
		constexpr PYGMALION_INLINE static objectivescore makeObjective(const subjectiveType sc) noexcept
		{
			objectivescore result;
			if constexpr (PLAYER == 0)
				result.m_PlayerZeroScore = sc;
			else
				result.m_PlayerZeroScore = -sc;
			return result;
		}
		constexpr PYGMALION_INLINE static inline objectivescore<SCORE, 2> zero() noexcept
		{
			constexpr const objectivescore<SCORE, 2> zro{ objectivescore<SCORE, 2>() };
			return zro;
		};
		std::string toString() const noexcept
		{
			return m_PlayerZeroScore.toString();
		}
	};

	template<typename SCORE, size_t COUNTPLAYERS>
	std::ostream& operator<<(std::ostream& str, const objectivescore<SCORE, COUNTPLAYERS>& value) noexcept
	{
		str << value.toString();
		return str;
	}
}