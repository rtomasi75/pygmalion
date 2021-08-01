namespace pygmalion::chess
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
	public:
		static evaluationType evaluate_Implementation(const boardType& position) noexcept
		{
			evaluationType sc{ static_cast<evaluationType>(position.material()) };
			return sc;
		}
	};
}