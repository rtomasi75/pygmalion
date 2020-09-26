#include <pygmalion-chess-state.h>
namespace pygmalion::chess
{
	typename board::squareType board::kingSquare(const playerType player) const noexcept
	{
		return *(pieceOccupancy(king) & playerOccupancy(player)).begin();
	}

	std::string board::flagToString_Implementation(const flagType flag) noexcept
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

	bool board::parseFlag_Implementation(std::string& text, flagType& flag) noexcept
	{
		if (text.length() > 0)
		{
			switch (text[0])
			{
			case 'k':
				flag = castleRightKingsideBlack;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'K':
				flag = castleRightKingsideWhite;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'q':
				flag = castleRightQueensideBlack;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'Q':
				flag = castleRightQueensideWhite;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'a':
			case 'A':
				flag = enPassantFileA;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'b':
			case 'B':
				flag = enPassantFileB;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'd':
			case 'D':
				flag = enPassantFileC;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'c':
			case 'C':
				flag = enPassantFileD;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'e':
			case 'E':
				flag = enPassantFileE;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'f':
			case 'F':
				flag = enPassantFileF;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'g':
			case 'G':
				flag = enPassantFileG;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'h':
			case 'H':
				flag = enPassantFileH;
				text = text.substr(1, text.length() - 1);
				return true;
			default:
				return false;
			}
		}
		else
			return false;
	}
	
	std::string board::rankToString_Implementation(const rankType rank) noexcept
	{
		const char c{ static_cast<char>('1' + static_cast<char>(rank)) };
		std::string txt = "";
		txt += c;
		return txt;
	}

	bool board::parseRank_Implementation(std::string& text, rankType& rank) noexcept
	{
		if (text.length() > 0)
		{
			if ((text[0] >= '1') && (text[0] < ('1' + countRanks)))
			{
				rank = text[0] - '1';
				text = text.substr(1, text.length() - 1);
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}

	std::string board::fileToString_Implementation(const fileType file) noexcept
	{
		const char c{ static_cast<char>('a' + static_cast<char>(file)) };
		std::string txt = "";
		txt += c;
		return txt;
	}

	bool board::parseFile_Implementation(std::string& text, fileType& file) noexcept
	{
		if (text.length() > 0)
		{
			if ((text[0] >= 'a') && (text[0] < ('a' + countFiles)))
			{
				file = text[0] - 'a';
				text = text.substr(1, text.length() - 1);
				return true;
			}
			else if ((text[0] >= 'A') && (text[0] < ('A' + countFiles)))
			{
				file = text[0] - 'A';
				text = text.substr(1, text.length() - 1);
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}

	std::string board::playerToString_Implementation(const playerType player) noexcept
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

	bool board::parsePlayer_Implementation(std::string& text, playerType& player) noexcept
	{
		if (text.length() > 0)
		{
			switch (text[0])
			{
			case '+':
			case '0':
				player = 0;
				text = text.substr(1, text.length() - 1);
				return true;
			case '-':
			case '1':
				player = 1;
				text = text.substr(1, text.length() - 1);
				return true;
			default:
				return false;
			}
		}
		else
			return false;
	}

	std::string board::pieceToString_Implementation(const pieceType piece, const playerType player) noexcept
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

	bool board::parsePiece_Implementation(std::string& text, pieceType& piece, playerType& player) noexcept
	{
		if (text.length() > 0)
		{
			switch (text[0])
			{
			case 'p':
				piece = pawn;
				player = 1;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'P':
				piece = pawn;
				player = 0;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'r':
				piece = rook;
				player = 1;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'R':
				piece = rook;
				player = 0;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'q':
				piece = queen;
				player = 1;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'Q':
				piece = queen;
				player = 0;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'b':
				piece = bishop;
				player = 1;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'B':
				piece = bishop;
				player = 0;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'k':
				piece = king;
				player = 1;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'K':
				piece = king;
				player = 0;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'n':
				piece = knight;
				player = 1;
				text = text.substr(1, text.length() - 1);
				return true;
			case 'N':
				piece = knight;
				player = 0;
				text = text.substr(1, text.length() - 1);
				return true;
			default:
				return false;
			}
		}
		else
			return false;
	}

	void board::onClear_Implementation() noexcept
	{
	}

	void board::onAddedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
	{
	}

	void board::onSetMovingPlayer_Implementation(const playerType player) noexcept
	{
	}

	void board::onRemovedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
	{
	}

	void board::onSetFlag_Implementation(const flagType flag) noexcept
	{
	}

	void board::onClearedFlag_Implementation(const flagType flag) noexcept
	{
	}

	void board::onInitialize_Implementation() noexcept
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