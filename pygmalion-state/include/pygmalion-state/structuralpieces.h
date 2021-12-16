namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE>
	class structuralpieces :
		public set<typename DESCRIPTION_STATE::structuralpieceType, structuralpieces<DESCRIPTION_STATE>>,
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
	public:
		PYGMALION_INLINE constexpr explicit structuralpieces(const typename set<typename DESCRIPTION_STATE::structuralpieceType, structuralpieces<DESCRIPTION_STATE>>::bitsType& bits) noexcept :
			set<typename DESCRIPTION_STATE::structuralpieceType, structuralpieces<DESCRIPTION_STATE>>(bits)
		{

		}
		PYGMALION_INLINE constexpr structuralpieces(const structuralpieces&) noexcept = default;
		PYGMALION_INLINE constexpr structuralpieces(const structuralpieceType structuralpiece) noexcept :
			set<typename descriptorState::structuralpieceType, structuralpieces<descriptorState>>(structuralpiece)
		{

		}
		PYGMALION_INLINE constexpr structuralpieces(structuralpieces&&) noexcept = default;
		PYGMALION_INLINE constexpr structuralpieces& operator=(const structuralpieces&) = default;
		PYGMALION_INLINE constexpr structuralpieces& operator=(structuralpieces&&) = default;
		PYGMALION_INLINE ~structuralpieces() noexcept = default;
		std::string toString() const noexcept
		{
			std::stringstream result;
			if (!static_cast<bool>(*this))
				result << "-";
			else
			{
				for (const auto f : structuralpieceType::range)
				{
					if ((*this)[f])
						result << f.toShortString();
				}
			}
			return result.str();
		}
		static bool parse(const std::string& text, size_t& pos, structuralpieces& parsed) noexcept
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
					structuralpieceType f;
					if (len > countFlags)
						return false;
					else if (text.length() <= cnt)
						bParsing = false;
					else if (structuralpieceType::parse(text, cnt, f))
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