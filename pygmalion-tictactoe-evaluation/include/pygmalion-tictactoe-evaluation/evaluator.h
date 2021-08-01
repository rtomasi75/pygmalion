namespace pygmalion::tictactoe
{
	class descriptor_evaluation :
		public pygmalion::descriptor_evaluation<generator, 7, 0, 10>
	{
	public:
	};

	class evaluator :
		public pygmalion::evaluator<descriptor_evaluation, evaluator>
	{
	private:
		static const inline patterns<descriptorEvaluation> m_Patterns;
	public:
		static evaluationType evaluate_Implementation(const boardType& position) noexcept
		{
			evaluationType sc{ evaluationType::zero() };
			for (int line = 0; line < m_Patterns.countLines; line++)
			{
				const auto ctr1 = (position.playerOccupancy(0) & m_Patterns.line(line)).count();
				const auto ctr2 = (position.playerOccupancy(1) & m_Patterns.line(line)).count();

				if ((ctr1 > 0) && (ctr2 == 0))
					sc += evaluationType::one() * (ctr1 * ctr1);
				if ((ctr2 > 0) && (ctr1 == 0))
					sc -= evaluationType::one() * (ctr2 * ctr2);
			}
			return sc;
		}
	};
}