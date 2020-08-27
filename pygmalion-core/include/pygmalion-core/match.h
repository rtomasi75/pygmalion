namespace pygmalion
{
	template<typename GAME, typename MOVEGEN>
	class match
	{
	public:
		using gameType = GAME;
		using movegenType = MOVEGEN;
		using moveType = typename gameType::moveType;
		using boardType = typename gameType::boardType;
		using playerType = typename gameType::playerType;
		using indexType = typename movegenType::indexType;
	private:
		boardType m_RootNode;
	public:
		match() noexcept :
			m_RootNode{ boardType() }
		{

		}
		~match() noexcept = default;
		match(match&&) noexcept = default;
		match(const match&) noexcept = default;
		auto movingPlayer() const noexcept
		{
			return m_RootNode.board().movingPlayer();
		}
		auto board() const noexcept
		{
			return m_RootNode;
		}
		void reset() noexcept
		{
			m_RootNode = boardType();
		}
		bool isMoveLegal(const moveType& move) noexcept
		{
			return movegenType::isMoveLegal(m_RootNode, move);
		}
		void doMove(const moveType& move) noexcept
		{
			m_RootNode = movegenType::makeMove(m_RootNode, move);
		}
	};
}