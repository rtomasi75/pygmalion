namespace pygmalion::config::chess
{
	class pawnInfo :
		public pieceInfo
	{
	public:
		constexpr pawnInfo() noexcept :
			pieceInfo("p", "pawn")
		{

		}
	};

	class knightInfo :
		public pieceInfo
	{
	public:
		constexpr knightInfo() noexcept :
			pygmalion::config::pieceInfo("n", "knight")
		{

		}
	};

	class bishopInfo :
		public pieceInfo
	{
	public:
		constexpr bishopInfo()noexcept :
			pieceInfo("b", "bishop")
		{

		}
	};

	class rookInfo :
		public pieceInfo
	{
	public:
		constexpr rookInfo() noexcept :
			pieceInfo("r", "rook")
		{

		}
	};

	class queenInfo :
		public pieceInfo
	{
	public:
		constexpr queenInfo() noexcept :
			pieceInfo("q", "queen")
		{

		}
	};

	class kingInfo :
		public pieceInfo
	{
	public:
		constexpr kingInfo() noexcept :
			pieceInfo("k", "king")
		{

		}
	};

	class standardpiecesInfo :
		public piecesInfo<knightInfo, bishopInfo, rookInfo, queenInfo, pawnInfo, kingInfo>
	{
	public:
		constexpr standardpiecesInfo() noexcept :
			piecesInfo<knightInfo, bishopInfo, rookInfo, queenInfo, pawnInfo, kingInfo>(knightInfo(), bishopInfo(), rookInfo(), queenInfo(), pawnInfo(), kingInfo())
		{

		}
	};
}