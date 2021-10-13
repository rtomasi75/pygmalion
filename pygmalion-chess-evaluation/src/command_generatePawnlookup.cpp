#include <pygmalion-chess-evaluation.h>
namespace pygmalion::chess::evaluation
{
	bool command_generatePawnLookup::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		using positionType = pawnlookupPosition<descriptorDynamics>;
		using positionList = list<positionType, 9>;
		if (token == "generate-pawnlookup")
		{
			if (remainder == "")
				remainder = "pawnstructure.data";
			std::ofstream generatedFile(remainder);
			if (!generatedFile.is_open())
			{
				this->output() << "ERROR: failed to open file \"" << remainder << "\"" << std::endl;
				this->output() << std::endl;
				return true;
			}
			this->output() << std::endl;
			this->output() << "starting pawn-lookup generation..." << std::endl;
			constexpr const std::uint32_t countPositions{ 7 * 7 * 7 * 7 * 7 * 7 * 2 };
			this->output() << "  initializing " << countPositions << " potential positions...";
			positionType* pPositions = new positionType[countPositions];
			positionType* pNewPositions = new positionType[countPositions];
			std::uint32_t illegals{ 0 };
			std::uint32_t whiteWins{ 0 };
			std::uint32_t blackWins{ 0 };
			std::uint32_t draws{ 0 };
			std::uint32_t processed{ 0 };
			std::uint32_t oldProcessed{ processed };
			for (const auto movingPlayer : playerType::range)
			{
				for (int rankW1 = -1; rankW1 < 6; rankW1++)
				{
					for (int rankW2 = -1; rankW2 < 6; rankW2++)
					{
						for (int rankW3 = -1; rankW3 < 6; rankW3++)
						{
							for (int rankB1 = -1; rankB1 < 6; rankB1++)
							{
								for (int rankB2 = -1; rankB2 < 6; rankB2++)
								{
									for (int rankB3 = -1; rankB3 < 6; rankB3++)
									{
										const size_t index{ static_cast<size_t>(movingPlayer) + 2 * ((rankW1 + 1) + 7 * ((rankW2 + 1) + 7 * ((rankW3 + 1) + 7 * ((rankB1 + 1) + 7 * ((rankB2 + 1) + 7 * (rankB3 + 1)))))) };
										pPositions[index].isSolved() = false;
										pPositions[index].whitePawns() = squaresType::none();
										pPositions[index].blackPawns() = squaresType::none();
										pPositions[index].movingSide() = movingPlayer;
										if (rankW1 >= 0)
										{
											const rankType rank{ static_cast<rankType>(rankW1 + 1) };
											const fileType file{ fileB };
											const squareType square{ rank & file };
											pPositions[index].whitePawns()[square] = true;
										}
										if (rankW2 >= 0)
										{
											const rankType rank{ static_cast<rankType>(rankW2 + 1) };
											const fileType file{ fileC };
											const squareType square{ rank & file };
											pPositions[index].whitePawns()[square] = true;
										}
										if (rankW3 >= 0)
										{
											const rankType rank{ static_cast<rankType>(rankW3 + 1) };
											const fileType file{ fileD };
											const squareType square{ rank & file };
											pPositions[index].whitePawns()[square] = true;
										}
										if (rankB1 >= 0)
										{
											const rankType rank{ static_cast<rankType>(rankB1 + 1) };
											const fileType file{ fileB };
											const squareType square{ rank & file };
											pPositions[index].blackPawns()[square] = true;
										}
										if (rankB2 >= 0)
										{
											const rankType rank{ static_cast<rankType>(rankB2 + 1) };
											const fileType file{ fileC };
											const squareType square{ rank & file };
											pPositions[index].blackPawns()[square] = true;
										}
										if (rankB3 >= 0)
										{
											const rankType rank{ static_cast<rankType>(rankB3 + 1) };
											const fileType file{ fileD };
											const squareType square{ rank & file };
											pPositions[index].blackPawns()[square] = true;
										}
										if (pPositions[index].whitePawns() & pPositions[index].blackPawns())
										{
											pPositions[index].isLegal() = false;
											pPositions[index].isSolved() = true;
											illegals++;
											processed++;
										}
										else
										{
											pPositions[index].isLegal() = true;
											if (pPositions[index].whitePawns() | pPositions[index].blackPawns())
											{
												if (movingPlayer == whitePlayer)
												{
													if (pPositions[index].whitePawns() & rank7)
													{
														pPositions[index].outcome() = 1;
														pPositions[index].isSolved() = true;
														whiteWins++;
														processed++;
													}
												}
												if (movingPlayer == blackPlayer)
												{
													if (pPositions[index].blackPawns() & rank2)
													{
														pPositions[index].outcome() = -1;
														pPositions[index].isSolved() = true;
														blackWins++;
														processed++;
													}
												}
											}
											else
											{
												pPositions[index].outcome() = 0;
												pPositions[index].isSolved() = true;
												draws++;
												processed++;
											}
										}
										PYGMALION_ASSERT(processed < countPositions);
									}
								}
							}
						}
					}
				}
			}
			this->output() << "done:" << std::endl;
			this->output() << "    " << processed << " positions solved (" << ((100 * processed) / countPositions) << "%)." << std::endl;
			this->output() << "    " << illegals << " positions illegal (" << ((100 * illegals) / countPositions) << "%)." << std::endl;
			this->output() << "    " << whiteWins << " white wins (" << ((100 * whiteWins) / countPositions) << "%)." << std::endl;
			this->output() << "    " << blackWins << " black wins (" << ((100 * blackWins) / countPositions) << "%)." << std::endl;
			this->output() << "    " << draws << " draws (" << ((100 * draws) / countPositions) << "%)." << std::endl;
			std::array<positionType, 10> successors;
			size_t successorCount;
			this->output() << std::endl;
			this->output() << "  duplicating positions...";
			for (std::uint32_t index = 0; index < countPositions; index++)
				pNewPositions[index] = pPositions[index];
			this->output() << "done." << std::endl;
			std::int8_t distance = 1;
			while ((processed < countPositions) && (oldProcessed != processed))
			{
				distance++;
				oldProcessed = processed;
				this->output() << std::endl;
				this->output() << "  performing sanity checks...";
				for (std::uint32_t index = 0; index < countPositions; index++)
				{
					if ((pPositions[index].whitePawns() & rank1).count() > 0)
					{
						this->output() << "failed (white pawns on rank 1)." << std::endl;
						dumpSquares(pPositions[index].whitePawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].whitePawns() & rank8).count() > 0)
					{
						this->output() << "failed (white pawns on rank 8)." << std::endl;
						dumpSquares(pNewPositions[index].whitePawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].blackPawns() & rank1).count() > 0)
					{
						this->output() << "failed (black pawns on rank 1)." << std::endl;
						dumpSquares(pNewPositions[index].blackPawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].blackPawns() & rank8).count() > 0)
					{
						this->output() << "failed (black pawns on rank 8)." << std::endl;
						dumpSquares(pPositions[index].blackPawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].whitePawns() & fileA).count() > 0)
					{
						this->output() << "failed (white pawns on file A)." << std::endl;
						dumpSquares(pPositions[index].whitePawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].whitePawns() & fileB).count() > 1)
					{
						this->output() << "failed (more than 1 white pawn on file B)." << std::endl;
						dumpSquares(pPositions[index].whitePawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].whitePawns() & fileC).count() > 1)
					{
						this->output() << "failed (more than 1 white pawn on file C)." << std::endl;
						dumpSquares(pPositions[index].whitePawns());
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].whitePawns() & fileD).count() > 1)
					{
						this->output() << "failed (more than 1 white pawn on file D)." << std::endl;
						dumpSquares(pPositions[index].whitePawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].whitePawns() & fileE).count() > 0)
					{
						this->output() << "failed (white pawns on file E)." << std::endl;
						dumpSquares(pPositions[index].whitePawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].whitePawns() & fileF).count() > 0)
					{
						this->output() << "failed (white pawns on file F)." << std::endl;
						dumpSquares(pPositions[index].whitePawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].whitePawns() & fileG).count() > 0)
					{
						this->output() << "failed (white pawns on file G)." << std::endl;
						dumpSquares(pPositions[index].whitePawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].whitePawns() & fileH).count() > 0)
					{
						this->output() << "failed (white pawns on file H)." << std::endl;
						dumpSquares(pPositions[index].whitePawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].blackPawns() & fileA).count() > 0)
					{
						this->output() << "failed (black pawns on file A)." << std::endl;
						dumpSquares(pPositions[index].blackPawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].blackPawns() & fileB).count() > 1)
					{
						this->output() << "failed (more than 1 black pawn on file B)." << std::endl;
						dumpSquares(pPositions[index].blackPawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].blackPawns() & fileC).count() > 1)
					{
						this->output() << "failed (more than 1 black pawn on file C)." << std::endl;
						dumpSquares(pPositions[index].blackPawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].blackPawns() & fileD).count() > 1)
					{
						this->output() << "failed (more than 1 black pawn on file D)." << std::endl;
						dumpSquares(pPositions[index].blackPawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].blackPawns() & fileE).count() > 0)
					{
						this->output() << "failed (black pawns on file E)." << std::endl;
						dumpSquares(pPositions[index].blackPawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].blackPawns() & fileF).count() > 0)
					{
						this->output() << "failed (black pawns on file F)." << std::endl;
						dumpSquares(pPositions[index].blackPawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].blackPawns() & fileG).count() > 0)
					{
						this->output() << "failed (black pawns on file G)." << std::endl;
						dumpSquares(pPositions[index].blackPawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
					if ((pPositions[index].blackPawns() & fileH).count() > 0)
					{
						this->output() << "failed (black pawns on file H)." << std::endl;
						dumpSquares(pPositions[index].blackPawns());
						this->output() << std::endl;
						generatedFile.close();
						return true;
					}
				}
				this->output() << "done." << std::endl;
				for (std::uint32_t index = 0; index < countPositions; index++)
				{
					if (!pPositions[index].isSolved())
					{
						pPositions[index].generateSuccessors(successors, successorCount);
						if (successorCount == 0)
						{
							pNewPositions[index].outcome() = 0;
							pNewPositions[index].isSolved() = true;
							draws++;
							processed++;
						}
						else
						{
							int bestIndex = -1;
							int bestOutcome = (pPositions[index].movingSide() == whitePlayer) ? INT_MAX : (-INT_MAX);
							for (int i = 0; i < successorCount; i++)
							{
								bool bFound = false;
								std::uint32_t A_white;
								std::uint32_t B_white;
								std::uint32_t C_white;
								std::uint32_t A_black;
								std::uint32_t B_black;
								std::uint32_t C_black;
								std::uint32_t side;
								squareType sq;
								if (successors[i].whitePawns() & fileB)
								{
									sq = (successors[i].whitePawns() & fileB).last();
									A_white = static_cast<std::int8_t>(sq.rank());
								}
								else
									A_white = 0;
								if (successors[i].whitePawns() & fileC)
								{
									sq = (successors[i].whitePawns() & fileC).last();
									B_white = static_cast<std::int8_t>(sq.rank());
								}
								else
									B_white = 0;
								if (successors[i].whitePawns() & fileD)
								{
									sq = (successors[i].whitePawns() & fileD).last();
									C_white = static_cast<std::int8_t>(sq.rank());
								}
								else
									C_white = 0;
								if (successors[i].blackPawns() & fileB)
								{
									sq = (successors[i].blackPawns() & fileB).first();
									A_black = static_cast<std::int8_t>(sq.rank());
								}
								else
									A_black = 0;
								if (successors[i].blackPawns() & fileC)
								{
									sq = (successors[i].blackPawns() & fileC).first();
									B_black = static_cast<std::int8_t>(sq.rank());
								}
								else
									B_black = 0;
								if (successors[i].blackPawns() & fileD)
								{
									sq = (successors[i].blackPawns() & fileD).first();
									C_black = static_cast<std::int8_t>(sq.rank());
								}
								else
									C_black = 0;
								side = static_cast<std::int8_t>(successors[i].movingSide());
								const std::uint32_t index2{ static_cast<std::uint32_t>(side + 2 * (A_white + 7 * (B_white + 7 * (C_white + 7 * (A_black + 7 * (B_black + 7 * C_black)))))) };
								if (pPositions[index2].isSolved())
								{
									if (pPositions[index].movingSide() == whitePlayer)
									{
										if (pPositions[index2].outcome() < bestOutcome)
										{
											bestIndex = index2;
											bestOutcome = pPositions[index2].outcome();
										}
									}
									else
									{
										if (pPositions[index2].outcome() > bestOutcome)
										{
											bestIndex = index2;
											bestOutcome = pPositions[index2].outcome();
										}
									}
								}
							}
							if (bestIndex >= 0)
							{
								pNewPositions[index].isSolved() = true;
								processed++;
								if (pPositions[bestIndex].outcome() == 0)
								{
									pNewPositions[index].outcome() = 0;
									draws++;
								}
								else
								{
									if (pPositions[bestIndex].outcome() > 0)
									{
										pNewPositions[index].outcome() = distance;
										whiteWins++;
									}
									else
									{
										pNewPositions[index].outcome() = -distance;
										blackWins++;
									}
								}
							}
						}
					}
				}
				this->output() << std::endl;
				this->output() << "    " << processed << " positions solved (" << ((100 * processed) / countPositions) << "%)." << std::endl;
				this->output() << "    " << illegals << " positions illegal (" << ((100 * illegals) / countPositions) << "%)." << std::endl;
				this->output() << "    " << whiteWins << " white wins (" << ((100 * whiteWins) / countPositions) << "%)." << std::endl;
				this->output() << "    " << blackWins << " black wins (" << ((100 * blackWins) / countPositions) << "%)." << std::endl;
				this->output() << "    " << draws << " draws (" << ((100 * draws) / countPositions) << "%)." << std::endl;
				this->output() << std::endl;
				this->output() << "  copying positions...";
				for (std::uint32_t index = 0; index < countPositions; index++)
					pPositions[index] = pNewPositions[index];
				this->output() << "done." << std::endl;
			}
			delete[] pNewPositions;
			this->output() << "  declaring remaining " << (countPositions - processed) << " positions as draws...";
			for (std::uint32_t index = 0; index < countPositions; index++)
			{
				if (!pPositions[index].isSolved())
				{
					pPositions[index].isSolved() = true;
					pPositions[index].outcome() = 0;
					draws++;
					processed++;
				}
			}
			this->output() << "done." << std::endl;
			this->output() << "...done." << std::endl;
			this->output() << std::endl;
			this->output() << processed << " positions solved (" << ((100 * processed) / countPositions) << "%)." << std::endl;
			this->output() << illegals << " positions illegal (" << ((100 * illegals) / countPositions) << "%)." << std::endl;
			this->output() << whiteWins << " white wins (" << ((100 * whiteWins) / countPositions) << "%)." << std::endl;
			this->output() << blackWins << " black wins (" << ((100 * blackWins) / countPositions) << "%)." << std::endl;
			this->output() << draws << " draws (" << ((100 * draws) / countPositions) << "%)." << std::endl;
			this->output() << std::endl;
			this->output() << "generating output file \"" << remainder << "\"...";
			signed char* pData = new signed char[countPositions];
			for (std::uint32_t index = 0; index < countPositions; index++)
			{
				pData[index] = static_cast<signed char>(pPositions[index].outcome());
			}
			delete[] pPositions;
			generatedFile.write(reinterpret_cast<char*>(pData), countPositions);
			generatedFile.close();
			delete[] pData;
			this->output() << "done." << std::endl;
			return true;
		}
		else
			return false;
	}
}