namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename BOARD, size_t FIRST, size_t LAST>
		class clearflagsMovedata
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
			constexpr static flagType firstFlag{ static_cast<typename flagType::baseType>(FIRST) };
			constexpr static flagType lastFlag{ static_cast<typename flagType::baseType>(LAST) };
			constexpr static size_t countAffectedFlags{ 1 + LAST - FIRST };
		private:
			uint_t<countAffectedFlags, false> m_OldFlags;
		public:
			constexpr const uint_t<countAffectedFlags, false>& oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr clearflagsMovedata() noexcept = default;
			constexpr clearflagsMovedata(const uint_t<countAffectedFlags, false>& oldFlags_) noexcept :
				m_OldFlags{ oldFlags_ }
			{}
			constexpr clearflagsMovedata(clearflagsMovedata&&) noexcept = default;
			constexpr clearflagsMovedata(const clearflagsMovedata&) noexcept = default;
			constexpr clearflagsMovedata& operator=(clearflagsMovedata&&) noexcept = default;
			constexpr clearflagsMovedata& operator=(const clearflagsMovedata&) noexcept = default;
			~clearflagsMovedata() noexcept = default;
		};
	}

	template<typename BOARD, size_t FIRST, size_t LAST>
	class clearflagsmove :
		public move<BOARD, 0, detail::clearflagsMovedata<BOARD, FIRST, LAST>, clearflagsmove<BOARD, FIRST, LAST>>
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static flagType firstFlag{ static_cast<typename flagType::baseType>(FIRST) };
		constexpr static flagType lastFlag{ static_cast<typename flagType::baseType>(LAST) };
		constexpr static size_t countAffectedFlags{ 1 + LAST - FIRST };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename clearflagsmove::movedataType) << ":" << clearflagsmove::countBits << "@clearflags(" << boardType::flagToString(firstFlag) << ":" << boardType::flagToString(lastFlag) << ")";
			return sstr.str();
		}
		constexpr clearflagsmove() noexcept = default;
		~clearflagsmove() noexcept = default;
		constexpr clearflagsmove(clearflagsmove&&) noexcept = default;
		constexpr clearflagsmove(const clearflagsmove&) noexcept = default;
		constexpr clearflagsmove& operator=(clearflagsmove&&) noexcept = default;
		constexpr clearflagsmove& operator=(const clearflagsmove&) noexcept = default;
		constexpr typename clearflagsmove::movedataType doMove_Implementation(boardType& position, const typename clearflagsmove::movebitsType& moveBits) const noexcept
		{
			const uint_t<countAffectedFlags, false> oldFlags{ position.template extractFlagRange<FIRST,LAST>() };
			position.template clearFlagRange<FIRST, LAST>();
			return typename clearflagsmove::movedataType(oldFlags);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename clearflagsmove::movedataType& data) const noexcept
		{
			position.template storeFlagRange<FIRST, LAST>(data.oldFlags());
		}
		constexpr typename clearflagsmove::movebitsType create() const noexcept
		{
			constexpr const typename clearflagsmove::movebitsType bits{ clearflagsmove::movebitsType::zero() };
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename clearflagsmove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			if ((temp.length() > 0) && (temp[0] == '.'))
			{
				temp = temp.substr(1, temp.length() - 1);
				flagType f1;
				if (boardType::parseFlag(temp, f1) && (f1 == firstFlag))
				{
					if ((temp.length() > 0) && (temp[0] == ':'))
					{
						temp = temp.substr(1, temp.length() - 1);
						flagType f2;
						if (boardType::parseFlag(temp, f2) && (f2 == lastFlag))
						{
							moveBits = create();
							text = temp;
							return true;
						}
					}
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename clearflagsmove::movebitsType& moveBits) const noexcept
		{
			return "." + boardType::flagToString(firstFlag) + ":" + boardType::flagToString(lastFlag);
		}
	};
}