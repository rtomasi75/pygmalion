namespace pygmalion::chess
{
	class front :
		public pygmalion::front<descriptor_frontend, front>
	{
	public:
		static std::string gamestateToString_Implementation(const boardType& position, const gamestateType gs) noexcept
		{
			PYGMALION_ASSERT(!gamestateType::isOpen(gs));
			if (gamestateType::isDraw(gs))
				return "1/2-1/2";
			else if (gamestateType::isWin(gs, whitePlayer))
				return "1-0";
			else
				return "0-1";
		}
		front() noexcept :
			pygmalion::front<descriptor_frontend, front>()
		{

		}
	};
}