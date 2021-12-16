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
		void onInitialize_Implementation(const materialTableType& materialTable) noexcept;
	public:
	};

}
