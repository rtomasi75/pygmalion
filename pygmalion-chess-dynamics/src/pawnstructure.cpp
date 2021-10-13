#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess
{
	pawnlookup::pawnlookup() noexcept
	{
		m_pData = new signed char[countPositions];
		loadData();
	}

	pawnlookup::~pawnlookup() noexcept
	{
		delete[] m_pData;
	}

	void pawnlookup::loadData() noexcept
	{
		std::ifstream dataFile("pawnstructure.data");
		if (dataFile.is_open())
		{
			dataFile.read(reinterpret_cast<char*>(m_pData), countPositions);
			dataFile.close();
		}
		else
		{
			using positionType = pawnlookupPosition<descriptorDynamics>;
			using positionList = list<positionType, 9>;
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
									}
								}
							}
						}
					}
				}
			}
			std::array<positionType, 10> successors;
			size_t successorCount{ 0 };
			for (std::uint32_t index = 0; index < countPositions; index++)
				pNewPositions[index] = pPositions[index];
			std::int8_t distance = 1;
			while ((processed < countPositions) && (oldProcessed != processed))
			{
				distance++;
				oldProcessed = processed;
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
								std::uint32_t A_white{ 0 };
								std::uint32_t B_white{ 0 };
								std::uint32_t C_white{ 0 };
								std::uint32_t A_black{ 0 };
								std::uint32_t B_black{ 0 };
								std::uint32_t C_black{ 0 };
								std::uint32_t side{ 0 };
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
				for (std::uint32_t index = 0; index < countPositions; index++)
					pPositions[index] = pNewPositions[index];
			}
			delete[] pNewPositions;
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
			for (std::uint32_t index = 0; index < countPositions; index++)
			{
				m_pData[index] = static_cast<signed char>(pPositions[index].outcome());
			}
			delete[] pPositions;
			std::ofstream generatedFile("pawnstructure.data");
			generatedFile.write(reinterpret_cast<char*>(m_pData), countPositions);
			generatedFile.close();
		}
	}

	const pawnlookup pawnstructure::m_LookUp{ pawnlookup() };
}