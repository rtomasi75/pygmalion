namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename BOARD>
		class nextplayermoveMovedata :
			public pygmalion::mechanics::movedataBase<BOARD>
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			playerType m_MovingPlayer;
		public:
			PYGMALION_INLINE playerType movingPlayer() const noexcept
			{
				return m_MovingPlayer;
			}
			PYGMALION_INLINE nextplayermoveMovedata(const playerType p) noexcept :
				m_MovingPlayer{ p }
			{}
			PYGMALION_INLINE nextplayermoveMovedata() noexcept = default;
			PYGMALION_INLINE nextplayermoveMovedata(nextplayermoveMovedata&&) noexcept = default;
			PYGMALION_INLINE nextplayermoveMovedata(const nextplayermoveMovedata&) noexcept = default;
			PYGMALION_INLINE nextplayermoveMovedata& operator=(nextplayermoveMovedata&&) noexcept = default;
			PYGMALION_INLINE nextplayermoveMovedata& operator=(const nextplayermoveMovedata&) noexcept = default;
			PYGMALION_INLINE ~nextplayermoveMovedata() noexcept = default;
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
		PYGMALION_INLINE constexpr nextplayermove() noexcept = default;
		PYGMALION_INLINE ~nextplayermove() noexcept = default;
		PYGMALION_INLINE constexpr nextplayermove(nextplayermove&&) noexcept = default;
		PYGMALION_INLINE constexpr nextplayermove(const nextplayermove&) noexcept = default;
		PYGMALION_INLINE constexpr nextplayermove& operator=(nextplayermove&&) noexcept = default;
		PYGMALION_INLINE constexpr nextplayermove& operator=(const nextplayermove&) noexcept = default;
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename nextplayermove::movedataType) << ":" << nextplayermove::countBits << "@nextplayer";
			return sstr.str();
		}
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename nextplayermove::movebitsType moveBits, typename nextplayermove::movedataType& movedata) const noexcept
		{
			movedata = typename nextplayermove::movedataType(position.movingPlayer()++);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename nextplayermove::movedataType& data) const noexcept
		{
			position.movingPlayer() = data.movingPlayer();
		}
		PYGMALION_INLINE typename nextplayermove::movebitsType create() const noexcept
		{
			constexpr const typename nextplayermove::movebitsType bits{ nextplayermove::movebitsType::zero() };
			return bits;
		}
		bool parse_Implementation(const boardType& position, const std::string& text, typename nextplayermove::movebitsType& moveBits, size_t& count) const noexcept
		{
			if (text.length() >= 1)
			{
				if (text[0] == '+')
				{
					count++;
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