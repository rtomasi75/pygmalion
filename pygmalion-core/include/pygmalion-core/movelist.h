namespace pygmalion
{
	template<typename MOVE, int MOVECOUNT>
	class movelist
	{
	public:
		constexpr static int maxMoveCount{ MOVECOUNT };
		using moveType = MOVE;
		using counterType = typename int_traits< requiredSignedBytes(maxMoveCount)>::STYPE;
	private:
		counterType m_MoveCount;
		std::array<moveType, maxMoveCount> m_Moves;
	public:
		void replace(const counterType idx, const moveType& move) noexcept
		{
			assert(idx <= (m_MoveCount + 1));
			assert(m_MoveCount < (maxMoveCount - 1));
			m_Moves[idx] = move;
			m_MoveCount = std::max(m_MoveCount, static_cast<counterType>(idx + 1));
		}
		void replace(const counterType idx, moveType&& move) noexcept
		{
			assert(idx <= (m_MoveCount + 1));
			assert(m_MoveCount < (maxMoveCount - 1));
			m_Moves[idx] = std::move(move);
			m_MoveCount = std::max(m_MoveCount, static_cast<counterType>(idx + 1));
		}
		void combine(const MOVE& move, const movelist& tail) noexcept
		{
			assert(tail.m_MoveCount < maxMoveCount);
			m_Moves[0] = move;
			for (counterType i = 0; i < tail.m_MoveCount; i++)
			{
				m_Moves[i + 1] = tail.m_Moves[i];
			}
			m_MoveCount = tail.m_MoveCount + 1;
		}
		movelist& operator=(const movelist&) = default;
		movelist(movelist<moveType, maxMoveCount>&&) noexcept = delete;
		movelist(const movelist<moveType, maxMoveCount>& other) noexcept :
			m_MoveCount(other.m_MoveCount)
		{
			for (counterType i = 0; i < m_MoveCount; i++)
				m_Moves[i] = other.m_Moves[i];
		}
		movelist() noexcept :
			m_MoveCount(0)
		{

		}
		~movelist() noexcept = default;
		counterType length() const noexcept
		{
			return m_MoveCount;
		}
		moveType operator[](const counterType idx) const noexcept
		{
			assert(idx < m_MoveCount);
			return m_Moves[idx];
		}
		void clear() noexcept
		{
			m_MoveCount = 0;
		}
		void add(const moveType& move) noexcept
		{
			assert(m_MoveCount < maxMoveCount);
			m_Moves[m_MoveCount++] = move;
		}
	};
}