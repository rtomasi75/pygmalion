namespace pygmalion
{
	template <typename DESCRIPTOR_MECHANICS, typename INSTANCE>
	class motor :
		public DESCRIPTOR_MECHANICS
	{
	public:
		using motorType = INSTANCE;
		using mechanicsType = INSTANCE;
		using descriptorMechanics = DESCRIPTOR_MECHANICS;
#include "include_mechanics.h"
	private:
		constexpr static const inline moveType m_Move{ moveType() };
	public:
		constexpr static const moveType& move() noexcept
		{
			return m_Move;
		}
		static movedataType makeMove(boardType& position, const movebitsType movebits) noexcept
		{
			movedataType data{ m_Move.doMove(position, movebits) };
			return data;
		}

		static void unmakeMove(boardType& position, const movedataType& data) noexcept
		{
			m_Move.undoMove(position, data);
		}

		static bool parseMove(const boardType& position, std::string& text, movebitsType& movebits) noexcept
		{
			return m_Move.parse(position, text, movebits);
		}

		static std::string moveToString(const boardType& position, const movebitsType movebits) noexcept
		{
			return m_Move.toString(position, movebits);
		}

		static bool isTacticalMove(const movebitsType movebits) noexcept
		{
			return motorType::isTacticalMove_Implementation(movebits);
		}
	};
}