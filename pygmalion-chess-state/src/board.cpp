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
			fen << "-";
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
		}
		else
		{
			bool bParsing = true;
			size_t len = 0;
			while (bParsing)
			{
				if (len > countFlags)
					return false;
				switch (text[pos])
				{
				default:
					return false;
				case ' ':
					bParsing = false;
					break;
				case 'K':
					flags |= castleRightKingsideWhite;
					pos++;
					len++;
					break;
				case 'k':
					flags |= castleRightKingsideBlack;
					pos++;
					len++;
					break;
				case 'Q':
					flags |= castleRightQueensideWhite;
					pos++;
					len++;
					break;
				case 'q':
					flags |= castleRightQueensideBlack;
					pos++;
					len++;
					break;
				}
			}
		}
		count += pos;
		return true;
	}

	void board::onInitialize_Implementation(const materialTableType& materialTable) noexcept
	{
		setMovingPlayer(whitePlayer);
		// pawns
		for (const auto f : fileType::range)
		{
			addPiece(pawn, rank2 & f, whitePlayer, materialTable);
			addPiece(pawn, rank7 & f, blackPlayer, materialTable);
		}
		clearEnPassant();
		addPiece(king, squareE1, whitePlayer, materialTable);
		addPiece(king, squareE8, blackPlayer, materialTable);
		// rooks
		addPiece(rook, squareA1, whitePlayer, materialTable);
		addPiece(rook, squareH1, whitePlayer, materialTable);
		addPiece(rook, squareA8, blackPlayer, materialTable);
		addPiece(rook, squareH8, blackPlayer, materialTable);
		setCastleRightQueensideBlack();
		setCastleRightQueensideWhite();
		setCastleRightKingsideBlack();
		setCastleRightKingsideWhite();
		// knights
		addPiece(knight, squareB1, whitePlayer, materialTable);
		addPiece(knight, squareG1, whitePlayer, materialTable);
		addPiece(knight, squareB8, blackPlayer, materialTable);
		addPiece(knight, squareG8, blackPlayer, materialTable);
		// bishops
		addPiece(bishop, squareC1, whitePlayer, materialTable);
		addPiece(bishop, squareF1, whitePlayer, materialTable);
		addPiece(bishop, squareC8, blackPlayer, materialTable);
		addPiece(bishop, squareF8, blackPlayer, materialTable);
		// queens
		addPiece(queen, squareD1, whitePlayer, materialTable);
		addPiece(queen, squareD8, blackPlayer, materialTable);
	}

	std::ostream& operator<<(std::ostream& str, const board& position) noexcept
	{
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		for (const auto r : rankType::range)
		{
			const rankType rank{ -r };
			str << rank.toShortString();
			str << "|";
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
							str << (piece & player).toShortString();
						}
						else
							str << "@";
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
					{
						if (position.checkEnPassantTarget(square))
							str << "#";
						else
							str << ".";
					}
				}
			}
			str << std::endl;
		}
		str << "-+";
		for (const auto file : fileType::range)
		{
			str << "-";
		}
		str << std::endl;
		str << " |";
		for (const auto file : fileType::range)
		{
			str << file.toShortString();
		}
		str << std::endl;
		str << std::endl;
		for (const auto flag : descriptorState::castleFlags)
		{
			if (position.testFlag(flag))
				str << flag.toShortString();
			else
				str << "_";
		}
		str << std::endl;
		str << "Pieces: " << boardType::pieceMaskToString(position.pieces(descriptorState::whitePlayer), descriptorState::whitePlayer) << ":" << boardType::pieceMaskToString(position.pieces(descriptorState::blackPlayer), descriptorState::blackPlayer) << std::endl;
		str << std::endl;
		str << std::endl;
		str << "Material: " << position.material().makeSubjective(position.movingPlayer()) << std::endl;
		str << std::endl;
		str << "Hash: " << std::setw(8) << std::hex << static_cast<std::uint64_t>(position.hash()) << std::dec << std::endl;
		str << std::endl;
		str << "Half-move clock: " << static_cast<std::uint64_t>(position.getReversiblePlyCount()) << std::endl;
		str << "Moves played:    " << static_cast<std::uint64_t>(position.getMoveCount()) << std::endl;
		str << std::endl;
		str << "Player " << position.movingPlayer().toShortString() << " is on the move." << std::endl;
		return str;
	}


}