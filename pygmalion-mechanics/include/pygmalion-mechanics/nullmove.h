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
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << nullmove::countBits << "bit@null";
			return sstr.str();
		}
		constexpr static typename nullmove::movedataType doMove_Implementation(boardType& position, const typename nullmove::movebitsType& moveBits) noexcept
		{
			return typename nullmove::movedataType();
		}
		constexpr static void undoMove_Implementation(boardType& position, const typename nullmove::movedataType& data, const playerType movingPlayer) noexcept
		{
		}
		constexpr static typename nullmove::movebitsType nullMove() noexcept
		{
			typename nullmove::movebitsType bits{ nullmove::movebitsType::zero() };
			return bits;
		}
		static bool parse_Implementation(const boardType& position, std::string& text, typename nullmove::movebitsType& moveBits) noexcept
		{
			if (text.length() >= 4)
			{
				if (parser::toLower(text.substr(0, 4)) == "null")
				{
					text = text.substr(4, text.length() - 4);
					moveBits = nullMove();
					return true;
				}
			}
			return false;
		}
		static std::string toString_Implementation(const boardType& position, const typename nullmove::movebitsType& moveBits) noexcept
		{
			return "null";
		}
	};
}