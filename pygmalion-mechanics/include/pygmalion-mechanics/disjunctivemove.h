namespace pygmalion::mechanics
{
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
		class disjunctiveMovedata
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
			constexpr static const size_t countMuxBits{ pygmalion::detail::requiredUnsignedBits(sizeof...(MOVES)) };
			constexpr static const size_t countDataBits{ detail::computeDisjunctiveBitsRequired<MOVES...>() };
			constexpr static const size_t countMoveBits{ countMuxBits + countDataBits };
			constexpr static size_t payloadSize{ detail::computeDisjunctiveDataSize<MOVES...>() };
			using muxbitsType = uint_t<countMuxBits, false>;
		private:
			muxbitsType m_Mux;
			unsigned char m_Data[payloadSize];
		public:
			constexpr muxbitsType& mux() noexcept
			{
				return m_Mux;
			}
			constexpr const muxbitsType& mux() const noexcept
			{
				return m_Mux;
			}
			constexpr unsigned char* dataPtr() noexcept
			{
				return m_Data;
			}
			constexpr const unsigned char* dataPtr() const noexcept
			{
				return m_Data;
			}
			constexpr disjunctiveMovedata() noexcept = default;
		};

	}

	template<typename BOARD, typename... MOVES>
	class disjunctivemove :
		public move<BOARD, detail::computeDisjunctiveBitsRequired<MOVES...>() + pygmalion::detail::requiredUnsignedBits(sizeof...(MOVES)), detail::disjunctiveMovedata<BOARD, MOVES...>, disjunctivemove<BOARD, MOVES...>>
	{
	public:
		constexpr static const size_t countDataBits{ detail::computeDisjunctiveBitsRequired<MOVES...>() };
		constexpr static const size_t countMuxBits{ pygmalion::detail::requiredUnsignedBits(sizeof...(MOVES)) };
		using muxbitsType = uint_t<countMuxBits, false>;
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
	private:
		template<typename MOVE, typename... MOVES2>
		static std::string namePack() noexcept
		{
			if constexpr (sizeof...(MOVES2) > 0)
				return MOVE::name() + " | " + disjunctivemove::namePack<MOVES2...>();
			else
				return MOVE::name();
		}
	public:
		static std::string name_Implementation() noexcept
		{
			size_t N = pygmalion::detail::requiredUnsignedBits(sizeof...(MOVES));
			std::stringstream sstr;
			sstr << disjunctivemove::countBits << "bit@[ ";
			sstr << disjunctivemove::countMuxBits << "bit@mux & " << disjunctivemove::countDataBits << "bit@( ";
			if constexpr (sizeof...(MOVES) > 0)
				sstr << disjunctivemove::namePack<MOVES...>();
			sstr << " ) ]";
			return sstr.str();
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		constexpr static void doMovePack(boardType& position, const size_t selector, const typename disjunctivemove::movebitsType& moveBits, typename disjunctivemove::movedataType& combinedData) noexcept
		{
			if (INDEX == selector)
			{
				typename MOVE::movebitsType bits{ moveBits.template extractBits<0,MOVE::countBits>() };
				typename MOVE::movedataType& data{ *reinterpret_cast<typename MOVE::movedataType*>(combinedData.dataPtr()) };
				data = MOVE::doMove(position, bits);
				constexpr const muxbitsType mux{ static_cast<muxbitsType>(static_cast<typename std::make_unsigned<size_t>::type>(INDEX)) };
				combinedData.mux() = mux;
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					disjunctivemove::doMovePack<INDEX + 1, MOVES2...>(position, selector, moveBits, combinedData);
			}
		}
	public:
		constexpr static typename disjunctivemove::movedataType doMove_Implementation(boardType& position, const typename disjunctivemove::movebitsType& moveBits) noexcept
		{
			const muxbitsType mux{ moveBits.template extractBits<countDataBits, countMuxBits>() };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			typename disjunctivemove::movedataType data;
			if constexpr (sizeof...(MOVES) > 0)
				disjunctivemove::doMovePack<0, MOVES...>(position, selector, moveBits, data);
			return data;
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		constexpr static void undoMovePack(boardType& position, const typename disjunctivemove::movedataType& combinedData, const playerType movingPlayer) noexcept
		{
			constexpr const muxbitsType mux{ static_cast<muxbitsType>(static_cast<typename std::make_unsigned<size_t>::type>(INDEX)) };
			if (mux == combinedData.mux())
			{
				const typename MOVE::movedataType& data{ *reinterpret_cast<const typename MOVE::movedataType*>(combinedData.dataPtr()) };
				MOVE::undoMove(position, data, movingPlayer);
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					disjunctivemove::undoMovePack<INDEX + 1, MOVES2...>(position, combinedData, movingPlayer);
			}
		}
	public:
		constexpr static void undoMove_Implementation(boardType& position, const typename disjunctivemove::movedataType& data, const playerType movingPlayer) noexcept
		{
			if constexpr (sizeof...(MOVES) > 0)
				disjunctivemove::undoMovePack<0, MOVES...>(position, data, movingPlayer);
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		static bool parsePack(const boardType& position, std::string& text, typename disjunctivemove::movebitsType& moveBits) noexcept
		{
			typename MOVE::movebitsType bits;
			if (MOVE::parse(position, text, bits))
			{
				constexpr const muxbitsType mux{ static_cast<muxbitsType>(static_cast<typename std::make_unsigned<size_t>::type>(INDEX)) };
				moveBits.template storeBits<0, MOVE::movebitsType::countBits>(bits);
				moveBits.template storeBits<countDataBits, countMuxBits>(mux);
				return true;
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					return disjunctivemove::parsePack<INDEX + 1, MOVES2...>(position, text, moveBits);
				else
					return false;
			}
		}
	public:
		static bool parse_Implementation(const boardType& position, std::string& text, typename disjunctivemove::movebitsType& moveBits) noexcept
		{
			if constexpr (sizeof...(MOVES) > 0)
				return disjunctivemove::parsePack<0, MOVES...>(position, text, moveBits);
			else
				return true;
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		static std::string printPack(const boardType& position, const size_t selector, const typename disjunctivemove::movebitsType& moveBits) noexcept
		{
			if (INDEX == selector)
			{
				typename MOVE::movebitsType bits{ moveBits.template extractBits<0,MOVE::countBits>() };
				return MOVE::toString(position, bits);
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					return disjunctivemove::printPack<INDEX + 1, MOVES2...>(position, selector, moveBits);
				else
					return "";
			}
		}
	public:
		static std::string toString_Implementation(const boardType& position, const typename disjunctivemove::movebitsType& moveBits) noexcept
		{
			const muxbitsType mux{ moveBits.template extractBits<countDataBits, countMuxBits>() };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			if constexpr (sizeof...(MOVES) > 0)
				return disjunctivemove::printPack<0, MOVES...>(position, selector, moveBits);
			else
				return "";
		}
	};
}