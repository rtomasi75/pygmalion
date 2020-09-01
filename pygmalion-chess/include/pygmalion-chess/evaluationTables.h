namespace pygmalion::chess
{
	template<typename DESCRIPTION_EVALUATION>
	class evaluationTables :
		public base_evaluation<DESCRIPTION_EVALUATION>
	{
	public:
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include <pygmalion-core/include_evaluation.h>

		constexpr static objectiveType m_PromotionStep{ 0.25 };
	private:
		constexpr static int8_t m_LazyMaterial[7]
		{
			3, // knight
			3, // bishop
			5, // rook
			9, // queen
			1, // pawn
			0  // king
		};
		constexpr static int8_t m_SquareValue[64]
		{
			1,1,1,1,1,1,1,1,
			1,2,2,2,2,2,2,1,
			1,2,3,3,3,3,2,1,
			1,2,3,4,4,3,2,1,
			1,2,3,4,4,3,2,1,
			1,2,3,3,3,3,2,1,
			1,2,2,2,2,2,2,1,
			1,1,1,1,1,1,1,1,
		};
		constexpr static int8_t maxSquareValue{ 4 };
		squaresType m_SquareImportance[maxSquareValue+1];
		objectiveType m_Material[2][6][64];
	public:
		evaluationTables() noexcept;
		~evaluationTables() noexcept = default;
		constexpr objectiveType material(const playerType p, const pieceType pc, const squareType sq) const noexcept
		{
			assert(p.isValid());
			assert(pc.isValid());
			assert(sq.isValid());
			return m_Material[p][pc][sq];
		}
	};
}