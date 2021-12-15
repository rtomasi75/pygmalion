namespace pygmalion::config
{
	template<>
	class playerpieceInfo<chess::whitePlayerInfo, chess::pawnInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::whitePlayerInfo&, const chess::pawnInfo&) :
			valueInfo("P", "white_pawn")
		{

		}
	};

	template<>
	class playerpieceInfo<chess::whitePlayerInfo, chess::knightInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::whitePlayerInfo&, const chess::knightInfo&) :
			valueInfo("N", "white_knight")
		{

		}
	};

	template<>
	class playerpieceInfo<chess::whitePlayerInfo, chess::bishopInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::whitePlayerInfo&, const chess::bishopInfo&) :
			valueInfo("B", "white_bishop")
		{

		}
	};

	template<>
	class playerpieceInfo<chess::whitePlayerInfo, chess::rookInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::whitePlayerInfo&, const chess::rookInfo&) :
			valueInfo("R", "white_rook")
		{

		}
	};

	template<>
	class playerpieceInfo<chess::whitePlayerInfo, chess::queenInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::whitePlayerInfo&, const chess::queenInfo&) :
			valueInfo("Q", "white_queen")
		{

		}
	};

	template<>
	class playerpieceInfo<chess::whitePlayerInfo, chess::kingInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::whitePlayerInfo&, const chess::kingInfo&) :
			valueInfo("K", "white_king")
		{

		}
	};

	template<>
	class playerpieceInfo<chess::blackPlayerInfo, chess::pawnInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::blackPlayerInfo&, const chess::pawnInfo&) :
			valueInfo("p", "black_pawn")
		{

		}
	};

	template<>
	class playerpieceInfo<chess::blackPlayerInfo, chess::knightInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::blackPlayerInfo&, const chess::knightInfo&) :
			valueInfo("n", "black_knight")
		{

		}
	};

	template<>
	class playerpieceInfo<chess::blackPlayerInfo, chess::bishopInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::blackPlayerInfo&, const chess::bishopInfo&) :
			valueInfo("b", "black_bishop")
		{

		}
	};

	template<>
	class playerpieceInfo<chess::blackPlayerInfo, chess::rookInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::blackPlayerInfo&, const chess::rookInfo&) :
			valueInfo("r", "black_rook")
		{

		}
	};

	template<>
	class playerpieceInfo<chess::blackPlayerInfo, chess::queenInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::blackPlayerInfo&, const chess::queenInfo&) :
			valueInfo("q", "black_queen")
		{

		}
	};

	template<>
	class playerpieceInfo<chess::blackPlayerInfo, chess::kingInfo> :
		public valueInfo
	{
	public:
		constexpr playerpieceInfo(const chess::blackPlayerInfo&, const chess::kingInfo&) :
			valueInfo("k", "black_king")
		{

		}
	};
}