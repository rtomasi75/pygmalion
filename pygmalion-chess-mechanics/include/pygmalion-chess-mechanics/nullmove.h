namespace pygmalion::chess
{
	namespace detail
	{
		class nullmoveMovedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			uint_t<countFlags, false> m_OldFlags;
			std::uint16_t m_ReversiblePlies{ 0 };
		public:
			constexpr std::uint16_t reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			constexpr const uint_t<countFlags, false>& oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr nullmoveMovedata(const uint_t<countFlags, false>& oldFlags_, const std::uint16_t reversiblePlies_) noexcept :
				m_OldFlags{ oldFlags_ },
				m_ReversiblePlies{ reversiblePlies_ }
			{}
			constexpr nullmoveMovedata() noexcept = default;
			constexpr nullmoveMovedata(nullmoveMovedata&&) noexcept = default;
			constexpr nullmoveMovedata(const nullmoveMovedata&) noexcept = default;
			constexpr nullmoveMovedata& operator=(nullmoveMovedata&&) noexcept = default;
			constexpr nullmoveMovedata& operator=(const nullmoveMovedata&) noexcept = default;
			~nullmoveMovedata() noexcept = default;
		};
	}

	class nullmove :
		public pygmalion::mechanics::move<board, 0, detail::nullmoveMovedata, nullmove>,
		public board::descriptorState
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countFromBits{ squareType::countUnsignedBits };
		constexpr static const size_t countToBits{ squareType::countUnsignedBits };
		std::string name_Implementation() const noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename nullmove::movedataType) << ":" << nullmove::countBits << "@null";
			return sstr.str();
		}
	private:
	public:
		constexpr nullmove() noexcept = default;
		~nullmove() noexcept = default;
		constexpr nullmove(nullmove&&) noexcept = default;
		constexpr nullmove(const nullmove&) noexcept = default;
		constexpr nullmove& operator=(nullmove&&) noexcept = default;
		constexpr nullmove& operator=(const nullmove&) noexcept = default;
		constexpr typename nullmove::movedataType doMove_Implementation(boardType& position, const typename nullmove::movebitsType& moveBits) const noexcept
		{
			const uint_t<countFlags, false> oldFlags{ position.extractFlagRange<0, 11>() };
			const std::uint16_t reversiblePlies{ position.cumulation().reversiblePlies() };
			position.clearEnPassantFiles();
			position.setMovingPlayer(++position.movingPlayer());
			position.cumulation().reversiblePlies() = 0;
			return typename nullmove::movedataType(oldFlags, reversiblePlies);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename nullmove::movedataType& data) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.storeFlagRange<0, 11>(data.oldFlags());
			position.cumulation().reversiblePlies() = data.reversiblePlies();
		}
		constexpr typename nullmove::movebitsType create() const noexcept
		{
			typename nullmove::movebitsType bits{ nullmove::movebitsType::zero() };
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename nullmove::movebitsType& moveBits) const noexcept
		{
			if (text == "@@@@")
			{
				moveBits = create();
				return true;
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename nullmove::movebitsType& moveBits) const noexcept
		{
			return "@@@@";
		}
		constexpr squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return squaresType::none();
		}
		constexpr squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return squaresType::none();
		}
		constexpr squareType fromSquare_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return squareType(0);
		}
		constexpr squareType toSquare_Implementation(const boardType& position, const movebitsType& moveBits) const noexcept
		{
			return squareType(0);
		}
	};
}