namespace pygmalion::chess
{

	class board :
		public pygmalion::board<state::descriptor_state, board>
	{
	public:
		board() noexcept :
			pygmalion::board<state::descriptor_state, board>()
		{
		}
		PYGMALION_INLINE void clearCastleRightQueensideBlack() noexcept
		{
			clearFlag(castleRightQueensideBlack);
		}
		PYGMALION_INLINE void clearCastleRightQueensideWhite() noexcept
		{
			clearFlag(castleRightQueensideWhite);
		}
		PYGMALION_INLINE void clearCastleRightKingsideBlack() noexcept
		{
			clearFlag(castleRightKingsideBlack);
		}
		PYGMALION_INLINE void clearCastleRightKingsideWhite() noexcept
		{
			clearFlag(castleRightKingsideWhite);
		}
		PYGMALION_INLINE void setCastleRightQueensideBlack() noexcept
		{
			setFlag(castleRightQueensideBlack);
		}
		PYGMALION_INLINE void setCastleRightQueensideWhite() noexcept
		{
			setFlag(castleRightQueensideWhite);
		}
		PYGMALION_INLINE void setCastleRightKingsideBlack() noexcept
		{
			setFlag(castleRightKingsideBlack);
		}
		PYGMALION_INLINE void setCastleRightKingsideWhite() noexcept
		{
			setFlag(castleRightKingsideWhite);
		}
		PYGMALION_INLINE bool checkCastleRightQueensideBlack() const noexcept
		{
			return testFlag(castleRightQueensideBlack);
		}
		PYGMALION_INLINE bool checkCastleRightQueensideWhite() const noexcept
		{
			return testFlag(castleRightQueensideWhite);
		}
		PYGMALION_INLINE bool checkCastleRightKingsideBlack() const noexcept
		{
			return testFlag(castleRightKingsideBlack);
		}
		PYGMALION_INLINE bool checkCastleRightKingsideWhite() const noexcept
		{
			return testFlag(castleRightKingsideWhite);
		}
		PYGMALION_INLINE bool checkCastleRightQueenside(const playerType player) const noexcept
		{
			return (player == whitePlayer) ? checkCastleRightQueensideWhite() : checkCastleRightQueensideBlack();
		}
		PYGMALION_INLINE bool checkCastleRightKingside(const playerType player) const noexcept
		{
			return (player == whitePlayer) ? checkCastleRightKingsideWhite() : checkCastleRightKingsideBlack();
		}
		PYGMALION_INLINE void clearCastleRightsBlack() noexcept
		{
			clearFlags(castleFlagsBlack);
		}
		PYGMALION_INLINE void clearCastleRightsWhite() noexcept
		{
			clearFlags(castleFlagsWhite);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType makeSubjective_Implementation(const scoreType score) noexcept
		{
			constexpr const playerType player{ static_cast<playerType>(PLAYER) };
			if constexpr (player == whitePlayer)
				return score;
			else
				return -score;
		}
		// Implementation
		static std::string flagToString_Implementation(const flagType flag) noexcept;
		static bool parseFlag_Implementation(const std::string& text, flagType& flag, size_t& count) noexcept;
		static std::string rankToString_Implementation(const rankType rank) noexcept;
		static bool parseRank_Implementation(const std::string& text, rankType& rank, size_t& count) noexcept;
		static std::string fileToString_Implementation(const fileType file) noexcept;
		static bool parseFile_Implementation(const std::string& text, fileType& file, size_t& count) noexcept;
		static std::string playerToString_Implementation(const playerType player) noexcept;
		static bool parsePlayer_Implementation(const std::string& text, playerType& player, size_t& count) noexcept;
		static std::string pieceToString_Implementation(const pieceType piece, const playerType player) noexcept;
		static bool parsePiece_Implementation(const std::string& text, pieceType& piece, playerType& player, size_t& count) noexcept;
		PYGMALION_INLINE void onClear_Implementation() noexcept
		{
			cumulation().clear();
		}
		PYGMALION_INLINE void onAddedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			switch (piece)
			{
			case pawn:
				cumulation().pawnHash() ^= pieceHash(pawn, square, player);
				break;
			case king:
				cumulation().pawnHash() ^= pieceHash(king, square, player);
				break;
			}
		}
		PYGMALION_INLINE void onSetMovingPlayer_Implementation(const playerType player) noexcept
		{
		}
		PYGMALION_INLINE void onMovedPiece_Implementation(const pieceType piece, const squareType from, const squareType to, const playerType player) noexcept
		{
			switch (piece)
			{
			case pawn:
				cumulation().pawnHash() ^= pieceHash(pawn, from, player);
				cumulation().pawnHash() ^= pieceHash(pawn, to, player);
				break;
			case king:
				cumulation().pawnHash() ^= pieceHash(king, from, player);
				cumulation().pawnHash() ^= pieceHash(king, to, player);
				break;
			}
		}
		PYGMALION_INLINE void onRemovedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
		{
			switch (piece)
			{
			case pawn:
				cumulation().pawnHash() ^= pieceHash(pawn, square, player);
				break;
			case king:
				cumulation().pawnHash() ^= pieceHash(king, square, player);
				break;
			}
		}
		PYGMALION_INLINE void onSetFlag_Implementation(const flagType flag) noexcept
		{
		}
		PYGMALION_INLINE void onClearedFlag_Implementation(const flagType flag) noexcept
		{
		}
		void onInitialize_Implementation(const materialTableType& materialTable) noexcept;
		static std::string cumulationToString_Implementation(const cumulationType&) noexcept;
		PYGMALION_INLINE hashType pawnHash() const noexcept
		{
			return cumulation().pawnHash();
		}
		static std::string flagsToString_Implementation(const flagsType flags, const playerType movingPlayer) noexcept;
		static bool parseFlags_Implementation(const std::string& text, flagsType& flags, size_t& count) noexcept;
	private:
		constexpr static inline double m_PST_King[64]
		{
				-0.32, -0.064, -0.064, -0.064, -0.064, -0.064, -0.064, -0.32,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.32, -0.064, -0.064, -0.064, -0.064, -0.064, -0.064, -0.32,
		};
		constexpr static inline double m_PST_Knight[64]
		{
				-0.384, -0.256, -0.128, -0.128, -0.128, -0.128, -0.256, -0.384,
				-0.256, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.256,
				-0.128, 0.128, 0.384, 0.384, 0.384, 0.384, 0.128, -0.128,
				-0.128, 0.128, 0.384, 0.384, 0.384, 0.384, 0.128, -0.128,
				-0.128, 0.128, 0.384, 0.384, 0.384, 0.384, 0.128, -0.128,
				-0.128, 0.128, 0.384, 0.384, 0.384, 0.384, 0.128, -0.128,
				-0.256, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.256,
				-0.384, -0.256, -0.128, -0.128, -0.128, -0.128, -0.256, -0.384,
		};
		constexpr static inline double m_PST_Bishop[64]
		{
				-0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384,
				-0.384, -0.128, -0.128, -0.128, -0.128, -0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.384, 0.384, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.384, 0.384, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.384,
				-0.384, -0.128, -0.128, -0.128, -0.128, -0.128, -0.128, -0.384,
				-0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384,
		};
		constexpr static inline double m_PST_Rook[64]
		{
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
		};
		constexpr static inline double m_PST_Queen[64]
		{
				-0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384,
				-0.384, -0.128, -0.128, -0.128, -0.128, -0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.384, 0.384, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.384, 0.384, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.384,
				-0.384, -0.128, -0.128, -0.128, -0.128, -0.128, -0.128, -0.384,
				-0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384,
		};
		constexpr static inline double m_PST_Pawn[64]
		{
				0, 0, 0, 0, 0, 0, 0, 0,
				-0.288, -0.224, -0.224, -0.224, -0.224, -0.224, -0.224, -0.288,
				-0.224, -0.16, -0.16, -0.16, -0.16, -0.16, -0.16, -0.224,
				-0.096, -0.032, -0.032, -0.032, -0.032, -0.032, -0.032, -0.096,
				0.032, 0.096, 0.096, 0.096, 0.096, 0.096, 0.096, 0.032,
				0.16, 0.224, 0.224, 0.224, 0.224, 0.224, 0.224, 0.16,
				0.224, 0.288, 0.288, 0.288, 0.288, 0.288, 0.288, 0.224,
				0, 0, 0, 0, 0, 0, 0, 0,
		};
		constexpr static inline double m_LazyMaterial[6]
		{
			3.0,  //knight
			3.3,  //bishop
			5.5,  //rook
			10.0, //queen
			1.0,  //pawn
			0.0   //king
		};
	public:
		PYGMALION_INLINE static scoreType defaultLazyMaterial_Implementation(const pieceType pc) noexcept
		{
			return static_cast<scoreType>(m_LazyMaterial[pc]);
		}
		PYGMALION_INLINE static scoreType defaultMaterial_Implementation(const playerType pl, const pieceType pc, const squareType sq) noexcept
		{
			squareType lsq;
			if (pl == whitePlayer)
				lsq = sq;
			else
				lsq = sq.flipRank();
			switch (pc)
			{
			default:
				PYGMALION_UNREACHABLE;
				return scoreType::zero();
			case pawn:
				return static_cast<scoreType>(m_PST_Pawn[lsq]);
			case knight:
				return static_cast<scoreType>(m_PST_Knight[lsq]);
			case bishop:
				return static_cast<scoreType>(m_PST_Bishop[lsq]);
			case rook:
				return static_cast<scoreType>(m_PST_Rook[lsq]);
			case queen:
				return static_cast<scoreType>(m_PST_Queen[lsq]);
			case king:
				return static_cast<scoreType>(m_PST_King[lsq]);
			}
		}
	};

	std::ostream& operator<<(std::ostream& str, const board& position) noexcept;
}
