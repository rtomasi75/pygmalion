namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename BOARD>
		class nullmoveMovedata
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
		public:
			PYGMALION_INLINE nullmoveMovedata() noexcept = default;
			PYGMALION_INLINE nullmoveMovedata(nullmoveMovedata&&) noexcept = default;
			PYGMALION_INLINE nullmoveMovedata(const nullmoveMovedata&) noexcept = default;
			PYGMALION_INLINE nullmoveMovedata& operator=(nullmoveMovedata&&) noexcept = default;
			PYGMALION_INLINE nullmoveMovedata& operator=(const nullmoveMovedata&) noexcept = default;
			PYGMALION_INLINE ~nullmoveMovedata() noexcept = default;
		};
	}

	template<typename BOARD>
	class nullmove :
		public move<BOARD, 0, detail::nullmoveMovedata<BOARD>, nullmove<BOARD>>
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		PYGMALION_INLINE constexpr nullmove() noexcept = default;
		PYGMALION_INLINE ~nullmove() noexcept = default;
		PYGMALION_INLINE constexpr nullmove(nullmove&&) noexcept = default;
		PYGMALION_INLINE constexpr nullmove(const nullmove&) noexcept = default;
		PYGMALION_INLINE constexpr nullmove& operator=(nullmove&&) noexcept = default;
		PYGMALION_INLINE constexpr nullmove& operator=(const nullmove&) noexcept = default;
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename nullmove::movedataType) << ":" << nullmove::countBits << "@null";
			return sstr.str();
		}
		PYGMALION_INLINE typename nullmove::movedataType doMove_Implementation(boardType& position, const typename nullmove::movebitsType moveBits, typename nullmove::movedataType& movedata) const noexcept
		{
			movedata = typename nullmove::movedataType();
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename nullmove::movedataType& data) const noexcept
		{
		}
		PYGMALION_INLINE typename nullmove::movebitsType create() const noexcept
		{
			constexpr const typename nullmove::movebitsType bits{ nullmove::movebitsType::zero() };
			return bits;
		}
		bool parse_Implementation(const boardType& position, const std::string& text, typename nullmove::movebitsType& moveBits, size_t& count) const noexcept
		{
			if (text.length() >= 4)
			{
				if (parser::toLower(text.substr(0, 4)) == "null")
				{
					count += 4;
					moveBits = create();
					return true;
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename nullmove::movebitsType moveBits) const noexcept
		{
			return "null";
		}
	};
}