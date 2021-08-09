namespace pygmalion::tictactoe
{
	class descriptor_dynamics :
		public pygmalion::descriptor_dynamics<motor, 9>
	{
	public:
		static inline movetable<descriptor_dynamics> moveTable{ movetable<descriptor_dynamics>(0x0095,9) };
	};

	class generator :
		public pygmalion::generator<descriptor_dynamics, generator>
	{
	public:
		using stackType = typename pygmalion::generator<descriptor_dynamics, generator>::stack;
		static bool isMoveLegal_Implementation(const stackType& stack, const movebitsType& mv) noexcept
		{
			return !stack.position().isOccupied(moveType::extractSquare(mv));
		}
		static std::deque<std::shared_ptr<pygmalion::intrinsics::command>> commandsImplementation() noexcept
		{
			std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ std::deque<std::shared_ptr<pygmalion::intrinsics::command>>() };
			return list;
		}

		static bool generateMoves_Implementation(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept
		{
			if (currentPass == 0)
			{
				moves = moveTable[static_cast<typename squaresType::bitsType>(stack.position().totalOccupancy())];
				currentPass++;
				return true;
			}
			else
				return false;
		}
		static bool generateTacticalMoves_Implementation(const stackType& stack, movelistType& moves, size_t& currentPass) noexcept
		{
			return false;
		}
		static std::string moveToString_Implementation(const stackType& stack, const movebitsType moveBits) noexcept
		{
			squareType sq = moveType::extractSquare(moveBits);
			auto file = sq.file();
			auto rank = sq.rank();
			std::string text{ "" };
			switch (file)
			{
			default:
				assert(false);
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
				assert(false);
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
	};
}