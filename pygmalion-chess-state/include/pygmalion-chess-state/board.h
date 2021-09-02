namespace pygmalion::chess
{

	class board :
		public pygmalion::board<state::descriptor_state, board>
	{
	private:
		static state::materialTables<state::descriptor_state> m_Material;
	public:
		constexpr static materialScore materialValue(const pieceType pc, const playerType pl) noexcept
		{
			return m_Material.material(pl, pc);
		}
		constexpr void clearCastleRightQueensideBlack() noexcept
		{
			clearFlag(castleRightQueensideBlack);
		}
		constexpr void clearCastleRightQueensideWhite() noexcept
		{
			clearFlag(castleRightQueensideWhite);
		}
		constexpr void clearCastleRightKingsideBlack() noexcept
		{
			clearFlag(castleRightKingsideBlack);
		}
		constexpr void clearCastleRightKingsideWhite() noexcept
		{
			clearFlag(castleRightKingsideWhite);
		}
		constexpr void setCastleRightQueensideBlack() noexcept
		{
			setFlag(castleRightQueensideBlack);
		}
		constexpr void setCastleRightQueensideWhite() noexcept
		{
			setFlag(castleRightQueensideWhite);
		}
		constexpr void setCastleRightKingsideBlack() noexcept
		{
			setFlag(castleRightKingsideBlack);
		}
		constexpr void setCastleRightKingsideWhite() noexcept
		{
			setFlag(castleRightKingsideWhite);
		}
		constexpr bool checkCastleRightQueensideBlack() const noexcept
		{
			return checkFlag(castleRightQueensideBlack);
		}
		constexpr bool checkCastleRightQueensideWhite() const noexcept
		{
			return checkFlag(castleRightQueensideWhite);
		}
		constexpr bool checkCastleRightKingsideBlack() const noexcept
		{
			return checkFlag(castleRightKingsideBlack);
		}
		constexpr bool checkCastleRightKingsideWhite() const noexcept
		{
			return checkFlag(castleRightKingsideWhite);
		}
		constexpr bool checkCastleRightQueenside(const playerType player) const noexcept
		{
			return (player == whitePlayer) ? checkCastleRightQueensideWhite() : checkCastleRightQueensideBlack();
		}
		constexpr bool checkCastleRightKingside(const playerType player) const noexcept
		{
			return (player == whitePlayer) ? checkCastleRightKingsideWhite() : checkCastleRightKingsideBlack();
		}
		constexpr void clearCastleRightsBlack() noexcept
		{
			clearFlags(castleFlagsBlack);
		}
		constexpr void clearCastleRightsWhite() noexcept
		{
			clearFlags(castleFlagsWhite);
		}
		constexpr void setEnPassantFile(const fileType file) noexcept
		{
			setFlag(enPassantFlag(file));
		}
		constexpr void clearEnPassantFile(const fileType file) noexcept
		{
			clearFlag(enPassantFlag(file));
		}
		constexpr bool checkEnPassantFile(const fileType file) const noexcept
		{
			return checkFlag(enPassantFlag(file));
		}
		constexpr void clearEnPassantFiles() noexcept
		{
			clearFlags(enPassantFlags);
		}
		squareType kingSquare(const playerType player) const noexcept;
		bool setFen(const std::string& fen, std::string& error) noexcept;
		std::string getFen() const noexcept;
		constexpr materialScore material() const noexcept
		{
			return cumulation().score();
		}
		// Implementation
		static std::string flagToString_Implementation(const flagType flag) noexcept;
		static bool parseFlag_Implementation(std::string& text, flagType& flag) noexcept;
		static std::string rankToString_Implementation(const rankType rank) noexcept;
		static bool parseRank_Implementation(std::string& text, rankType& rank) noexcept;
		static std::string fileToString_Implementation(const fileType file) noexcept;
		static bool parseFile_Implementation(std::string& text, fileType& file) noexcept;
		static std::string playerToString_Implementation(const playerType player) noexcept;
		static bool parsePlayer_Implementation(std::string& text, playerType& player) noexcept;
		static std::string pieceToString_Implementation(const pieceType piece, const playerType player) noexcept;
		static bool parsePiece_Implementation(std::string& text, pieceType& piece, playerType& player) noexcept;
		void onClear_Implementation() noexcept;
		void onAddedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept;
		void onSetMovingPlayer_Implementation(const playerType player) noexcept;
		void onRemovedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept;
		void onSetFlag_Implementation(const flagType flag) noexcept;
		void onClearedFlag_Implementation(const flagType flag) noexcept;
		void onInitialize_Implementation() noexcept;
		static std::string cumulationToString_Implementation(const cumulationType&) noexcept;
	};

	std::ostream& operator<<(std::ostream& str, const board& position) noexcept;
}
