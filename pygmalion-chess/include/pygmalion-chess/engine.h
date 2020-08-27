namespace pygmalion::chess
{
	class engine : public pygmalion::engine<pygmalion::chess::frontend>
	{
	private:
		class command_debugTable : public commandType
		{
		private:
		protected:
			virtual bool onProcess(engineType& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-table")
				{
					eng.outputStream() << std::endl;
					std::string table;
					std::string remainder2;
					parser::parseToken(remainder, table, remainder2);
					if (table == "kingmovemap" || table == "kmm")
					{
						std::string square;
						std::string remainder3;
						parser::parseToken(remainder2, square, remainder3);
						squareType sq{ frontendType::squareFromString(square) };
						if (sq.isValid())
						{
							if (remainder3 == "")
								frontend::dumpBitboard(movegen::tables().kingMoveMap(sq), eng.outputStream());
							else
							{
								eng.outputStream() << "(untabled)" << std::endl;
								frontend::dumpBitboard(movegen::kingMoveMap_untabled(sq), eng.outputStream());
							}
						}
						else
						{
							eng.outputStream() << "invalid square: " << square << std::endl;
						}
					}
					else if (table == "knightmovemap" || table == "nmm")
					{
						std::string square;
						std::string remainder3;
						parser::parseToken(remainder2, square, remainder3);
						squareType sq{ frontendType::squareFromString(square) };
						if (sq.isValid())
						{
							if (remainder3 == "")
								frontend::dumpBitboard(movegen::tables().knightMoveMap(sq), eng.outputStream());
							else
							{
								eng.outputStream() << "(untabled)" << std::endl;
								frontend::dumpBitboard(movegen::knightMoveMap_untabled(sq), eng.outputStream());
							}
						}
						else
						{
							eng.outputStream() << "invalid square: " << square << std::endl;
						}
					}
					else if (table == "pawmmovemap" || table == "pmm")
					{
						std::string player;
						std::string remainder3;
						parser::parseToken(remainder2, player, remainder3);
						playerType p{ playerType::invalid };
						if (player == "white" || player == "w" || player == "+" || player == "0")
							p = boardType::whitePlayer;
						else if (player == "black" || player == "b" || player == "-" || player == "1")
							p = boardType::blackPlayer;
						if (p.isValid())
						{
							std::string square;
							std::string remainder4;
							parser::parseToken(remainder3, square, remainder4);
							squareType sq{ frontendType::squareFromString(square) };
							if (sq.isValid())
							{
								if (remainder4 == "")
									frontend::dumpBitboard(movegen::tables().pawnMoveMap(sq, p), eng.outputStream());
								else
								{
									eng.outputStream() << "(untabled)" << std::endl;
									frontend::dumpBitboard(movegen::pawnMoveMap_untabled(p, sq, false), eng.outputStream());
								}
							}
							else
								eng.outputStream() << "invalid square: " << square << std::endl;
						}
						else
							eng.outputStream() << "invalid player: " << player << std::endl;
					}
					else if (table == "material" || table == "mat")
					{
						std::string player;
						std::string remainder3;
						parser::parseToken(remainder2, player, remainder3);
						playerType p{ playerType::invalid };
						if (player == "white" || player == "w" || player == "+" || player == "0")
							p = boardType::whitePlayer;
						else if (player == "black" || player == "b" || player == "-" || player == "1")
							p = boardType::blackPlayer;
						if (p.isValid())
						{
							std::string square;
							std::string remainder4;
							parser::parseToken(remainder3, square, remainder4);
							squareType sq{ frontendType::squareFromString(square) };
							if (sq.isValid())
							{
								eng.outputStream() << frontend::playerToString(p) << " " << frontend::pieceToString(board::pawn) << ": " << frontend::objectiveToString(evaluator::material(p, board::pawn, sq)) << std::endl;
								eng.outputStream() << frontend::playerToString(p) << " " << frontend::pieceToString(board::knight) << ": " << frontend::objectiveToString(evaluator::material(p, board::knight, sq)) << std::endl;
								eng.outputStream() << frontend::playerToString(p) << " " << frontend::pieceToString(board::bishop) << ": " << frontend::objectiveToString(evaluator::material(p, board::bishop, sq)) << std::endl;
								eng.outputStream() << frontend::playerToString(p) << " " << frontend::pieceToString(board::rook) << ": " << frontend::objectiveToString(evaluator::material(p, board::rook, sq)) << std::endl;
								eng.outputStream() << frontend::playerToString(p) << " " << frontend::pieceToString(board::queen) << ": " << frontend::objectiveToString(evaluator::material(p, board::queen, sq)) << std::endl;
								eng.outputStream() << frontend::playerToString(p) << " " << frontend::pieceToString(board::king) << ": " << frontend::objectiveToString(evaluator::material(p, board::king, sq)) << std::endl;
							}
							else
								eng.outputStream() << "invalid square: " << square << std::endl;
						}
						else
							eng.outputStream() << "invalid player: " << player << std::endl;
					}
					else
						eng.outputStream() << "invalid table: " << table << std::endl;

					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugScore : public commandType
		{
		private:
		protected:
			virtual bool onProcess(engineType& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-score")
				{
					eng.outputStream() << std::endl;
					std::string table;
					std::string remainder2;
					parser::parseToken(remainder, table, remainder2);
					if (table == "material" || table == "mat")
					{
						std::string player;
						std::string remainder3;
						parser::parseToken(remainder2, player, remainder3);
						playerType p{ playerType::invalid };
						if (player == "white" || player == "w" || player == "+" || player == "0")
							p = boardType::whitePlayer;
						else if (player == "black" || player == "b" || player == "-" || player == "1")
							p = boardType::blackPlayer;
						if (p.isValid())
						{
							std::string piece;
							std::string remainder4;
							parser::parseToken(remainder3, piece, remainder4);
							pieceType pc{ frontendType::pieceFromString(piece) };
							if (pc.isValid())
							{
								eng.outputStream() << frontend::playerToString(p) << " " << frontend::pieceToString(pc) << ": " << std::endl;
								for (typename boardType::rank rank = 7; rank >= 0; rank--)
								{
									for (const auto file : boardType::file::range)
									{
										const squareType sq{ boardType::fromRankFile(rank,file) };
										eng.outputStream() << std::setw(10) << frontend::objectiveToString(evaluator::material(p, pc, sq)) << " ";
									}
									eng.outputStream() << std::endl;
								}
								eng.outputStream() << std::endl;
							}
							else
								eng.outputStream() << "invalid piece: " << piece << std::endl;
						}
						else
							eng.outputStream() << "invalid player: " << player << std::endl;
					}
					else
						eng.outputStream() << "invalid table: " << table << std::endl;

					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugMagic : public commandType
		{
		private:
		protected:
			virtual bool onProcess(engineType& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-magic")
				{
					eng.outputStream() << std::endl;
					std::string table;
					std::string remainder2;
					parser::parseToken(remainder, table, remainder2);
					if (table == "slider" || table == "s")
					{
#if !(defined(PYGMALION_CPU_BMI2)&&defined(PYGMALION_CPU_X64))
						eng.outputStream() << "refreshing slider magics..." << std::endl;
						for (const auto sq : squareType::range)
						{
							movegen::tables().magic(false, sq) = slidermagic(slidermagicinfo(sq, false));
							movegen::tables().magic(true, sq) = slidermagic(slidermagicinfo(sq, true));
						}
						eng.outputStream() << "...done." << std::endl;
						eng.outputStream() << std::endl;
						eng.outputStream() << "slidermagic m_SliderMagics[2][64] " << std::endl;
						eng.outputStream() << "{" << std::endl;
						eng.outputStream() << "    {" << std::endl;
						for (const auto sq : squareType::range)
							eng.outputStream() << "        slidermagic(slidermagicinfo(" << static_cast<int>(sq) << ", false), " << parser::toString(movegen::tables().magic(false, sq).factor()) << ")" << (sq == 63 ? " " : ",") << std::endl;
						eng.outputStream() << "    }," << std::endl;
						eng.outputStream() << "    {" << std::endl;
						for (const auto sq : squareType::range)
							eng.outputStream() << "        slidermagic(slidermagicinfo(" << static_cast<int>(sq) << ", true), " << parser::toString(movegen::tables().magic(true, sq).factor()) << ")" << (sq == 63 ? " " : ",") << std::endl;
						eng.outputStream() << "    }" << std::endl;
						eng.outputStream() << "};" << std::endl;
#else
						eng.outputStream() << "(no magics used)" << std::endl;
#endif
					}
					else
						eng.outputStream() << "invalid table: " << table << std::endl;

					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
	public:
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::engine<pygmalion::chess::frontend>(input, output)
		{
			addCommand<command_debugTable>();
			addCommand<command_debugScore>();
			addCommand<command_debugMagic>();
		}

	};
}