#include <pygmalion-chess-state.h>
namespace pygmalion::chess
{
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
			PYGMALION_UNREACHABLE;
			return "?";
		}
	}

	std::string board::cumulationToString_Implementation(const cumulationType&) noexcept
	{
		return "none";
	}

	bool board::parseFlag_Implementation(const std::string& text, flagType& flag, size_t& count) noexcept
	{
		if (text.length() > 0)
		{
			switch (text[0])
			{
			case 'k':
				flag = castleRightKingsideBlack;
				count++;
				return true;
			case 'K':
				flag = castleRightKingsideWhite;
				count++;
				return true;
			case 'q':
				flag = castleRightQueensideBlack;
				count++;
				return true;
			case 'Q':
				flag = castleRightQueensideWhite;
				count++;
				return true;
			case 'a':
			case 'A':
				flag = enPassantFileA;
				count++;
				return true;
			case 'b':
			case 'B':
				flag = enPassantFileB;
				count++;
				return true;
			case 'd':
			case 'D':
				flag = enPassantFileC;
				count++;
				return true;
			case 'c':
			case 'C':
				flag = enPassantFileD;
				count++;
				return true;
			case 'e':
			case 'E':
				flag = enPassantFileE;
				count++;
				return true;
			case 'f':
			case 'F':
				flag = enPassantFileF;
				count++;
				return true;
			case 'g':
			case 'G':
				flag = enPassantFileG;
				count++;
				return true;
			case 'h':
			case 'H':
				flag = enPassantFileH;
				count++;
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

	bool board::parseRank_Implementation(const std::string& text, rankType& rank, size_t& count) noexcept
	{
		if (text.length() > 0)
		{
			if ((text[0] >= '1') && (text[0] < ('1' + countRanks)))
			{
				rank = text[0] - '1';
				count++;
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

	bool board::parseFile_Implementation(const std::string& text, fileType& file, size_t& count) noexcept
	{
		if (text.length() > 0)
		{
			if ((text[0] >= 'a') && (text[0] < ('a' + countFiles)))
			{
				file = text[0] - 'a';
				count++;
				return true;
			}
			else if ((text[0] >= 'A') && (text[0] < ('A' + countFiles)))
			{
				file = text[0] - 'A';
				count++;
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
			return "w";
		case blackPlayer:
			return "b";
		}
	}

	bool board::parsePlayer_Implementation(const std::string& text, playerType& player, size_t& count) noexcept
	{
		if (text.length() > 0)
		{
			switch (text[0])
			{
			case 'W':
			case 'w':
			case '+':
			case '0':
				player = 0;
				count++;
				return true;
			case 'B':
			case 'b':
			case '-':
			case '1':
				player = 1;
				count++;
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
				PYGMALION_UNREACHABLE;
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
				PYGMALION_UNREACHABLE;
				return "?";
			}
		}
	}

	bool board::parsePiece_Implementation(const std::string& text, pieceType& piece, playerType& player, size_t& count) noexcept
	{
		if (text.length() > 0)
		{
			switch (text[0])
			{
			case 'p':
				piece = pawn;
				player = 1;
				count++;
				return true;
			case 'P':
				piece = pawn;
				player = 0;
				count++;
				return true;
			case 'r':
				piece = rook;
				player = 1;
				count++;
				return true;
			case 'R':
				piece = rook;
				player = 0;
				count++;
				return true;
			case 'q':
				piece = queen;
				player = 1;
				count++;
				return true;
			case 'Q':
				piece = queen;
				player = 0;
				count++;
				return true;
			case 'b':
				piece = bishop;
				player = 1;
				count++;
				return true;
			case 'B':
				piece = bishop;
				player = 0;
				count++;
				return true;
			case 'k':
				piece = king;
				player = 1;
				count++;
				return true;
			case 'K':
				piece = king;
				player = 0;
				count++;
				return true;
			case 'n':
				piece = knight;
				player = 1;
				count++;
				return true;
			case 'N':
				piece = knight;
				player = 0;
				count++;
				return true;
			default:
				return false;
			}
		}
		else
			return false;
	}

	std::string board::flagsToString_Implementation(const flagsType flags, const playerType movingPlayer) noexcept
	{
		std::stringstream fen;
		if (!flags.extractRange<0, 3>())
			fen << "- ";
		else
		{
			if (flags[castleRightKingsideWhite])
				fen << "K";
			if (flags[castleRightQueensideWhite])
				fen << "Q";
			if (flags[castleRightKingsideBlack])
				fen << "k";
			if (flags[castleRightQueensideBlack])
				fen << "q";
			fen << " ";
		}
		if (!flags.extractRange<4, 11>())
			fen << "-";
		else
		{
			if (flags[enPassantFlag(fileA)])
				fen << "a";
			else if (flags[enPassantFlag(fileB)])
				fen << "b";
			else if (flags[enPassantFlag(fileC)])
				fen << "c";
			else if (flags[enPassantFlag(fileD)])
				fen << "d";
			else if (flags[enPassantFlag(fileE)])
				fen << "e";
			else if (flags[enPassantFlag(fileF)])
				fen << "f";
			else if (flags[enPassantFlag(fileG)])
				fen << "g";
			else if (flags[enPassantFlag(fileH)])
				fen << "h";
			if (movingPlayer == whitePlayer)
				fen << "6";
			else
				fen << "3";
		}
		return fen.str();
	}

	bool board::parseFlags_Implementation(const std::string& text, flagsType& flags, size_t& count) noexcept
	{
		size_t pos{ 0 };
		flags.clear();
		if (text.length() <= pos)
		{
			return false;
		}
		if (text[pos] == '-')
		{
			pos++;
			if (text.length() <= pos)
			{
				return false;
			}
			if (text[pos] != ' ')
			{
				return false;
			}
			pos++;
		}
		else
		{
			bool bParsing = true;
			size_t len = 0;
			while (bParsing)
			{
				if (len >= 5)
				{
					return false;
				}
				switch (text[pos])
				{
				default:
					return false;
				case ' ':
					bParsing = false;
					break;
				case 'K':
					flags.set(castleRightKingsideWhite);
					break;
				case 'k':
					flags.set(castleRightKingsideBlack);
					break;
				case 'Q':
					flags.set(castleRightQueensideWhite);
					break;
				case 'q':
					flags.set(castleRightQueensideBlack);
					break;
				}
				pos++;
				len++;
			}
			if (len == 0)
			{
				return false;
			}
		}
		if (text.length() <= pos)
		{
			return false;
		}
		if (text[pos] != '-')
		{
			typename fileType::baseType epfile{ 0 };
			typename rankType::baseType eprank{ 0 };
			switch (text[pos])
			{
			default:
				return false;
			case 'a':
				epfile = 0;
				break;
			case 'b':
				epfile = 1;
				break;
			case 'c':
				epfile = 2;
				break;
			case 'd':
				epfile = 3;
				break;
			case 'e':
				epfile = 4;
				break;
			case 'f':
				epfile = 5;
				break;
			case 'g':
				epfile = 6;
				break;
			case 'h':
				epfile = 7;
				break;
			}
			pos++;
			if (text.length() <= pos)
			{
				return false;
			}
			switch (text[pos])
			{
			default:
				return false;
			case '3':
				eprank = 3;
				break;
			case '6':
				eprank = 6;
				break;
			}
			pos++;
			flags.set(enPassantFlag(epfile));
		}
		else
			pos++;
		count += pos;
		return true;
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
					if (position.playerOccupancy(descriptorState::whitePlayer)[square] && position.playerOccupancy(descriptorState::blackPlayer)[square])
						str << "!";
					else
					{
						bool hasPiece{ false };
						for (const auto pc : pieceType::range)
						{
							if (position.pieceOccupancy(pc)[square])
							{
								hasPiece = true;
								break;
							}
						}
						if (hasPiece)
						{
							const pieceType piece{ position.getPiece(square) };
							const playerType player{ position.getPlayer(square) };
							str << boardType::pieceToString(piece, player);
						}
						else
							str << "E";
					}
				}
				else
				{
					bool hasPiece{ false };
					for (const auto pc : pieceType::range)
					{
						if (position.pieceOccupancy(pc)[square])
						{
							hasPiece = true;
							break;
						}
					}
					if (hasPiece)
						str << "?";
					else
						str << ".";
				}
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
		str << "Material: " << position.material() << std::endl;
		str << std::endl;
		str << "Hash: " << std::setw(8) << std::hex << static_cast<std::uint64_t>(position.hash()) << std::dec << std::endl;
		str << std::endl;
		str << "Half-move clock: " << static_cast<std::uint64_t>(position.getReversiblePlyCount()) << std::endl;
		str << "Moves played:    " << static_cast<std::uint64_t>(position.getMoveCount()) << std::endl;
		str << std::endl;
		str << "Player " << boardType::playerToString(position.movingPlayer()) << " is on the move." << std::endl;
		return str;
	}


}