namespace pygmalion::mechanics
{
	namespace detail
	{
		template<size_t value0, size_t... values>
		class F
		{
		public:
			constexpr static const size_t value{ std::max(value0,F<values...>::value) };
		};

		template<size_t value0>
		class F<value0>
		{
		public:
			constexpr static const size_t value{ value0 };
		};
		template<typename BOARD, typename... MOVES>
		class combinedMovedata
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
			constexpr static const size_t countMuxBits{ pygmalion::detail::requiredUnsignedBits(sizeof...(MOVES)) };
			constexpr static size_t payloadSize{ F < (sizeof(typename MOVES::movedataType))... > ::value };
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
			constexpr combinedMovedata() noexcept = default;
		};

	}

	template<typename BOARD, typename... MOVES>
	class combinedmove :
		public move<BOARD, detail::F<MOVES::countBits...>::value + pygmalion::detail::requiredUnsignedBits(sizeof...(MOVES)), detail::combinedMovedata<BOARD, MOVES...>, combinedmove<BOARD, MOVES...>>
	{
	public:
		constexpr static const size_t countDataBits{ detail::F<MOVES::countBits...>::value };
		constexpr static const size_t countMuxBits{ pygmalion::detail::requiredUnsignedBits(sizeof...(MOVES)) };
		using muxbitsType = uint_t<countMuxBits, false>;
		using databitsType = uint_t<countDataBits, false>;
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "|" << combinedmove::countMuxBits << "bit@mux|";
			((sstr << MOVES::name() << "|"), ...);
			sstr << "=>" << combinedmove::countBits << "bit";
			return sstr.str();
		}
		template<typename MOVE>
		static bool doMovePack(boardType& position, databitsType& dataBits, muxbitsType& count, const muxbitsType& selector, typename combinedmove::movedataType& combinedData) noexcept
		{
			if (count == selector)
			{
				typename MOVE::movebitsType bits{ dataBits.template extractBits<0,MOVE::countBits>() };
				typename MOVE::movedataType& data{ *reinterpret_cast<typename MOVE::movedataType*>(combinedData.dataPtr()) };
				data = MOVE::doMove(position, bits);
				combinedData.mux() = selector;
				count++;
				return true;
			}
			else
			{
				count++;
				return false;
			}
		}
		constexpr static typename combinedmove::movedataType doMove_Implementation(boardType& position, const typename combinedmove::movebitsType& moveBits) noexcept
		{
			muxbitsType mux{ moveBits.template extractBits<countDataBits, countMuxBits>() };
			databitsType bits{ moveBits.template extractBits<0, countDataBits>() };
			muxbitsType count{ muxbitsType::zero() };
			typename combinedmove::movedataType data;
			if ((combinedmove::doMovePack<MOVES>(position, bits, count, mux, data) || ...))
				return data;
			else
			{
				assert(0);
				return data;
			}
			return typename combinedmove::movedataType();
		}
		template<typename MOVE>
		static bool undoMovePack(boardType& position, muxbitsType& count, const typename combinedmove::movedataType& combinedData, const playerType movingPlayer) noexcept
		{
			if (count == combinedData.mux())
			{
				count++;
				const typename MOVE::movedataType& data{ *reinterpret_cast<const typename MOVE::movedataType*>(combinedData.dataPtr()) };
				MOVE::undoMove(position, data, movingPlayer);
				return true;
			}
			else
			{
				count++;
				return false;
			}
		}
		constexpr static void undoMove_Implementation(boardType& position, const typename combinedmove::movedataType& data, const playerType movingPlayer) noexcept
		{
			muxbitsType count{ muxbitsType::zero() };
			if (!((combinedmove::undoMovePack<MOVES>(position, count, data, movingPlayer) || ...)))
				assert(0);
		}
	private:
		template<typename MOVE>
		static bool parsePack(const boardType& position, std::string& text, databitsType& dataBits, muxbitsType& count) noexcept
		{
			typename MOVE::movebitsType bits{ MOVE::movebitsType::zero() };
			if (MOVE::parse(position, text, bits))
			{
				dataBits.template storeBits<0, MOVE::countBits>(bits);
				return true;
			}
			else
			{
				count++;
				return false;
			}
		}
	public:
		static bool parse_Implementation(const boardType& position, std::string& text, typename combinedmove::movebitsType& moveBits) noexcept
		{
			databitsType bits{ databitsType::zero() };
			muxbitsType mux{ muxbitsType::zero() };
			if ((combinedmove::parsePack<MOVES>(position, text, bits, mux) || ...))
			{
				moveBits.template storeBits<0, countDataBits>(bits);
				moveBits.template storeBits<countDataBits, countMuxBits>(mux);
				return true;
			}
			else
				return false;
		}
	private:
		template<typename MOVE>
		static bool printPack(const boardType& position, databitsType& dataBits, muxbitsType& count, const muxbitsType& selector, std::string& text) noexcept
		{
			if (count == selector)
			{
				typename MOVE::movebitsType bits{ dataBits.template extractBits<0,MOVE::countBits>() };
				count++;
				text = MOVE::toString(position, bits);
				return true;
			}
			else
			{
				count++;
				return false;
			}
		}
	public:
		static std::string toString_Implementation(const boardType& position, const typename combinedmove::movebitsType& moveBits) noexcept
		{
			muxbitsType mux{ moveBits.template extractBits<countDataBits, countMuxBits>() };
			databitsType bits{ moveBits.template extractBits<0, countDataBits>() };
			muxbitsType count{ muxbitsType::zero() };
			std::string text;
			if ((combinedmove::printPack<MOVES>(position, bits, count, mux, text) || ...))
				return text;
			else
			{
				assert(0);
				return "";
			}
		}
	};
}