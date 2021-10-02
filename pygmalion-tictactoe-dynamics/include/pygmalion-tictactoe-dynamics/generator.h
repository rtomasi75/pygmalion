namespace pygmalion::tictactoe
{
	class descriptor_dynamics :
		public pygmalion::descriptor_dynamics<motor, 9, 7, 0, 10, 1, 0, 0, 0, 0, 0>
	{
	public:
		static inline movetable<descriptor_dynamics> moveTable{ movetable<descriptor_dynamics>(0x0095,9) };
	};

	class generator :
		public pygmalion::generator<descriptor_dynamics, generator>
	{
	public:
		using stackType = typename pygmalion::generator<descriptor_dynamics, generator>::stack;
		using contextType = typename pygmalion::generator<descriptor_dynamics, generator>::context;
		static bool isMoveLegal_Implementation(const stackType& stack, const movebitsType& mv) noexcept
		{
			return !stack.position().isOccupied(moveType::extractSquare(mv));
		}
		static bool isGeneratedMoveLegal_Implementation(const stackType& stack, const movebitsType& mv) noexcept
		{
			return !stack.position().isOccupied(moveType::extractSquare(mv));
		}
		static bool isMoveTactical_Implementation(const stackType& stack, const movebitsType& mv) noexcept
		{
			return false;
		}
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept
		{
			std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ std::deque<std::shared_ptr<pygmalion::intrinsics::command>>() };
			return list;
		}
		static void generateMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			if (currentPass == 0)
			{
				moves = moveTable[static_cast<typename squaresType::bitsType>(stack.position().totalOccupancy())];
			}
			else
				PYGMALION_ASSERT(0);
		}
		static void generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			PYGMALION_ASSERT(0);
		}
		static void generateCriticalMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			PYGMALION_ASSERT(0);
		}
		static void generateQuietCriticalMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			PYGMALION_ASSERT(0);
		}
		static void generateCriticalEvasionMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			PYGMALION_ASSERT(0);
		}
		static void generateTacticalCriticalEvasionMoves_Implementation(const stackType& stack, movelistType& moves, const passType currentPass) noexcept
		{
			PYGMALION_ASSERT(0);
		}
		static std::string moveToString_Implementation(const stackType& stack, const movebitsType moveBits, const size_t depth) noexcept
		{
			squareType sq = moveType::extractSquare(moveBits);
			auto file = sq.file();
			auto rank = sq.rank();
			std::string text{ "" };
			switch (file)
			{
			default:
				PYGMALION_UNREACHABLE;
				break;
			case 0:
				text += "a";
				break;
			case 1:
				text += "b";
				break;
			case 2:
				text += "c";
				break;
			}
			switch (rank)
			{
			default:
				PYGMALION_UNREACHABLE;
				break;
			case 0:
				text += "1";
				break;
			case 1:
				text += "2";
				break;
			case 2:
				text += "3";
				break;
			}
			return text;
		}
		static std::string passToString_Implementation(const passType pass) noexcept
		{
			return "standard";
		}
		static std::string tacticalPassToString_Implementation(const passType tacticalPass) noexcept
		{
			return "standard tactical";
		}
		static std::string tacticalCriticalEvasionPassToString_Implementation(const passType tacticalPass) noexcept
		{
			return "standard tactical critical evasion";
		}
		static std::string criticalPassToString_Implementation(const passType criticalPass) noexcept
		{
			return "standard critical";
		}
		static std::string criticalEvasionPassToString_Implementation(const passType criticalPass) noexcept
		{
			return "standard critical evasion";
		}
		static std::string quietCriticalPassToString_Implementation(const passType quietCriticalPass) noexcept
		{
			return "standard quiet critical";
		}
		constexpr static size_t countMoveBuckets_Implementation() noexcept
		{
			return countSquares;
		}
		constexpr static size_t moveBucket_Implementation(const boardType& position, const movebitsType& mv) noexcept
		{
			const squareType sq{ moveType::extractSquare(mv) };
			return static_cast<size_t>(sq);
		}
		constexpr static bool hasNullMove_Implementation() noexcept
		{
			return false;
		}
		constexpr static movebitsType nullMove_Implementation() noexcept
		{
			return movebitsType(0);
		}
		constexpr static bool isMoveCritical_Implementation(const stackType& stack, const movebitsType& moveBits) noexcept
		{
			return false;
		}
		constexpr static bool isPositionCritical_Implementation(const stackType& stack) noexcept
		{
			return false;
		}
	};
}