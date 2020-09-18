namespace pygmalion
{
	template <typename DESCRIPTOR_MECHANICS, typename INSTANCE>
	class motor :
		public DESCRIPTOR_MECHANICS
	{
	public:

		using mechanicsType = INSTANCE;
		using descriptorMechanics = DESCRIPTOR_MECHANICS;
#include "include_mechanics.h"

		class moveinfo
		{
		private:
			playerType m_Player;
			movedataType m_Movedata;
		public:
			constexpr moveinfo(const moveinfo&) noexcept = default;
			constexpr moveinfo(moveinfo&&) noexcept = default;
			constexpr moveinfo& operator=(const moveinfo&) noexcept = default;
			constexpr moveinfo& operator=(moveinfo&&) noexcept = default;
			constexpr moveinfo() noexcept = default;
			constexpr moveinfo(const playerType p, movedataType&& md) noexcept :
				m_Player{ p },
				m_Movedata{ std::move(md) }
			{}
			constexpr playerType player() const noexcept
			{
				return m_Player;
			}
			constexpr const movedataType& data() const noexcept
			{
				return m_Movedata;
			}
			~moveinfo() noexcept = default;
		};
		using moveinfoType = moveinfo;
		static moveinfoType makeMove(boardType& position, const movebitsType& movebits) noexcept
		{
			moveinfoType info{ moveinfo(position.movingPlayer(), moveType::doMove(position, movebits)) };
			position.setMovingPlayer(++position.movingPlayer());
			return info;
		}

		static void unmakeMove(boardType& position, const moveinfoType& info) noexcept
		{
			moveType::undoMove(position, info.data(), info.player());
			position.setMovingPlayer(info.player());
		}

		static bool parseMove(const boardType& position, std::string& text, movebitsType& movebits) noexcept
		{
			return moveType::parse(position, text, movebits);
		}

		static std::string moveToString(const boardType& position, const movebitsType& movebits) noexcept
		{
			return moveType::toString(position, movebits);
		}
	};
}