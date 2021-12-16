namespace pygmalion::config
{
	template<typename PLAYERS, typename PIECES, typename FILES, typename RANKS, typename FLAGS>
	class boardInfo
	{
	private:
		static_assert(std::is_base_of<playersInfoBase, PLAYERS>::value, "PLAYERS must inherit playersInfo type.");
		static_assert(std::is_base_of<piecesInfoBase, PIECES>::value, "PIECES must inherit piecesInfo type.");
		static_assert(std::is_base_of<filesInfoBase, FILES>::value, "FILES must inherit filesInfo type.");
		static_assert(std::is_base_of<ranksInfoBase, RANKS>::value, "RANKS must inherit ranksInfo type.");
		static_assert(std::is_base_of<flagsInfoBase, FLAGS>::value, "FLAGS must inherit flagsInfoBase type.");
		const playerpiecesInfo<PLAYERS, PIECES> m_Playerpieces;
		const squaresInfo<FILES, RANKS> m_Squares;
		const scoreInfo m_MaterialScore;
		const FLAGS m_Flags;
	public:
		constexpr static inline const size_t countPlayers{ PLAYERS::count };
		constexpr static inline const size_t countPieces{ PIECES::count };
		constexpr static inline const size_t countFiles{ FILES::count };
		constexpr static inline const size_t countRanks{ RANKS::count };
		constexpr static inline const size_t countFlags{ FLAGS::count };
		constexpr static inline const size_t countSquares{ squaresInfo<FILES, RANKS>::count };
		constexpr static inline const size_t countFlagCombinations{ 1 << countFlags };
		const std::array<std::array<std::array<std::uint64_t, countSquares>, countPieces>, countPlayers> playerPieceSquareHash;
		const std::array<std::uint64_t, countSquares> enPassantHash;
		const std::array<std::uint64_t, 1 << countFlags> flagHash;
		const std::array<std::uint64_t, PLAYERS::count> movingPlayerHash;
		const size_t countHashBits;
		constexpr const FLAGS& flags() const noexcept
		{
			return m_Flags;
		}
		constexpr const squaresInfo<FILES, RANKS>& squares() const noexcept
		{
			return m_Squares;
		}
		constexpr const playerpiecesInfo<PLAYERS, PIECES>& playerpieces() const noexcept
		{
			return m_Playerpieces;
		}
		constexpr const scoreInfo& materialScore() const noexcept
		{
			return m_MaterialScore;
		}
	public:
		virtual bool initialFlag(const size_t flagIndex) const noexcept
		{
			PYGMALION_ASSERT(false);
			return false;
		}
		virtual size_t initialPlayerIndex() const noexcept
		{
			PYGMALION_ASSERT(false);
			return 0;
		}
		virtual bool initialPlayerPieceOnSquare(const size_t squareIndex, size_t& playerpieceIndex) const noexcept
		{
			PYGMALION_ASSERT(false);
			return false;
		}
		virtual bool initialEnPassant(size_t& victimSquareIndex, list<size_t, countSquares>& targetSquareIndices) const noexcept
		{
			PYGMALION_ASSERT(false);
			return false;
		}
		virtual double materialPiece(const size_t pieceIndex) const noexcept
		{
			PYGMALION_ASSERT(false);
			return 0.0;
		}
		virtual double materialPieceSquare(const size_t playerIndex, const size_t pieceIndex, const size_t fileIndex, const size_t rankIndex) const noexcept
		{
			PYGMALION_ASSERT(false);
			return 0.0;
		}
		constexpr boardInfo(const size_t countHashBits_, const PLAYERS& players, const PIECES& pieces, const FILES& files, const RANKS& ranks, const FLAGS& flags, const std::array<std::uint64_t, PLAYERS::count>& movingPlayerHash_, const std::array<std::uint64_t, squaresInfo<FILES, RANKS>::count> enPassantHash_, const std::array<std::uint64_t, countFlags> flagHash_, const std::array<std::array<std::array<std::uint64_t, countSquares>, countPieces>, countPlayers>& playerPieceSquareHash_, const scoreInfo& materialScore) noexcept :
			m_Playerpieces{ playerpiecesInfo<PLAYERS, PIECES>(players,pieces) },
			m_Squares{ squaresInfo<FILES, RANKS>(files,ranks) },
			m_MaterialScore{ materialScore },
			m_Flags{ flags },
			movingPlayerHash{ movingPlayerHash_ },
			enPassantHash{ enPassantHash_ },
			countHashBits{ countHashBits_ },
			flagHash{
			arrayhelper::generate<countFlagCombinations,std::uint64_t>(
				[&flagHash_](const size_t flagsIndex)
				{
					std::uint64_t result{UINT64_C(0)};
					using flagsType = uint_t<countFlags, false>;
					const flagsType idx{ flagsType(static_cast<std::make_unsigned_t<size_t>>(flagsIndex)) };
					for (size_t f = 0; f < countFlags; f++)
					{
						if (idx[f])
							result |= flagHash_[f];
					}
					return result;
				})
		},
			playerPieceSquareHash{ playerPieceSquareHash_ }
				{}
	};
}