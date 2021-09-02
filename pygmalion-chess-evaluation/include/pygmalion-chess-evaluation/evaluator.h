namespace pygmalion::chess
{
	class descriptor_evaluation :
		public pygmalion::descriptor_evaluation<generator>
	{
	public:
	};

	class evaluator :
		public pygmalion::evaluator<descriptor_evaluation, evaluator>
	{
	public:
		constexpr static inline double Mobility{ 0.125 };
		constexpr static inline double Attack{ 0.125 };
		constexpr static inline double Control{ 0.25 };
	private:
		constexpr static inline scoreType MobilityFactor{ static_cast<scoreType>(Mobility / 64.0) };
		constexpr static inline scoreType AttackFactor{ static_cast<scoreType>(Attack / 64.0) };
		constexpr static inline scoreType ControlFactor{ static_cast<scoreType>(Control / 64.0) };
		constexpr static inline scoreType DeltaMobility{ static_cast<scoreType>(Mobility) };
		constexpr static inline scoreType DeltaAttack{ static_cast<scoreType>(Attack) };
		constexpr static inline scoreType DeltaControl{ static_cast<scoreType>(Control) };
		constexpr static inline size_t CountStages{ 3 };
		static inline scoreType Delta[]{ DeltaMobility + DeltaAttack + DeltaControl,DeltaAttack + DeltaControl,DeltaControl };
		static scoreType attack(const generatorType::stackType& stack) noexcept;
		static scoreType mobility(const generatorType::stackType& stack) noexcept;
		static scoreType control(const generatorType::stackType& stack) noexcept;
		constexpr static scoreType evaluationFunction(int i, const generatorType::stackType& stack) noexcept
		{
			switch (i)
			{
			default:
				assert(0);
				return scoreType::zero();
			case 0:
				return attack(stack);
			case 1:
				return mobility(stack);
			case 2:
				return control(stack);
			}
		}
	public:
		constexpr static scoreType aspirationWindowSize_Implementation(const size_t index) noexcept
		{
			constexpr const scoreType windows[]
			{
				static_cast<scoreType>(0.75 * 0.015625),
				static_cast<scoreType>(3.0 * 0.015625),
				static_cast<scoreType>(12.0 * 0.015625),
				static_cast<scoreType>(48.0 * 0.015625),
			};
			return windows[index];
		}
		constexpr static size_t countAspirationWindows_Implementation() noexcept
		{
			return 4;
		}
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept;
		template<bool LAZY>
		static gamestateType earlyResult_Implementation(const generatorType::stackType& stack, bool& allowStoreTT) noexcept
		{
			if constexpr (!LAZY)
			{
				if (stack.position().cumulation().reversiblePlies() >= 100)
				{
					allowStoreTT = false;
					return gamestateType::draw();
				}
			}
			if (stack.position().playerOccupancy(whitePlayer) == squaresType(stack.kingSquare(whitePlayer)))
			{
				if (stack.position().playerOccupancy(blackPlayer) == squaresType(stack.kingSquare(blackPlayer)))
					return gamestateType::draw();
				if (stack.position().playerOccupancy(blackPlayer) & (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen) | stack.position().pieceOccupancy(pawn)) == squaresType::none())
				{
					if ((stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(bishop)) == squaresType::none())
					{
						if ((stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(knight)).count() == 1)
						{
							allowStoreTT = true;
							return gamestateType::draw();
						}
					}
					if ((stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(knight)) == squaresType::none())
					{
						if ((stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(bishop)).count() == 1)
						{
							allowStoreTT = true;
							return gamestateType::draw();
						}
					}
				}
			}
			else if (stack.position().playerOccupancy(blackPlayer) == squaresType(stack.kingSquare(blackPlayer)))
			{
				if (stack.position().playerOccupancy(whitePlayer) & (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen) | stack.position().pieceOccupancy(pawn)) == squaresType::none())
				{
					if ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)) == squaresType::none())
					{
						if ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(knight)).count() == 1)
						{
							allowStoreTT = true;
							return gamestateType::draw();
						}
					}
					if ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(knight)) == squaresType::none())
					{
						if ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).count() == 1)
						{
							allowStoreTT = true;
							return gamestateType::draw();
						}
					}
				}
			}
			else if ((stack.position().pieceOccupancy(queen) | stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(knight) | stack.position().pieceOccupancy(pawn)) == squaresType::none())
			{
				if (((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).count() == 1) && ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).count() == 1))
				{
					const squareType whiteBishop{ *(stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).begin() };
					const squareType blackBishop{ *(stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(bishop)).begin() };
					if (whiteBishop.isDark() == blackBishop.isDark())
					{
						allowStoreTT = true;
						return gamestateType::draw();
					}
				}
			}
			if constexpr (!LAZY)
			{
				if (stack.occurs(stack.position(), 2, 4, 4))
				{
					allowStoreTT = false;
					return gamestateType::draw();
				}
			}
			return gamestateType::open();
		}
		static gamestateType lateResult_Implementation(const typename generatorType::stackType& stack) noexcept;
		static scoreType evaluate_Implementation(const scoreType alpha, const scoreType beta, const generatorType::stackType& stack) noexcept;
	};
}