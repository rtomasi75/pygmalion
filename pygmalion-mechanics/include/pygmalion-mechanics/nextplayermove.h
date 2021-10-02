namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename BOARD>
		class nextplayermoveMovedata
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			playerType m_MovingPlayer;
		public:
			constexpr playerType movingPlayer() const noexcept
			{
				return m_MovingPlayer;
			}
			constexpr nextplayermoveMovedata(const playerType p) noexcept :
				m_MovingPlayer{ p }
			{}
			constexpr nextplayermoveMovedata() noexcept = default;
			constexpr nextplayermoveMovedata(nextplayermoveMovedata&&) noexcept = default;
			constexpr nextplayermoveMovedata(const nextplayermoveMovedata&) noexcept = default;
			constexpr nextplayermoveMovedata& operator=(nextplayermoveMovedata&&) noexcept = default;
			constexpr nextplayermoveMovedata& operator=(const nextplayermoveMovedata&) noexcept = default;
			~nextplayermoveMovedata() noexcept = default;
		};
	}

	template<typename BOARD>
	class nextplayermove :
		public move<BOARD, 0, detail::nextplayermoveMovedata<BOARD>, nextplayermove<BOARD>>
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr nextplayermove() noexcept = default;
		~nextplayermove() noexcept = default;
		constexpr nextplayermove(nextplayermove&&) noexcept = default;
		constexpr nextplayermove(const nextplayermove&) noexcept = default;
		constexpr nextplayermove& operator=(nextplayermove&&) noexcept = default;
		constexpr nextplayermove& operator=(const nextplayermove&) noexcept = default;
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename nextplayermove::movedataType) << ":" << nextplayermove::countBits << "@nextplayer";
			return sstr.str();
		}
		constexpr typename nextplayermove::movedataType doMove_Implementation(boardType& position, const typename nextplayermove::movebitsType moveBits) const noexcept
		{
			return typename nextplayermove::movedataType(position.movingPlayer()++);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename nextplayermove::movedataType& data) const noexcept
		{
			position.movingPlayer() = data.movingPlayer();
		}
		constexpr typename nextplayermove::movebitsType create() const noexcept
		{
			constexpr const typename nextplayermove::movebitsType bits{ nextplayermove::movebitsType::zero() };
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename nextplayermove::movebitsType& moveBits) const noexcept
		{
			if (text.length() >= 1)
			{
				if (text[0] == '+')
				{
					text = text.substr(1, text.length() - 1);
					moveBits = create();
					return true;
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename nextplayermove::movebitsType moveBits) const noexcept
		{
			return "+";
		}
	};
}