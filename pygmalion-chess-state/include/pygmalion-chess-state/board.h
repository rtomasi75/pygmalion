namespace pygmalion::chess
{

	class board :
		public pygmalion::board<state::descriptor_state, board>
	{
	public:
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
		squareType kingSquare(const playerType player) const noexcept
		{
			return *(pieceOccupancy(king) & playerOccupancy(player)).begin();
		}

		// Implementation
		static std::string flagToString_Implementation(const flagType flag) noexcept
		{
			switch (flag)
			{
			case castleRightKingsideBlack:
				return "k";
			case castleRightKingsideWhite:
				return "K";
			case castleRightQueensideBlack:
				return "q";
			case castleRightQueensideWhite:
				return "Q";
			case enPassantFileA:
				return "A";
			case enPassantFileB:
				return "B";
			case enPassantFileC:
				return "C";
			case enPassantFileD:
				return "D";
			case enPassantFileE:
				return "E";
			case enPassantFileF:
				return "F";
			case enPassantFileG:
				return "G";
			case enPassantFileH:
				return "H";
			default:
				assert(false);
				return "?";
			}
		}
		static bool parseFlag_Implementation(const std::string& text, flagType& flag) noexcept
		{
			if (text.length() > 0)
			{
				switch (text[0])
				{
				case 'k':
					flag = castleRightKingsideBlack;
					return true;
				case 'K':
					flag = castleRightKingsideWhite;
					return true;
				case 'q':
					flag = castleRightQueensideBlack;
					return true;
				case 'Q':
					flag = castleRightQueensideWhite;
					return true;
				case 'a':
				case 'A':
					flag = enPassantFileA;
					return true;
				case 'b':
				case 'B':
					flag = enPassantFileB;
					return true;
				case 'd':
				case 'D':
					flag = enPassantFileC;
					return true;
				case 'c':
				case 'C':
					flag = enPassantFileD;
					return true;
				case 'e':
				case 'E':
					flag = enPassantFileE;
					return true;
				case 'f':
				case 'F':
					flag = enPassantFileF;
					return true;
				case 'g':
				case 'G':
					flag = enPassantFileG;
					return true;
				case 'h':
				case 'H':
					flag = enPassantFileH;
					return true;
				default:
					return false;
				}
			}
			else
				return false;
		}
		static std::string rankToString_Implementation(const rankType rank) noexcept
		{
			const char c{ static_cast<char>('1' + static_cast<char>(rank)) };
			std::string txt = "";
			txt += c;
			return txt;
		}
		static bool parseRank_Implementation(const std::string& text, rankType& rank) noexcept
		{
			if (text.length() > 0)
			{
				if ((text[0] >= '1') && (text[0] < ('1' + countFiles)))
				{
					rank = text[0] - '1';
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		static std::string fileToString_Implementation(const fileType file) noexcept
		{
			const char c{ static_cast<char>('a' + static_cast<char>(file)) };
			std::string txt = "";
			txt += c;
			return txt;
		}
		static bool parseFile_Implementation(const std::string& text, fileType& file) noexcept
		{
			if (text.length() > 0)
			{
				if ((text[0] >= 'a') && (text[0] < ('a' + countFiles)))
				{
					file = text[0] - 'a';
					return true;
				}
				else if ((text[0] >= 'A') && (text[0] < ('A' + countFiles)))
				{
					file = text[0] - 'A';
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		static std::string playerToString_Implementation(const playerType player) noexcept
		{
			switch (player)
			{
			default:
				return "?";
			case whitePlayer:
				return "+";
			case blackPlayer:
				return "-";
			}
		}
		static bool parsePlayer_Implementation(const std::string& text, playerType& player) noexcept
		{
			if (text.length() > 0)
			{
				switch (text[0])
				{
				case '+':
				case '0':
					player = 0;
					return true;
				case '-':
				case '1':
					player = 1;
					return true;
				default:
					return false;
				}
			}
			else
				return false;
		}
		static std::string pieceToString_Implementation(const pieceType piece, const playerType player) noexcept
		{
			if (player == whitePlayer)
			{
				switch (piece)
				{
				case knight:
					return "N";
				case pawn:
					return "P";
				case rook:
					return "R";
				case bishop:
					return "B";
				case queen:
					return "Q";
				case king:
					return "K";
				default:
					assert(false);
					return "?";
				}
			}
			else
			{
				switch (piece)
				{
				case knight:
					return "n";
				case pawn:
					return "p";
				case rook:
					return "r";
				case bishop:
					return "b";
				case queen:
					return "q";
				case king:
					return "k";
				default:
					assert(false);
					return "?";
				}
			}
		}
		static std::string pieceToString_Implementation(const pieceType piece) noexcept
		{
			switch (piece)
			{
			case knight:
				return "N";
			case pawn:
				return "P";
			case rook:
				return "R";
			case bishop:
				return "B";
			case queen:
				return "Q";
			case king:
				return "K";
			default:
				assert(false);
				return "?";
			}
		}
		static bool parsePiece_Implementation(const std::string& text, pieceType& piece) noexcept
		{
			if (text.length() > 0)
			{
				switch (text[0])
				{
				case 'p':
				case 'P':
					piece = pawn;
					return true;
				case 'r':
				case 'R':
					piece = rook;
					return true;
				case 'q':
				case 'Q':
					piece = queen;
					return true;
				case 'b':
				case 'B':
					piece = bishop;
					return true;
				case 'k':
				case 'K':
					piece = king;
					return true;
				case 'n':
				case 'N':
					piece = knight;
					return true;
				default:
					return false;
				}
			}
			else
				return false;
		}
		void onClear_Implementation() noexcept
		{
		}
		void onAddedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
		{
		}
		void onSetMovingPlayer_Implementation(const playerType player) noexcept
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
		void onInitialize_Implementation() noexcept
		{
			setMovingPlayer(whitePlayer);
			// pawns
			for (const auto f : fileType::range)
			{
				addPiece(pawn, rank2 & f, whitePlayer);
				addPiece(pawn, rank7 & f, blackPlayer);
			}
			clearEnPassantFiles();
			addPiece(king, squareE1, whitePlayer);
			addPiece(king, squareE8, blackPlayer);
			// rooks
			addPiece(rook, squareA1, whitePlayer);
			addPiece(rook, squareH1, whitePlayer);
			addPiece(rook, squareA8, blackPlayer);
			addPiece(rook, squareH8, blackPlayer);
			setCastleRightQueensideBlack();
			setCastleRightQueensideWhite();
			setCastleRightKingsideBlack();
			setCastleRightKingsideWhite();
			// knights
			addPiece(knight, squareB1, whitePlayer);
			addPiece(knight, squareG1, whitePlayer);
			addPiece(knight, squareB8, blackPlayer);
			addPiece(knight, squareG8, blackPlayer);
			// bishops
			addPiece(bishop, squareC1, whitePlayer);
			addPiece(bishop, squareF1, whitePlayer);
			addPiece(bishop, squareC8, blackPlayer);
			addPiece(bishop, squareF8, blackPlayer);
			// queens
			addPiece(queen, squareD1, whitePlayer);
			addPiece(queen, squareD8, blackPlayer);
		}
	};


	std::ostream& operator<<(std::ostream& str, const board& position) noexcept
	{
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		for (const auto r : rankType::range)
		{
			const rankType rank{ -r };
			str << boardType::rankToString(rank) << "|";
			for (const auto file : fileType::range)
			{
				const squareType square{ rank & file };
				if (position.totalOccupancy()[square])
				{
					const pieceType piece{ position.getPiece(square) };
					const playerType player{ position.getPlayer(square) };
					str << boardType::pieceToString(piece, player);
				}
				else
					str << ".";
			}
			str << std::endl;
		}
		str << "-+";
		for (const auto file : fileType::range)
		{
			if (position.checkEnPassantFile(file))
				str << "^";
			else
				str << "-";
		}
		str << std::endl;
		str << " |";
		for (const auto file : fileType::range)
		{
			str << boardType::fileToString(file);
		}
		str << std::endl;
		str << std::endl;
		for (const auto flag : descriptorState::castleFlags)
		{
			if (position.checkFlag(flag))
				str << board::flagToString(flag);
			else
				str << "_";
		}
		str << std::endl;
		str << std::endl;
		str << "Player " << boardType::playerToString(position.movingPlayer()) << " is on the move." << std::endl;
		return str;
	}

}
