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
			unsigned char m_Data[payloadSize];
		public:
			constexpr unsigned char* dataPtr() noexcept
			{
				return m_Data;
			}
			constexpr const unsigned char* dataPtr() const noexcept
			{
				return m_Data;
			}
			constexpr conjunctiveMovedata() noexcept = default;
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
		template<typename MOVE, typename... MOVES2>
		static std::string namePack() noexcept
		{
			if constexpr (sizeof...(MOVES2) > 0)
				return MOVE::name() + " & " + conjunctivemove::namePack<MOVES2...>();
			else
				return MOVE::name();
		}
	public:
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << conjunctivemove::countBits << "bit@[ ";
			if constexpr (sizeof...(MOVES) > 0)
				sstr << conjunctivemove::namePack<MOVES...>();
			sstr << " ]";
			return sstr.str();
		}
	private:
		template<size_t BITSPOS, size_t DATAPOS, typename MOVE, typename... MOVES2>
		constexpr static void doMovePack(boardType& position, const typename MOVE::movebitsType& moveBits, typename conjunctivemove::movedataType& combinedData) noexcept
		{
			typename MOVE::movebitsType bits{ moveBits.template extractBits<BITSPOS,MOVE::countBits>() };
			typename MOVE::movedataType& data{ *reinterpret_cast<typename MOVE::movedataType*>(combinedData.dataPtr() + DATAPOS) };
			data = MOVE::doMove(position, bits);
			if constexpr (sizeof...(MOVES2) > 0)
				conjunctivemove::doMovePack<BITSPOS + MOVE::countBits, DATAPOS + sizeof(typename MOVE::movedataType), MOVES2...>(position, moveBits, combinedData);
		}
	public:
		constexpr static typename conjunctivemove::movedataType doMove_Implementation(boardType& position, const typename conjunctivemove::movebitsType& moveBits) noexcept
		{
			typename conjunctivemove::movedataType data;
			if constexpr (sizeof...(MOVES) > 0)
				conjunctivemove::doMovePack<0, 0, MOVES...>(position, moveBits, data);
			return data;
		}
	private:
		template<size_t DATAPOS, typename MOVE, typename... MOVES2>
		constexpr static void undoMovePack(boardType& position, const typename conjunctivemove::movedataType& combinedData, const playerType movingPlayer) noexcept
		{
			const typename MOVE::movedataType& data{ *reinterpret_cast<const typename MOVE::movedataType*>(combinedData.dataPtr() + DATAPOS) };
			MOVE::undoMove(position, data, movingPlayer);
			if constexpr (sizeof...(MOVES2) > 0)
				conjunctivemove::undoMovePack<DATAPOS + sizeof(typename MOVE::movedataType), MOVES2...>(position, combinedData, movingPlayer);
		}
	public:
		constexpr static void undoMove_Implementation(boardType& position, const typename conjunctivemove::movedataType& data, const playerType movingPlayer) noexcept
		{
			if constexpr (sizeof...(MOVES) > 0)
				conjunctivemove::undoMovePack<0, MOVES...>(position, data, movingPlayer);
		}
	private:
		template<size_t BITSPOS, typename MOVE, typename... MOVES2>
		static bool parsePack(const boardType& position, std::string& text, typename conjunctivemove::movedataType& moveBits) noexcept
		{
			typename MOVE::movebitsType bits{ MOVE::movebitsType::zero() };
			if (!MOVE::parse(position, text, bits))
				return false;
			else
			{
				moveBits.template storeBits<BITSPOS, MOVE::countBits>(bits);
				if constexpr (sizeof...(MOVES2) > 0)
				{
					if (text[0] == ',')
					{
						text = text.substr(1, text.length() - 1);
						return conjunctivemove::parsePack<BITSPOS + MOVE::countBits, MOVES2...>(position, text, moveBits);
					}
					else
						return false;
				}
				else
					return true;
			}
		}
	public:
		static bool parse_Implementation(const boardType& position, std::string& text, typename conjunctivemove::movebitsType& moveBits) noexcept
		{
			std::string txt{ text };
			if constexpr (sizeof...(MOVES) > 0)
			{
				if (conjunctivemove::parsePack<0, MOVES...>(position, text, moveBits))
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
		template<size_t BITSPOS, typename MOVE, typename... MOVES2>
		static std::string printPack(const boardType& position, const typename conjunctivemove::movebitsType& moveBits) noexcept
		{
			const typename MOVE::movebitsType bits{ moveBits.template extractBits<BITSPOS,MOVE::countBits>() };
			std::string text{ MOVE::toString(position, bits) };
			if constexpr (sizeof...(MOVES2) > 0)
				return text + "," + conjunctivemove::printPack<BITSPOS + MOVE::countBits, MOVES2...>(position, moveBits);
			else
				return text;
		}
	private:
		template<size_t BITSPOS, typename MOVE, typename... MOVES2>
		static void encodePack(typename conjunctivemove::movebitsType& moveBits, typename MOVE::movebitsType bit, typename MOVES2::movebitsType... bits) noexcept
		{
			moveBits.template storeBits<BITSPOS, MOVE::countBits>(bits);
			if constexpr (sizeof...(MOVES2) > 0)
				encodePack<BITSPOS + MOVE::countBits, MOVES2...>(moveBits, bits...);
		}
	public:
		static std::string toString_Implementation(const boardType& position, const typename conjunctivemove::movebitsType& moveBits) noexcept
		{
			return conjunctivemove::printPack<0, MOVES...>(position, moveBits);
		}
		constexpr static typename conjunctivemove::movebitsType create(typename MOVES::movebitsType... bits) noexcept
		{
			typename conjunctivemove::movebitsType moveBits;
			if constexpr (sizeof...(MOVES) > 0)
				encodePack<0, MOVES...>(moveBits, bits...);
			return moveBits;
		}
	};
}