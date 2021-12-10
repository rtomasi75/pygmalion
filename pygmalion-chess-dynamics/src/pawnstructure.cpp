#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess
{
	pawnlookup::pawnlookup() noexcept
	{
		m_pData = new std::int8_t[countPositions];
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
			std::uint32_t version;
			dataFile.read(reinterpret_cast<char*>(&version), sizeof(std::uint32_t));
			if (version == fileVersion)
			{
/*				dataFile.read(reinterpret_cast<char*>(m_MaxQuiet1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinQuiet1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxQuiet2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinQuiet2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxQuiet3.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinQuiet3.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxCapture1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinCapture1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxCapture2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinCapture2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxCapture3.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinCapture3.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxDeath1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinDeath1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxDeath2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinDeath2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxDeath3.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinDeath3.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxPromotion1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinPromotion1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxPromotion2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinPromotion2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxPromotion3.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinPromotion3.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxCaptureOther1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinCaptureOther1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxCaptureOther2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinCaptureOther2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxCaptureOther3.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinCaptureOther3.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxBirth1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinBirth1.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxBirth2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinBirth2.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MaxBirth3.data()), countPlayers * sizeof(std::int8_t));
				dataFile.read(reinterpret_cast<char*>(m_MinBirth3.data()), countPlayers * sizeof(std::int8_t));*/
				dataFile.read(reinterpret_cast<char*>(m_pData), countPositions * sizeof(std::int8_t));
				dataFile.close();
				return;
			}
		}
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
		std::array<positionType, positionType::countMaxSuccessors> successors;
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
							const std::uint32_t index2{ successors[i].computeIndex() };
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
/*		m_MaxQuiet1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinQuiet1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxQuiet2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinQuiet2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxQuiet3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinQuiet3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxCapture1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinCapture1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxCapture2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinCapture2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxCapture3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinCapture3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxCaptureOther1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinCaptureOther1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxCaptureOther2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinCaptureOther2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxCaptureOther3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinCaptureOther3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxDeath1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinDeath1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxDeath2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinDeath2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxDeath3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinDeath3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxPromotion1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinPromotion1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxPromotion2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinPromotion2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxPromotion3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinPromotion3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxBirth1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinBirth1 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxBirth2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinBirth2 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		m_MaxBirth3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::min());
		m_MinBirth3 = arrayhelper::make<countPlayers, std::int8_t>(std::numeric_limits<std::int8_t>::max());
		for (std::uint32_t index = 0; index < countPositions; index++)
		{
			for (const auto side : playerType::range)
			{
				if (pPositions[index].isLegal())
				{
					pPositions[index].generateQuiet1Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxQuiet1[side] = std::max(delta, m_MaxQuiet1[side]);
							m_MinQuiet1[side] = std::min(delta, m_MinQuiet1[side]);
						}
					}
					pPositions[index].generateQuiet2Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxQuiet2[side] = std::max(delta, m_MaxQuiet2[side]);
							m_MinQuiet2[side] = std::min(delta, m_MinQuiet2[side]);
						}
					}
					pPositions[index].generateQuiet3Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxQuiet3[side] = std::max(delta, m_MaxQuiet3[side]);
							m_MinQuiet3[side] = std::min(delta, m_MinQuiet3[side]);
						}
					}
					pPositions[index].generateCapture1Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxCapture1[side] = std::max(delta, m_MaxCapture1[side]);
							m_MinCapture1[side] = std::min(delta, m_MinCapture1[side]);
						}
					}
					pPositions[index].generateCapture2Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxCapture2[side] = std::max(delta, m_MaxCapture2[side]);
							m_MinCapture2[side] = std::min(delta, m_MinCapture2[side]);
						}
					}
					pPositions[index].generateCapture3Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxCapture3[side] = std::max(delta, m_MaxCapture3[side]);
							m_MinCapture3[side] = std::min(delta, m_MinCapture3[side]);
						}
					}
					pPositions[index].generateCaptureOther1Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxCaptureOther1[side] = std::max(delta, m_MaxCaptureOther1[side]);
							m_MinCaptureOther1[side] = std::min(delta, m_MinCaptureOther1[side]);
						}
					}
					pPositions[index].generateCaptureOther2Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxCaptureOther2[side] = std::max(delta, m_MaxCaptureOther2[side]);
							m_MinCaptureOther2[side] = std::min(delta, m_MinCaptureOther2[side]);
						}
					}
					pPositions[index].generateCaptureOther3Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxCaptureOther3[side] = std::max(delta, m_MaxCaptureOther3[side]);
							m_MinCaptureOther3[side] = std::min(delta, m_MinCaptureOther3[side]);
						}
					}
					pPositions[index].generateDeath1Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxDeath1[side] = std::max(delta, m_MaxDeath1[side]);
							m_MinDeath1[side] = std::min(delta, m_MinDeath1[side]);
						}
					}
					pPositions[index].generateDeath2Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxDeath2[side] = std::max(delta, m_MaxDeath2[side]);
							m_MinDeath2[side] = std::min(delta, m_MinDeath2[side]);
						}
					}
					pPositions[index].generateDeath3Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxDeath2[side] = std::max(delta, m_MaxDeath3[side]);
							m_MinDeath2[side] = std::min(delta, m_MinDeath3[side]);
						}
					}
					pPositions[index].generatePromotion1Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxPromotion1[side] = std::max(delta, m_MaxPromotion1[side]);
							m_MinPromotion1[side] = std::min(delta, m_MinPromotion1[side]);
						}
					}
					pPositions[index].generatePromotion2Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxPromotion2[side] = std::max(delta, m_MaxPromotion2[side]);
							m_MinPromotion2[side] = std::min(delta, m_MinPromotion2[side]);
						}
					}
					pPositions[index].generatePromotion3Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxPromotion3[side] = std::max(delta, m_MaxPromotion3[side]);
							m_MinPromotion3[side] = std::min(delta, m_MinPromotion3[side]);
						}
					}
					pPositions[index].generateBirth1Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxBirth1[side] = std::max(delta, m_MaxBirth1[side]);
							m_MinBirth1[side] = std::min(delta, m_MinBirth1[side]);
						}
					}
					pPositions[index].generateBirth2Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxBirth2[side] = std::max(delta, m_MaxBirth2[side]);
							m_MinBirth2[side] = std::min(delta, m_MinBirth2[side]);
						}
					}
					pPositions[index].generateBirth3Successors(side, successors, successorCount);
					for (size_t i = 0; i < successorCount; i++)
					{
						const std::uint32_t index2{ successors[i].computeIndex() };
						if ((index2 < countPositions) && pPositions[index2].isLegal())
						{
							std::int8_t delta{ 0 };
							delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index2].outcome());
							successors[i].movingSide() = successors[i].movingSide().next();
							const std::uint32_t index3{ successors[i].computeIndex() };
							if ((index3 < countPositions) && pPositions[index3].isLegal())
								delta += static_cast<std::int8_t>(pPositions[index].outcome() - pPositions[index3].outcome());
							m_MaxBirth3[side] = std::max(delta, m_MaxBirth3[side]);
							m_MinBirth3[side] = std::min(delta, m_MinBirth3[side]);
						}
					}
				}
			}
		}*/
		for (std::uint32_t index = 0; index < countPositions; index++)
		{
			m_pData[index] = static_cast<std::int8_t>(pPositions[index].outcome());
		}
		delete[] pPositions;
		std::ofstream generatedFile("pawnstructure.data");
		if (generatedFile.is_open())
		{
			generatedFile.write(reinterpret_cast<const char*>(&fileVersion), sizeof(std::uint32_t));
	/*		generatedFile.write(reinterpret_cast<const char*>(m_MaxQuiet1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinQuiet1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxQuiet2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinQuiet2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxQuiet3.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinQuiet3.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxCapture1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinCapture1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxCapture2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinCapture2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxCapture3.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinCapture3.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxDeath1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinDeath1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxDeath2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinDeath2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxDeath3.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinDeath3.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxPromotion1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinPromotion1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxPromotion2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinPromotion2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxPromotion3.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinPromotion3.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxCaptureOther1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinCaptureOther1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxCaptureOther2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinCaptureOther2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxCaptureOther3.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinCaptureOther3.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxBirth1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinBirth1.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxBirth2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinBirth2.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MaxBirth3.data()), countPlayers * sizeof(std::int8_t));
			generatedFile.write(reinterpret_cast<const char*>(m_MinBirth3.data()), countPlayers * sizeof(std::int8_t));*/
			generatedFile.write(reinterpret_cast<const char*>(m_pData), countPositions * sizeof(std::int8_t));
			generatedFile.close();
		}
	}

	const pawnlookup pawnstructure::m_LookUp{ pawnlookup() };
}