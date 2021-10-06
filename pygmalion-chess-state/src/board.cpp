#include <pygmalion-chess-state.h>
namespace pygmalion::chess
{
	state::materialTables<state::descriptor_state> board::m_Material;

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
			PYGMALION_UNREACHABLE;
			return "?";
		}
	}

	std::string board::cumulationToString_Implementation(const cumulationType&) noexcept
	{
		return "none";
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
		cumulation().clear();
	}

	void board::onAddedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
	{
		cumulation().score() += m_Material.material(player, piece);
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

	void board::onSetMovingPlayer_Implementation(const playerType player) noexcept
	{
	}

	void board::onRemovedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
	{
		cumulation().score() -= m_Material.material(player, piece);
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

	bool board::setFen(const std::string& fen, std::string& error) noexcept
	{
		clear();
		size_t pos{ 0 };
		typename fileType::baseType file{ fileA };
		typename rankType::baseType rank{ rank8 };
		bool bParse{ true };
		while (bParse)
		{
			if (fen.length() <= pos)
			{
				error = "Unexpected end of string.";
				clear();
				return false;
			}
			switch (fen[pos])
			{
			default:
				error = "Invalid symbol.";
				clear();
				return false;
			case ' ':
				bParse = false;
				break;
			case '1':
				file++;
				break;
			case '2':
				file += 2;
				break;
			case '3':
				file += 3;
				break;
			case '4':
				file += 4;
				break;
			case '5':
				file += 5;
				break;
			case '6':
				file += 6;
				break;
			case '7':
				file += 7;
				break;
			case '8':
				break;
			case '/':
				file = 0;
				rank--;
				break;
			case 'p':
				addPiece(pawn, fileType(file) & rankType(rank), blackPlayer);
				file++;
				break;
			case 'P':
				addPiece(pawn, fileType(file) & rankType(rank), whitePlayer);
				file++;
				break;
			case 'n':
				addPiece(knight, fileType(file) & rankType(rank), blackPlayer);
				file++;
				break;
			case 'N':
				addPiece(knight, fileType(file) & rankType(rank), whitePlayer);
				file++;
				break;
			case 'b':
				addPiece(bishop, fileType(file) & rankType(rank), blackPlayer);
				file++;
				break;
			case 'B':
				addPiece(bishop, fileType(file) & rankType(rank), whitePlayer);
				file++;
				break;
			case 'r':
				addPiece(rook, fileType(file) & rankType(rank), blackPlayer);
				file++;
				break;
			case 'R':
				addPiece(rook, fileType(file) & rankType(rank), whitePlayer);
				file++;
				break;
			case 'q':
				addPiece(queen, fileType(file) & rankType(rank), blackPlayer);
				file++;
				break;
			case 'Q':
				addPiece(queen, fileType(file) & rankType(rank), whitePlayer);
				file++;
				break;
			case 'k':
				addPiece(king, fileType(file) & rankType(rank), blackPlayer);
				file++;
				break;
			case 'K':
				addPiece(king, fileType(file) & rankType(rank), whitePlayer);
				file++;
				break;
			}
			pos++;
			if (file < 0)
				break;
		}
		if (fen.length() <= pos)
		{
			error = "Unexpected end of string.";
			clear();
			return false;
		}
		switch (fen[pos])
		{
		default:
			error = "Invalid symbol.";
			clear();
			return false;
		case 'w':
			setMovingPlayer(whitePlayer);
			break;
		case 'b':
			setMovingPlayer(blackPlayer);
			break;
		}
		pos++;
		if (fen.length() <= pos)
		{
			error = "Unexpected end of string.";
			clear();
			return false;
		}
		if (fen[pos] != ' ')
		{
			error = "Invalid symbol.";
			clear();
			return false;
		}
		pos++;
		if (fen.length() <= pos)
		{
			error = "Unexpected end of string.";
			clear();
			return false;
		}
		if (fen[pos] == '-')
		{
			pos++;
			if (fen.length() <= pos)
			{
				error = "Unexpected end of string.";
				clear();
				return false;
			}
			if (fen[pos] != ' ')
			{
				error = "Invalid symbol.";
				clear();
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
					error = "Invalid symbol.";
					clear();
					return false;
				}
				switch (fen[pos])
				{
				default:
					error = "Invalid symbol.";
					clear();
					return false;
				case ' ':
					bParsing = false;
					break;
				case 'K':
					setCastleRightKingsideWhite();
					break;
				case 'k':
					setCastleRightKingsideBlack();
					break;
				case 'Q':
					setCastleRightQueensideWhite();
					break;
				case 'q':
					setCastleRightQueensideBlack();
					break;
				}
				pos++;
				len++;
			}
			if (len == 0)
			{
				error = "Invalid symbol.";
				clear();
				return false;
			}
		}
		if (fen.length() <= pos)
		{
			error = "Unexpected end of string.";
			clear();
			return false;
		}
		if (fen[pos] != '-')
		{
			typename fileType::baseType epfile{ 0 };
			typename rankType::baseType eprank{ 0 };
			switch (fen[pos])
			{
			default:
				error = "Invalid symbol.";
				clear();
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
			if (fen.length() <= pos)
			{
				error = "Unexpected end of string.";
				clear();
				return false;
			}
			switch (fen[pos])
			{
			default:
				error = "Invalid symbol.";
				clear();
				return false;
			case '3':
				eprank = 3;
				break;
			case '6':
				eprank = 6;
				break;
			}
			pos++;
			const playerType moveSide{ movingPlayer() };
			if ((eprank == 3) && (moveSide == blackPlayer))
			{
				const squaresType whitepawns{ pieceOccupancy(pawn) & playerOccupancy(whitePlayer) };
				setEnPassantFile(fileType(epfile));
			}
			else if ((eprank == 6) && (moveSide == whitePlayer))
			{
				const squaresType blackpawns{ pieceOccupancy(pawn) & playerOccupancy(blackPlayer) };
				setEnPassantFile(fileType(epfile));
			}
		}
		else
			pos++;
		pos++;
		std::string revCountStr = "";
		while (pos < fen.length())
		{
			bool bBreak = false;
			switch (fen[pos])
			{
			case '0':
				revCountStr += fen[pos];
				break;
			case '1':
				revCountStr += fen[pos];
				break;
			case '2':
				revCountStr += fen[pos];
				break;
			case '3':
				revCountStr += fen[pos];
				break;
			case '4':
				revCountStr += fen[pos];
				break;
			case '5':
				revCountStr += fen[pos];
				break;
			case '6':
				revCountStr += fen[pos];
				break;
			case '7':
				revCountStr += fen[pos];
				break;
			case '8':
				revCountStr += fen[pos];
				break;
			case '9':
				revCountStr += fen[pos];
				break;
			default:
				bBreak = true;
				break;
			}
			pos++;
			if (bBreak)
				break;
		}
		if (revCountStr != "")
			cumulation().reversiblePlies() = static_cast<std::uint16_t>(parser::parseInt(revCountStr));
		std::string mvCountStr = "";
		while (pos < fen.length())
		{
			bool bBreak = false;
			switch (fen[pos])
			{
			case '0':
				mvCountStr += fen[pos];
				break;
			case '1':
				mvCountStr += fen[pos];
				break;
			case '2':
				mvCountStr += fen[pos];
				break;
			case '3':
				mvCountStr += fen[pos];
				break;
			case '4':
				mvCountStr += fen[pos];
				break;
			case '5':
				mvCountStr += fen[pos];
				break;
			case '6':
				mvCountStr += fen[pos];
				break;
			case '7':
				mvCountStr += fen[pos];
				break;
			case '8':
				mvCountStr += fen[pos];
				break;
			case '9':
				mvCountStr += fen[pos];
				break;
			default:
				bBreak = true;
				break;
			}
			pos++;
			if (bBreak)
				break;
		}
		return true;
	}

	std::string board::getFen() const noexcept
	{
		std::string fen = "";
		for (typename rankType::baseType rank = 7; rank >= 0; rank--)
		{
			size_t l{ 0 };
			for (typename fileType::baseType file = 0; file < 8; file++)
			{
				const squareType square{ fileType(file) & rankType(rank) };
				if (totalOccupancy()[square])
				{
					if (l != 0)
					{
						fen = fen + parser::fromInt(l);
					}
					l = 0;
					const playerType side{ getPlayer(square) };
					const pieceType piece{ getPiece(square) };
					if (side == whitePlayer)
					{
						switch (piece)
						{
						default:
							PYGMALION_UNREACHABLE;
							break;
						case pawn:
							fen = fen + "P";
							break;
						case rook:
							fen = fen + "R";
							break;
						case bishop:
							fen = fen + "B";
							break;
						case knight:
							fen = fen + "N";
							break;
						case queen:
							fen = fen + "Q";
							break;
						case king:
							fen = fen + "K";
							break;
						}
					}
					else
					{
						switch (piece)
						{
						default:
							PYGMALION_UNREACHABLE;
							break;
						case pawn:
							fen = fen + "p";
							break;
						case rook:
							fen = fen + "r";
							break;
						case bishop:
							fen = fen + "b";
							break;
						case knight:
							fen = fen + "n";
							break;
						case queen:
							fen = fen + "q";
							break;
						case king:
							fen = fen + "k";
							break;
						}
					}
				}
				else
					l++;
			}
			if (l != 0)
				fen = fen + parser::fromInt(l);
			if (rank != 0)
				fen = fen + "/";
		}
		fen = fen + " ";
		if (movingPlayer() == whitePlayer)
			fen = fen + "w ";
		else
			fen = fen + "b ";
		if (!extractFlagRange<0, 3>())
			fen = fen + "- ";
		else
		{
			if (checkCastleRightKingsideWhite())
				fen = fen + "K";
			if (checkCastleRightQueensideWhite())
				fen = fen + "Q";
			if (checkCastleRightKingsideBlack())
				fen = fen + "k";
			if (checkCastleRightQueensideBlack())
				fen = fen + "q";
			fen = fen + " ";
		}
		if (!extractFlagRange<4, 11>())
			fen = fen + "-";
		else
		{
			if (checkEnPassantFile(fileA))
				fen = fen + "a";
			else if (checkEnPassantFile(fileB))
				fen = fen + "b";
			else if (checkEnPassantFile(fileC))
				fen = fen + "c";
			else if (checkEnPassantFile(fileD))
				fen = fen + "d";
			else if (checkEnPassantFile(fileE))
				fen = fen + "e";
			else if (checkEnPassantFile(fileF))
				fen = fen + "f";
			else if (checkEnPassantFile(fileG))
				fen = fen + "g";
			else if (checkEnPassantFile(fileH))
				fen = fen + "h";
			if (movingPlayer() == whitePlayer)
				fen = fen + "6 ";
			else
				fen = fen + "3 ";
		}
		return fen;
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
		str << "Half-move clock: " << static_cast<std::uint64_t>(position.cumulation().reversiblePlies()) << std::endl;
		str << std::endl;
		str << "Player " << boardType::playerToString(position.movingPlayer()) << " is on the move." << std::endl;
		return str;
	}


}