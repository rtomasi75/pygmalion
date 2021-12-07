namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class piecemask :
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
		using maskType = uint_t<countPieces, false>;
	private:
		maskType m_Mask;
		constexpr static const inline maskType m_InitialValue{ maskType(0) };
	public:
		PYGMALION_INLINE constexpr size_t toIndex() const noexcept
		{
			return static_cast<size_t>(m_Mask);
		}
		PYGMALION_INLINE constexpr piecemask(const maskType& bits) noexcept :
			m_Mask{ bits }
		{

		}
		PYGMALION_INLINE constexpr piecemask(maskType&& bits) noexcept :
			m_Mask{ bits }
		{

		}
		PYGMALION_INLINE constexpr operator maskType() const noexcept
		{
			return m_Mask;
		}
		PYGMALION_INLINE constexpr piecemask(const piecemask&) noexcept = default;
		PYGMALION_INLINE constexpr piecemask(piecemask&&) noexcept = default;
		PYGMALION_INLINE constexpr piecemask() noexcept :
			m_Mask{ m_InitialValue }
		{
		}
		PYGMALION_INLINE constexpr piecemask& operator=(piecemask&&) noexcept = default;
		PYGMALION_INLINE constexpr piecemask& operator=(const piecemask&) noexcept = default;
		PYGMALION_INLINE constexpr void clearPiece(const pieceType pc) noexcept
		{
			return m_Mask.clear(static_cast<size_t>(pc));
		}
		PYGMALION_INLINE constexpr void setPiece(const pieceType pc) noexcept
		{
			return m_Mask.set(static_cast<size_t>(pc));
		}
		PYGMALION_INLINE constexpr void setPiece(const pieceType pc, bool bSet) noexcept
		{
			return m_Mask.check(static_cast<size_t>(pc), bSet);
		}
		PYGMALION_INLINE constexpr bool getPiece(const pieceType pc) const noexcept
		{
			return m_Mask[static_cast<size_t>(pc)];
		}
		PYGMALION_INLINE constexpr void clear() noexcept
		{
			m_Mask = m_InitialValue;
		}
		struct iteratorRange
		{
		private:
			size_t m_Current;
		public:
			typedef piecemask value_type;
			typedef std::ptrdiff_t difference_type;
			typedef piecemask* pointer;
			typedef piecemask& reference;
			typedef std::input_iterator_tag iterator_category;
			PYGMALION_INLINE constexpr iteratorRange(const size_t& start) noexcept :
				m_Current{ start }
			{

			}
			PYGMALION_INLINE ~iteratorRange() noexcept = default;
			PYGMALION_INLINE constexpr auto operator++(int) noexcept
			{
				iterator ret(m_Current);
				++(*this);
				return std::move(ret);
			}
			PYGMALION_INLINE constexpr iteratorRange& operator++() noexcept
			{
				++m_Current;
				return *this;
			}
			PYGMALION_INLINE constexpr value_type operator*() const noexcept
			{
				return piecemask(static_cast<typename piecemask::maskType>(m_Current));
			}
			PYGMALION_INLINE constexpr bool operator==(const iteratorRange& other) const noexcept
			{
				return m_Current == other.m_Current;
			}
			PYGMALION_INLINE constexpr bool operator!=(const iteratorRange& other) const noexcept
			{
				return m_Current != other.m_Current;
			}
		};
		struct piecemaskRange
		{
		public:
			PYGMALION_INLINE constexpr piecemaskRange() noexcept = default;
			PYGMALION_INLINE ~piecemaskRange() noexcept = default;
			PYGMALION_INLINE constexpr auto begin() const noexcept
			{
				return iteratorRange(0);
			}
			PYGMALION_INLINE constexpr auto end() const noexcept
			{
				constexpr iteratorRange endValue{ iteratorRange(1 << countPieces) };
				return endValue;
			}
		};
		constexpr static piecemaskRange range{ piecemaskRange() };
		class iterator
		{
			friend class piecemask;
		public:
			using value_type = pieceType;
		private:
			typename maskType::iterator m_Iterator;
			PYGMALION_INLINE constexpr iterator(const typename maskType::iterator& it) noexcept :
				m_Iterator{ it }
			{
			}
		public:
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::input_iterator_tag;
			PYGMALION_INLINE constexpr iterator(const iterator&) noexcept = default;
			PYGMALION_INLINE ~iterator() noexcept = default;
			PYGMALION_INLINE constexpr iterator&& operator++(int) noexcept
			{
				iterator ret(m_Iterator);
				++(*this);
				return std::move(ret);
			}
			PYGMALION_INLINE constexpr iterator& operator++() noexcept
			{
				++m_Iterator;
				return *this;
			}
			PYGMALION_INLINE constexpr value_type operator*() const noexcept
			{
				return static_cast<value_type>(*m_Iterator);
			}
			PYGMALION_INLINE constexpr bool operator==(const iterator& other) const noexcept
			{
				return m_Iterator == other.m_Iterator;
			}
			PYGMALION_INLINE constexpr bool operator!=(const iterator& other) const noexcept
			{
				return m_Iterator != other.m_Iterator;
			}
		};
		constexpr static piecemask none() noexcept
		{
			return piecemask(maskType::zero());
		}
		constexpr static piecemask all() noexcept
		{
			return ~none();
		}
		PYGMALION_INLINE constexpr piecemask operator|(const piecemask other) const noexcept
		{
			const maskType mask{ m_Mask | other.m_Mask };
			return piecemask(std::move(mask));
		}
		PYGMALION_INLINE constexpr piecemask operator-(const piecemask other) const noexcept
		{
			return piecemask(m_Mask & ~other.m_Mask);
		}
		PYGMALION_INLINE constexpr piecemask operator&(const piecemask other) const noexcept
		{
			return piecemask(m_Mask & other.m_Mask);
		}
		PYGMALION_INLINE constexpr piecemask operator^(const piecemask other) const noexcept
		{
			return piecemask(m_Mask ^ other.m_Mask);
		}
		PYGMALION_INLINE constexpr piecemask operator~() const noexcept
		{
			return piecemask(~m_Mask);
		}
		PYGMALION_INLINE constexpr piecemask& operator|=(const piecemask other) noexcept
		{
			m_Mask |= other.m_Mask;
			return *this;
		}
		PYGMALION_INLINE constexpr piecemask& operator-=(const piecemask other) noexcept
		{
			m_Mask &= ~other.m_Mask;
			return *this;
		}
		PYGMALION_INLINE constexpr piecemask& operator&=(const piecemask other) noexcept
		{
			m_Mask &= other.m_Mask;
			return *this;
		}
		PYGMALION_INLINE constexpr piecemask& operator^=(const piecemask other) noexcept
		{
			m_Mask ^= other.m_Mask;
			return *this;
		}
		PYGMALION_INLINE constexpr piecemask& operator|=(const pieceType pc) noexcept
		{
			m_Mask.set(static_cast<typename pieceType::baseType>(pc));
			return *this;
		}
		PYGMALION_INLINE constexpr piecemask& operator&=(const pieceType pc) noexcept
		{
			m_Mask &= maskType::setMask(static_cast<typename pieceType::baseType>(pc));
			return *this;
		}
		PYGMALION_INLINE constexpr piecemask& operator-=(const pieceType pc) noexcept
		{
			m_Mask.clear(static_cast<typename pieceType::baseType>(pc));
			return *this;
		}
		PYGMALION_INLINE constexpr piecemask& operator^=(const pieceType pc) noexcept
		{
			m_Mask.toggle(static_cast<typename pieceType::baseType>(pc));
			return *this;
		}
		PYGMALION_INLINE constexpr auto begin() const noexcept
		{
			return iterator(m_Mask.begin());
		}
		PYGMALION_INLINE constexpr auto end() const noexcept
		{
			return iterator(m_Mask.end());
		}
		PYGMALION_INLINE constexpr auto counter() const noexcept
		{
			return counterType(*this);
		}
		PYGMALION_INLINE size_t count() const noexcept
		{
			return m_Mask.populationCount();
		}
	};

}