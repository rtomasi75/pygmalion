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
						squareType sq{ frontendType::squareFromString(square) };
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
							p = frontendType::whitePlayer;
						else if (player == "black" || player == "b" || player == "-" || player == "1")
							p = frontendType::blackPlayer;
						if (p.isValid())
						{
							std::string square;
							std::string remainder4;
							parser::parseToken(remainder3, square, remainder4);
							squareType sq{ frontendType::squareFromString(square) };
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
							p = frontendType::whitePlayer;
						else if (player == "black" || player == "b" || player == "-" || player == "1")
							p = frontendType::blackPlayer;
						if (p.isValid())
						{
							std::string square;
							std::string remainder4;
							parser::parseToken(remainder3, square, remainder4);
							squareType sq{ frontendType::squareFromString(square) };
							if (sq.isValid())
							{
								eng.outputStream() << frontendType::playerToString(p) << " " << frontendType::pieceToString(frontendType::pawn) << ": " << frontendType::objectiveToString(evaluationType::material(p, frontendType::pawn, sq)) << std::endl;
								eng.outputStream() << frontendType::playerToString(p) << " " << frontendType::pieceToString(frontendType::knight) << ": " << frontendType::objectiveToString(evaluationType::material(p, frontendType::knight, sq)) << std::endl;
								eng.outputStream() << frontendType::playerToString(p) << " " << frontendType::pieceToString(frontendType::bishop) << ": " << frontendType::objectiveToString(evaluationType::material(p, frontendType::bishop, sq)) << std::endl;
								eng.outputStream() << frontendType::playerToString(p) << " " << frontendType::pieceToString(frontendType::rook) << ": " << frontendType::objectiveToString(evaluationType::material(p, frontendType::rook, sq)) << std::endl;
								eng.outputStream() << frontendType::playerToString(p) << " " << frontendType::pieceToString(frontendType::queen) << ": " << frontendType::objectiveToString(evaluationType::material(p, frontendType::queen, sq)) << std::endl;
								eng.outputStream() << frontendType::playerToString(p) << " " << frontendType::pieceToString(frontendType::king) << ": " << frontendType::objectiveToString(evaluationType::material(p, frontendType::king, sq)) << std::endl;
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
							p = frontendType::whitePlayer;
						else if (player == "black" || player == "b" || player == "-" || player == "1")
							p = frontendType::blackPlayer;
						if (p.isValid())
						{
							std::string piece;
							std::string remainder4;
							parser::parseToken(remainder3, piece, remainder4);
							pieceType pc{ frontendType::pieceFromString(piece) };
							if (pc.isValid())
							{
								eng.outputStream() << frontendType::playerToString(p) << " " << frontendType::pieceToString(pc) << ": " << std::endl;
								for (typename boardType::rankType rank = 7; rank >= 0; rank--)
								{
									for (const auto file : boardType::fileType::range)
									{
										const squareType sq{ squareType::fromRankFile(rank,file) };
										eng.outputStream() << std::setw(10) << frontendType::objectiveToString(evaluationType::material(p, pc, sq)) << " ";
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