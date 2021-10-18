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
		PYGMALION_TUNABLE static inline std::array<materialScore, 6> m_LazyMaterial
		{
			arrayhelper::generate<6,materialScore>(
				[](const size_t index)
				{
					switch (index)
					{
					case 0x0: //knight
						return static_cast<materialScore>(3.0);
					case 0x1: //bishop
						return static_cast<materialScore>(3.0);
					case 0x2: //rook
						return static_cast<materialScore>(5.0);
					case 0x3: //queen
						return static_cast<materialScore>(9.0);
					case 0x4: //pawn
						return static_cast<materialScore>(1.0);
					case 0x5: //king
						return static_cast<materialScore>(0.0);
					default:
						PYGMALION_UNREACHABLE;
						return static_cast<materialScore>(0.0);
					}
				}
			)
		};
	public:
		constexpr materialTables() noexcept
		{
		}
		~materialTables() noexcept = default;
		PYGMALION_INLINE PYGMALION_TUNABLE materialScore material(const playerType p, const pieceType pc) const noexcept
		{
			return p == descriptorState::whitePlayer ? m_LazyMaterial[pc] : -m_LazyMaterial[pc];
		}
#if defined(PYGMALION_TUNE)&&(PYGMALION_TUNE==1)
		static void setTunedMaterial(const pieceType pc, const double whiteValue) noexcept
		{
			m_LazyMaterial[pc] = static_cast<materialScore>(whiteValue);
		}
#endif

	};
}