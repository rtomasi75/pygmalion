namespace pygmalion::chess
{
	class frontend :
		public pygmalion::frontend<descriptor_frontend, frontend>
	{
	private:
	public:
		static std::string subjectiveToString_Implementation(const subjectiveType& score) noexcept
		{
			return static_cast<std::string>(score);
		}
		static std::string objectiveToString_Implementation(const scoreType& score) noexcept
		{
			return static_cast<std::string>(score);
		}
		static void dumpBoard_Implementation(const boardType& position, std::ostream& str) noexcept
		{
			str << std::endl;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					const squareType sq{ squareType::fromRankFile(- i, j) };
					if (position.totalOccupancy()[sq])
					{
						if (position.playerOccupancy(blackPlayer)[sq])
						{
							switch (position.getPiece(sq))
							{
							case pawn:
								str << "p";
								break;
							case bishop:
								str << "b";
								break;
							case knight:
								str << "n";
								break;
							case rook:
								str << "r";
								break;
							case queen:
								str << "q";
								break;
							case king:
								str << "k";
								break;
							}
						}
						else
						{
							switch (position.getPiece(sq))
							{
							case pawn:
								str << "P";
								break;
							case bishop:
								str << "B";
								break;
							case knight:
								str << "N";
								break;
							case rook:
								str << "R";
								break;
							case queen:
								str << "Q";
								break;
							case king:
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
			for (const auto i : fileType::range)
			{
				if (position.checkEnPassantFile(i))
					str << "^";
				else
					str << "_";
			}
			str << std::endl;
			if (position.movingPlayer() == whitePlayer)
				str << "+";
			else
				str << "-";
			if( position.checkCastleRightKingsideBlack())
				str << "k";
			else
				str << "_";
			if (position.checkCastleRightQueensideBlack())
				str << "q";
			else
				str << "_";
			if (position.checkCastleRightKingsideWhite())
				str << "K";
			else
				str << "_";
			if (position.checkCastleRightQueensideWhite())
				str << "Q";
			else
				str << "_";
			str << std::endl;
		}
		static std::string playerToString(const playerType p)
		{
			switch (p)
			{
			case whitePlayer:
				return "white";
			case blackPlayer:
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
				auto rank = sq.rank();
				auto file = sq.file();
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
			case bishop:
				return "b";
			case knight:
				return "n";
			case rook:
				return "r";
			case queen:
				return "q";
			case pawn:
				return "p";
			case king:
				return "k";
			}
			return "?";
		}
		static std::string moveToString_Implementation(const stackType& stack, const moveType mv) noexcept
		{
			const boardType& position{ stack.position() };
			const squareType from{mv.square(square_from)};
			const squareType to{ mv.square(square_to) };
			const pieceType piece{ position.getPiece(from) };
			const playerType side{ position.movingPlayer() };
			if (mechanicsType::isCastleKingside(mv))
				return "O-O";
			if (mechanicsType::isCastleQueenside(mv))
				return "O-O-O";
			std::string ret = "";
			switch (piece)
			{
			default:
				assert(0);
				break;
			case pawn:
				break;
			case knight:
				ret += "N";
				break;
			case bishop:
				ret += "B";
				break;
			case rook:
				ret += "R";
				break;
			case queen:
				ret += "Q";
				break;
			case king:
				ret += "K";
				break;
			}
			int countamb{ 0 };
			for (const auto sq : squareType::range)
			{
				if ((position.pieceOccupancy(piece) & position.playerOccupancy(side))[sq])
				{
					squaresType captures{ squaresType::none() };
					squaresType moves{ squaresType::none() };
					generatorType::movesFromSquare(stack, sq, moves, captures);
					if ((captures | moves)[to])
					{
						countamb++;
					}
				}
			}
			if (countamb > 1)
			{
				const auto file{ from.file() };
				countamb = 0;
				for (const auto sq : squareType::range)
				{
					if ((position.pieceOccupancy(piece) & position.playerOccupancy(side))[sq])
					{
						squaresType captures{ squaresType::none() };
						squaresType moves{ squaresType::none() };
						generatorType::movesFromSquare(stack, sq, moves, captures);
						if ((captures | moves)[to])
						{
							if (sq.file() == file)
								countamb++;
						}
					}
				}
				if (countamb > 1)
				{
					const auto rank{ from.rank() };
					countamb = 0;
					for (const auto sq : squareType::range)
					{
						if ((position.pieceOccupancy(piece) & position.playerOccupancy(side))[sq])
						{
							squaresType captures{ squaresType::none() };
							squaresType moves{ squaresType::none() };
							generatorType::movesFromSquare(stack, sq, moves, captures);
							if ((captures | moves)[to])
							{
								if (sq.rank() == rank)
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
			if (mechanicsType::isCapture(mv))
				ret += "x";
			ret = ret + squareToString(to);
			if (mechanicsType::isCaptureEnPassant(mv))
				ret += "ep";
			if (mechanicsType::isPromotion(mv))
			{
				switch (mv.piece(piece_promotion))
				{
				case knight:
					ret += "=N";
					break;
				case bishop:
					ret += "=B";
					break;
				case rook:
					ret += "=R";
					break;
				case queen:
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
				return pawn;
			case 'n':
				return knight;
			case 'r':
				return rook;
			case 'b':
				return bishop;
			case 'q':
				return queen;
			case 'k':
				return king;
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
				return squareType::fromRankFile(rank, file);
			}
		}
		static bool parseMove_Implementation(const std::string str, const stackType& stack, moveType& move, std::string& error) noexcept
		{
			const boardType& position{ stack.position() };
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
			case pawn:
				error = "cannot promote to pawn";
				return false;
			case king:
				error = "cannot promote to king";
				return false;
			case knight:
			case bishop:
			case rook:
			case queen:
				bPromotion = true;
				break;
			}
			if (!position.totalOccupancy()[from])
			{
				error = "no piece on " + str.substr(0, 2);
				return false;
			}
			const pieceType piece{ position.getPiece(from) };
			const playerType side{ position.movingPlayer() };
			const playerType sideOther{ side.next() };
			if (!position.playerOccupancy(side)[from])
			{
				if (side == whitePlayer)
					error = "it's whites turn";
				else
					error = "it's blacks turn";
				return false;
			}
			if (promote != pieceType::invalid)
			{
				if (piece != pawn)
				{
					error = "only pawns can promote";
					return false;
				}
				if (side == whitePlayer)
				{
					if (from.rank() != rank7)
					{
						error = "white can only promote from rank 7";
						return false;
					}
					if (to.rank() != rank8)
					{
						error = "white can only promote to rank 8";
						return false;
					}
				}
				else
				{
					if (from.rank() != rank2)
					{
						error = "black can only promote from rank 2";
						return false;
					}
					if (to.rank() != rank1)
					{
						error = "black can only promote to rank 1";
						return false;
					}
				}
			}
			squaresType captures{ squaresType::none() };
			squaresType moves{ squaresType::none() };
			generatorType::movesFromSquare(stack, from, moves, captures);
			const squaresType combimap{ moves | captures };
			bool bCapture{ false };
			bool bEnPassant{ false };
			bool bCastleKingSide{ false };
			bool bCastleQueenSide{ false };
			bool bDoublePush{ false };
			if (combimap[to])
			{
				if (captures[to])
				{
					bCapture = true;
					if (!position.totalOccupancy()[to])
					{
						if (position.pieceOccupancy(pawn)[to])
						{
							const auto file{ to.file() };
							if (position.checkEnPassantFile(file))
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
				if (piece == king)
				{
					if ((from == squareE1) && (to == squareG1) && (side ==whitePlayer))
					{
						if (position.checkCastleRightKingsideWhite())
							bCastleKingSide = true;
						else
						{
							error = "no right for white to castle kingside.";
							return false;
						}
					}
					else if ((from == squareE8) && (to == squareG8) && (side == blackPlayer))
					{
						if (position.checkCastleRightKingsideBlack())
							bCastleKingSide = true;
						else
						{
							error = "no right for black to castle kingside.";
							return false;
						}
					}
					else if ((from == squareE1) && (to == squareC1) && (side == whitePlayer))
					{
						if (position.checkCastleRightQueensideWhite())
							bCastleQueenSide = true;
						else
						{
							error = "no right for white to castle queenside.";
							return false;
						}
					}
					else if ((from == squareE8) && (to == squareC8) && (side == blackPlayer))
					{
						if (position.checkCastleRightQueensideBlack())
							bCastleQueenSide = true;
						else
						{
							error = "no right for black to castle queenside.";
							return false;
						}
					}
				}
				else if (piece == pawn)
				{
					if ((side == whitePlayer) && (from.rank() == rank2) && (to.rank() == rank4))
					{
						bDoublePush = true;
					}
					else if ((side == blackPlayer) && (from.rank() == rank2) && (to.rank() == rank4))
					{
						bDoublePush = true;
					}
				}
				if (bPromotion)
				{
					if (bCapture)
						move = mechanicsType::capturePromotionMove(from, to, promote);
					else
						move = mechanicsType::promotionMove(from, to, promote);
				}
				else
				{
					if (bCapture)
					{
						if (bEnPassant)
							move = mechanicsType::captureEnPassantMove(from, to);
						else
							move = mechanicsType::captureMove(from, to);
					}
					else
					{
						if (bDoublePush)
							move = mechanicsType::doublePushMove(from, to);
						else if (bCastleKingSide)
							move = (side == whitePlayer) ? mechanicsType::castleKingsideWhiteMove() : mechanicsType::castleKingsideBlackMove();
						else if (bCastleQueenSide)
							move = (side == whitePlayer) ? mechanicsType::castleQueensideWhiteMove() : mechanicsType::castleQueensideBlackMove();
						else
							move = mechanicsType::quietMove(from, to);
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
	};
}