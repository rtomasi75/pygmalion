namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class flags :
		public set<typename DESCRIPTION_STATE::flagType, flags<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
	public:
		PYGMALION_INLINE constexpr explicit flags(const typename set<typename DESCRIPTION_STATE::flagType, flags<DESCRIPTION_STATE>>::bitsType& bits) noexcept :
			set<typename DESCRIPTION_STATE::flagType, flags<DESCRIPTION_STATE>>(bits)
		{

		}
		PYGMALION_INLINE constexpr flags(const flags&) noexcept = default;
		PYGMALION_INLINE constexpr flags(const flagType flag) noexcept :
			set<typename descriptorState::flagType, flags<descriptorState>>(flag)
		{

		}
		PYGMALION_INLINE constexpr flags(flags&&) noexcept = default;
		PYGMALION_INLINE constexpr flags& operator=(const flags&) = default;
		PYGMALION_INLINE constexpr flags& operator=(flags&&) = default;
		PYGMALION_INLINE ~flags() noexcept = default;
		std::string toString() const noexcept
		{
			std::stringstream result;
			if (!static_cast<bool>(*this))
				result << "-";
			else
			{
				for (const auto f : flagType::range)
				{
					if ((*this)[f])
						result << f.toShortString();
				}
			}
			return result.str();
		}
		static bool parse(const std::string& text, size_t& pos, flags& parsed) noexcept
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
					flagType f;
					if (len > countFlags)
						return false;
					else if (text.length() <= cnt)
						bParsing = false;
					else if (flagType::parse(text, cnt, f))
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