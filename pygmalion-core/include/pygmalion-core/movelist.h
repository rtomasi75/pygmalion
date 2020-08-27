namespace pygmalion
{
	template<typename ITEM, int MAXLENGTH>
	class list
	{
	public:
		constexpr static int maxLength{ MAXLENGTH };
		using itemType = ITEM;
		using counterType = typename int_traits< requiredSignedBytes(maxLength + 1)>::STYPE;
	private:
		std::array<itemType, maxLength> m_Items;
		counterType m_Length;
	public:
		void replace(const counterType idx, const itemType& item) noexcept
		{
			assert(idx <= (m_Length + 1));
			assert(m_Length < (maxLength - 1));
			m_Items[idx] = item;
			m_Length = std::max(m_Length, static_cast<counterType>(idx + 1));
		}
		void combine(const itemType& item, const list& tail) noexcept
		{
			assert(tail.m_Length < maxLength);
			m_Items[0] = item;
			for (counterType i = 0; i < tail.m_Length; i++)
			{
				m_Items[i + 1] = tail.m_Items[i];
			}
			m_Length = tail.m_Length + 1;
		}
		list& operator=(const list&) = default;
		list(list&&) noexcept = delete;
		list(const list& other) noexcept :
			m_Length(other.m_Length)
		{
			for (counterType i = 0; i < m_Length; i++)
				m_Items[i] = other.m_Items[i];
		}
		list() noexcept :
			m_Length(0)
		{

		}
		~list() noexcept = default;
		counterType length() const noexcept
		{
			return m_Length;
		}
		const itemType& operator[](const counterType idx) const noexcept
		{
			assert(idx < m_Length);
			return m_Items[idx];
		}
		void clear() noexcept
		{
			m_Length = 0;
		}
		void add(const itemType& item) noexcept
		{
			assert(m_Length < maxLength);
			m_Items[m_Length++] = item;
		}
	};
}