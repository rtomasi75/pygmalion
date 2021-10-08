namespace pygmalion::chess
{
	class gametree :
		public pygmalion::gametree<descriptor_search, gametree>
	{
	public:
		using descriptorSearch = descriptor_search;
#include <pygmalion-search/include_search.h>
		template<size_t PLAYER>
		class node :
			public pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>
		{
		public:
			constexpr static inline const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr static inline const playerType otherPlayer{ movingPlayer.next() };
			using parentType = node< static_cast<size_t>(movingPlayer.previous())>;
			using childType = node< static_cast<size_t>(movingPlayer.next())>;
			using stackType = typename generatorType::template stackType<PLAYER>;
			node(const stackType& stack, std::atomic_bool& isRunning, heuristicsType& heuristics, const size_t depth) noexcept :
				pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>(stack, isRunning, heuristics, depth)
			{

			}
			PYGMALION_INLINE static bool futilityPruningEnabled_Implementation(const size_t depthRemaining) noexcept
			{
//				return depthRemaining <= 5;
				return depthRemaining <= 3;
			}
			node(const parentType& parent, const movebitsType moveBits) noexcept :
				pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>(parent, moveBits)
			{
			}
			PYGMALION_INLINE constexpr static depthType nullMoveReduction_Implementation(const size_t depthRemaining) noexcept
			{
				return depthType(2) + depthRemaining / depthType(4);
			}
			PYGMALION_INLINE bool nullMoveAllowed_Implementation() const noexcept
			{
				const squaresType pieces{ this->stack().position().pieceOccupancy(descriptorSearch::knight) | this->stack().position().pieceOccupancy(descriptorSearch::bishop) | this->stack().position().pieceOccupancy(descriptorSearch::rook) | this->stack().position().pieceOccupancy(descriptorSearch::queen) };
				const squaresType playerPieces{ pieces & this->stack().position().playerOccupancy(movingPlayer) };
				return playerPieces;
			}
			PYGMALION_INLINE static scoreType futilityMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				switch (depthRemaining)
				{
				case 0:
				{
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange };
					return positionalValue;
				}
				case 1:
				{
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
					return positionalValue;
				}
				case 2:
				{
					const squaresType ownPawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & stack.position().playerOccupancy(movingPlayer) };
					constexpr const squaresType promotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? descriptorSearch::rank7 : descriptorSearch::rank2 };
					const squaresType promotionPawns{ ownPawns & promotionsMask };
					scoreType promotionValue{ zero };
					if (promotionPawns)
					{
						constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) - static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
						promotionValue += singlePromotionsValue;
					}
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
					bool noCapture{ true };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					if (queens)
					{
						constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) };
						captureValue += queenValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						if (rooks)
						{
							constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::rook, descriptorSearch::whitePlayer)) };
							captureValue += rookValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							if (bishops)
							{
								constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::bishop, descriptorSearch::whitePlayer)) };
								captureValue += bishopValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								if (knights)
								{
									constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::knight, descriptorSearch::whitePlayer)) };
									captureValue += knightValue;
									noCapture = false;
								}
								if (noCapture)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									if (pawns)
									{
										constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
										captureValue += pawnValue;
										noCapture = false;
									}
								}
							}
						}
					}
					return positionalValue + captureValue + promotionValue;
				}
				case 3:
				{
					const squaresType ownPawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & stack.position().playerOccupancy(movingPlayer) };
					constexpr const squaresType promotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? descriptorSearch::rank7 : descriptorSearch::rank2 };
					const squaresType promotionPawns{ ownPawns & promotionsMask };
					scoreType promotionValue{ zero };
					if (promotionPawns)
					{
						constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) - static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
						promotionValue += singlePromotionsValue;
					}
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
					bool noCapture{ true };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					if (queens)
					{
						constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) };
						captureValue += queenValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						if (rooks)
						{
							constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::rook, descriptorSearch::whitePlayer)) };
							captureValue += rookValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							if (bishops)
							{
								constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::bishop, descriptorSearch::whitePlayer)) };
								captureValue += bishopValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								if (knights)
								{
									constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::knight, descriptorSearch::whitePlayer)) };
									captureValue += knightValue;
									noCapture = false;
								}
								if (noCapture)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									if (pawns)
									{
										constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
										captureValue += pawnValue;
										noCapture = false;
									}
								}
							}
						}
					}
					return positionalValue + captureValue + promotionValue;
				}
/*				case 4:
				{
					const squaresType ownPawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & stack.position().playerOccupancy(movingPlayer) };
					constexpr const squaresType promotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? descriptorSearch::rank7 : descriptorSearch::rank2 };
					const squaresType promotionPawns{ ownPawns & promotionsMask };
					size_t countPossiblePromotions{ promotionPawns.count() };
					if (countPossiblePromotions < 2)
					{
						constexpr const squaresType prePromotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? (descriptorSearch::rank7 | descriptorSearch::rank6) : (descriptorSearch::rank2 | descriptorSearch::rank3) };
						const squaresType prePromotionPawns{ ownPawns & prePromotionsMask };
						countPossiblePromotions += static_cast<bool>(prePromotionPawns);
					}
					scoreType promotionValue{ zero };
					if (countPossiblePromotions >= 1)
					{
						constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) - static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
						promotionValue += singlePromotionsValue;
						promotionValue += singlePromotionsValue * (countPossiblePromotions > 1);
					}
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) };
						captureValue += queenValue;
						countCaptures++;
						if (countCaptures >= 2)
							break;
					}
					if (countCaptures < 2)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						for (const auto sq : rooks)
						{
							constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::rook, descriptorSearch::whitePlayer)) };
							captureValue += rookValue;
							countCaptures++;
							if (countCaptures >= 2)
								break;
						}
						if (countCaptures < 2)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							for (const auto sq : bishops)
							{
								constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::bishop, descriptorSearch::whitePlayer)) };
								captureValue += bishopValue;
								countCaptures++;
								if (countCaptures >= 2)
									break;
							}
							if (countCaptures < 2)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								for (const auto sq : knights)
								{
									constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::knight, descriptorSearch::whitePlayer)) };
									captureValue += knightValue;
									countCaptures++;
									if (countCaptures >= 2)
										break;
								}
								if (countCaptures < 2)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									for (const auto sq : pawns)
									{
										constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
										captureValue += pawnValue;
										countCaptures++;
										if (countCaptures >= 2)
											break;
									}
								}
							}
						}
					}
					return positionalValue + captureValue + promotionValue;
				}
				case 5:
				{
					const squaresType ownPawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & stack.position().playerOccupancy(movingPlayer) };
					constexpr const squaresType promotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? descriptorSearch::rank7 : descriptorSearch::rank2 };
					const squaresType promotionPawns{ ownPawns & promotionsMask };
					size_t countPossiblePromotions{ promotionPawns.count() };
					if (countPossiblePromotions < 2)
					{
						constexpr const squaresType prePromotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? (descriptorSearch::rank7 | descriptorSearch::rank6) : (descriptorSearch::rank2 | descriptorSearch::rank3) };
						const squaresType prePromotionPawns{ ownPawns & prePromotionsMask };
						countPossiblePromotions += static_cast<bool>(prePromotionPawns);
					}
					scoreType promotionValue{ zero };
					if (countPossiblePromotions >= 1)
					{
						constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) - static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
						promotionValue += singlePromotionsValue;
						promotionValue += singlePromotionsValue * (countPossiblePromotions > 1);
					}
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) };
						captureValue += queenValue;
						countCaptures++;
						if (countCaptures >= 2)
							break;
					}
					if (countCaptures < 2)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						for (const auto sq : rooks)
						{
							constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::rook, descriptorSearch::whitePlayer)) };
							captureValue += rookValue;
							countCaptures++;
							if (countCaptures >= 2)
								break;
						}
						if (countCaptures < 2)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							for (const auto sq : bishops)
							{
								constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::bishop, descriptorSearch::whitePlayer)) };
								captureValue += bishopValue;
								countCaptures++;
								if (countCaptures >= 2)
									break;
							}
							if (countCaptures < 2)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								for (const auto sq : knights)
								{
									constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::knight, descriptorSearch::whitePlayer)) };
									captureValue += knightValue;
									countCaptures++;
									if (countCaptures >= 2)
										break;
								}
								if (countCaptures < 2)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									for (const auto sq : pawns)
									{
										constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
										captureValue += pawnValue;
										countCaptures++;
										if (countCaptures >= 2)
											break;
									}
								}
							}
						}
					}
					return positionalValue + captureValue + promotionValue;
				}*/
				default:
					PYGMALION_UNREACHABLE;
					return zero;
				}
			}
			PYGMALION_INLINE static scoreType futilityGlobalMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				switch (depthRemaining)
				{
				case 0:
				{
					const squaresType ownPawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & stack.position().playerOccupancy(movingPlayer) };
					constexpr const squaresType promotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? descriptorSearch::rank7 : descriptorSearch::rank2 };
					const squaresType promotionPawns{ ownPawns & promotionsMask };
					scoreType promotionValue{ zero };
					if (promotionPawns)
					{
						constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) - static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
						promotionValue += singlePromotionsValue;
					}
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange };
					bool noCapture{ true };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					if (queens)
					{
						constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) };
						captureValue += queenValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						if (rooks)
						{
							constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::rook, descriptorSearch::whitePlayer)) };
							captureValue += rookValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							if (bishops)
							{
								constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::bishop, descriptorSearch::whitePlayer)) };
								captureValue += bishopValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								if (knights)
								{
									constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::knight, descriptorSearch::whitePlayer)) };
									captureValue += knightValue;
									noCapture = false;
								}
								if (noCapture)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									if (pawns)
									{
										constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
										captureValue += pawnValue;
										noCapture = false;
									}
								}
							}
						}
					}
					return positionalValue + captureValue + promotionValue;
				}
				case 1:
				{
					const squaresType ownPawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & stack.position().playerOccupancy(movingPlayer) };
					constexpr const squaresType promotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? descriptorSearch::rank7 : descriptorSearch::rank2 };
					const squaresType promotionPawns{ ownPawns & promotionsMask };
					scoreType promotionValue{ zero };
					if (promotionPawns)
					{
						constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) - static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
						promotionValue += singlePromotionsValue;
					}
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
					bool noCapture{ true };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					if (queens)
					{
						constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) };
						captureValue += queenValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						if (rooks)
						{
							constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::rook, descriptorSearch::whitePlayer)) };
							captureValue += rookValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							if (bishops)
							{
								constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::bishop, descriptorSearch::whitePlayer)) };
								captureValue += bishopValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								if (knights)
								{
									constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::knight, descriptorSearch::whitePlayer)) };
									captureValue += knightValue;
									noCapture = false;
								}
								if (noCapture)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									if (pawns)
									{
										constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
										captureValue += pawnValue;
										noCapture = false;
									}
								}
							}
						}
					}
					return positionalValue + captureValue + promotionValue;
				}
				case 2:
				{
					const squaresType ownPawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & stack.position().playerOccupancy(movingPlayer) };
					constexpr const squaresType promotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? descriptorSearch::rank7 : descriptorSearch::rank2 };
					const squaresType promotionPawns{ ownPawns & promotionsMask };
					size_t countPossiblePromotions{ promotionPawns.count() };
					if (countPossiblePromotions < 2)
					{
						constexpr const squaresType prePromotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? (descriptorSearch::rank7 | descriptorSearch::rank6) : (descriptorSearch::rank2 | descriptorSearch::rank3) };
						const squaresType prePromotionPawns{ ownPawns & prePromotionsMask };
						countPossiblePromotions += static_cast<bool>(prePromotionPawns);
					}
					scoreType promotionValue{ zero };
					if (countPossiblePromotions >= 1)
					{
						constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) - static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
						promotionValue += singlePromotionsValue;
						promotionValue += singlePromotionsValue * (countPossiblePromotions > 1);
					}
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) };
						captureValue += queenValue;
						countCaptures++;
						if (countCaptures >= 2)
							break;
					}
					if (countCaptures < 2)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						for (const auto sq : rooks)
						{
							constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::rook, descriptorSearch::whitePlayer)) };
							captureValue += rookValue;
							countCaptures++;
							if (countCaptures >= 2)
								break;
						}
						if (countCaptures < 2)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							for (const auto sq : bishops)
							{
								constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::bishop, descriptorSearch::whitePlayer)) };
								captureValue += bishopValue;
								countCaptures++;
								if (countCaptures >= 2)
									break;
							}
							if (countCaptures < 2)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								for (const auto sq : knights)
								{
									constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::knight, descriptorSearch::whitePlayer)) };
									captureValue += knightValue;
									countCaptures++;
									if (countCaptures >= 2)
										break;
								}
								if (countCaptures < 2)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									for (const auto sq : pawns)
									{
										constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
										captureValue += pawnValue;
										countCaptures++;
										if (countCaptures >= 2)
											break;
									}
								}
							}
						}
					}
					return positionalValue + captureValue + promotionValue;
				}
				case 3:
				{
					const squaresType ownPawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & stack.position().playerOccupancy(movingPlayer) };
					constexpr const squaresType promotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? descriptorSearch::rank7 : descriptorSearch::rank2 };
					const squaresType promotionPawns{ ownPawns & promotionsMask };
					size_t countPossiblePromotions{ promotionPawns.count() };
					if (countPossiblePromotions < 2)
					{
						constexpr const squaresType prePromotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? (descriptorSearch::rank7 | descriptorSearch::rank6) : (descriptorSearch::rank2 | descriptorSearch::rank3) };
						const squaresType prePromotionPawns{ ownPawns & prePromotionsMask };
						countPossiblePromotions += static_cast<bool>(prePromotionPawns);
					}
					scoreType promotionValue{ zero };
					if (countPossiblePromotions >= 1)
					{
						constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) - static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
						promotionValue += singlePromotionsValue;
						promotionValue += singlePromotionsValue * (countPossiblePromotions > 1);
					}
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) };
						captureValue += queenValue;
						countCaptures++;
						if (countCaptures >= 2)
							break;
					}
					if (countCaptures < 2)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						for (const auto sq : rooks)
						{
							constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::rook, descriptorSearch::whitePlayer)) };
							captureValue += rookValue;
							countCaptures++;
							if (countCaptures >= 2)
								break;
						}
						if (countCaptures < 2)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							for (const auto sq : bishops)
							{
								constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::bishop, descriptorSearch::whitePlayer)) };
								captureValue += bishopValue;
								countCaptures++;
								if (countCaptures >= 2)
									break;
							}
							if (countCaptures < 2)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								for (const auto sq : knights)
								{
									constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::knight, descriptorSearch::whitePlayer)) };
									captureValue += knightValue;
									countCaptures++;
									if (countCaptures >= 2)
										break;
								}
								if (countCaptures < 2)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									for (const auto sq : pawns)
									{
										constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
										captureValue += pawnValue;
										countCaptures++;
										if (countCaptures >= 2)
											break;
									}
								}
							}
						}
					}
					return positionalValue + captureValue + promotionValue;
				}
				/*case 4:
				{
					const squaresType ownPawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & stack.position().playerOccupancy(movingPlayer) };
					constexpr const squaresType promotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? descriptorSearch::rank7 : descriptorSearch::rank2 };
					const squaresType promotionPawns{ ownPawns & promotionsMask };
					size_t countPossiblePromotions{ promotionPawns.count() };
					if (countPossiblePromotions < 3)
					{
						constexpr const squaresType prePromotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? (descriptorSearch::rank7 | descriptorSearch::rank6) : (descriptorSearch::rank2 | descriptorSearch::rank3) };
						const squaresType prePromotionPawns{ ownPawns & prePromotionsMask };
						countPossiblePromotions += prePromotionPawns.count();
						if (countPossiblePromotions < 2)
						{
							constexpr const squaresType prePrePromotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? (descriptorSearch::rank7 | descriptorSearch::rank6 | descriptorSearch::rank5) : (descriptorSearch::rank2 | descriptorSearch::rank3 | descriptorSearch::rank4) };
							const squaresType prePrePromotionPawns{ ownPawns & prePrePromotionsMask };
							countPossiblePromotions += static_cast<bool>(prePrePromotionPawns);
						}
					}
					scoreType promotionValue{ zero };
					if (countPossiblePromotions >= 1)
					{
						constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) - static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
						promotionValue += singlePromotionsValue;
						if (countPossiblePromotions > 1)
						{
							promotionValue += singlePromotionsValue;
							promotionValue += singlePromotionsValue * (countPossiblePromotions > 2);
						}
					}
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) };
						captureValue += queenValue;
						countCaptures++;
						if (countCaptures >= 3)
							break;
					}
					if (countCaptures < 3)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						for (const auto sq : rooks)
						{
							constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::rook,descriptorSearch::whitePlayer)) };
							captureValue += rookValue;
							countCaptures++;
							if (countCaptures >= 3)
								break;
						}
						if (countCaptures < 3)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							for (const auto sq : bishops)
							{
								constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::bishop, descriptorSearch::whitePlayer)) };
								captureValue += bishopValue;
								countCaptures++;
								if (countCaptures >= 3)
									break;
							}
							if (countCaptures < 3)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								for (const auto sq : knights)
								{
									constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::knight, descriptorSearch::whitePlayer)) };
									captureValue += knightValue;
									countCaptures++;
									if (countCaptures >= 3)
										break;
								}
								if (countCaptures < 3)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									for (const auto sq : pawns)
									{
										constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
										captureValue += pawnValue;
										countCaptures++;
										if (countCaptures >= 3)
											break;
									}
								}
							}
						}
					}
					return positionalValue + captureValue + promotionValue;
				}
				case 5:
				{
					const squaresType ownPawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & stack.position().playerOccupancy(movingPlayer) };
					constexpr const squaresType promotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? descriptorSearch::rank7 : descriptorSearch::rank2 };
					const squaresType promotionPawns{ ownPawns & promotionsMask };
					size_t countPossiblePromotions{ promotionPawns.count() };
					if (countPossiblePromotions < 3)
					{
						constexpr const squaresType prePromotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? (descriptorSearch::rank7 | descriptorSearch::rank6) : (descriptorSearch::rank2 | descriptorSearch::rank3) };
						const squaresType prePromotionPawns{ ownPawns & prePromotionsMask };
						countPossiblePromotions += prePromotionPawns.count();
						if (countPossiblePromotions < 2)
						{
							constexpr const squaresType prePrePromotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? (descriptorSearch::rank7 | descriptorSearch::rank6 | descriptorSearch::rank5) : (descriptorSearch::rank2 | descriptorSearch::rank3 | descriptorSearch::rank4) };
							const squaresType prePrePromotionPawns{ ownPawns & prePrePromotionsMask };
							countPossiblePromotions += static_cast<bool>(prePrePromotionPawns);
						}
					}
					scoreType promotionValue{ zero };
					if (countPossiblePromotions >= 1)
					{
						constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) - static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
						promotionValue += singlePromotionsValue;
						if (countPossiblePromotions > 1)
						{
							promotionValue += singlePromotionsValue;
							promotionValue += singlePromotionsValue * (countPossiblePromotions > 2);
						}
					}
					constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::queen, descriptorSearch::whitePlayer)) };
						captureValue += queenValue;
						countCaptures++;
						if (countCaptures >= 3)
							break;
					}
					if (countCaptures < 3)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						for (const auto sq : rooks)
						{
							constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::rook,descriptorSearch::whitePlayer)) };
							captureValue += rookValue;
							countCaptures++;
							if (countCaptures >= 3)
								break;
						}
						if (countCaptures < 3)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							for (const auto sq : bishops)
							{
								constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::bishop, descriptorSearch::whitePlayer)) };
								captureValue += bishopValue;
								countCaptures++;
								if (countCaptures >= 3)
									break;
							}
							if (countCaptures < 3)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								for (const auto sq : knights)
								{
									constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::knight, descriptorSearch::whitePlayer)) };
									captureValue += knightValue;
									countCaptures++;
									if (countCaptures >= 3)
										break;
								}
								if (countCaptures < 3)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									for (const auto sq : pawns)
									{
										constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(descriptorSearch::pawn, descriptorSearch::whitePlayer)) };
										captureValue += pawnValue;
										countCaptures++;
										if (countCaptures >= 3)
											break;
									}
								}
							}
						}
					}
					return positionalValue + captureValue + promotionValue;
				}*/
				default:
					PYGMALION_UNREACHABLE;
					return zero;
				}
			}
			PYGMALION_INLINE scoreType moveFutilityValue_Implementation(const movebitsType move) const noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				if (motorType::move().isCapture(move))
				{
					const squareType captureSquare{ motorType::move().captureSquare(this->stack().position(),move) };
					const pieceType capturedPiece{ this->stack().position().getPiece(captureSquare) };
					const scoreType victimValue{ static_cast<scoreType>(boardType::materialValue(capturedPiece, descriptorSearch::whitePlayer)) };
					if (motorType::move().isPromotion(move))
					{
						const pieceType promotedPiece{ motorType::move().promotedPiece(move) };
						const scoreType promotionValue{ static_cast<scoreType>(boardType::materialValue(promotedPiece, descriptorSearch::whitePlayer)) };
						return victimValue + promotionValue;
					}
					else
						return victimValue;
				}
				else
				{
					if (motorType::move().isPromotion(move))
					{
						const pieceType promotedPiece{ motorType::move().promotedPiece(move) };
						const scoreType promotionValue{ static_cast<scoreType>(boardType::materialValue(promotedPiece, descriptorSearch::whitePlayer)) };
						return promotionValue;
					}
					else
						return zero;
				}
			}
		};
		template<size_t PLAYER>
		using nodeType = node<PLAYER>;
	};
}