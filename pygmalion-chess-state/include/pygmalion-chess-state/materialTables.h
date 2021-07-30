namespace pygmalion::chess::state
{
	template<typename DESCRIPTION_STATE>
	class materialTables :
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include <pygmalion-state/include_state.h>
	private:
		constexpr static materialScore m_LazyMaterial[]
		{
			static_cast<materialScore>(3.0), // knight
			static_cast<materialScore>(3.0), // bishop
			static_cast<materialScore>(5.0), // rook
			static_cast<materialScore>(9.0), // queen
			static_cast<materialScore>(1.0), // pawn
			static_cast<materialScore>(0.0)  // king
		};
	public:
		constexpr materialTables() noexcept
		{
		}
		~materialTables() noexcept = default;
		constexpr materialScore material(const playerType p, const pieceType pc) const noexcept
		{
			assert(p.isValid());
			assert(pc.isValid());
			return p == descriptorState::whitePlayer ? m_LazyMaterial[pc] : -m_LazyMaterial[pc];
		}
	};
}