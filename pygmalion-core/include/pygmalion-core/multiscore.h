namespace pygmalion
{
	template<typename EVALUATOR>
	class multiscore
	{
	public:
		using evaluatorType = EVALUATOR;
		using objectiveType = typename evaluatorType::objectiveType;
		using subjectiveType = typename evaluatorType::subjectiveType;
		using boardType = typename evaluatorType::boardType;
		using playerType = typename evaluatorType::playerType;
	private:
		std::array<objectiveType, playerType::countValues> m_Scores;
		constexpr multiscore(const std::array<objectiveType, playerType::countValues>& ar) noexcept :
			m_Scores(ar)
		{

		}
		constexpr multiscore(std::array<objectiveType, playerType::countValues>&& ar) noexcept :
			m_Scores(std::move(ar))
		{

		}
	public:
		constexpr void plyUp() noexcept
		{
			for (const playerType i : playerType::range)
			{
				evaluatorType::plyUp(m_Scores[i]);
			}
		}
		constexpr void plyDown() noexcept
		{
			for (const playerType i : playerType::range)
			{
				evaluatorType::plyDown(m_Scores[i]);
			}
		}
		constexpr auto score(const playerType self) const noexcept
		{
			assert(self.isValid());
			return m_Scores[self];
		}
		constexpr auto refuted(playerType self, const objectiveType& sc) noexcept
		{
			assert(self.isValid());
			playerType other{ self };
			for (int i = 1; i < playerType::countValues; i++)
			{
				other = other.next();
				const subjectiveType sc_other{ evaluatorType::makeSubjective(sc, other) };
				const subjectiveType beta_other{ evaluatorType::makeSubjective(m_Scores[other], other) };
				if (sc_other <= beta_other)
					return true;
			}
			return false;
		}
		constexpr auto accepted(const playerType self, const objectiveType& sc) noexcept
		{
			assert(self.isValid());
			const subjectiveType sc_self{ evaluatorType::makeSubjective(sc, self) };
			const subjectiveType alpha_self{ evaluatorType::makeSubjective(m_Scores[self], self) };
			if (sc_self > alpha_self)
			{
				m_Scores[self] = sc;
				return true;
			}
			else
				return false;
		}
		constexpr multiscore() noexcept :
			m_Scores{ make_array_n<playerType::countValues,objectiveType>(evaluatorType::neutralScore()) }
		{
			for (const playerType p : playerType::range)
			{
				m_Scores[p] = evaluatorType::minScore(p);
			}
		}
		~multiscore() noexcept = default;
		constexpr multiscore(const multiscore&) noexcept = default;
		constexpr multiscore(multiscore&&) noexcept = default;
		constexpr multiscore& operator=(const multiscore&) noexcept = default;
		constexpr multiscore& operator=(multiscore&&) noexcept = default;
	};
}