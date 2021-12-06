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
		constexpr PYGMALION_INLINE static const moveType& move() noexcept
		{
			return m_Move;
		}
		PYGMALION_INLINE static void makeMove(boardType& position, const movebitsType movebits, movedataType& data, const materialTableType& materialTable) noexcept
		{
			m_Move.doMove(position, movebits, data, materialTable);
			position.doMove();
		}

		PYGMALION_INLINE static void unmakeMove(boardType& position, const movedataType& data, const materialTableType& materialTable) noexcept
		{
			position.undoMove();
			m_Move.undoMove(position, data, materialTable);
		}

		PYGMALION_INLINE static bool parseMove(const boardType& position, const std::string& text, movebitsType& movebits, size_t& count) noexcept
		{
			return m_Move.parse(position, text, movebits, count);
		}

		PYGMALION_INLINE static std::string moveToString(const boardType& position, const movebitsType movebits) noexcept
		{
			return m_Move.toString(position, movebits);
		}

		PYGMALION_INLINE static bool isTacticalMove(const movebitsType movebits) noexcept
		{
			return motorType::isTacticalMove_Implementation(movebits);
		}
	};
}