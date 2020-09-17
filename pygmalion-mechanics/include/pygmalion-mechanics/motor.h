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
		};
		using moveinfoType = moveinfo;
		static moveinfoType&& makeMove(boardType& position, const movebitsType& movebits) noexcept
		{
			moveinfoType info{ moveinfo(position.movingPlayer(), moveType::doMove(position, movebits)) };
			position.setMovingPlayer(++postion.movingPlayer());
			return std::move(info);
		}

		template<typename MOVEDATA>
		static void unmakeMove(boardType& position, const moveinfoType& info) noexcept
		{
			mechanicsType::unmakeMove_Implementation(position, info.data(), info.player());
			position.setMovingPlayer(info.player());
		}
	};
}