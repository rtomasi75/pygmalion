namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename MOVE, typename... MOVES2>
		constexpr static size_t computeConjunctiveBitsRequired() noexcept
		{
			if constexpr (sizeof...(MOVES2) > 0)
				return MOVE::countBits + detail::computeConjunctiveBitsRequired<MOVES2...>();
			else
				return MOVE::countBits;
		}
		template<typename MOVE, typename... MOVES2>
		constexpr static size_t computeConjunctiveDataSize() noexcept
		{
			if constexpr (sizeof...(MOVES2) > 0)
				return sizeof(typename MOVE::movedataType) + detail::computeConjunctiveDataSize<MOVES2...>();
			else
				return sizeof(typename MOVE::movedataType);
		}

		template<typename BOARD, typename... MOVES>
		class conjunctiveMovedata
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
			constexpr static size_t payloadSize{ detail::computeConjunctiveDataSize<MOVES...>() };
		private:
			std::array<unsigned char, payloadSize> m_Data;
		public:
			constexpr unsigned char* dataPtr() noexcept
			{
				return m_Data.data();
			}
			constexpr const unsigned char* dataPtr() const noexcept
			{
				return m_Data.data();
			}
			constexpr conjunctiveMovedata() noexcept :
				m_Data{ arrayhelper::make<payloadSize, unsigned char>(0) }
			{}
			constexpr conjunctiveMovedata(conjunctiveMovedata&&) noexcept = default;
			constexpr conjunctiveMovedata(const conjunctiveMovedata&) noexcept = default;
			constexpr conjunctiveMovedata& operator=(conjunctiveMovedata&&) noexcept = default;
			constexpr conjunctiveMovedata& operator=(const conjunctiveMovedata&) noexcept = default;
			~conjunctiveMovedata() noexcept = default;
		};

	}

	template<typename BOARD, typename... MOVES>
	class conjunctivemove :
		public move<BOARD, detail::computeConjunctiveBitsRequired<MOVES...>(), detail::conjunctiveMovedata<BOARD, MOVES...>, conjunctivemove<BOARD, MOVES...>>
	{
	public:
		constexpr static const size_t countDataBits{ detail::computeConjunctiveBitsRequired<MOVES...>() };
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
	private:
		std::tuple<MOVES...> m_Moves;
		template<typename MOVE, typename... MOVES2>
		static std::string namePack() noexcept
		{
			constexpr const MOVE move;
			if constexpr (sizeof...(MOVES2) > 0)
				return move.name() + "&" + conjunctivemove::namePack<MOVES2...>();
			else
				return move.name();
		}
	public:
		std::string name_Implementation() const noexcept
		{
			std::stringstream sstr;
			sstr << sizeof(typename conjunctivemove::movedataType) << ":" << conjunctivemove::countBits << "@[";
			if constexpr (sizeof...(MOVES) > 0)
				sstr << conjunctivemove::namePack<MOVES...>();
			sstr << "]";
			return sstr.str();
		}
		template<size_t INDEX>
		const auto& component() const noexcept
		{
			return std::get<INDEX>(this->m_Moves);
		}
	private:
		template<size_t BITSPOS, size_t DATAPOS, size_t INDEX, typename MOVE, typename... MOVES2>
		constexpr void doMovePack(boardType& position, const typename conjunctivemove::movebitsType& moveBits, typename conjunctivemove::movedataType& combinedData) const noexcept
		{
			typename MOVE::movebitsType bits{ moveBits.template extractBits<BITSPOS,MOVE::countBits>() };
			typename MOVE::movedataType& data{ *static_cast<typename MOVE::movedataType*>(combinedData.dataPtr() + DATAPOS) };
			data = std::get<INDEX>(this->m_Moves).doMove(position, bits);
			if constexpr (sizeof...(MOVES2) > 0)
				this->template doMovePack<BITSPOS + MOVE::countBits, DATAPOS + sizeof(typename MOVE::movedataType), INDEX + 1, MOVES2...>(position, moveBits, combinedData);
		}
	public:
		constexpr typename conjunctivemove::movedataType doMove_Implementation(boardType& position, const typename conjunctivemove::movebitsType& moveBits) const noexcept
		{
			typename conjunctivemove::movedataType data;
			if constexpr (sizeof...(MOVES) > 0)
				this->template doMovePack<0, 0, 0, MOVES...>(position, moveBits, data);
			return data;
		}
	private:
		template<size_t DATAPOS, size_t INDEX, typename MOVE, typename... MOVES2>
		constexpr void undoMovePack(boardType& position, const typename conjunctivemove::movedataType& combinedData) const noexcept
		{
			const typename MOVE::movedataType& data{ *static_cast<const typename MOVE::movedataType*>(combinedData.dataPtr() + DATAPOS) };
			if constexpr (sizeof...(MOVES2) > 0)
				this->template undoMovePack<DATAPOS + sizeof(typename MOVE::movedataType), INDEX + 1, MOVES2...>(position, combinedData);
			std::get<INDEX>(this->m_Moves).undoMove(position, data);
		}
	public:
		constexpr void undoMove_Implementation(boardType& position, const typename conjunctivemove::movedataType& data) const noexcept
		{
			if constexpr (sizeof...(MOVES) > 0)
				this->template undoMovePack<0, 0, MOVES...>(position, data);
		}
	private:
		template<size_t BITSPOS, size_t INDEX, typename MOVE, typename... MOVES2>
		bool parsePack(const boardType& position, std::string& text, typename conjunctivemove::movebitsType& moveBits) const noexcept
		{
			typename MOVE::movebitsType bits{ MOVE::movebitsType::zero() };
			if (!std::get<INDEX>(this->m_Moves).parse(position, text, bits))
				return false;
			else
			{
				moveBits.template storeBits<BITSPOS, MOVE::countBits>(bits);
				if constexpr (sizeof...(MOVES2) > 0)
					return this->template parsePack<BITSPOS + MOVE::countBits, INDEX + 1, MOVES2...>(position, text, moveBits);
				else
					return true;
			}
		}
	public:
		bool parse_Implementation(const boardType& position, std::string& text, typename conjunctivemove::movebitsType& moveBits) const noexcept
		{
			std::string txt{ text };
			if constexpr (sizeof...(MOVES) > 0)
			{
				if (this->template parsePack<0, 0, MOVES...>(position, text, moveBits))
				{
					text = txt;
					return true;
				}
				else
					return false;
			}
			else
				return true;
		}
	private:
		template<size_t BITSPOS, size_t INDEX, typename MOVE, typename... MOVES2>
		std::string printPack(const boardType& position, const typename conjunctivemove::movebitsType& moveBits) const noexcept
		{
			const typename MOVE::movebitsType bits{ moveBits.template extractBits<BITSPOS,MOVE::countBits>() };
			std::string text{ std::get<INDEX>(this->m_Moves).toString(position, bits) };
			if constexpr (sizeof...(MOVES2) > 0)
				return text + this->template printPack<BITSPOS + MOVE::countBits, INDEX + 1, MOVES2...>(position, moveBits);
			else
				return text;
		}
	public:
		std::string toString_Implementation(const boardType& position, const typename conjunctivemove::movebitsType& moveBits) const noexcept
		{
			return this->template printPack<0, 0, MOVES...>(position, moveBits);
		}
	private:
		template<size_t BITSPOS, typename MOVE, typename... MOVES2>
		constexpr void encodePack(typename conjunctivemove::movebitsType& moveBits, typename MOVE::movebitsType bit, typename MOVES2::movebitsType... bits) const noexcept
		{
			moveBits.template storeBits<BITSPOS, MOVE::countBits>(bit);
			if constexpr (sizeof...(MOVES2) > 0)
				this->template encodePack<BITSPOS + MOVE::countBits, MOVES2...>(moveBits, bits...);
		}
	public:
		constexpr typename conjunctivemove::movebitsType create(typename MOVES::movebitsType... bits) const noexcept
		{
			typename conjunctivemove::movebitsType moveBits;
			if constexpr (sizeof...(MOVES) > 0)
				this->template encodePack<0, MOVES...>(moveBits, bits...);
			return moveBits;
		}
	public:
		constexpr conjunctivemove() noexcept :
			m_Moves{ std::tuple<MOVES...>(MOVES()...) }
		{

		}
		~conjunctivemove() noexcept = default;
		constexpr conjunctivemove(conjunctivemove&&) noexcept = default;
		constexpr conjunctivemove(const conjunctivemove&) noexcept = default;
		constexpr conjunctivemove& operator=(conjunctivemove&&) noexcept = default;
		constexpr conjunctivemove& operator=(const conjunctivemove&) noexcept = default;
	};
}