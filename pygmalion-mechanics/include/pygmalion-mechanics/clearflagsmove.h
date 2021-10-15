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
			PYGMALION_INLINE const uint_t<countAffectedFlags, false>& oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			PYGMALION_INLINE clearflagsMovedata() noexcept = default;
			PYGMALION_INLINE clearflagsMovedata(const uint_t<countAffectedFlags, false> oldFlags_) noexcept :
				m_OldFlags{ oldFlags_ }
			{}
			PYGMALION_INLINE clearflagsMovedata(clearflagsMovedata&&) noexcept = default;
			PYGMALION_INLINE clearflagsMovedata(const clearflagsMovedata&) noexcept = default;
			PYGMALION_INLINE clearflagsMovedata& operator=(clearflagsMovedata&&) noexcept = default;
			PYGMALION_INLINE clearflagsMovedata& operator=(const clearflagsMovedata&) noexcept = default;
			PYGMALION_INLINE ~clearflagsMovedata() noexcept = default;
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
		PYGMALION_INLINE constexpr clearflagsmove() noexcept = default;
		PYGMALION_INLINE ~clearflagsmove() noexcept = default;
		PYGMALION_INLINE constexpr clearflagsmove(clearflagsmove&&) noexcept = default;
		PYGMALION_INLINE constexpr clearflagsmove(const clearflagsmove&) noexcept = default;
		PYGMALION_INLINE constexpr clearflagsmove& operator=(clearflagsmove&&) noexcept = default;
		PYGMALION_INLINE constexpr clearflagsmove& operator=(const clearflagsmove&) noexcept = default;
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename clearflagsmove::movebitsType moveBits, typename clearflagsmove::movedataType& movedata) const noexcept
		{
			const uint_t<countAffectedFlags, false> oldFlags{ position.template extractFlagRange<FIRST,LAST>() };
			position.template clearFlagRange<FIRST, LAST>();
			movedata= typename clearflagsmove::movedataType(oldFlags);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename clearflagsmove::movedataType& data) const noexcept
		{
			position.template storeFlagRange<FIRST, LAST>(data.oldFlags());
		}
		PYGMALION_INLINE typename clearflagsmove::movebitsType create() const noexcept
		{
			constexpr const typename clearflagsmove::movebitsType bits{ clearflagsmove::movebitsType::zero() };
			return bits;
		}
		bool parse_Implementation(const boardType& position, const std::string& text, typename clearflagsmove::movebitsType& moveBits, size_t& count) const noexcept
		{
			std::string temp{ text };
			size_t cnt{ 0 };
			if ((temp.length() > 0) && (temp[0] == '.'))
			{
				cnt++;
				std::string temp2{ temp.substr(cnt, temp.length() - cnt) };
				flagType f1;
				if (boardType::parseFlag(temp2, f1, cnt) && (f1 == firstFlag))
				{
					std::string temp3{ temp.substr(cnt, temp.length() - cnt) };
					if ((temp3.length() > 0) && (temp3[0] == ':'))
					{
						cnt++;
						std::string temp4{ temp.substr(cnt, temp.length() - cnt) };
						flagType f2;
						if (boardType::parseFlag(temp4, f2,cnt) && (f2 == lastFlag))
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
		std::string toString_Implementation(const boardType& position, const typename clearflagsmove::movebitsType moveBits) const noexcept
		{
			return "." + boardType::flagToString(firstFlag) + ":" + boardType::flagToString(lastFlag);
		}
	};
}