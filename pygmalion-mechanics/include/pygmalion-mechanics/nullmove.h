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
			constexpr nullmoveMovedata() noexcept = default;
			constexpr nullmoveMovedata(nullmoveMovedata&&) noexcept = default;
			constexpr nullmoveMovedata(const nullmoveMovedata&) noexcept = default;
			constexpr nullmoveMovedata& operator=(nullmoveMovedata&&) noexcept = default;
			constexpr nullmoveMovedata& operator=(const nullmoveMovedata&) noexcept = default;
			~nullmoveMovedata() noexcept = default;
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
		constexpr nullmove() noexcept = default;
		~nullmove() noexcept = default;
		constexpr nullmove(nullmove&&) noexcept = default;
		constexpr nullmove(const nullmove&) noexcept = default;
		constexpr nullmove& operator=(nullmove&&) noexcept = default;
		constexpr nullmove& operator=(const nullmove&) noexcept = default;
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename nullmove::movedataType) << ":" << nullmove::countBits << "@null";
			return sstr.str();
		}
		constexpr typename nullmove::movedataType doMove_Implementation(boardType& position, const typename nullmove::movebitsType& moveBits) const noexcept
		{
			return typename nullmove::movedataType();
		}
		constexpr void undoMove_Implementation(boardType& position, const typename nullmove::movedataType& data) const noexcept
		{
		}
		constexpr typename nullmove::movebitsType create() const noexcept
		{
			typename nullmove::movebitsType bits{ nullmove::movebitsType::zero() };
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename nullmove::movebitsType& moveBits) const noexcept
		{
			if (text.length() >= 4)
			{
				if (parser::toLower(text.substr(0, 4)) == "null")
				{
					text = text.substr(4, text.length() - 4);
					moveBits = create();
					return true;
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename nullmove::movebitsType& moveBits) const noexcept
		{
			return "null";
		}
	};
}