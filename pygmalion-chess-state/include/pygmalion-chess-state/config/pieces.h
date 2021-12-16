namespace pygmalion::config::chess
{
	class pawnInfo :
		public pieceInfo
	{
	public:
		constexpr pawnInfo() noexcept :
			pieceInfo("p", "pawn", true, false)
		{

		}
	};

	class knightInfo :
		public pieceInfo
	{
	public:
		constexpr knightInfo() noexcept :
			pygmalion::config::pieceInfo("n", "knight", false, false)
		{

		}
	};

	class bishopInfo :
		public pieceInfo
	{
	public:
		constexpr bishopInfo()noexcept :
			pieceInfo("b", "bishop", false, false)
		{

		}
	};

	class rookInfo :
		public pieceInfo
	{
	public:
		constexpr rookInfo() noexcept :
			pieceInfo("r", "rook", false, false)
		{

		}
	};

	class queenInfo :
		public pieceInfo
	{
	public:
		constexpr queenInfo() noexcept :
			pieceInfo("q", "queen", false, false)
		{

		}
	};

	class kingInfo :
		public pieceInfo
	{
	public:
		constexpr kingInfo() noexcept :
			pieceInfo("k", "king", true, true)
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