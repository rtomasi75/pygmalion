namespace pygmalion::tictactoe
{
	class descriptor_dynamics :
		public pygmalion::descriptor_dynamics<motor, 9, 7, 0, 10>
	{
	public:
		static inline movetable<descriptor_dynamics> moveTable{ movetable<descriptor_dynamics>(0x0095,9) };
	};

	class generator :
		public pygmalion::generator<descriptor_dynamics, generator>
	{
	public:
		template<size_t PLAYER>
		using stackType = typename pygmalion::generator<descriptor_dynamics, generator>::stack<PLAYER>;
		using contextType = typename pygmalion::generator<descriptor_dynamics, generator>::context;
		template<size_t PLAYER>
		static bool isMoveLegal_Implementation(const stackType<PLAYER>& stack, const movebitsType& mv) noexcept
		{
			return !stack.position().isOccupied(moveType::extractSquare(mv));
		}
		template<size_t PLAYER>
		static bool isGeneratedMoveLegal_Implementation(const stackType<PLAYER>& stack, const movebitsType& mv) noexcept
		{
			return !stack.position().isOccupied(moveType::extractSquare(mv));
		}
		template<size_t PLAYER>
		static bool isMoveTactical_Implementation(const stackType<PLAYER>& stack, const movebitsType& mv) noexcept
		{
			return false;
		}
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept
		{
			std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ std::deque<std::shared_ptr<pygmalion::intrinsics::command>>() };
			return list;
		}
		template<size_t PLAYER>
		static void generateMoves_Implementation(const stageType stage, const stackType<PLAYER>& stack, movelistType& moves, const passType currentPass) noexcept
		{
			PYGMALION_ASSERT(stage == 0);
			PYGMALION_ASSERT(currentPass == 0);
			moves = moveTable[static_cast<typename squaresType::bitsType>(stack.position().totalOccupancy())];
		}
		template<size_t PLAYER>
		static std::string moveToString_Implementation(const stackType<PLAYER>& stack, const movebitsType moveBits, const size_t depth) noexcept
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
		static std::string passToString_Implementation(const stageType stage, const passType pass) noexcept
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
		template<size_t PLAYER>
		constexpr static bool isMoveCritical_Implementation(const stackType<PLAYER>& stack, const movebitsType& moveBits) noexcept
		{
			return false;
		}
		template<size_t PLAYER>
		constexpr static bool isPositionCritical_Implementation(const stackType<PLAYER>& stack) noexcept
		{
			return false;
		}
		template<size_t PLAYER>
		constexpr static scoreType makeSubjective(const scoreType score) noexcept
		{
			if constexpr (PLAYER == 0)
				return score;
			else
				return -score;
		}
		constexpr static size_t countMovegenStages_Implementation(const movegenPhase phase) noexcept
		{
			if (phase == movegenPhase::normal)
				return 1;
			else
				return 0;
		}
		constexpr static size_t countMovegenPasses_Implementation(const size_t stage) noexcept
		{
			return 0;
		}
		constexpr static size_t movegenStage_Implementation(const movegenPhase phase, const size_t stageIndex) noexcept
		{
			return 0;
		}
		constexpr static size_t countTotalMovegenStages_Implementation() noexcept
		{
			return 1;
		}
	};
}