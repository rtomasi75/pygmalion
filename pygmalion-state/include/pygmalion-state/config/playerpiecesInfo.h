namespace pygmalion::config
{
	template<size_t COUNTPLAYERS, size_t COUNTPIECES>
	class playerpiecesInfo
	{
	public:
		constexpr static const inline size_t countPlayerpieces{ COUNTPLAYERS * COUNTPIECES };
		const std::array<std::array<playerpieceInfo, COUNTPIECES>, COUNTPLAYERS> m_Playerpieces;
	protected:
		constexpr playerpiecesInfo(const std::array<std::array<playerpieceInfo, COUNTPIECES>, COUNTPLAYERS>& playerpieces) noexcept :
			m_Playerpieces{ playerpieces }
		{
		}
	public:
		~playerpiecesInfo() noexcept
		{

		}
		constexpr const playerpieceInfo& playerpiece(const size_t playerIndex, const size_t pieceIndex) const noexcept
		{
			return m_Playerpieces[playerIndex][pieceIndex];
		}
		constexpr const playerpieceInfo& playerpiece(const size_t playerpieceIndex) const noexcept
		{
			const size_t playerIndex{ playerpieceIndex / COUNTPIECES };
			const size_t pieceIndex{ playerpieceIndex % COUNTPIECES };;
			return m_Playerpieces[playerIndex][pieceIndex];
		}
	};
}