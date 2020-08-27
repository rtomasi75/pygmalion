namespace pygmalion
{

	template<typename SEARCH, typename INSTANCE>
	class frontend
	{
	public:
		using searchType = SEARCH;
		using instanceType = INSTANCE;
		using movegenType = typename searchType::movegenType;
		using gamestateType = typename searchType::gamestateType;
		using boardType = typename movegenType::boardType;
		using playerType = typename movegenType::playerType;
		using squareType = typename movegenType::squareType;
		using pieceType = typename movegenType::pieceType;
		using subjectiveType = typename searchType::subjectiveType;
		using objectiveType = typename searchType::objectiveType;
		using moveType = typename movegenType::moveType;
		using variationType = typename searchType::variationType;
		using evaluatorType = typename searchType::evaluatorType;
		using bitsType = typename boardType::bitsType;
		static std::string subjectiveToString(const subjectiveType& score) noexcept
		{
			return instanceType::subjectiveToString_Implementation(score);
		}
		static std::string objectiveToString(const objectiveType& score) noexcept
		{
			return instanceType::objectiveToString_Implementation(score);
		}
		static std::string moveToString(const boardType& position, const moveType mv) noexcept
		{
			return instanceType::moveToString_Implementation(position, mv);
		}
		static void dumpBoard(const boardType& board, std::ostream& str) noexcept
		{
			return instanceType::dumpBoard_Implementation(board, str);
		}
		static bool parseMove(const std::string str, const boardType& position, moveType& move, std::string& error) noexcept
		{
			return instanceType::parseMove_Implementation(str, position, move, error);
		}
		static std::string variationToString(const boardType& position, const variationType& variation)
		{
			return instanceType::variationToString_Implementation(position, variation);
		}
	};
}