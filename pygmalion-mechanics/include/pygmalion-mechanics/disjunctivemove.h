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
			std::array<unsigned char, payloadSize> m_Data;
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
				return m_Data.data();
			}
			constexpr const unsigned char* dataPtr() const noexcept
			{
				return m_Data.data();
			}
			constexpr disjunctiveMovedata() noexcept :
				m_Data{ arrayhelper::make<payloadSize, unsigned char>(0) }
			{}
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
			using moveType = typename disjunctivemoveSelector<INDEX, COUNTER + 1, MOVES2...>::moveType;
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
		constexpr static bool enableIndex(const size_t idx) noexcept
		{
			return (idx < sizeof...(MOVES)) && (idx >= 0);
		}
		template<size_t INDEX, size_t COUNTER, typename MOVE, typename... MOVES2>
		constexpr static auto databitsPack(const typename disjunctivemove::movebitsType& moveBits) noexcept
		{
			if constexpr (INDEX == COUNTER)
				return moveBits.template extractBits<0, MOVE::countBits>();
			else
				return disjunctivemove::databitsPack<INDEX, COUNTER + 1, MOVES2...>(moveBits);
		}
	protected:
		constexpr static muxbitsType muxbits(const typename disjunctivemove::movebitsType& moveBits) noexcept
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
		template<typename MOVE, typename... MOVES2>
		static std::string namePack() noexcept
		{
			constexpr const MOVE move;
			if constexpr (sizeof...(MOVES2) > 0)
				return move.name() + "|" + disjunctivemove::namePack<MOVES2...>();
			else
				return move.name();
		}
	public:
		std::string name_Implementation() const noexcept
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
		template<size_t INDEX>
		constexpr const auto& component() const noexcept
		{
			return std::get<INDEX>(this->m_Moves);
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
			const muxbitsType mux{ disjunctivemove::muxbits(moveBits) };
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
			const muxbitsType mux{ disjunctivemove::muxbits(moveBits) };
			const size_t selector{ static_cast<size_t>(static_cast<typename std::make_unsigned<size_t>::type>(mux)) };
			if constexpr (sizeof...(MOVES) > 0)
				return this->template printPack<0, MOVES...>(position, selector, moveBits);
			else
				return "";
		}
	private:
	public:
		template<size_t INDEX>
		constexpr typename disjunctivemove::movebitsType create(const typename detail::disjunctivemoveSelector<INDEX, 0, MOVES...>::moveType::movebitsType& bits) const noexcept
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