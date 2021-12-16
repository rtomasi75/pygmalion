namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class royalpieces :
		public set<typename DESCRIPTION_STATE::royalpieceType, royalpieces<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
	public:
		PYGMALION_INLINE constexpr explicit royalpieces(const typename set<typename DESCRIPTION_STATE::royalpieceType, royalpieces<DESCRIPTION_STATE>>::bitsType& bits) noexcept :
			set<typename DESCRIPTION_STATE::royalpieceType, royalpieces<DESCRIPTION_STATE>>(bits)
		{

		}
		PYGMALION_INLINE constexpr royalpieces(const royalpieces&) noexcept = default;
		PYGMALION_INLINE constexpr royalpieces(const royalpieceType royalpiece) noexcept :
			set<typename descriptorState::royalpieceType, royalpieces<descriptorState>>(royalpiece)
		{

		}
		PYGMALION_INLINE constexpr royalpieces(royalpieces&&) noexcept = default;
		PYGMALION_INLINE constexpr royalpieces& operator=(const royalpieces&) = default;
		PYGMALION_INLINE constexpr royalpieces& operator=(royalpieces&&) = default;
		PYGMALION_INLINE ~royalpieces() noexcept = default;
		std::string toString() const noexcept
		{
			std::stringstream result;
			if (!static_cast<bool>(*this))
				result << "-";
			else
			{
				for (const auto f : royalpieceType::range)
				{
					if ((*this)[f])
						result << f.toShortString();
				}
			}
			return result.str();
		}
		static bool parse(const std::string& text, size_t& pos, royalpieces& parsed) noexcept
		{
			size_t cnt{ pos };
			parsed.clear();
			if (text.length() <= cnt)
				return false;
			if (text[cnt] == '-')
			{
				cnt++;
				pos = cnt;
				return true;
			}
			else
			{
				bool bParsing = true;
				size_t len = 0;
				while (bParsing)
				{
					royalpieceType f;
					if (len > countFlags)
						return false;
					else if (text.length() <= cnt)
						bParsing = false;
					else if (royalpieceType::parse(text, cnt, f))
					{
						parsed |= f;
						len++;
					}
					else
						bParsing = false;
				}
				if (len > 0)
				{
					pos = cnt;
					return true;
				}
				else
					return false;
			}
		}
	};
}