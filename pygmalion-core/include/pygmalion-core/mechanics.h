namespace pygmalion
{
	template <typename DESCRIPTOR_MECHANICS, typename INSTANCE>
	class mechanics :
		public base_mechanics<DESCRIPTOR_MECHANICS>
	{
	public:

		using mechanicsType = INSTANCE;

		using descriptorMechanics = DESCRIPTOR_MECHANICS;
#include "include_mechanics.h"


		class movedata :
			public base_mechanics<DESCRIPTOR_MECHANICS>
		{
		public:
			using mechanicsType = INSTANCE;

			using descriptorMechanics = DESCRIPTOR_MECHANICS;
#include "include_mechanics.h"

		private:
			playerType m_MovingPlayer;
			moveType m_Move;
			bool m_IsNullMove;
		public:
			constexpr movedata(const boardType& position, const playerType movingPlayer) noexcept :
				m_MovingPlayer{ movingPlayer },
				m_IsNullMove{ true }
			{

			}
			constexpr movedata(const boardType& position, const moveType& mv) noexcept :
				m_MovingPlayer{ position.movingPlayer() },
				m_Move{ mv },
				m_IsNullMove{ false }
			{
			}
			~movedata() noexcept = default;
			constexpr const playerType& movingPlayer() const noexcept
			{
				return m_MovingPlayer;
			}
			constexpr bool isNullMove() const noexcept
			{
				return m_IsNullMove;
			}
			constexpr const moveType& move() const noexcept
			{
				return m_Move;
			}
		};


		static void initializePosition(boardType& position) noexcept
		{
			mechanicsType::initializePosition_Implementation(position);
		}

		template<typename MOVEDATA>
		static void makeMove(boardType& position, const MOVEDATA& md) noexcept
		{
			mechanicsType::makeMove_Implementation(position, md);
		}

		template<typename MOVEDATA>
		static void unmakeMove(boardType& position, const MOVEDATA& md) noexcept
		{
			mechanicsType::unmakeMove_Implementation(position, md);
		}
	};
}