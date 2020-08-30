namespace pygmalion::chess
{
	class frontend : public pygmalion::frontend<search<movegen, evaluator, 63>, frontend>
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
					const squareType sq{ squareType::fromRankFile(7 - i, j) };
					if (pattern[sq])
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
					const squareType sq{ squareType::fromRankFile(7 - i, j) };
					if (board.totalOccupancy()[sq])
					{
						if (board.playerOccupancy(movegenType::blackPlayer)[sq])
						{
							switch (board.getPiece(sq))
							{
							case movegenType::pawn:
								str << "p";
								break;
							case movegenType::bishop:
								str << "b";
								break;
							case movegenType::knight:
								str << "n";
								break;
							case movegenType::rook:
								str << "r";
								break;
							case movegenType::queen:
								str << "q";
								break;
							case movegenType::king:
								str << "k";
								break;
							}
						}
						else
						{
							switch (board.getPiece(sq))
							{
							case movegenType::pawn:
								str << "P";
								break;
							case movegenType::bishop:
								str << "B";
								break;
							case movegenType::knight:
								str << "N";
								break;
							case movegenType::rook:
								str << "R";
								break;
							case movegenType::queen:
								str << "Q";
								break;
							case movegenType::king:
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
			for (const auto i : boardType::fileType::range)
			{
				if (movegen::position_checkEnPassantFlag(board, i))
					str << "^";
				else
					str << "_";
			}
			str << std::endl;
			if (board.movingPlayer() == movegenType::whitePlayer)
				str << "+";
			else
				str << "-";
			if (movegen::position_checkCastlerightKingsideBlack(board))
				str << "k";
			else
				str << "_";
			if (movegen::position_checkCastlerightQueensideBlack(board))
				str << "q";
			else
				str << "_";
			if (movegen::position_checkCastlerightKingsideWhite(board))
				str << "K";
			else
				str << "_";
			if (movegen::position_checkCastlerightQueensideWhite(board))
				str << "Q";
			else
				str << "_";
			str << std::endl;
		}
		static std::string playerToString(const playerType p)
		{
			switch (p)
			{
			case movegenType::whitePlayer:
				return "white";
			case movegenType::blackPlayer:
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
			case movegenType::bishop:
				return "b";
			case movegenType::knight:
				return "n";
			case movegenType::rook:
				return "r";
			case movegenType::queen:
				return "q";
			case movegenType::pawn:
				return "p";
			case movegenType::king:
				return "k";
			}
			return "?";
		}
		static std::string moveToString_Implementation(const boardType& position, const moveType mv) noexcept
		{
			//if (mv.isNull())
				//return "null";
			//		if (move.isDraw())
			//			return "draw";
			const squareType from{ movegenType::move_from(mv) };
			const squareType to{ movegenType::move_to(mv) };
			const pieceType piece{ position.getPiece(from) };
			const playerType side{ position.movingPlayer() };
			if (movegenType::move_isCastleKingside(mv))
				return "O-O";
			if (movegenType::move_isCastleQueenside(mv))
				return "O-O-O";
			std::string ret = "";
			switch (piece)
			{
			default:
				assert(0);
				break;
			case movegenType::pawn:
				break;
			case movegenType::knight:
				ret += "N";
				break;
			case movegenType::bishop:
				ret += "B";
				break;
			case movegenType::rook:
				ret += "R";
				break;
			case movegenType::queen:
				ret += "Q";
				break;
			case movegenType::king:
				ret += "K";
				break;
			}
			int countamb{ 0 };
			for (const auto sq : squareType::range)
			{
				if ((position.pieceOccupancy(piece) & position.playerOccupancy(side))[sq])
				{
					bitsType captures{ bitsType::empty() };
					bitsType moves{ bitsType::empty() };
					movegen::moveMaps(position, sq, moves, captures);
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
						bitsType captures{ bitsType::empty() };
						bitsType moves{ bitsType::empty() };
						movegen::moveMaps(position, sq, moves, captures);
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
							bitsType captures{ bitsType::empty() };
							bitsType moves{ bitsType::empty() };
							movegen::moveMaps(position, sq, moves, captures);
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
			if (movegenType::move_isCapture(mv))
				ret += "x";
			ret = ret + squareToString(to);
			if (movegenType::move_isCaptureEnPassant(mv))
				ret += "ep";
			if (movegenType::move_isPromotion(mv))
			{
				switch (movegenType::move_promotionPiece(mv))
				{
				case movegenType::knight:
					ret += "=N";
					break;
				case movegenType::bishop:
					ret += "=B";
					break;
				case movegenType::rook:
					ret += "=R";
					break;
				case movegenType::queen:
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
				return movegenType::pawn;
			case 'n':
				return movegenType::knight;
			case 'r':
				return movegenType::rook;
			case 'b':
				return movegenType::bishop;
			case 'q':
				return movegenType::queen;
			case 'k':
				return movegenType::king;
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
			case movegenType::pawn:
				error = "cannot promote to pawn";
				return false;
			case movegenType::king:
				error = "cannot promote to king";
				return false;
			case movegenType::knight:
			case movegenType::bishop:
			case movegenType::rook:
			case movegenType::queen:
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
				if (side == movegenType::whitePlayer)
					error = "it's whites turn";
				else
					error = "it's blacks turn";
				return false;
			}
			if (promote != pieceType::invalid)
			{
				if (piece != movegenType::pawn)
				{
					error = "only pawns can promote";
					return false;
				}
				if (side == movegenType::whitePlayer)
				{
					if (from.rank() != movegen::rank7)
					{
						error = "white can only promote from rank 7";
						return false;
					}
					if (to.rank() != movegen::rank8)
					{
						error = "white can only promote to rank 8";
						return false;
					}
				}
				else
				{
					if (from.rank() != movegen::rank2)
					{
						error = "black can only promote from rank 2";
						return false;
					}
					if (to.rank() != movegen::rank1)
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
			if (combimap[to])
			{
				if (captures[to])
				{
					bCapture = true;
					if (!position.totalOccupancy()[to])
					{
						if (position.pieceOccupancy(movegenType::pawn)[to])
						{
							const auto file{ to.file() };
							if (movegenType::position_checkEnPassantFlag(position, file))
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
				if (piece == movegenType::king)
				{
					if ((from == movegen::squareE1) && (to == movegen::squareG1) && (side == movegenType::whitePlayer))
					{
						if (movegenType::position_checkCastlerightKingsideWhite(position))
							bCastleKingSide = true;
						else
						{
							error = "no right for white to castle kingside.";
							return false;
						}
					}
					else if ((from == movegen::squareE8) && (to == movegen::squareG8) && (side == movegenType::blackPlayer))
					{
						if (movegenType::position_checkCastlerightKingsideBlack(position))
							bCastleKingSide = true;
						else
						{
							error = "no right for black to castle kingside.";
							return false;
						}
					}
					else if ((from == movegen::squareE1) && (to == movegen::squareC1) && (side == movegenType::whitePlayer))
					{
						if (movegenType::position_checkCastlerightQueensideWhite(position))
							bCastleQueenSide = true;
						else
						{
							error = "no right for white to castle queenside.";
							return false;
						}
					}
					else if ((from == movegen::squareE8) && (to == movegen::squareC8) && (side == movegenType::blackPlayer))
					{
						if (movegenType::position_checkCastlerightQueensideBlack(position))
							bCastleQueenSide = true;
						else
						{
							error = "no right for black to castle queenside.";
							return false;
						}
					}
				}
				else if (piece == movegenType::pawn)
				{
					if ((side == movegenType::whitePlayer) && (from.rank() == movegen::rank2) && (to.rank() == movegen::rank4))
					{
						bDoublePush = true;
					}
					else if ((side == movegenType::blackPlayer) && (from.rank() == movegen::rank2) && (to.rank() == movegen::rank4))
					{
						bDoublePush = true;
					}
				}
				if (bPromotion)
				{
					if (bCapture)
						move = movegenType::move_capturePromotion(from, to, promote);
					else
						move = movegenType::move_promotion(from, to, promote);
				}
				else
				{
					if (bCapture)
					{
						if (bEnPassant)
							move = movegenType::move_captureEnPassant(from, to);
						else
							move = movegenType::move_capture(from, to);
					}
					else
					{
						if (bDoublePush)
							move = movegenType::move_doublePush(from, to);
						else if (bCastleKingSide)
							move = (side == movegenType::whitePlayer) ? movegenType::move_castleKingsideWhite() : movegenType::move_castleKingsideBlack();
						else if (bCastleQueenSide)
							move = (side == movegenType::whitePlayer) ? movegenType::move_castleQueensideWhite() : movegenType::move_castleQueensideBlack();
						else
							move = movegenType::move_quiet(from, to);
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
				movegenType::movedata md(currentPosition, variation[i]);
				movegenType::makeMove(currentPosition, md);
			}
			return sstr.str();
		}
	};
}