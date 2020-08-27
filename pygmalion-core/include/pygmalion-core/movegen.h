namespace pygmalion
{
	template<typename BOARD, size_t MAXMOVES, bool LEGALMOVES, typename MOVEDATA, typename INSTANCE>
	class movegen
	{
	public:
		using boardType = BOARD;
		using moveType = typename boardType::moveType;
		using instanceType = INSTANCE;
		using movedataType = MOVEDATA;
		using bitsType = typename boardType::bitsType;
		using playerType = typename boardType::player;
		using squareType = typename boardType::square;
		using pieceType = typename boardType::piece;
		using flagsType = typename boardType::flags;
		using gamestateType = typename boardType::gamestate;
		constexpr static int maxMoves{ MAXMOVES };
		using movelistType = typename boardType::stackType::movelistType;
		using indexType = typename movelistType::counterType;
		constexpr static size_t countPieces{ boardType::countPieces };
		constexpr static size_t countSquares{ boardType::countSquares };
		constexpr static size_t countPlayers{ boardType::countPlayers };
		constexpr static bool legalMovesOnly{ LEGALMOVES };
		using stackType = typename  boardType::stackType;
		static auto name() noexcept
		{
			return instanceType::name_Implementation();
		}
		static gamestateType earlyResult(const stackType& stack) noexcept
		{
			return instanceType::earlyResult_Implementation(stack);
		}
		static gamestateType lateResult(const stackType& stack) noexcept
		{
			return instanceType::lateResult_Implementation(stack);
		}
		static bool isMoveLegal(const stackType& stack, const moveType& move) noexcept
		{
			return instanceType::isMoveLegal_Implementation(stack, move);
		}
		static bool generateMoves(const stackType& stack, movelistType& moves, int& currentPass) noexcept
		{
			return instanceType::generateMoves_Implementation(stack, moves, currentPass);
		}
		static bool generateTacticalMoves(const stackType& stack, movelistType& moves, int& currentPass) noexcept
		{
			return instanceType::generateTacticalMoves_Implementation(stack, moves, currentPass);
		}
	};
}