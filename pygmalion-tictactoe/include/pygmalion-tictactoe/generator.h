namespace pygmalion::tictactoe
{
	class generator :
		public pygmalion::generator<descriptor_generator, generator>
	{
	private:
#if !defined(PYGMALION_CPU_BMI2)
		static inline movemagic<descriptor_generator> m_Magic{ movemagic<descriptor_generator>(movemagicinfo(), 0x000b) };
#else
		static inline movemagic<descriptor_generator> m_Magic{ movemagic<descriptor_generator>(movemagicinfo()) };
#endif
	public:
		static auto& magic() noexcept
		{
			return m_Magic;
		}
		static std::string name_Implementation() noexcept
		{
			return "TicTacToe ver. 1.0";
		}

		static bool isMoveLegal_Implementation(const stack& stack, const moveType& mv) noexcept
		{
			return !stack.position().isOccupied(mv.square(0));
		}

		static bool generateMoves_Implementation(const stack& stack, movelistType& moves, int& currentPass) noexcept
		{
			if (currentPass == 0)
			{
				moves = m_Magic[static_cast<typename squaresType::bitsType>(stack.position().totalOccupancy())];
				currentPass++;
				return true;
			}
			else
				return false;
		}
		static bool generateTacticalMoves_Implementation(const stack& stack, movelistType& moves, int& currentPass) noexcept
		{
			return false;
		}

		using stackType = stack;
	};
}