namespace pygmalion::chess
{

	class board : public pygmalion::board<descriptor_board, board>
	{
	public:
	private:
		score m_Material;
		uint8_t m_DistanceToDraw;
	public:
		constexpr score material() const noexcept
		{
			return m_Material;
		}
		constexpr score& material() noexcept
		{
			return m_Material;
		}
		constexpr uint8_t getDistanceToDraw() const noexcept
		{
			return m_DistanceToDraw;
		}
		constexpr void setDistanceToDraw(const uint8_t distance) noexcept
		{
			m_DistanceToDraw = distance;
		}
		constexpr score getMaterial() const noexcept
		{
			return m_Material;
		}
		constexpr void setMaterial(const score material) noexcept
		{
			m_Material = material;
		}
		constexpr board(const board&) noexcept = default;
		constexpr board(board&&) noexcept = default;
		~board() = default;
		board& operator=(const board&) = default;
		board& operator=(board&&) = default;
		board() noexcept;
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
			clearCastleRightQueensideBlack();
			clearCastleRightKingsideBlack();
		}
		constexpr void clearCastleRightsWhite() noexcept
		{
			clearCastleRightQueensideWhite();
			clearCastleRightKingsideWhite();
		}
		constexpr void setEnPassantFile(const fileType file) noexcept
		{
			setFlag(enPassantFlag(file));
		}
		constexpr void clearEnPassantFile(const fileType file) noexcept
		{
			clearFlag(enPassantFlag(file));
		}
		constexpr bool checkEnPassantFile(const fileType file) noexcept
		{
			return checkFlag(enPassantFlag(file));
		}
		constexpr void clearEnPassantFiles() noexcept
		{
			setFlags((getFlags()-enPassantFlags));
		}
		squareType kingSquare(const playerType player) const noexcept
		{
			return (pieceOccupancy(king) & playerOccupancy(player)).first();
		}
		constexpr void initialize() noexcept
		{
			clear();
			setMovingPlayer(whitePlayer);
			// pawns
			for (const auto f : fileType::range)
			{
				addPiece(pawn, squareType::fromRankFile(rank2, f), whitePlayer);
				//				position.material() += evaluator::material(whitePlayer, pawn, squareType::fromRankFile(rank2, f));
				addPiece(pawn, squareType::fromRankFile(rank7, f), blackPlayer);
				//				position.material() += evaluator::material(blackPlayer, pawn, squareType::fromRankFile(rank7, f));
			}
			clearEnPassantFiles();
			// kings
			addPiece(king, squareE1, whitePlayer);
			//		position.material() += evaluator::material(whitePlayer, king, squareE1);
			addPiece(king, squareE8, blackPlayer);
			//		position.material() += evaluator::material(blackPlayer, king, squareE8);
					// rooks
			addPiece(rook, squareA1, whitePlayer);
			//		position.material() += evaluator::material(whitePlayer, rook, squareA1);
			addPiece(rook, squareH1, whitePlayer);
			//		position.material() += evaluator::material(whitePlayer, rook, squareH1);
			addPiece(rook, squareA8, blackPlayer);
			//		position.material() += evaluator::material(blackPlayer, rook, squareA8);
			addPiece(rook, squareH8, blackPlayer);
			//		position.material() += evaluator::material(blackPlayer, rook, squareH8);
			setCastleRightQueensideBlack();
			setCastleRightQueensideWhite();
			setCastleRightKingsideBlack();
			setCastleRightKingsideWhite();
			// knights
	/*		position.addPiece(knight, squareB1, whitePlayer);
			position.material() += evaluator::material(whitePlayer, knight, squareB1);
			position.addPiece(knight, squareG1, whitePlayer);
			position.material() += evaluator::material(whitePlayer, knight, squareG1);
			position.addPiece(knight, squareB8, blackPlayer);
			position.material() += evaluator::material(blackPlayer, knight, squareB8);
			position.addPiece(knight, squareG8, blackPlayer);
			position.material() += evaluator::material(blackPlayer, knight, squareG8);
			// bishops
			position.addPiece(bishop, squareC1, whitePlayer);
			position.material() += evaluator::material(whitePlayer, bishop, squareC1);
			position.addPiece(bishop, squareF1, whitePlayer);
			position.material() += evaluator::material(whitePlayer, bishop, squareF1);
			position.addPiece(bishop, squareC8, blackPlayer);
			position.material() += evaluator::material(blackPlayer, bishop, squareC8);
			position.addPiece(bishop, squareF8, blackPlayer);
			position.material() += evaluator::material(blackPlayer, bishop, squareF8);
			// queens
			position.addPiece(queen, squareD1, whitePlayer);
			position.material() += evaluator::material(whitePlayer, queen, squareD1);
			position.addPiece(queen, squareD8, blackPlayer);
			position.material() += evaluator::material(blackPlayer, queen, squareD8);*/
		}
		void onClear_Implementation() noexcept
		{
		}
		void onAddedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
		{
		}
		void onRemovedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
		{
		}
		void onSetFlag_Implementation(const flagType flag) noexcept
		{
		}
		void onClearedFlag_Implementation(const flagType flag) noexcept
		{
		}
	};
}