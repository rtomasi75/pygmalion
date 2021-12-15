namespace pygmalion::chess
{
	namespace detail
	{
		class nullmoveMovedata :
			public pygmalion::mechanics::movedataBase<board>
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			squaresType m_OldEnPassantTargets;
			size_t m_ReversiblePlies{ 0 };
			squareType m_OldEnPassantVictim;
		public:
			PYGMALION_INLINE const size_t& reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			PYGMALION_INLINE const squaresType& oldEnPassantTargets() const noexcept
			{
				return m_OldEnPassantTargets;
			}
			PYGMALION_INLINE const squareType& oldEnPassantVictim() const noexcept
			{
				return m_OldEnPassantVictim;
			}
			PYGMALION_INLINE nullmoveMovedata(const size_t reversiblePlies_, const squaresType oldEnPassantTargets_, const squareType oldEnPassantVictim_) noexcept :
				m_OldEnPassantTargets{ oldEnPassantTargets_ },
				m_OldEnPassantVictim{ oldEnPassantVictim_ },
				m_ReversiblePlies{ reversiblePlies_ }
			{}
			PYGMALION_INLINE nullmoveMovedata() noexcept = default;
			PYGMALION_INLINE nullmoveMovedata(nullmoveMovedata&&) noexcept = default;
			PYGMALION_INLINE nullmoveMovedata(const nullmoveMovedata&) noexcept = default;
			PYGMALION_INLINE nullmoveMovedata& operator=(nullmoveMovedata&&) noexcept = default;
			PYGMALION_INLINE nullmoveMovedata& operator=(const nullmoveMovedata&) noexcept = default;
			PYGMALION_INLINE ~nullmoveMovedata() noexcept = default;
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
		static std::string name_Implementation() noexcept
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
		constexpr nullmove& operator=(nullmove&&) noexcept
		{
			return *this;
		}
		constexpr nullmove& operator=(const nullmove&) noexcept
		{
			return *this;
		}
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename nullmove::movebitsType moveBits, typename nullmove::movedataType& movedata, const materialTableType& materialTable) const noexcept
		{
			const squaresType oldEnPassantTargets{ position.enPassantTargets() };
			const squareType oldEnPassantVictim{ position.enPassantVictim() };
			const size_t reversiblePlies{ position.getReversiblePlyCount() };
			position.clearEnPassant();
			position.setMovingPlayer(++position.movingPlayer());
			position.resetReversiblePlyCount();
			movedata = typename nullmove::movedataType(reversiblePlies, oldEnPassantTargets, oldEnPassantVictim);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename nullmove::movedataType& data, const materialTableType& materialTable) const noexcept
		{
			const playerType p{ --position.movingPlayer() };
			position.setMovingPlayer(p);
			position.setEnPassant(data.oldEnPassantTargets(), data.oldEnPassantVictim());
			position.setReversiblePlyCount(data.reversiblePlies());
		}
		PYGMALION_INLINE constexpr typename nullmove::movebitsType create() const noexcept
		{
			typename nullmove::movebitsType bits{ nullmove::movebitsType::zero() };
			return bits;
		}
		PYGMALION_INLINE bool parse_Implementation(const boardType& position, const std::string& text, typename nullmove::movebitsType& moveBits, size_t& count) const noexcept
		{
			if (text == "@@@@")
			{
				moveBits = create();
				count += 4;
				return true;
			}
			return false;
		}
		PYGMALION_INLINE std::string toString_Implementation(const boardType& position, const typename nullmove::movebitsType moveBits) const noexcept
		{
			return "@@@@";
		}
		PYGMALION_INLINE squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			return none;
		}
		PYGMALION_INLINE squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			return none;
		}
		PYGMALION_INLINE squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			return none;
		}
		PYGMALION_INLINE squareType fromSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squareType(0);
		}
		PYGMALION_INLINE squareType toSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squareType(0);
		}
	};
}