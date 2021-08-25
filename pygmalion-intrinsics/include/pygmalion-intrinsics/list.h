namespace pygmalion
{
	namespace detail
	{
		template<size_t COUNT_BYTES>
		class list_traits
		{
		public:
			using UTYPE = std::uintmax_t;
			using STYPE = std::intmax_t;
		};

		template<>
		class list_traits<1>
		{
		public:
			using UTYPE = std::uint8_t;
			using STYPE = std::int8_t;
		};

		template<>
		class list_traits<2>
		{
		public:
			using UTYPE = std::uint16_t;
			using STYPE = std::int16_t;
		};

		template<>
		class list_traits<3>
		{
		public:
			using UTYPE = std::uint32_t;
			using STYPE = std::int32_t;
		};

		template<>
		class list_traits<4>
		{
		public:
			using UTYPE = std::uint32_t;
			using STYPE = std::int32_t;
		};

		template<>
		class list_traits<5>
		{
		public:
			using UTYPE = std::uint64_t;
			using STYPE = std::int64_t;
		};

		template<>
		class list_traits<6>
		{
		public:
			using UTYPE = std::uint64_t;
			using STYPE = std::int64_t;
		};

		template<>
		class list_traits<7>
		{
		public:
			using UTYPE = std::uint64_t;
			using STYPE = std::int64_t;
		};

		template<>
		class list_traits<8>
		{
		public:
			using UTYPE = std::uint64_t;
			using STYPE = std::int64_t;
		};
	}
	template<typename ITEM, int MAXLENGTH>
	class list
	{
	private:
		constexpr static size_t requiredSignedBytes(const std::uintmax_t number) noexcept
		{
			if (number >= (size_t(1) << 31))
			{
				assert(sizeof(size_t) > 4);
				return 8;
			}
			if (number >= (size_t(1) << 15))
				return 4;
			if (number >= (size_t(1) << 7))
				return 2;
			return 1;
		}
	public:
		constexpr static int maxLength{ MAXLENGTH };
		using itemType = ITEM;
		using counterType = typename detail::list_traits<requiredSignedBytes(maxLength + 1)>::STYPE;
	private:
		std::array<itemType, maxLength> m_Items;
		counterType m_Length;
	public:
		ITEM* ptr() noexcept
		{
			return &m_Items[0];
		}
		void replace(const counterType idx, const itemType& item) noexcept
		{
			assert(idx <= (m_Length + 1));
			assert(m_Length < (maxLength - 1));
			m_Items[idx] = item;
			m_Length = std::max(m_Length, static_cast<counterType>(idx + 1));
		}
		void replace(const counterType idx, itemType&& item) noexcept
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
		void combine(const list& head, const list& tail) noexcept
		{
			assert(tail.m_Length + head.m_Length <= maxLength);
			for (counterType i = 0; i < tail.m_Length; i++)
			{
				m_Items[i] = head.m_Items[i];
			}
			for (counterType i = 0; i < tail.m_Length; i++)
			{
				m_Items[i + head.m_Length] = tail.m_Items[i];
			}
			m_Length = tail.m_Length + head.m_Length;
		}
		bool contains(const itemType& item) const noexcept
		{
			for (counterType i = 0; i < m_Length; i++)
			{
				if (m_Items[i] == item)
					return true;
			}
			return false;
		}
		void combine(const itemType& item, list&& tail) noexcept
		{
			assert(tail.m_Length < maxLength);
			m_Items[0] = item;
			for (counterType i = 0; i < tail.m_Length; i++)
			{
				m_Items[i + 1] = std::move(tail.m_Items[i]);
			}
			m_Length = tail.m_Length + 1;
		}
		list& operator=(const list& other) noexcept
		{
			m_Length = other.m_Length;
			for (counterType i = 0; i < m_Length; i++)
				m_Items[i] = other.m_Items[i];
			return *this;
		}
		list& operator=(list&& other) noexcept
		{
			m_Length = std::move(other.m_Length);
			for (counterType i = 0; i < m_Length; i++)
				m_Items[i] = std::move(other.m_Items[i]);
			return *this;
		}
		list(list&& other) noexcept :
			m_Length(std::move(other.m_Length))
		{
			for (counterType i = 0; i < m_Length; i++)
				m_Items[i] = std::move(other.m_Items[i]);
		}
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
		list(const itemType& item) noexcept :
			m_Length(1)
		{
			m_Items[0] = item;
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
		void add(itemType&& item) noexcept
		{
			assert(m_Length < maxLength);
			m_Items[m_Length++] = std::move(item);
		}
	};
}