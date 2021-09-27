namespace pygmalion::chess
{
	class node :
		public pygmalion::node<descriptor_search, node>
	{
	public:
		node(const stackType& stack, std::atomic_bool& isRunning, heuristicsType& heuristics) noexcept :
			pygmalion::node<descriptor_search, node>(stack, isRunning, heuristics)
		{

		}
		constexpr static bool futilityPruningEnabled_Implementation(const size_t depthRemaining) noexcept
		{
			return depthRemaining <= 5;
		}
		node(const node& parent, const movebitsType moveBits) noexcept :
			pygmalion::node<descriptor_search, node>(parent, moveBits)
		{
		}
		constexpr static depthType nullMoveReduction_Implementation(const size_t depthRemaining) noexcept
		{
			return depthType(2) + depthRemaining / depthType(4);
		}
		bool nullMoveAllowed_Implementation() const noexcept
		{
			const squaresType pieces{ this->stack().position().pieceOccupancy(knight) | this->stack().position().pieceOccupancy(bishop) | this->stack().position().pieceOccupancy(rook) | this->stack().position().pieceOccupancy(queen) };
			const squaresType playerPieces{ pieces & this->stack().position().playerOccupancy(this->stack().position().movingPlayer()) };
			return playerPieces != squaresType::none();
		}
		constexpr static scoreType futilityMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
		{
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
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer()) };
				const squaresType promotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? rank7 : rank2) };
				size_t countPossiblePromotions{ promotionPawns.count() };
				scoreType promotionValue{ scoreType::zero() };
				if (countPossiblePromotions >= 1)
				{
					constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
					promotionValue += singlePromotionsValue;
				}
				constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
				bool noCapture{ true };
				const squaresType queens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()) };
				scoreType captureValue{ scoreType::zero() };
				if (queens != squaresType::none())
				{
					constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) };
					captureValue += queenValue;
					noCapture = false;
				}
				if (noCapture)
				{
					const squaresType rooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()) };
					if (rooks != squaresType::none())
					{
						constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) };
						captureValue += rookValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType bishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()) };
						if (bishops)
						{
							constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) };
							captureValue += bishopValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType knights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()) };
							if (knights)
							{
								constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) };
								captureValue += knightValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()) };
								if (pawns)
								{
									constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
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
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer()) };
				const squaresType promotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? rank7 : rank2) };
				size_t countPossiblePromotions{ promotionPawns.count() };
				scoreType promotionValue{ scoreType::zero() };
				if (countPossiblePromotions >= 1)
				{
					constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
					promotionValue += singlePromotionsValue;
				}
				constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
				bool noCapture{ true };
				const squaresType queens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()) };
				scoreType captureValue{ scoreType::zero() };
				if (queens != squaresType::none())
				{
					constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) };
					captureValue += queenValue;
					noCapture = false;
				}
				if (noCapture)
				{
					const squaresType rooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()) };
					if (rooks != squaresType::none())
					{
						constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) };
						captureValue += rookValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType bishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()) };
						if (bishops)
						{
							constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) };
							captureValue += bishopValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType knights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()) };
							if (knights)
							{
								constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) };
								captureValue += knightValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()) };
								if (pawns)
								{
									constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
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
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer()) };
				const squaresType promotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? rank7 : rank2) };
				size_t countPossiblePromotions{ promotionPawns.count() };
				if (countPossiblePromotions < 2)
				{
					const squaresType prePromotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? (rank7 | rank6) : (rank2 | rank3)) };
					countPossiblePromotions += prePromotionPawns != squaresType::none();
				}
				scoreType promotionValue{ scoreType::zero() };
				if (countPossiblePromotions >= 1)
				{
					constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
					promotionValue += singlePromotionsValue;
					if (countPossiblePromotions > 1)
						promotionValue += singlePromotionsValue;
				}
				constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
				size_t countCaptures{ 0 };
				const squaresType queens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()) };
				scoreType captureValue{ scoreType::zero() };
				for (const auto sq : queens)
				{
					constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) };
					captureValue += queenValue;
					countCaptures++;
					if (countCaptures >= 2)
						break;
				}
				if (countCaptures < 2)
				{
					const squaresType rooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()) };
					for (const auto sq : rooks)
					{
						constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) };
						captureValue += rookValue;
						countCaptures++;
						if (countCaptures >= 2)
							break;
					}
					if (countCaptures < 2)
					{
						const squaresType bishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto sq : bishops)
						{
							constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) };
							captureValue += bishopValue;
							countCaptures++;
							if (countCaptures >= 2)
								break;
						}
						if (countCaptures < 2)
						{
							const squaresType knights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()) };
							for (const auto sq : knights)
							{
								constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) };
								captureValue += knightValue;
								countCaptures++;
								if (countCaptures >= 2)
									break;
							}
							if (countCaptures < 2)
							{
								const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()) };
								for (const auto sq : pawns)
								{
									constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
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
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer()) };
				const squaresType promotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? rank7 : rank2) };
				size_t countPossiblePromotions{ promotionPawns.count() };
				if (countPossiblePromotions < 2)
				{
					const squaresType prePromotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? (rank7 | rank6) : (rank2 | rank3)) };
					countPossiblePromotions += prePromotionPawns != squaresType::none();
				}
				scoreType promotionValue{ scoreType::zero() };
				if (countPossiblePromotions >= 1)
				{
					constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
					promotionValue += singlePromotionsValue;
					if (countPossiblePromotions > 1)
						promotionValue += singlePromotionsValue;
				}
				constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
				size_t countCaptures{ 0 };
				const squaresType queens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()) };
				scoreType captureValue{ scoreType::zero() };
				for (const auto sq : queens)
				{
					constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) };
					captureValue += queenValue;
					countCaptures++;
					if (countCaptures >= 2)
						break;
				}
				if (countCaptures < 2)
				{
					const squaresType rooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()) };
					for (const auto sq : rooks)
					{
						constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) };
						captureValue += rookValue;
						countCaptures++;
						if (countCaptures >= 2)
							break;
					}
					if (countCaptures < 2)
					{
						const squaresType bishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto sq : bishops)
						{
							constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) };
							captureValue += bishopValue;
							countCaptures++;
							if (countCaptures >= 2)
								break;
						}
						if (countCaptures < 2)
						{
							const squaresType knights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()) };
							for (const auto sq : knights)
							{
								constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) };
								captureValue += knightValue;
								countCaptures++;
								if (countCaptures >= 2)
									break;
							}
							if (countCaptures < 2)
							{
								const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()) };
								for (const auto sq : pawns)
								{
									constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
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
				assert(false);
				return scoreType::zero();
			}
		}
		constexpr static scoreType futilityGlobalMargin_Implementation(const size_t depthRemaining, const stackType& stack) noexcept
		{
			switch (depthRemaining)
			{
			case 0:
			{
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer()) };
				const squaresType promotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? rank7 : rank2) };
				size_t countPossiblePromotions{ promotionPawns.count() };
				scoreType promotionValue{ scoreType::zero() };
				if (countPossiblePromotions >= 1)
				{
					constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
					promotionValue += singlePromotionsValue;
				}
				constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange };
				bool noCapture{ true };
				const squaresType queens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()) };
				scoreType captureValue{ scoreType::zero() };
				if (queens != squaresType::none())
				{
					constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) };
					captureValue += queenValue;
					noCapture = false;
				}
				if (noCapture)
				{
					const squaresType rooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()) };
					if (rooks != squaresType::none())
					{
						constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) };
						captureValue += rookValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType bishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()) };
						if (bishops)
						{
							constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) };
							captureValue += bishopValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType knights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()) };
							if (knights)
							{
								constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) };
								captureValue += knightValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()) };
								if (pawns)
								{
									constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
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
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer()) };
				const squaresType promotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? rank7 : rank2) };
				size_t countPossiblePromotions{ promotionPawns.count() };
				scoreType promotionValue{ scoreType::zero() };
				if (countPossiblePromotions >= 1)
				{
					constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
					promotionValue += singlePromotionsValue;
				}
				constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
				bool noCapture{ true };
				const squaresType queens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()) };
				scoreType captureValue{ scoreType::zero() };
				if (queens != squaresType::none())
				{
					constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) };
					captureValue += queenValue;
					noCapture = false;
				}
				if (noCapture)
				{
					const squaresType rooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()) };
					if (rooks != squaresType::none())
					{
						constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) };
						captureValue += rookValue;
						noCapture = false;
					}
					if (noCapture)
					{
						const squaresType bishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()) };
						if (bishops)
						{
							constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) };
							captureValue += bishopValue;
							noCapture = false;
						}
						if (noCapture)
						{
							const squaresType knights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()) };
							if (knights)
							{
								constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) };
								captureValue += knightValue;
								noCapture = false;
							}
							if (noCapture)
							{
								const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()) };
								if (pawns)
								{
									constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
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
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer()) };
				const squaresType promotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? rank7 : rank2) };
				size_t countPossiblePromotions{ promotionPawns.count() };
				if (countPossiblePromotions < 2)
				{
					const squaresType prePromotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? (rank7 | rank6) : (rank2 | rank3)) };
					countPossiblePromotions += prePromotionPawns != squaresType::none();
				}
				scoreType promotionValue{ scoreType::zero() };
				if (countPossiblePromotions >= 1)
				{
					constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
					promotionValue += singlePromotionsValue;
					if (countPossiblePromotions > 1)
						promotionValue += singlePromotionsValue;
				}
				constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
				size_t countCaptures{ 0 };
				const squaresType queens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()) };
				scoreType captureValue{ scoreType::zero() };
				for (const auto sq : queens)
				{
					constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) };
					captureValue += queenValue;
					countCaptures++;
					if (countCaptures >= 2)
						break;
				}
				if (countCaptures < 2)
				{
					const squaresType rooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()) };
					for (const auto sq : rooks)
					{
						constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) };
						captureValue += rookValue;
						countCaptures++;
						if (countCaptures >= 2)
							break;
					}
					if (countCaptures < 2)
					{
						const squaresType bishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto sq : bishops)
						{
							constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) };
							captureValue += bishopValue;
							countCaptures++;
							if (countCaptures >= 2)
								break;
						}
						if (countCaptures < 2)
						{
							const squaresType knights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()) };
							for (const auto sq : knights)
							{
								constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) };
								captureValue += knightValue;
								countCaptures++;
								if (countCaptures >= 2)
									break;
							}
							if (countCaptures < 2)
							{
								const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()) };
								for (const auto sq : pawns)
								{
									constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
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
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer()) };
				const squaresType promotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? rank7 : rank2) };
				size_t countPossiblePromotions{ promotionPawns.count() };
				if (countPossiblePromotions < 2)
				{
					const squaresType prePromotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? (rank7 | rank6) : (rank2 | rank3)) };
					countPossiblePromotions += prePromotionPawns != squaresType::none();
				}
				scoreType promotionValue{ scoreType::zero() };
				if (countPossiblePromotions >= 1)
				{
					constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
					promotionValue += singlePromotionsValue;
					if (countPossiblePromotions > 1)
						promotionValue += singlePromotionsValue;
				}
				constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
				size_t countCaptures{ 0 };
				const squaresType queens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()) };
				scoreType captureValue{ scoreType::zero() };
				for (const auto sq : queens)
				{
					constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) };
					captureValue += queenValue;
					countCaptures++;
					if (countCaptures >= 2)
						break;
				}
				if (countCaptures < 2)
				{
					const squaresType rooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()) };
					for (const auto sq : rooks)
					{
						constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) };
						captureValue += rookValue;
						countCaptures++;
						if (countCaptures >= 2)
							break;
					}
					if (countCaptures < 2)
					{
						const squaresType bishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto sq : bishops)
						{
							constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) };
							captureValue += bishopValue;
							countCaptures++;
							if (countCaptures >= 2)
								break;
						}
						if (countCaptures < 2)
						{
							const squaresType knights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()) };
							for (const auto sq : knights)
							{
								constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) };
								captureValue += knightValue;
								countCaptures++;
								if (countCaptures >= 2)
									break;
							}
							if (countCaptures < 2)
							{
								const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()) };
								for (const auto sq : pawns)
								{
									constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
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
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer()) };
				const squaresType promotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? rank7 : rank2) };
				size_t countPossiblePromotions{ promotionPawns.count() };
				if (countPossiblePromotions < 3)
				{
					const squaresType prePromotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? (rank7 | rank6) : (rank2 | rank3)) };
					countPossiblePromotions += prePromotionPawns.count();
					if (countPossiblePromotions < 2)
					{
						const squaresType prePrePromotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? (rank7 | rank6 | rank5) : (rank2 | rank3 | rank4)) };
						countPossiblePromotions += prePrePromotionPawns != squaresType::none();
					}
				}
				scoreType promotionValue{ scoreType::zero() };
				if (countPossiblePromotions >= 1)
				{
					constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
					promotionValue += singlePromotionsValue;
					if (countPossiblePromotions > 1)
					{
						promotionValue += singlePromotionsValue;
						if (countPossiblePromotions > 2)
						{
							promotionValue += singlePromotionsValue;
						}
					}
				}
				constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
				size_t countCaptures{ 0 };
				const squaresType queens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()) };
				scoreType captureValue{ scoreType::zero() };
				for (const auto sq : queens)
				{
					constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) };
					captureValue += queenValue;
					countCaptures++;
					if (countCaptures >= 3)
						break;
				}
				if (countCaptures < 3)
				{
					const squaresType rooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()) };
					for (const auto sq : rooks)
					{
						constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) };
						captureValue += rookValue;
						countCaptures++;
						if (countCaptures >= 3)
							break;
					}
					if (countCaptures < 3)
					{
						const squaresType bishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto sq : bishops)
						{
							constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) };
							captureValue += bishopValue;
							countCaptures++;
							if (countCaptures >= 3)
								break;
						}
						if (countCaptures < 3)
						{
							const squaresType knights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()) };
							for (const auto sq : knights)
							{
								constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) };
								captureValue += knightValue;
								countCaptures++;
								if (countCaptures >= 3)
									break;
							}
							if (countCaptures < 3)
							{
								const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()) };
								for (const auto sq : pawns)
								{
									constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
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
				const squaresType ownPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.movingPlayer()) };
				const squaresType promotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? rank7 : rank2) };
				size_t countPossiblePromotions{ promotionPawns.count() };
				if (countPossiblePromotions < 3)
				{
					const squaresType prePromotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? (rank7 | rank6) : (rank2 | rank3)) };
					countPossiblePromotions += prePromotionPawns.count();
					if (countPossiblePromotions < 2)
					{
						const squaresType prePrePromotionPawns{ ownPawns & (stack.movingPlayer() == whitePlayer ? (rank7 | rank6 | rank5) : (rank2 | rank3 | rank4)) };
						countPossiblePromotions += prePrePromotionPawns != squaresType::none();
					}
				}
				scoreType promotionValue{ scoreType::zero() };
				if (countPossiblePromotions >= 1)
				{
					constexpr const scoreType singlePromotionsValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) - static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
					promotionValue += singlePromotionsValue;
					if (countPossiblePromotions > 1)
					{
						promotionValue += singlePromotionsValue;
						if (countPossiblePromotions > 2)
						{
							promotionValue += singlePromotionsValue;
						}
					}
				}
				constexpr const scoreType positionalValue{ evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange + evaluatorType::MaxPositionChange };
				size_t countCaptures{ 0 };
				const squaresType queens{ stack.position().pieceOccupancy(queen) & stack.position().playerOccupancy(stack.nextPlayer()) };
				scoreType captureValue{ scoreType::zero() };
				for (const auto sq : queens)
				{
					constexpr const scoreType queenValue{ static_cast<scoreType>(boardType::materialValue(queen, whitePlayer)) };
					captureValue += queenValue;
					countCaptures++;
					if (countCaptures >= 3)
						break;
				}
				if (countCaptures < 3)
				{
					const squaresType rooks{ stack.position().pieceOccupancy(rook) & stack.position().playerOccupancy(stack.nextPlayer()) };
					for (const auto sq : rooks)
					{
						constexpr const scoreType rookValue{ static_cast<scoreType>(boardType::materialValue(rook, whitePlayer)) };
						captureValue += rookValue;
						countCaptures++;
						if (countCaptures >= 3)
							break;
					}
					if (countCaptures < 3)
					{
						const squaresType bishops{ stack.position().pieceOccupancy(bishop) & stack.position().playerOccupancy(stack.nextPlayer()) };
						for (const auto sq : bishops)
						{
							constexpr const scoreType bishopValue{ static_cast<scoreType>(boardType::materialValue(bishop, whitePlayer)) };
							captureValue += bishopValue;
							countCaptures++;
							if (countCaptures >= 3)
								break;
						}
						if (countCaptures < 3)
						{
							const squaresType knights{ stack.position().pieceOccupancy(knight) & stack.position().playerOccupancy(stack.nextPlayer()) };
							for (const auto sq : knights)
							{
								constexpr const scoreType knightValue{ static_cast<scoreType>(boardType::materialValue(knight, whitePlayer)) };
								captureValue += knightValue;
								countCaptures++;
								if (countCaptures >= 3)
									break;
							}
							if (countCaptures < 3)
							{
								const squaresType pawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(stack.nextPlayer()) };
								for (const auto sq : pawns)
								{
									constexpr const scoreType pawnValue{ static_cast<scoreType>(boardType::materialValue(pawn, whitePlayer)) };
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
				assert(false);
				return scoreType::zero();
			}
		}
		scoreType moveFutilityValue_Implementation(const movebitsType& move) const noexcept
		{
			if (motorType::move().isCapture(move))
			{
				const squareType captureSquare{ motorType::move().captureSquare(this->stack().position(),move) };
				const pieceType capturedPiece{ this->stack().position().getPiece(captureSquare) };
				const scoreType victimValue{ static_cast<scoreType>(boardType::materialValue(capturedPiece, whitePlayer)) };
				if (motorType::move().isPromotion(move))
				{
					const pieceType promotedPiece{ motorType::move().promotedPiece(move) };
					const scoreType promotionValue{ static_cast<scoreType>(boardType::materialValue(promotedPiece, whitePlayer)) };
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
					const scoreType promotionValue{ static_cast<scoreType>(boardType::materialValue(promotedPiece, whitePlayer)) };
					return promotionValue;
				}
				else
					return scoreType::zero();
			}
		}
	};
}