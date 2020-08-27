namespace pygmalion::tictactoe
{
	class patterns
	{
	public:
		using boardType = pygmalion::tictactoe::board;
		using bitsType = typename boardType::bitsType;
		constexpr static int lineCount = 8;
	private:
		bitsType m_Lines[lineCount];
		constexpr patterns() noexcept :
			m_Lines{ bitsType(0), bitsType(0), bitsType(0), bitsType(0), bitsType(0), bitsType(0), bitsType(0), bitsType(0) }
		{
			auto current = 0;
			for (int rank = 0; rank < 3; rank++)
			{
				for (int file = 0; file < 3; file++)
				{
					m_Lines[current].setBit(rank * 3 + file);
				}
				current++;
			}
			for (int file = 0; file < 3; file++)
			{
				for (int rank = 0; rank < 3; rank++)
				{
					m_Lines[current].setBit(rank * 3 + file);
				}
				current++;
			}
			for (int idx = 0; idx < 3; idx++)
			{
				m_Lines[current].setBit(idx * 3 + idx);
				m_Lines[current + 1].setBit(idx * 3 + 2 - idx);
			}
		}
		~patterns() noexcept = default;
		static patterns m_Singleton;
	public:
		static auto line(const int idx)  noexcept
		{
			assert(idx >= 0);
			assert(idx < lineCount);
			return m_Singleton.m_Lines[idx];
		}
	};
}