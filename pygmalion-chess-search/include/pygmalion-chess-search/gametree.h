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
			PYGMALION_INLINE ~node() noexcept = default;
			PYGMALION_INLINE node(const stackType& stack, signal& terminate, heuristicsType& heuristics, const size_t depth, const std::vector<scoreType>& parameters) noexcept :
				pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>(stack, terminate, heuristics, depth, parameters)
			{

			}
			PYGMALION_INLINE static bool futilityPruningEnabled_Implementation(const size_t depthRemaining) noexcept
			{
				return depthRemaining <= 5;
			}
			PYGMALION_INLINE node(const parentType& parent, const movebitsType moveBits) noexcept :
				pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>(parent, moveBits)
			{
			}
			PYGMALION_INLINE constexpr static depthType nullMoveReduction_Implementation(const size_t depthRemaining) noexcept
			{
				return depthType(2) + ((depthRemaining - depthType(2)) / depthType(2));
			}
			PYGMALION_INLINE bool nullMoveAllowed_Implementation() const noexcept
			{
				const squaresType pieces{ this->stack().position().pieceOccupancy(descriptorSearch::knight) | this->stack().position().pieceOccupancy(descriptorSearch::bishop) | this->stack().position().pieceOccupancy(descriptorSearch::rook) | this->stack().position().pieceOccupancy(descriptorSearch::queen) };
				const squaresType playerPieces{ pieces & this->stack().position().playerOccupancy(movingPlayer) };
				return playerPieces;
			}
			PYGMALION_INLINE scoreType futilityMargin_Implementation(const size_t depthRemaining, const stackType& stack) const noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				switch (depthRemaining)
				{
				case 0:
				{
					const scoreType positionalValue{ stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) };
					return positionalValue;
				}
				case 1:
				{
					const scoreType positionalValue{ stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) + stack.delta().maxQuietChange(stackType::NextPlayer,stack.position().pieceMask(stackType::NextPlayer)) };
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
						const scoreType singlePromotionsValue{ stack.materialTable().materialUpperBound(descriptorSearch::queen) - stack.materialTable().materialLowerBound(descriptorSearch::pawn) };
						promotionValue += singlePromotionsValue;
					}
					const scoreType positionalValue{ 2 * stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) + stack.delta().maxQuietChange(stackType::NextPlayer,stack.position().pieceMask(stackType::NextPlayer)) };
					bool noCapture{ true };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					if (queens)
					{
						const scoreType queenValue{ stack.materialTable().materialUpperBound(descriptorSearch::queen) };
						captureValue += queenValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						if (rooks)
						{
							const scoreType rookValue{ stack.materialTable().materialUpperBound(descriptorSearch::rook) };
							captureValue += rookValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							if (bishops)
							{
								const scoreType bishopValue{ stack.materialTable().materialUpperBound(descriptorSearch::bishop) };
								captureValue += bishopValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								if (knights)
								{
									const scoreType knightValue{ stack.materialTable().materialUpperBound(descriptorSearch::knight) };
									captureValue += knightValue;
									noCapture = false;
								}
								if (noCapture)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									if (pawns)
									{
										const scoreType pawnValue{ stack.materialTable().materialUpperBound(descriptorSearch::pawn) };
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
						const scoreType singlePromotionsValue{ stack.materialTable().materialUpperBound(descriptorSearch::queen) - stack.materialTable().materialLowerBound(descriptorSearch::pawn) };
						promotionValue += singlePromotionsValue;
					}
					const scoreType positionalValue{ 2 * stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) + 2 * stack.delta().maxQuietChange(stackType::NextPlayer,stack.position().pieceMask(stackType::NextPlayer)) };
					bool noCapture{ true };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					if (queens)
					{
						const scoreType queenValue{ stack.materialTable().materialUpperBound(descriptorSearch::queen) };
						captureValue += queenValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						if (rooks)
						{
							const scoreType rookValue{ stack.materialTable().materialUpperBound(descriptorSearch::rook) };
							captureValue += rookValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							if (bishops)
							{
								const scoreType bishopValue{ stack.materialTable().materialUpperBound(descriptorSearch::bishop) };
								captureValue += bishopValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								if (knights)
								{
									const scoreType knightValue{ stack.materialTable().materialUpperBound(descriptorSearch::knight) };
									captureValue += knightValue;
									noCapture = false;
								}
								if (noCapture)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									if (pawns)
									{
										const scoreType pawnValue{ stack.materialTable().materialUpperBound(descriptorSearch::pawn) };
										captureValue += pawnValue;
										noCapture = false;
									}
								}
							}
						}
					}
					return positionalValue + captureValue + promotionValue;
				}
				case 4:
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
						const scoreType singlePromotionsValue{ stack.materialTable().materialUpperBound(descriptorSearch::queen) - stack.materialTable().materialLowerBound(descriptorSearch::pawn) };
						promotionValue += singlePromotionsValue;
						promotionValue += singlePromotionsValue * (countPossiblePromotions > 1);
					}
					const scoreType positionalValue{ 3 * stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) + 2 * stack.delta().maxQuietChange(stackType::NextPlayer,stack.position().pieceMask(stackType::NextPlayer)) };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						const scoreType queenValue{ stack.materialTable().materialUpperBound(descriptorSearch::queen) };
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
							const scoreType rookValue{ stack.materialTable().materialUpperBound(descriptorSearch::rook) };
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
								const scoreType bishopValue{ stack.materialTable().materialUpperBound(descriptorSearch::bishop) };
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
									const scoreType knightValue{ stack.materialTable().materialUpperBound(descriptorSearch::knight) };
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
										const scoreType pawnValue{ stack.materialTable().materialUpperBound(descriptorSearch::pawn) };
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
						const scoreType singlePromotionsValue{ stack.materialTable().materialUpperBound(descriptorSearch::queen) - stack.materialTable().materialLowerBound(descriptorSearch::pawn) };
						promotionValue += singlePromotionsValue;
						promotionValue += singlePromotionsValue * (countPossiblePromotions > 1);
					}
					const scoreType positionalValue{ 3 * stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) + 3 * stack.delta().maxQuietChange(stackType::NextPlayer,stack.position().pieceMask(stackType::NextPlayer)) };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						const scoreType queenValue{ stack.materialTable().materialUpperBound(descriptorSearch::queen) };
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
							const scoreType rookValue{ stack.materialTable().materialUpperBound(descriptorSearch::rook) };
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
								const scoreType bishopValue{ stack.materialTable().materialUpperBound(descriptorSearch::bishop) };
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
									const scoreType knightValue{ stack.materialTable().materialUpperBound(descriptorSearch::knight) };
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
										const scoreType pawnValue{ stack.materialTable().materialUpperBound(descriptorSearch::pawn) };
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
				default:
					PYGMALION_UNREACHABLE;
					return zero;
				}
			}
			PYGMALION_INLINE scoreType deltaMargin_Implementation(const stackType& stack) const noexcept
			{
				return this->rootDelta();
			}
			PYGMALION_INLINE scoreType futilityGlobalMargin_Implementation(const size_t depthRemaining, const stackType& stack) const noexcept
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
						const scoreType singlePromotionsValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) - static_cast<scoreType>(stack.materialTable().materialLowerBound(descriptorSearch::pawn)) };
						promotionValue += singlePromotionsValue;
					}
					const scoreType positionalValue{ stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) };
					bool noCapture{ true };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					if (queens)
					{
						const scoreType queenValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) };
						captureValue += queenValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						if (rooks)
						{
							const scoreType rookValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::rook)) };
							captureValue += rookValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							if (bishops)
							{
								const scoreType bishopValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::bishop)) };
								captureValue += bishopValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								if (knights)
								{
									const scoreType knightValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::knight)) };
									captureValue += knightValue;
									noCapture = false;
								}
								if (noCapture)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									if (pawns)
									{
										const scoreType pawnValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::pawn)) };
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
						const scoreType singlePromotionsValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) - static_cast<scoreType>(stack.materialTable().materialLowerBound(descriptorSearch::pawn)) };
						promotionValue += singlePromotionsValue;
					}
					const scoreType positionalValue{ stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) + stack.delta().maxQuietChange(stackType::NextPlayer,stack.position().pieceMask(stackType::NextPlayer)) };
					bool noCapture{ true };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					if (queens)
					{
						const scoreType queenValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) };
						captureValue += queenValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
						if (rooks)
						{
							const scoreType rookValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::rook)) };
							captureValue += rookValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
							if (bishops)
							{
								const scoreType bishopValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::bishop)) };
								captureValue += bishopValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
								if (knights)
								{
									const scoreType knightValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::knight)) };
									captureValue += knightValue;
									noCapture = false;
								}
								if (noCapture)
								{
									const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
									if (pawns)
									{
										const scoreType pawnValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::pawn)) };
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
						const scoreType singlePromotionsValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) - static_cast<scoreType>(stack.materialTable().materialLowerBound(descriptorSearch::pawn)) };
						promotionValue += singlePromotionsValue;
						promotionValue += singlePromotionsValue * (countPossiblePromotions > 1);
					}
					const scoreType positionalValue{ 2 * stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) + stack.delta().maxQuietChange(stackType::NextPlayer,stack.position().pieceMask(stackType::NextPlayer)) };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						const scoreType queenValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) };
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
							const scoreType rookValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::rook)) };
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
								const scoreType bishopValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::bishop)) };
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
									const scoreType knightValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::knight)) };
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
										const scoreType pawnValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::pawn)) };
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
						const scoreType singlePromotionsValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) - static_cast<scoreType>(stack.materialTable().materialLowerBound(descriptorSearch::pawn)) };
						promotionValue += singlePromotionsValue;
						promotionValue += singlePromotionsValue * (countPossiblePromotions > 1);
					}
					const scoreType positionalValue{ 2 * stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) + 2 * stack.delta().maxQuietChange(stackType::NextPlayer,stack.position().pieceMask(stackType::NextPlayer)) };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						const scoreType queenValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) };
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
							const scoreType rookValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::rook)) };
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
								const scoreType bishopValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::bishop)) };
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
									const scoreType knightValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::knight)) };
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
										const scoreType pawnValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::pawn)) };
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
				case 4:
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
						const scoreType singlePromotionsValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) - static_cast<scoreType>(stack.materialTable().materialLowerBound(descriptorSearch::pawn)) };
						promotionValue += singlePromotionsValue;
						if (countPossiblePromotions > 1)
						{
							promotionValue += singlePromotionsValue;
							promotionValue += singlePromotionsValue * (countPossiblePromotions > 2);
						}
					}
					const scoreType positionalValue{ 3 * stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) + 2 * stack.delta().maxQuietChange(stackType::NextPlayer,stack.position().pieceMask(stackType::NextPlayer)) };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						const scoreType queenValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) };
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
							const scoreType rookValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::rook)) };
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
								const scoreType bishopValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::bishop)) };
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
									const scoreType knightValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::knight)) };
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
										const scoreType pawnValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::pawn)) };
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
						const scoreType singlePromotionsValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) - static_cast<scoreType>(stack.materialTable().materialLowerBound(descriptorSearch::pawn)) };
						promotionValue += singlePromotionsValue;
						if (countPossiblePromotions > 1)
						{
							promotionValue += singlePromotionsValue;
							promotionValue += singlePromotionsValue * (countPossiblePromotions > 2);
						}
					}
					const scoreType positionalValue{ 3 * stack.delta().maxQuietChange(stackType::MovingPlayer,stack.position().pieceMask(stackType::MovingPlayer)) + 3 * stack.delta().maxQuietChange(stackType::NextPlayer,stack.position().pieceMask(stackType::NextPlayer)) };
					size_t countCaptures{ 0 };
					const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
					const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
					scoreType captureValue{ zero };
					for (const auto sq : queens)
					{
						const scoreType queenValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::queen)) };
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
							const scoreType rookValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::rook)) };
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
								const scoreType bishopValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::bishop)) };
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
									const scoreType knightValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::knight)) };
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
										const scoreType pawnValue{ static_cast<scoreType>(stack.materialTable().materialUpperBound(descriptorSearch::pawn)) };
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
				default:
					PYGMALION_UNREACHABLE;
					return zero;
				}
			}
			PYGMALION_INLINE scoreType deltaGlobalMargin_Implementation(const stackType& stack) const noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				const squaresType ownPawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & stack.position().playerOccupancy(movingPlayer) };
				constexpr const squaresType promotionsMask{ movingPlayer == descriptorSearch::whitePlayer ? descriptorSearch::rank7 : descriptorSearch::rank2 };
				const squaresType promotionPawns{ ownPawns & promotionsMask };
				scoreType promotionValue{ zero };
				if (promotionPawns)
				{
					const scoreType singlePromotionsValue{ stack.materialTable().materialUpperBound(descriptorSearch::queen) - stack.materialTable().materialLowerBound(descriptorSearch::pawn) };
					promotionValue += singlePromotionsValue;
				}
				const scoreType positionalValue{ this->rootDelta() };
				bool noCapture{ true };
				const squaresType otherOcc{ stack.position().playerOccupancy(otherPlayer) };
				const squaresType queens{ stack.position().pieceOccupancy(descriptorSearch::queen) & otherOcc };
				scoreType captureValue{ zero };
				if (queens)
				{
					const scoreType queenValue{ stack.materialTable().materialUpperBound(descriptorSearch::queen) };
					captureValue += queenValue;
					noCapture = false;
				}
				if (noCapture)
				{
					const squaresType rooks{ stack.position().pieceOccupancy(descriptorSearch::rook) & otherOcc };
					if (rooks)
					{
						const scoreType rookValue{ stack.materialTable().materialUpperBound(descriptorSearch::rook) };
						captureValue += rookValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType bishops{ stack.position().pieceOccupancy(descriptorSearch::bishop) & otherOcc };
						if (bishops)
						{
							const scoreType bishopValue{ stack.materialTable().materialUpperBound(descriptorSearch::bishop) };
							captureValue += bishopValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType knights{ stack.position().pieceOccupancy(descriptorSearch::knight) & otherOcc };
							if (knights)
							{
								const scoreType knightValue{ stack.materialTable().materialUpperBound(descriptorSearch::knight) };
								captureValue += knightValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType pawns{ stack.position().pieceOccupancy(descriptorSearch::pawn) & otherOcc };
								if (pawns)
								{
									const scoreType pawnValue{ stack.materialTable().materialUpperBound(descriptorSearch::pawn) };
									captureValue += pawnValue;
									noCapture = false;
								}
							}
						}
					}
				}
				return positionalValue + captureValue + promotionValue;
			}
			PYGMALION_INLINE scoreType moveFutilityValue_Implementation(const movebitsType move) const noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				constexpr const playerType movingSide{ stackType::MovingPlayer };
				constexpr const playerType defendingSide{ stackType::NextPlayer };
				if (motorType::move().isCapture(move))
				{
					const squareType captureSquare{ motorType::move().captureSquare(this->stack().position(),move) };
					const pieceType capturedPiece{ this->stack().position().getPiece(captureSquare) };
					scoreType victimValue;
					victimValue = -this->stack().materialTable().template materialRelative < static_cast<size_t>(movingSide) >(defendingSide, capturedPiece, captureSquare);
					if (motorType::move().isPromotion(move))
					{
						const squareType to{ motorType::move().toSquare(this->stack().position(),move) };
						const squareType from{ motorType::move().fromSquare(this->stack().position(),move) };
						const pieceType promotedPiece{ motorType::move().promotedPiece(move) };
						scoreType promotionValue;
						promotionValue = this->stack().materialTable().template materialRelative < static_cast<size_t>(movingSide) >(movingSide, promotedPiece, to) - this->stack().materialTable().template materialRelative < static_cast<size_t>(movingSide) >(movingSide, descriptorState::pawn, from);
						return victimValue + promotionValue;
					}
					else
						return victimValue;
				}
				else
				{
					if (motorType::move().isPromotion(move))
					{
						const squareType to{ motorType::move().toSquare(this->stack().position(),move) };
						const squareType from{ motorType::move().fromSquare(this->stack().position(),move) };
						const pieceType promotedPiece{ motorType::move().promotedPiece(move) };
						scoreType promotionValue;
						promotionValue = this->stack().materialTable().template materialRelative < static_cast<size_t>(movingSide) >(movingSide, promotedPiece, to) - this->stack().materialTable().template materialRelative < static_cast<size_t>(movingSide) >(movingSide, descriptorState::pawn, from);
						return promotionValue;
					}
					else
						return zero;
				}
			}
			PYGMALION_INLINE scoreType moveDeltaValue_Implementation(const movebitsType move) const noexcept
			{
				constexpr const scoreType zero{ scoreType::zero() };
				if (motorType::move().isCapture(move))
				{
					const playerType movingSide{ this->stack().movingPlayer() };
					const playerType defendingSide{ movingSide.next() };
					const squareType captureSquare{ motorType::move().captureSquare(this->stack().position(),move) };
					const pieceType capturedPiece{ this->stack().position().getPiece(captureSquare) };
					const scoreType victimValue{ static_cast<scoreType>(boardType::materialValueRelative(capturedPiece,captureSquare,defendingSide)) };
					if (motorType::move().isPromotion(move))
					{
						const squareType from{ motorType::move().fromSquare(this->stack().position(),move) };
						const pieceType promotedPiece{ motorType::move().promotedPiece(move) };
						const scoreType promotionValue{ static_cast<scoreType>(boardType::materialValueRelative(promotedPiece,captureSquare,movingSide) - boardType::materialValueRelative(descriptorState::pawn,from,movingSide)) };
						return victimValue + promotionValue;
					}
					else
						return victimValue;
				}
				else
				{
					const playerType movingSide{ this->stack().movingPlayer() };
					const squareType toSquare{ motorType::move().toSquare(this->stack().position(),move) };
					const scoreType victimValue{ zero };
					if (motorType::move().isPromotion(move))
					{
						const squareType from{ motorType::move().fromSquare(this->stack().position(),move) };
						const pieceType promotedPiece{ motorType::move().promotedPiece(move) };
						const scoreType promotionValue{ static_cast<scoreType>(boardType::materialValueRelative(promotedPiece,toSquare,movingSide) - boardType::materialValueRelative(descriptorState::pawn,from,movingSide)) };
						return victimValue + promotionValue;
					}
					else
						return victimValue;
				}
			}
		};
		template<size_t PLAYER>
		using nodeType = node<PLAYER>;
	};
}