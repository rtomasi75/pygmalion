namespace pygmalion::chess::config
{
	class whitePlayerInfo :
		public pygmalion::config::playerInfo
	{
	public:
		constexpr whitePlayerInfo() noexcept :
			pygmalion::config::playerInfo("w", "white")
		{}
	};

	class blackPlayerInfo :
		public pygmalion::config::playerInfo
	{
	public:
		constexpr blackPlayerInfo() noexcept :
			pygmalion::config::playerInfo("b", "black")
		{}
	};

	class standardplayersInfo :
		public pygmalion::config::playersInfo<2>
	{
	private:
		constexpr static inline std::array<pygmalion::config::playerInfo, countPlayers> m_Players
		{
			whitePlayerInfo(),
			blackPlayerInfo()
		};
	public:
		constexpr standardplayersInfo() noexcept :
			pygmalion::config::playersInfo<2>(m_Players)
		{

		}
	};

	class pawnInfo :
		public pygmalion::config::pieceInfo
	{
	public:
		constexpr pawnInfo() noexcept :
			pygmalion::config::pieceInfo("P", "pawn")
		{

		}
	};

	class knightInfo :
		public pygmalion::config::pieceInfo
	{
	public:
		constexpr knightInfo() noexcept :
			pygmalion::config::pieceInfo("N", "knight")
		{

		}
	};

	class bishopInfo :
		public pygmalion::config::pieceInfo
	{
	public:
		constexpr bishopInfo()noexcept :
			pygmalion::config::pieceInfo("B", "bishop")
		{

		}
	};

	class rookInfo :
		public pygmalion::config::pieceInfo
	{
	public:
		constexpr rookInfo() noexcept :
			pygmalion::config::pieceInfo("R", "rook")
		{

		}
	};

	class queenInfo :
		public pygmalion::config::pieceInfo
	{
	public:
		constexpr queenInfo() noexcept :
			pygmalion::config::pieceInfo("Q", "queen")
		{

		}
	};

	class kingInfo :
		public pygmalion::config::pieceInfo
	{
	public:
		constexpr kingInfo() noexcept :
			pygmalion::config::pieceInfo("K", "king")
		{

		}
	};

	class standardpiecesInfo :
		public pygmalion::config::piecesInfo<6>
	{
	private:
		constexpr static inline std::array<pygmalion::config::pieceInfo, countPieces> m_Pieces
		{
			pawnInfo(),
			knightInfo(),
			bishopInfo(),
			rookInfo(),
			queenInfo(),
			kingInfo()
		};
	public:
		constexpr standardpiecesInfo() noexcept :
			pygmalion::config::piecesInfo<6>(m_Pieces)
		{

		}
	};

	class whitepawnInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr whitepawnInfo() noexcept :
			pygmalion::config::playerpieceInfo("P", "white_pawn")
		{

		}
	};

	class whiteknightInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr whiteknightInfo() noexcept :
			pygmalion::config::playerpieceInfo("N", "white_knight")
		{

		}
	};

	class whitebishopInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr whitebishopInfo() noexcept :
			pygmalion::config::playerpieceInfo("B", "white_bishop")
		{

		}
	};

	class whiterookInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr whiterookInfo() noexcept :
			pygmalion::config::playerpieceInfo("R", "white_rook")
		{

		}
	};

	class whitequeenInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr whitequeenInfo() noexcept :
			pygmalion::config::playerpieceInfo("Q", "white_queen")
		{

		}
	};

	class whitekingInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr whitekingInfo() noexcept :
			pygmalion::config::playerpieceInfo("K", "white_king")
		{

		}
	};

	class blackpawnInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr blackpawnInfo() noexcept :
			pygmalion::config::playerpieceInfo("p", "black_pawn")
		{

		}
	};

	class blackknightInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr blackknightInfo() noexcept :
			pygmalion::config::playerpieceInfo("n", "black_knight")
		{

		}
	};

	class blackbishopInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr blackbishopInfo() noexcept :
			pygmalion::config::playerpieceInfo("b", "black_bishop")
		{

		}
	};

	class blackrookInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr blackrookInfo() noexcept :
			pygmalion::config::playerpieceInfo("r", "black_rook")
		{

		}
	};

	class blackqueenInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr blackqueenInfo() noexcept :
			pygmalion::config::playerpieceInfo("q", "black_queen")
		{

		}
	};

	class blackkingInfo :
		public pygmalion::config::playerpieceInfo
	{
	public:
		constexpr blackkingInfo() noexcept :
			pygmalion::config::playerpieceInfo("k", "black_king")
		{

		}
	};

	class standardplayerpiecesInfo :
		public pygmalion::config::playerpiecesInfo<2, 6>
	{
	private:
		constexpr static const inline std::array<std::array<pygmalion::config::playerpieceInfo, 6>, 2> m_Playerpieces
		{
			std::array<pygmalion::config::playerpieceInfo,6>({
				whitepawnInfo(),
				whiteknightInfo(),
				whitebishopInfo(),
				whiterookInfo(),
				whitequeenInfo(),
				whitekingInfo()
			}),
			std::array<pygmalion::config::playerpieceInfo,6>({
				blackpawnInfo(),
				blackknightInfo(),
				blackbishopInfo(),
				blackrookInfo(),
				blackqueenInfo(),
				blackkingInfo()
			})
		};
	public:
		constexpr standardplayerpiecesInfo() noexcept :
			pygmalion::config::playerpiecesInfo<2, 6>(m_Playerpieces)
		{

		}
	};

	class standardfilesInfo :
		public pygmalion::config::filesInfo<8>
	{
	private:
		constexpr static const inline std::array<pygmalion::config::fileInfo, 8> m_Files
		{
			pygmalion::config::fileInfo("a", "file_A"),
			pygmalion::config::fileInfo("b", "file_B"),
			pygmalion::config::fileInfo("c", "file_C"),
			pygmalion::config::fileInfo("d", "file_D"),
			pygmalion::config::fileInfo("e", "file_E"),
			pygmalion::config::fileInfo("f", "file_F"),
			pygmalion::config::fileInfo("g", "file_G"),
			pygmalion::config::fileInfo("h", "file_H")
		};
	public:
		constexpr standardfilesInfo() noexcept :
			pygmalion::config::filesInfo<8>(m_Files)
		{

		}
	};

	class standardranksInfo :
		public pygmalion::config::ranksInfo<8>
	{
	private:
		constexpr static const inline std::array<pygmalion::config::rankInfo, 8> m_Files
		{
			pygmalion::config::rankInfo("1", "rank_1"),
			pygmalion::config::rankInfo("2", "rank_2"),
			pygmalion::config::rankInfo("3", "rank_3"),
			pygmalion::config::rankInfo("4", "rank_4"),
			pygmalion::config::rankInfo("5", "rank_5"),
			pygmalion::config::rankInfo("6", "rank_6"),
			pygmalion::config::rankInfo("7", "rank_7"),
			pygmalion::config::rankInfo("8", "rank_8")
		};
	public:
		constexpr standardranksInfo() noexcept :
			pygmalion::config::ranksInfo<8>(m_Files)
		{

		}
	};

}