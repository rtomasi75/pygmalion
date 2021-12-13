namespace pygmalion::mechanics
{
	//#define PYGMALION_MOVESTATISTICS

	namespace detail
	{
		template<typename MOVE, typename... MOVES2>
		constexpr static size_t computeDisjunctiveBitsRequired() noexcept
		{
			if constexpr (sizeof...(MOVES2) > 0)
				return std::max(MOVE::countBits, detail::computeDisjunctiveBitsRequired<MOVES2...>());
			else
				return MOVE::countBits;
		}
		template<typename MOVE, typename... MOVES2>
		constexpr static size_t computeDisjunctiveDataSize() noexcept
		{
			if constexpr (sizeof...(MOVES2) > 0)
				return std::max(sizeof(typename MOVE::movedataType), detail::computeDisjunctiveDataSize<MOVES2...>());
			else
				return sizeof(typename MOVE::movedataType);
		}

		template<typename BOARD, typename... MOVES>
		class disjunctiveMovedata :
			public pygmalion::mechanics::movedataBase<BOARD>
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
			constexpr static const size_t countMuxBits{ arrayhelper::requiredUnsignedBits(sizeof...(MOVES)) };
			constexpr static const size_t countDataBits{ detail::computeDisjunctiveBitsRequired<MOVES...>() };
			constexpr static const size_t countMoveBits{ countMuxBits + countDataBits };
			constexpr static size_t payloadSize{ detail::computeDisjunctiveDataSize<MOVES...>() };
			using muxbitsType = uint_t<countMuxBits, false>;
			template<typename MOVE, typename... MOVES2>
			union movedataHolder
			{
			public:
				typename MOVE::movedataType CurrentDataView;
				movedataHolder<MOVES2...> OtherDataViews;
				movedataHolder() noexcept :
					CurrentDataView{ typename MOVE::movedataType() }
				{
				}
			};
			template<typename MOVE>
			union movedataHolder<MOVE>
			{
			public:
				typename MOVE::movedataType CurrentDataView;
				movedataHolder() noexcept :
					CurrentDataView{ typename MOVE::movedataType() }
				{
				}
			};
		private:
			movedataHolder<MOVES...> m_Data;
			muxbitsType m_Mux;
		public:
			PYGMALION_INLINE muxbitsType& mux() noexcept
			{
				return m_Mux;
			}
			PYGMALION_INLINE const muxbitsType& mux() const noexcept
			{
				return m_Mux;
			}
			PYGMALION_INLINE movedataHolder<MOVES...>& data() noexcept
			{
				return m_Data;
			}
			PYGMALION_INLINE const movedataHolder<MOVES...>& data() const noexcept
			{
				return m_Data;
			}
			PYGMALION_INLINE disjunctiveMovedata() noexcept :
				m_Data{ movedataHolder<MOVES...>() },
				m_Mux{ muxbitsType(0) }
			{
			}
			PYGMALION_INLINE disjunctiveMovedata(disjunctiveMovedata&&) noexcept = default;
			PYGMALION_INLINE disjunctiveMovedata(const disjunctiveMovedata&) noexcept = default;
			PYGMALION_INLINE disjunctiveMovedata& operator=(disjunctiveMovedata&&) noexcept = default;
			PYGMALION_INLINE disjunctiveMovedata& operator=(const disjunctiveMovedata&) noexcept = default;
			PYGMALION_INLINE ~disjunctiveMovedata() noexcept = default;
		};
		template<size_t INDEX, size_t COUNTER, typename MOVE, typename... MOVES2>
		class disjunctivemoveSelector
		{
		public:
			using moveType = typename disjunctivemoveSelector<INDEX, COUNTER + 1, MOVES2...>::moveType;
		};

		template<size_t INDEX, typename MOVE, typename... MOVES2>
		class disjunctivemoveSelector<INDEX, INDEX, MOVE, MOVES2...>
		{
		public:
			using moveType = MOVE;
		};

	}

	template<typename BOARD, typename INSTANCE, typename... MOVES>
	class disjunctivemove :
		public move<BOARD, detail::computeDisjunctiveBitsRequired<MOVES...>() + arrayhelper::requiredUnsignedBits(sizeof...(MOVES)), detail::disjunctiveMovedata<BOARD, MOVES...>, disjunctivemove<BOARD, INSTANCE, MOVES...>>
	{
	public:
		using instanceType = INSTANCE;
		constexpr static const size_t countDataBits{ detail::computeDisjunctiveBitsRequired<MOVES...>() };
		constexpr static const size_t countMuxBits{ arrayhelper::requiredUnsignedBits(sizeof...(MOVES)) };
		constexpr static const size_t countChannels{ sizeof...(MOVES) };
		using muxbitsType = uint_t<countMuxBits, false>;
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		using materialTableType = state::materialTables<descriptorState, boardType>;
		constexpr static bool enableIndex(const size_t idx) noexcept
		{
			return (idx < sizeof...(MOVES)) && (idx >= 0);
		}
		template<size_t INDEX, size_t COUNTER, typename MOVE, typename... MOVES2>
		PYGMALION_INLINE static auto databitsPack(const typename disjunctivemove::movebitsType moveBits) noexcept
		{
			if constexpr (INDEX == COUNTER)
				return moveBits.template extractBits<0, MOVE::countBits>();
			else
				return disjunctivemove::databitsPack<INDEX, COUNTER + 1, MOVES2...>(moveBits);
		}
	protected:
		constexpr static muxbitsType muxbits(const typename disjunctivemove::movebitsType moveBits) noexcept
		{
			return moveBits.template extractBits<countDataBits, countMuxBits>();
		}
		template<size_t INDEX, typename = typename std::enable_if<disjunctivemove::enableIndex(INDEX)>::type>
		constexpr static auto databits(const typename disjunctivemove::movebitsType& moveBits) noexcept
		{
			return databitsPack<INDEX, 0, MOVES...>(moveBits);
		}
	private:
		std::tuple<MOVES...> m_Moves;
#if defined(PYGMALION_MOVESTATISTICS)
		static inline std::array<std::uintmax_t, sizeof...(MOVES)> m_Statistics{ arrayhelper::make<sizeof...(MOVES),std::uintmax_t>(0) };
#endif
		template<typename MOVE, typename... MOVES2>
		static std::string namePack() noexcept
		{
			constexpr const MOVE move;
			if constexpr (sizeof...(MOVES2) > 0)
				return move.name() + "|" + disjunctivemove::namePack<MOVES2...>();
			else
				return move.name();
		}
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		static std::string channelPack(const size_t index) noexcept
		{
			if (INDEX == index)
				return MOVE::name();
			if constexpr (sizeof...(MOVES2) > 0)
				return disjunctivemove::channelPack<INDEX + 1, MOVES2...>(index);
			else
				return "";
		}
	public:
		static std::string name_Implementation() noexcept
		{
			constexpr size_t N{ arrayhelper::requiredUnsignedBits(sizeof...(MOVES)) };
			std::stringstream sstr;
			sstr << sizeof(typename disjunctivemove::movedataType) << ":" << disjunctivemove::countBits << "@[";
			sstr << "" << sizeof(muxbitsType) << ":" << disjunctivemove::countMuxBits << "@mux&" << disjunctivemove::movedataType::payloadSize << ":" << disjunctivemove::countDataBits << "@[";
			if constexpr (sizeof...(MOVES) > 0)
				sstr << disjunctivemove::namePack<MOVES...>();
			sstr << "]]";
			return sstr.str();
		}
		static std::string channel(const size_t channel) noexcept
		{
			if constexpr (sizeof...(MOVES) > 0)
				return disjunctivemove::channelPack<0, MOVES...>(channel);
			return "";
		}
		template<size_t INDEX>
		PYGMALION_INLINE constexpr const auto& component() const noexcept
		{
			return std::get<INDEX>(this->m_Moves);
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		PYGMALION_INLINE void doMovePack(boardType& position, const size_t selector, const typename disjunctivemove::movebitsType moveBits, typename disjunctivemove::movedataType::template movedataHolder<MOVE, MOVES2...>& combinedData, const materialTableType& materialTable) const noexcept
		{
			if (INDEX == selector)
			{
#if defined(PYGMALION_MOVESTATISTICS)
				m_Statistics[INDEX]++;
#endif
				typename MOVE::movebitsType bits{ moveBits.template extractBits<0,MOVE::countBits>() };
				std::get<INDEX>(this->m_Moves).doMove(position, bits, combinedData.CurrentDataView, materialTable);
				constexpr const muxbitsType mux{ static_cast<muxbitsType>(static_cast<typename std::make_unsigned<size_t>::type>(INDEX)) };
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					this->template doMovePack<INDEX + 1, MOVES2...>(position, selector, moveBits, combinedData.OtherDataViews, materialTable);
			}
		}
	public:
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename disjunctivemove::movebitsType moveBits, typename disjunctivemove::movedataType& movedata, const materialTableType& materialTable) const noexcept
		{
			const muxbitsType mux{ disjunctivemove::muxbits(moveBits) };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			movedata.mux() = mux;
			if constexpr (sizeof...(MOVES) > 0)
				this->template doMovePack<0, MOVES...>(position, selector, moveBits, movedata.data(), materialTable);
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		PYGMALION_INLINE void undoMovePack(boardType& position, const size_t selector, const typename disjunctivemove::movedataType::template movedataHolder<MOVE, MOVES2...>& combinedData, const materialTableType& materialTable) const noexcept
		{
			constexpr const muxbitsType mux{ static_cast<muxbitsType>(static_cast<typename std::make_unsigned<size_t>::type>(INDEX)) };
			if (mux == selector)
			{
				std::get<INDEX>(this->m_Moves).undoMove(position, combinedData.CurrentDataView, materialTable);
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					this->template undoMovePack<INDEX + 1, MOVES2...>(position, selector, combinedData.OtherDataViews, materialTable);
			}
		}
	public:
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename disjunctivemove::movedataType& movedata, const materialTableType& materialTable) const noexcept
		{
			const muxbitsType mux{ movedata.mux() };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			if constexpr (sizeof...(MOVES) > 0)
				this->template undoMovePack<0, MOVES...>(position, selector, movedata.data(), materialTable);
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		bool parsePack(const boardType& position, const std::string& text, typename disjunctivemove::movebitsType& moveBits, size_t& count) const noexcept
		{
			using currentMoveType = typename std::decay<decltype(std::get<getParseIndex(INDEX)>(this->m_Moves))>::type;
			typename currentMoveType::movebitsType bits;
			size_t cnt{ 0 };
			if (std::get<getParseIndex(INDEX)>(this->m_Moves).parse(position, text, bits, cnt))
			{
				constexpr const muxbitsType mux{ static_cast<muxbitsType>(static_cast<typename std::make_unsigned<size_t>::type>(getParseIndex(INDEX))) };
				moveBits.template storeBits<0, currentMoveType::movebitsType::countBits>(bits);
				moveBits.template storeBits<countDataBits, countMuxBits>(mux);
				count += cnt;
				return true;
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					return this->template parsePack<INDEX + 1, MOVES2...>(position, text, moveBits, count);
				else
					return false;
			}
		}
	public:
		bool parse_Implementation(const boardType& position, const std::string& text, typename disjunctivemove::movebitsType& moveBits, size_t& count) const noexcept
		{
			if constexpr (sizeof...(MOVES) > 0)
				return this->template parsePack<0, MOVES...>(position, text, moveBits, count);
			else
				return true;
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		std::string printPack(const boardType& position, const size_t selector, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			if (INDEX == selector)
			{
				typename MOVE::movebitsType bits{ moveBits.template extractBits<0,MOVE::countBits>() };
				return std::get<INDEX>(this->m_Moves).toString(position, bits);
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					return this->template printPack<INDEX + 1, MOVES2...>(position, selector, moveBits);
				else
					return "";
			}
		}
	public:
		std::string toString_Implementation(const boardType& position, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			const muxbitsType mux{ disjunctivemove::muxbits(moveBits) };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			if constexpr (sizeof...(MOVES) > 0)
				return this->template printPack<0, MOVES...>(position, selector, moveBits);
			else
				return "";
		}
	private:
	public:
#if defined(PYGMALION_MOVESTATISTICS)
		static std::uintmax_t statistics(const size_t index) noexcept
		{
			return m_Statistics[index];
		}
#endif
		template<size_t INDEX>
		PYGMALION_INLINE constexpr typename disjunctivemove::movebitsType create(const typename detail::disjunctivemoveSelector<INDEX, 0, MOVES...>::moveType::movebitsType bits) const noexcept
		{
			typename disjunctivemove::movebitsType moveBits;
			if constexpr (sizeof...(MOVES) > 0)
			{
				constexpr const muxbitsType mux{ static_cast<muxbitsType>(static_cast<typename std::make_unsigned<size_t>::type>(INDEX)) };
				using moveType = typename detail::disjunctivemoveSelector<INDEX, 0, MOVES...>::moveType;
				moveBits.template storeBits<0, moveType::movebitsType::countBits>(bits);
				moveBits.template storeBits<countDataBits, countMuxBits>(mux);
			}
			return moveBits;
		}
	public:
		PYGMALION_INLINE constexpr disjunctivemove() noexcept :
			m_Moves{ std::tuple<MOVES...>(MOVES()...) }
		{

		}
		PYGMALION_INLINE ~disjunctivemove() noexcept = default;
		PYGMALION_INLINE constexpr disjunctivemove(disjunctivemove&&) noexcept = default;
		PYGMALION_INLINE constexpr disjunctivemove(const disjunctivemove&) noexcept = default;
		PYGMALION_INLINE constexpr disjunctivemove& operator=(disjunctivemove&&) noexcept = default;
		PYGMALION_INLINE constexpr disjunctivemove& operator=(const disjunctivemove&) noexcept = default;
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		PYGMALION_INLINE squaresType otherOccupancyDeltaPack(const boardType& position, const size_t selector, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			if (INDEX == selector)
			{
				typename MOVE::movebitsType bits{ moveBits.template extractBits<0,MOVE::countBits>() };
				return std::get<INDEX>(this->m_Moves).otherOccupancyDelta(position, bits);
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					return this->template otherOccupancyDeltaPack<INDEX + 1, MOVES2...>(position, selector, moveBits);
				else
					return none;
			}
		}
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		PYGMALION_INLINE squaresType ownOccupancyDeltaPack(const boardType& position, const size_t selector, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			if (INDEX == selector)
			{
				typename MOVE::movebitsType bits{ moveBits.template extractBits<0,MOVE::countBits>() };
				return std::get<INDEX>(this->m_Moves).ownOccupancyDelta(position, bits);
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					return this->template ownOccupancyDeltaPack<INDEX + 1, MOVES2...>(position, selector, moveBits);
				else
					return none;
			}
		}
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		PYGMALION_INLINE squaresType pieceOccupancyDeltaPack(const boardType& position, const pieceType piece, const size_t selector, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			if (INDEX == selector)
			{
				typename MOVE::movebitsType bits{ moveBits.template extractBits<0,MOVE::countBits>() };
				return std::get<INDEX>(this->m_Moves).pieceOccupancyDelta(position, piece, bits);
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					return this->template pieceOccupancyDeltaPack<INDEX + 1, MOVES2...>(position, piece, selector, moveBits);
				else
					return none;
			}
		}
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		PYGMALION_INLINE squareType fromSquarePack(const boardType& position, const size_t selector, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			if (INDEX == selector)
			{
				typename MOVE::movebitsType bits{ moveBits.template extractBits<0,MOVE::countBits>() };
				return std::get<INDEX>(this->m_Moves).fromSquare(position, bits);
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					return this->template fromSquarePack<INDEX + 1, MOVES2...>(position, selector, moveBits);
				else
				{
					assert(false);
					return squareType::invalid;
				}
			}
		}
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		PYGMALION_INLINE squareType toSquarePack(const boardType& position, const size_t selector, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			if (INDEX == selector)
			{
				typename MOVE::movebitsType bits{ moveBits.template extractBits<0,MOVE::countBits>() };
				return std::get<INDEX>(this->m_Moves).toSquare(position, bits);
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					return this->template toSquarePack<INDEX + 1, MOVES2...>(position, selector, moveBits);
				else
				{
					PYGMALION_ASSERT(false);
					return squareType::invalid;
				}
			}
		}
	public:
		constexpr static size_t getParseIndex(const size_t index) noexcept
		{
			return instanceType::getParseIndex_Implementation(index);
		}
		constexpr squaresType otherOccupancyDelta_Implementation(const boardType& position, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			const muxbitsType mux{ disjunctivemove::muxbits(moveBits) };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			if constexpr (sizeof...(MOVES) > 0)
				return this->template otherOccupancyDeltaPack<0, MOVES...>(position, selector, moveBits);
			else
				return none;
		}
		PYGMALION_INLINE squaresType ownOccupancyDelta_Implementation(const boardType& position, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			const muxbitsType mux{ disjunctivemove::muxbits(moveBits) };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			if constexpr (sizeof...(MOVES) > 0)
				return this->template ownOccupancyDeltaPack<0, MOVES...>(position, selector, moveBits);
			else
				return none;
		}
		PYGMALION_INLINE squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			const muxbitsType mux{ disjunctivemove::muxbits(moveBits) };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			if constexpr (sizeof...(MOVES) > 0)
				return this->template pieceOccupancyDeltaPack<0, MOVES...>(position, piece, selector, moveBits);
			else
				return none;
		}
		PYGMALION_INLINE squareType fromSquare_Implementation(const boardType& position, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			const muxbitsType mux{ disjunctivemove::muxbits(moveBits) };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			if constexpr (sizeof...(MOVES) > 0)
				return this->template fromSquarePack<0, MOVES...>(position, selector, moveBits);
			else
			{
				PYGMALION_ASSERT(false);
				return squareType::invalid;
			}
		}
		PYGMALION_INLINE squareType toSquare_Implementation(const boardType& position, const typename disjunctivemove::movebitsType moveBits) const noexcept
		{
			const muxbitsType mux{ disjunctivemove::muxbits(moveBits) };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			if constexpr (sizeof...(MOVES) > 0)
				return this->template toSquarePack<0, MOVES...>(position, selector, moveBits);
			else
			{
				PYGMALION_ASSERT(false);
				return squareType::invalid;
			}
		}
	};
}