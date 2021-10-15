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
			PYGMALION_INLINE const uint_t<countAffectedFlags, false> oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			PYGMALION_INLINE setflagsMovedata() noexcept = default;
			PYGMALION_INLINE setflagsMovedata(const uint_t<countAffectedFlags, false> oldFlags_) noexcept :
				m_OldFlags{ oldFlags_ }
			{}
			PYGMALION_INLINE setflagsMovedata(setflagsMovedata&&) noexcept = default;
			PYGMALION_INLINE setflagsMovedata(const setflagsMovedata&) noexcept = default;
			PYGMALION_INLINE setflagsMovedata& operator=(setflagsMovedata&&) noexcept = default;
			PYGMALION_INLINE setflagsMovedata& operator=(const setflagsMovedata&) noexcept = default;
			PYGMALION_INLINE ~setflagsMovedata() noexcept = default;
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
		PYGMALION_INLINE constexpr setflagsmove() noexcept = default;
		PYGMALION_INLINE ~setflagsmove() noexcept = default;
		PYGMALION_INLINE constexpr setflagsmove(setflagsmove&&) noexcept = default;
		PYGMALION_INLINE constexpr setflagsmove(const setflagsmove&) noexcept = default;
		PYGMALION_INLINE constexpr setflagsmove& operator=(setflagsmove&&) noexcept = default;
		PYGMALION_INLINE constexpr setflagsmove& operator=(const setflagsmove&) noexcept = default;
		PYGMALION_INLINE typename setflagsmove::movedataType doMove_Implementation(boardType& position, const typename setflagsmove::movebitsType moveBits, typename setflagsmove::movedataType& movedata) const noexcept
		{
			const uint_t<countAffectedFlags, false> oldFlags{ position.template extractFlagRange<FIRST,LAST>() };
			position.template setFlagRange<FIRST, LAST>();
			movedata = typename setflagsmove::movedataType(oldFlags);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename setflagsmove::movedataType& data) const noexcept
		{
			position.template storeFlagRange<FIRST, LAST>(data.oldFlags());
		}
		PYGMALION_INLINE typename setflagsmove::movebitsType create() const noexcept
		{
			constexpr const typename setflagsmove::movebitsType bits{ setflagsmove::movebitsType::zero() };
			return bits;
		}
		bool parse_Implementation(const boardType& position, const std::string& text, typename setflagsmove::movebitsType& moveBits, size_t& count) const noexcept
		{
			std::string temp{ text };
			size_t cnt{ 0 };
			if ((temp.length() > 0) && (temp[0] == '#'))
			{
				cnt++;
				std::string temp2{ temp.substr(cnt,temp.length() - cnt) };
				flagType f1;
				if (boardType::parseFlag(temp2, f1, cnt) && (f1 == firstFlag))
				{
					std::string temp3{ temp.substr(cnt,temp.length() - cnt) };
					if ((temp3.length() > 0) && (temp3[0] == ':'))
					{
						cnt++;
						std::string temp4{ temp.substr(cnt,temp.length() - cnt) };
						flagType f2;
						if (boardType::parseFlag(temp4, f2, cnt) && (f2 == lastFlag))
						{
							moveBits = create();
							count += cnt;
							return true;
						}
					}
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename setflagsmove::movebitsType moveBits) const noexcept
		{
			return "#" + boardType::flagToString(firstFlag) + ":" + boardType::flagToString(lastFlag);
		}
	};
}