namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename BOARD, size_t FIRST, size_t LAST>
		class setflagsMovedata
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
			constexpr setflagsMovedata() noexcept = default;
			constexpr setflagsMovedata(const uint_t<countAffectedFlags, false>& oldFlags_) noexcept :
				m_OldFlags{ oldFlags_ }
			{}
			constexpr setflagsMovedata(setflagsMovedata&&) noexcept = default;
			constexpr setflagsMovedata(const setflagsMovedata&) noexcept = default;
			constexpr setflagsMovedata& operator=(setflagsMovedata&&) noexcept = default;
			constexpr setflagsMovedata& operator=(const setflagsMovedata&) noexcept = default;
			~setflagsMovedata() noexcept = default;
		};
	}

	template<typename BOARD, size_t FIRST, size_t LAST>
	class setflagsmove :
		public move<BOARD, 0, detail::setflagsMovedata<BOARD, FIRST, LAST>, setflagsmove<BOARD, FIRST, LAST>>
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
			sstr << "" << sizeof(typename setflagsmove::movedataType) << ":" << setflagsmove::countBits << "@setflags(" << boardType::flagToString(firstFlag) << ":" << boardType::flagToString(lastFlag) << ")";
			return sstr.str();
		}
		constexpr setflagsmove() noexcept = default;
		~setflagsmove() noexcept = default;
		constexpr setflagsmove(setflagsmove&&) noexcept = default;
		constexpr setflagsmove(const setflagsmove&) noexcept = default;
		constexpr setflagsmove& operator=(setflagsmove&&) noexcept = default;
		constexpr setflagsmove& operator=(const setflagsmove&) noexcept = default;
		constexpr typename setflagsmove::movedataType doMove_Implementation(boardType& position, const typename setflagsmove::movebitsType& moveBits) const noexcept
		{
			const uint_t<countAffectedFlags, false> oldFlags{ position.template extractFlagRange<FIRST,LAST>() };
			position.template setFlagRange<FIRST, LAST>();
			return typename setflagsmove::movedataType(oldFlags);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename setflagsmove::movedataType& data) const noexcept
		{
			position.template storeFlagRange<FIRST, LAST>(data.oldFlags());
		}
		constexpr typename setflagsmove::movebitsType create() const noexcept
		{
			constexpr const typename setflagsmove::movebitsType bits{ setflagsmove::movebitsType::zero() };
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename setflagsmove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			if ((temp.length() > 0) && (temp[0] == '#'))
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
		std::string toString_Implementation(const boardType& position, const typename setflagsmove::movebitsType& moveBits) const noexcept
		{
			return "#" + boardType::flagToString(firstFlag) + ":" + boardType::flagToString(lastFlag);
		}
	};
}