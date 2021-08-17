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
						squareType sq{ frontType::squareFromString(square) };
						if (sq.isValid())
						{
							frontend::dumpSquares(generatorType::movegenTable().kingMoveMap(sq), eng.outputStream());
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
						squareType sq{ frontType::squareFromString(square) };
						if (sq.isValid())
						{
							frontend::dumpSquares(generatorType::movegenTable().knightMoveMap(sq), eng.outputStream());
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
							p = frontType::whitePlayer;
						else if (player == "black" || player == "b" || player == "-" || player == "1")
							p = frontType::blackPlayer;
						if (p.isValid())
						{
							std::string square;
							std::string remainder4;
							parser::parseToken(remainder3, square, remainder4);
							squareType sq{ frontType::squareFromString(square) };
							if (sq.isValid())
							{
								frontend::dumpSquares(generatorType::movegenTable().pawnMoveMap(sq, p), eng.outputStream());
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
							p = frontType::whitePlayer;
						else if (player == "black" || player == "b" || player == "-" || player == "1")
							p = frontType::blackPlayer;
						if (p.isValid())
						{
							std::string square;
							std::string remainder4;
							parser::parseToken(remainder3, square, remainder4);
							squareType sq{ frontType::squareFromString(square) };
							if (sq.isValid())
							{
								eng.outputStream() << frontType::playerToString(p) << " " << frontType::pieceToString(frontType::pawn) << ": " << frontType::objectiveToString(evaluationType::material(p, frontType::pawn, sq)) << std::endl;
								eng.outputStream() << frontType::playerToString(p) << " " << frontType::pieceToString(frontType::knight) << ": " << frontType::objectiveToString(evaluationType::material(p, frontType::knight, sq)) << std::endl;
								eng.outputStream() << frontType::playerToString(p) << " " << frontType::pieceToString(frontType::bishop) << ": " << frontType::objectiveToString(evaluationType::material(p, frontType::bishop, sq)) << std::endl;
								eng.outputStream() << frontType::playerToString(p) << " " << frontType::pieceToString(frontType::rook) << ": " << frontType::objectiveToString(evaluationType::material(p, frontType::rook, sq)) << std::endl;
								eng.outputStream() << frontType::playerToString(p) << " " << frontType::pieceToString(frontType::queen) << ": " << frontType::objectiveToString(evaluationType::material(p, frontType::queen, sq)) << std::endl;
								eng.outputStream() << frontType::playerToString(p) << " " << frontType::pieceToString(frontType::king) << ": " << frontType::objectiveToString(evaluationType::material(p, frontType::king, sq)) << std::endl;
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
							p = frontType::whitePlayer;
						else if (player == "black" || player == "b" || player == "-" || player == "1")
							p = frontType::blackPlayer;
						if (p.isValid())
						{
							std::string piece;
							std::string remainder4;
							parser::parseToken(remainder3, piece, remainder4);
							pieceType pc{ frontType::pieceFromString(piece) };
							if (pc.isValid())
							{
								eng.outputStream() << frontType::playerToString(p) << " " << frontType::pieceToString(pc) << ": " << std::endl;
								for (typename boardType::rankType rank = 7; rank >= 0; rank--)
								{
									for (const auto file : boardType::fileType::range)
									{
										const squareType sq{ squareType::fromRankFile(rank,file) };
										eng.outputStream() << std::setw(10) << frontType::objectiveToString(evaluationType::material(p, pc, sq)) << " ";
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
						eng.outputStream() << "computing slider magics..." << std::endl;
						eng.outputStream() << std::endl;
						eng.outputStream() << "slidermagic m_SliderMagics[2][64] " << std::endl;
						eng.outputStream() << "{" << std::endl;
						eng.outputStream() << "    {" << std::endl;
						for (const auto sq : squareType::range)
						{
							slidermagic<descriptorGenerator> sm(slidermagicinfo<descriptorGenerator>(sq, false));
							auto premask{ sm.magic().premask() };
							auto factor{ premask };
							int bits;
							sm.magic().find(premask, factor, bits);
							eng.outputStream() << "static slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(" << static_cast<int>(static_cast<squareType::baseType>(sq)) << ", false), " << premask << ", " << factor << ", " << bits << ")" << ((sq == (squareType::countValues - 1)) ? " " : ",") << std::endl;
						}
						eng.outputStream() << "    }," << std::endl;
						eng.outputStream() << "    {" << std::endl;
						for (const auto sq : squareType::range)
						{
							slidermagic<descriptorGenerator> sm(slidermagicinfo<descriptorGenerator>(sq, true));
							auto premask{ sm.magic().premask() };
							auto factor{ premask };
							int bits;
							sm.magic().find(premask, factor, bits);
							eng.outputStream() << "static slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(" << static_cast<int>(static_cast<squareType::baseType>(sq)) << ", true), " << premask << ", " << factor << ", " << bits << ")" << ((sq == (squareType::countValues - 1)) ? " " : ",") << std::endl;
						}
						eng.outputStream() << "    }" << std::endl;
						eng.outputStream() << "};" << std::endl;
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