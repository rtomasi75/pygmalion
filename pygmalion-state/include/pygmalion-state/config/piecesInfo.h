namespace pygmalion::config
{
	template<size_t COUNTPIECES>
	class piecesInfo
	{
	public:
		const std::array<pieceInfo, COUNTPIECES> m_Pieces;
	protected:
		constexpr piecesInfo(const std::array<pieceInfo, COUNTPIECES>& pieces) noexcept :
			m_Pieces{ pieces }
		{
		}
	public:
		constexpr static const inline size_t countPieces{ COUNTPIECES };
		~piecesInfo() noexcept
		{

		}
		constexpr const pieceInfo& piece(const size_t pieceIndex) const noexcept
		{
			return m_Pieces[pieceIndex];
		}
	};
}