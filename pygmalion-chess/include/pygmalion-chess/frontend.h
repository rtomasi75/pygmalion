namespace pygmalion::chess
{
	class frontend : public pygmalion::frontend<search<movegen, evaluator, 48>, frontend>
	{
	private:
	public:
		static void dumpBitboard(const typename boardType::bitsType& pattern, std::ostream& stream) noexcept
		{
			stream << std::endl;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					const squareType sq{ boardType::fromRankFile(7 - i, j) };
					if (pattern.checkBit(sq))
						stream << "#";
					else
						stream << ".";
				}
				stream << std::endl;
			}
			stream << std::endl;
			stream << "population: " << static_cast<size_t>(pattern.populationCount());
			stream << std::endl;
		}
		static std::string subjectiveToString_Implementation(const subjectiveType& score) noexcept
		{
			return static_cast<std::string>(score);
		}
		static std::string objectiveToString_Implementation(const objectiveType& score) noexcept
		{
			return static_cast<std::string>(score);
		}
		static void dumpBoard_Implementation(const boardType& board, std::ostream& str) noexcept
		{
			str << std::endl;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					const squareType sq{ boardType::fromRankFile(7 - i, j) };
					if (board.totalOccupancy().checkBit(sq))
					{
						if (board.playerOccupancy(boardType::blackPlayer).checkBit(sq))
						{
							switch (board.getPiece(sq))
							{
							case boardType::pawn:
								str << "p";
								break;
							case boardType::bishop:
								str << "b";
								break;
							case boardType::knight:
								str << "n";
								break;
							case boardType::rook:
								str << "r";
								break;
							case boardType::queen:
								str << "q";
								break;
							case boardType::king:
								str << "k";
								break;
							}
						}
						else
						{
							switch (board.getPiece(sq))
							{
							case boardType::pawn:
								str << "P";
								break;
							case boardType::bishop:
								str << "B";
								break;
							case boardType::knight:
								str << "N";
								break;
							case boardType::rook:
								str << "R";
								break;
							case boardType::queen:
								str << "Q";
								break;
							case boardType::king:
								str << "K";
								break;
							}
						}
					}
					else
						str << ".";
				}
				str << std::endl;
			}
			for (const auto i : boardType::file::range)
			{
				if (board.getFlags() & boardType::enPassantFlags(i))
					str << "^";
				else
					str << "_";
			}
			str << std::endl;
			if (board.movingPlayer() == boardType::whitePlayer)
				str << "+";
			else
				str << "-";
			if (board.getFlags() & boardType::castlerightKingsideBlack)
				str << "k";
			else
				str << "_";
			if (board.getFlags() & boardType::castlerightQueensideBlack)
				str << "q";
			else
				str << "_";
			if (board.getFlags() & boardType::castlerightKingsideWhite)
				str << "K";
			else
				str << "_";
			if (board.getFlags() & boardType::castlerightQueensideWhite)
				str << "Q";
			else
				str << "_";
			str << std::endl;
			str << "positionHash: " << parser::toString(board.getHash()) << std::endl;
			str << "pawnHash:     " << parser::toString(board.getPawnstructureHash()) << std::endl;
		}
		static std::string playerToString(const playerType p)
		{
			switch (p)
			{
			case boardType::whitePlayer:
				return "white";
			case boardType::blackPlayer:
				return "black";
			default:
				return "invalid";
			}
		}
		static std::string squareToString(const squareType sq)
		{
			if (!sq.isValid())
				return "??";
			else
			{
				int rank = board::rankOfSquare(sq);
				int file = board::fileOfSquare(sq);
				std::string text{ "" };
				switch (file)
				{
				default:
					assert(false);
					break;
				case 0:
					text += "a";
					break;
				case 1:
					text += "b";
					break;
				case 2:
					text += "c";
					break;
				case 3:
					text += "d";
					break;
				case 4:
					text += "e";
					break;
				case 5:
					text += "f";
					break;
				case 6:
					text += "g";
					break;
				case 7:
					text += "h";
					break;
				}
				switch (rank)
				{
				default:
					assert(false);
					break;
				case 0:
					text += "1";
					break;
				case 1:
					text += "2";
					break;
				case 2:
					text += "3";
					break;
				case 3:
					text += "4";
					break;
				case 4:
					text += "5";
					break;
				case 5:
					text += "6";
					break;
				case 6:
					text += "7";
					break;
				case 7:
					text += "8";
					break;
				}
				return text;
			}
		}
		static std::string pieceToString(const pieceType p) noexcept
		{
			switch (p)
			{
			case board::bishop:
				return "b";
			case board::knight:
				return "n";
			case board::rook:
				return "r";
			case board::queen:
				return "q";
			case board::pawn:
				return "p";
			case board::king:
				return "k";
			}
			return "?";
		}
		/*		static std::string moveToString_Implementation(const moveType mv) noexcept
				{
					std::string str{ squareToString(mv.getFrom()) + squareToString(mv.getTo()) };
					if (mv.isPromotion())
						str += pieceToString(mv.get_PromotionPiece());
					return str;
				}*/
		static std::string moveToString_Implementation(const boardType& position, const moveType mv) noexcept
		{
			//if (mv.isNull())
				//return "null";
			//		if (move.isDraw())
			//			return "draw";
			const squareType from{ mv.from() };
			const squareType to{ mv.to() };
			const pieceType piece{ position.getPiece(from) };
			const playerType side{ position.movingPlayer() };
			if (mv.isCastleKingside())
				return "O-O";
			if (mv.isCastleQueenside())
				return "O-O-O";
			std::string ret = "";
			switch (piece)
			{
			default:
				assert(0);
				break;
			case boardType::pawn:
				break;
			case boardType::knight:
				ret += "N";
				break;
			case boardType::bishop:
				ret += "B";
				break;
			case boardType::rook:
				ret += "R";
				break;
			case boardType::queen:
				ret += "Q";
				break;
			case boardType::king:
				ret += "K";
				break;
			}
			int countamb{ 0 };
			for (const auto i : squareType::range)
			{
				if ((position.pieceOccupancy(piece) & position.playerOccupancy(side)).checkBit(i))
				{
					bitsType captures{ bitsType::empty() };
					bitsType moves{ bitsType::empty() };
					movegen::moveMaps(position, i, moves, captures);
					if ((captures | moves).checkBit(to))
					{
						countamb++;
					}
				}
			}
			if (countamb > 1)
			{
				const auto file{ boardType::fileOfSquare(from) };
				countamb = 0;
				for (const auto i : squareType::range)
				{
					if ((position.pieceOccupancy(piece) & position.playerOccupancy(side)).checkBit(i))
					{
						bitsType captures{ bitsType::empty() };
						bitsType moves{ bitsType::empty() };
						movegen::moveMaps(position, i, moves, captures);
						if ((captures | moves).checkBit(to))
						{
							if (boardType::fileOfSquare(i) == file)
								countamb++;
						}
					}
				}
				if (countamb > 1)
				{
					const auto rank{ boardType::rankOfSquare(from) };
					countamb = 0;
					for (const auto i : squareType::range)
					{
						if ((position.pieceOccupancy(piece) & position.playerOccupancy(side)).checkBit(i))
						{
							bitsType captures{ bitsType::empty() };
							bitsType moves{ bitsType::empty() };
							movegen::moveMaps(position, i, moves, captures);
							if ((captures | moves).checkBit(to))
							{
								if (boardType::rankOfSquare(i) == rank)
									countamb++;
							}
						}
					}
					if (countamb > 1)
					{
						ret += squareToString(from);
					}
					else
					{
						switch (rank)
						{
						case 0:
							ret += "1";
							break;
						case 1:
							ret += "2";
							break;
						case 2:
							ret += "3";
							break;
						case 3:
							ret += "4";
							break;
						case 4:
							ret += "5";
							break;
						case 5:
							ret += "6";
							break;
						case 6:
							ret += "7";
							break;
						case 7:
							ret += "8";
							break;
						}
					}
				}
				else
				{
					switch (file)
					{
					case 0:
						ret += "a";
						break;
					case 1:
						ret += "b";
						break;
					case 2:
						ret += "c";
						break;
					case 3:
						ret += "d";
						break;
					case 4:
						ret += "e";
						break;
					case 5:
						ret += "f";
						break;
					case 6:
						ret += "g";
						break;
					case 7:
						ret += "h";
						break;
					}
				}
			}
			if (mv.isCapture())
				ret += "x";
			ret = ret + squareToString(to);
			if (mv.isPromotion())
			{
				switch (mv.get_PromotionPiece())
				{
				case board::knight:
					ret += "=N";
					break;
				case board::bishop:
					ret += "=B";
					break;
				case board::rook:
					ret += "=R";
					break;
				case board::queen:
					ret += "=Q";
					break;
				}
			}
			return ret;
		}
		static pieceType pieceFromString(const std::string& text) noexcept
		{
			if (text.length() != 1)
				return pieceType::invalid;
			switch (std::tolower(text[0]))
			{
			case 'p':
				return boardType::pawn;
			case 'n':
				return boardType::knight;
			case 'r':
				return boardType::rook;
			case 'b':
				return boardType::bishop;
			case 'q':
				return boardType::queen;
			case 'k':
				return boardType::king;
			}
			return pieceType::invalid;
		}
		static squareType squareFromString(const std::string& text) noexcept
		{
			if (text.length() != 2)
				return squareType::invalid;
			else
			{
				int file;
				int rank;
				switch (text[0])
				{
				default:
					return squareType::invalid;
				case 'a':
				case 'A':
					file = 0;
					break;
				case 'b':
				case 'B':
					file = 1;
					break;
				case 'c':
				case 'C':
					file = 2;
					break;
				case 'd':
				case 'D':
					file = 3;
					break;
				case 'e':
				case 'E':
					file = 4;
					break;
				case 'f':
				case 'F':
					file = 5;
					break;
				case 'g':
				case 'G':
					file = 6;
					break;
				case 'h':
				case 'H':
					file = 7;
					break;
				}
				switch (text[1])
				{
				default:
					return squareType::invalid;
				case '1':
					rank = 0;
					break;
				case '2':
					rank = 1;
					break;
				case '3':
					rank = 2;
					break;
				case '4':
					rank = 3;
					break;
				case '5':
					rank = 4;
					break;
				case '6':
					rank = 5;
					break;
				case '7':
					rank = 6;
					break;
				case '8':
					rank = 7;
					break;
				}
				return boardType::fromRankFile(rank, file);
			}
		}
		static bool parseMove_Implementation(const std::string str, const boardType& position, moveType& move, std::string& error) noexcept
		{
			if (str.length() < 4)
			{
				error = "less than 4 chars";
				return false;
			}
			if (str.length() > 5)
			{
				error = "more than 5 chars";
				return false;
			}
			//					if (ToLower(str) == "null")
			//					{
			//						move = MOVE_EMPTY;
			//						return TRUE;
			//					}
			const squareType from{ squareFromString(str.substr(0, 2)) };
			if (!from.isValid())
			{
				error = "invalid square " + str.substr(0, 2);
				return false;
			}
			const squareType to{ squareFromString(str.substr(2, 2)) };
			if (!to.isValid())
			{
				error = "invalid square " + str.substr(2, 2);
				return false;
			}
			pieceType promote{ pieceType::invalid };
			if (str.length() == 5)
			{
				promote = pieceFromString(str.substr(4, 1));
				if (promote == pieceType::invalid)
				{
					error = "invalid piece " + str.substr(4, 1);
					return false;
				}
			}
			bool bPromotion{ false };
			switch (promote)
			{
			case board::pawn:
				error = "cannot promote to pawn";
				return false;
			case board::king:
				error = "cannot promote to king";
				return false;
			case board::knight:
			case board::bishop:
			case board::rook:
			case board::queen:
				bPromotion = true;
				break;
			}
			if (!position.totalOccupancy().checkBit(from))
			{
				error = "no piece on " + str.substr(0, 2);
				return false;
			}
			const pieceType piece{ position.getPiece(from) };
			const playerType side{ position.movingPlayer() };
			const playerType sideOther{ side.next() };
			if (!position.playerOccupancy(side).checkBit(from))
			{
				if (side == board::whitePlayer)
					error = "it's whites turn";
				else
					error = "it's blacks turn";
				return false;
			}
			if (promote != pieceType::invalid)
			{
				if (piece != board::pawn)
				{
					error = "only pawns can promote";
					return false;
				}
				if (side == board::whitePlayer)
				{
					if (board::rankOfSquare(from) != board::rank7)
					{
						error = "white can only promote from rank 7";
						return false;
					}
					if (board::rankOfSquare(to) != board::rank8)
					{
						error = "white can only promote to rank 8";
						return false;
					}
				}
				else
				{
					if (board::rankOfSquare(from) != board::rank2)
					{
						error = "black can only promote from rank 2";
						return false;
					}
					if (board::rankOfSquare(to) != board::rank1)
					{
						error = "black can only promote to rank 1";
						return false;
					}
				}
			}
			bitsType captures{ bitsType::empty() };
			bitsType moves{ bitsType::empty() };
			movegenType::moveMaps(position, from, moves, captures);
			const bitsType combimap{ moves | captures };
			bool bCapture{ false };
			bool bEnPassant{ false };
			bool bCastleKingSide{ false };
			bool bCastleQueenSide{ false };
			bool bDoublePush{ false };
			if (combimap.checkBit(to))
			{
				if (captures.checkBit(to))
				{
					bCapture = true;
					if (!position.totalOccupancy().checkBit(to))
					{
						if (position.pieceOccupancy(boardType::pawn).checkBit(to))
						{
							const auto file{ boardType::fileOfSquare(to) };
							if (position.getFlags() & boardType::enPassantFlags(file))
							{
								bEnPassant = true;
							}
							else
							{
								error = "en passant capture is illegal on that file";
								return false;
							}
						}
						else
						{
							error = "no piece to capture";
							return false;
						}
					}
				}
				if (piece == boardType::king)
				{
					if ((from == boardType::squareE1) && (to == boardType::squareG1) && (side == boardType::whitePlayer))
					{
						if (position.getFlags() & boardType::castlerightKingsideWhite)
							bCastleKingSide = true;
						else
						{
							error = "no right for white to castle kingside.";
							return false;
						}
					}
					else if ((from == boardType::squareE8) && (to == boardType::squareG8) && (side == boardType::blackPlayer))
					{
						if (position.getFlags() & boardType::castlerightKingsideBlack)
							bCastleKingSide = true;
						else
						{
							error = "no right for black to castle kingside.";
							return false;
						}
					}
					else if ((from == boardType::squareE1) && (to == boardType::squareC1) && (side == boardType::whitePlayer))
					{
						if (position.getFlags() & boardType::castlerightQueensideWhite)
							bCastleQueenSide = true;
						else
						{
							error = "no right for white to castle queenside.";
							return false;
						}
					}
					else if ((from == boardType::squareE8) && (to == boardType::squareC8) && (side == boardType::blackPlayer))
					{
						if (position.getFlags() & boardType::castlerightQueensideBlack)
							bCastleQueenSide = true;
						else
						{
							error = "no right for black to castle queenside.";
							return false;
						}
					}
				}
				else if (piece == board::pawn)
				{
					if ((side == boardType::whitePlayer) && (boardType::rankOfSquare(from) == boardType::rank2) && (boardType::rankOfSquare(to) == boardType::rank4))
					{
						bDoublePush = true;
					}
					else if ((side == boardType::blackPlayer) && (boardType::rankOfSquare(from) == boardType::rank2) && (boardType::rankOfSquare(to) == boardType::rank4))
					{
						bDoublePush = true;
					}
				}
				if (bPromotion)
				{
					if (bCapture)
						move = moveType::promotionCapture(from, to, promote);
					else
						move = moveType::promotion(from, to, promote);
				}
				else
				{
					if (bCapture)
					{
						if (bEnPassant)
							move = moveType::captureEnPassant(from, to);
						else
							move = moveType::capture(from, to);
					}
					else
					{
						if (bDoublePush)
							move = moveType::doublePush(from, to);
						else if (bCastleKingSide)
							move = moveType::castleKingside(side);
						else if (bCastleQueenSide)
							move = moveType::castleKingside(side);
						else
							move = moveType::quiet(from, to);
					}
				}
				return true;
			}
			else
			{
				error = "cannot move to " + str.substr(2, 2);
				return false;
			}
		}
		static std::string variationToString_Implementation(const boardType& position, const variationType& variation)
		{
			boardType currentPosition{ position };
			std::stringstream sstr;
			for (int i = 0; i < variation.length(); i++)
			{
				sstr << moveToString(currentPosition, variation[i]) << " ";
				boardType::movedata md(currentPosition, variation[i]);
				currentPosition.makeMove(md);
			}
			return sstr.str();
		}
	};
}