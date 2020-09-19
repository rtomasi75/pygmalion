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
			constexpr disjunctiveMovedata(disjunctiveMovedata&&) noexcept = default;
			constexpr disjunctiveMovedata(const disjunctiveMovedata&) noexcept = default;
			constexpr disjunctiveMovedata& operator=(disjunctiveMovedata&&) noexcept = default;
			constexpr disjunctiveMovedata& operator=(const disjunctiveMovedata&) noexcept = default;
			~disjunctiveMovedata() noexcept = default;
		};
		template<size_t INDEX, size_t COUNTER, typename MOVE, typename... MOVES2>
		class disjunctivemoveSelector
		{
		public:
			using moveType = typename disjunctivemoveSelector<INDEX, COUNTER + 1, MOVES2...>::type;
		};

		template<size_t INDEX, typename MOVE, typename... MOVES2>
		class disjunctivemoveSelector<INDEX, INDEX, MOVE, MOVES2...>
		{
		public:
			using moveType = MOVE;
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
		std::tuple<MOVES...> m_Moves;
		template<typename MOVE, typename... MOVES2>
		static std::string namePack() noexcept
		{
			if constexpr (sizeof...(MOVES2) > 0)
				return MOVE::name() + "|" + disjunctivemove::namePack<MOVES2...>();
			else
				return MOVE::name();
		}
	public:
		static std::string name_Implementation() noexcept
		{
			size_t N = pygmalion::detail::requiredUnsignedBits(sizeof...(MOVES));
			std::stringstream sstr;
			sstr << sizeof(typename disjunctivemove::movedataType) << ":" << disjunctivemove::countBits << "@[";
			sstr << "" << sizeof(muxbitsType) << ":" << disjunctivemove::countMuxBits << "@mux&" << disjunctivemove::movedataType::payloadSize << ":" << disjunctivemove::countDataBits << "@[";
			if constexpr (sizeof...(MOVES) > 0)
				sstr << disjunctivemove::namePack<MOVES...>();
			sstr << "]]";
			return sstr.str();
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		constexpr void doMovePack(boardType& position, const size_t selector, const typename disjunctivemove::movebitsType& moveBits, typename disjunctivemove::movedataType& combinedData) const noexcept
		{
			if (INDEX == selector)
			{
				typename MOVE::movebitsType bits{ moveBits.template extractBits<0,MOVE::countBits>() };
				typename MOVE::movedataType& data{ *reinterpret_cast<typename MOVE::movedataType*>(combinedData.dataPtr()) };
				data = std::get<INDEX>(this->m_Moves).doMove(position, bits);
				constexpr const muxbitsType mux{ static_cast<muxbitsType>(static_cast<typename std::make_unsigned<size_t>::type>(INDEX)) };
				combinedData.mux() = mux;
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					this->template doMovePack<INDEX + 1, MOVES2...>(position, selector, moveBits, combinedData);
			}
		}
	public:
		constexpr typename disjunctivemove::movedataType doMove_Implementation(boardType& position, const typename disjunctivemove::movebitsType& moveBits) const noexcept
		{
			const muxbitsType mux{ moveBits.template extractBits<countDataBits, countMuxBits>() };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			typename disjunctivemove::movedataType data;
			if constexpr (sizeof...(MOVES) > 0)
				this->template doMovePack<0, MOVES...>(position, selector, moveBits, data);
			return data;
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		constexpr void undoMovePack(boardType& position, const typename disjunctivemove::movedataType& combinedData) const noexcept
		{
			constexpr const muxbitsType mux{ static_cast<muxbitsType>(static_cast<typename std::make_unsigned<size_t>::type>(INDEX)) };
			if (mux == combinedData.mux())
			{
				const typename MOVE::movedataType& data{ *reinterpret_cast<const typename MOVE::movedataType*>(combinedData.dataPtr()) };
				std::get<INDEX>(this->m_Moves).undoMove(position, data);
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					this->template undoMovePack<INDEX + 1, MOVES2...>(position, combinedData);
			}
		}
	public:
		constexpr void undoMove_Implementation(boardType& position, const typename disjunctivemove::movedataType& data) const noexcept
		{
			if constexpr (sizeof...(MOVES) > 0)
				this->template undoMovePack<0, MOVES...>(position, data);
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		bool parsePack(const boardType& position, std::string& text, typename disjunctivemove::movebitsType& moveBits) const noexcept
		{
			typename MOVE::movebitsType bits;
			if (std::get<INDEX>(this->m_Moves).parse(position, text, bits))
			{
				constexpr const muxbitsType mux{ static_cast<muxbitsType>(static_cast<typename std::make_unsigned<size_t>::type>(INDEX)) };
				moveBits.template storeBits<0, MOVE::movebitsType::countBits>(bits);
				moveBits.template storeBits<countDataBits, countMuxBits>(mux);
				return true;
			}
			else
			{
				if constexpr (sizeof...(MOVES2) > 0)
					return this->template parsePack<INDEX + 1, MOVES2...>(position, text, moveBits);
				else
					return false;
			}
		}
	public:
		bool parse_Implementation(const boardType& position, std::string& text, typename disjunctivemove::movebitsType& moveBits) const noexcept
		{
			if constexpr (sizeof...(MOVES) > 0)
				return this->template parsePack<0, MOVES...>(position, text, moveBits);
			else
				return true;
		}
	private:
		template<size_t INDEX, typename MOVE, typename... MOVES2>
		std::string printPack(const boardType& position, const size_t selector, const typename disjunctivemove::movebitsType& moveBits) const noexcept
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
		std::string toString_Implementation(const boardType& position, const typename disjunctivemove::movebitsType& moveBits) const noexcept
		{
			const muxbitsType mux{ moveBits.template extractBits<countDataBits, countMuxBits>() };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			if constexpr (sizeof...(MOVES) > 0)
				return this->template printPack<0, MOVES...>(position, selector, moveBits);
			else
				return "";
		}
	private:
	public:
		template<size_t INDEX>
		constexpr typename disjunctivemove::movebitsType create(const typename detail::disjunctivemoveSelector<INDEX, 0, MOVES...>::type::movebitsType& bits) const noexcept
		{
			typename disjunctivemove::movebitsType moveBits;
			if constexpr (sizeof...(MOVES) > 0)
			{
				constexpr const muxbitsType mux{ static_cast<muxbitsType>(static_cast<typename std::make_unsigned<size_t>::type>(INDEX)) };
				using moveType = typename detail::disjunctivemoveSelector<INDEX, 0, MOVES...>::type;
				moveBits.template storeBits<0, moveType::movebitsType::countBits>(bits);
				moveBits.template storeBits<countDataBits, countMuxBits>(mux);
			}
			return moveBits;
		}
	public:
		constexpr disjunctivemove() noexcept :
			m_Moves{ std::tuple<MOVES...>(MOVES()...) }
		{

		}
		~disjunctivemove() noexcept = default;
		constexpr disjunctivemove(disjunctivemove&&) noexcept = default;
		constexpr disjunctivemove(const disjunctivemove&) noexcept = default;
		constexpr disjunctivemove& operator=(disjunctivemove&&) noexcept = default;
		constexpr disjunctivemove& operator=(const disjunctivemove&) noexcept = default;
	};
}