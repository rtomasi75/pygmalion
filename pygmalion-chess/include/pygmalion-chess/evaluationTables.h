namespace pygmalion::chess
{
	template<typename DESCRIPTION_EVALUATION>
	class evaluationTables :
		public base_evaluation<DESCRIPTION_EVALUATION>
	{
	public:
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include <pygmalion-core/include_evaluation.h>

		constexpr static scoreType m_PromotionStep{ 0.25 };
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
		squaresType m_SquareImportance[maxSquareValue + 1];
		scoreType m_Material[2][6][64];
	public:
		evaluationTables::evaluationTables() noexcept
		{
			for (const auto p : playerType::range)
			{
				for (const auto pc : pieceType::range)
				{
					for (const auto sq : squareType::range)
						m_Material[2][6][64] = scoreType::zero();
				}
			}
			for (int8_t i = 0; i <= maxSquareValue; i++)
			{
				m_SquareImportance[i] = squaresType::none();
				for (const auto square : squareType::range)
				{
					if (m_SquareValue[square] == i)
						m_SquareImportance[i] += square;
				}
			}
			for (const auto rank : rankType::range)
			{
				for (const auto file : fileType::range)
				{
					const typename squareType square{ (rank & file) };
					for (const auto s : playerType::range)
					{
						squaresType moveMap;
						squaresType capMap;
						int8_t imp{ 0 };
						if ((rank != rank1) && (rank != rank8))
						{
							moveMap = generatorType::movegenTable().pawnMoveMap(square, s);
							capMap = generatorType::movegenTable().pawnCaptureMap(square, s);
							if ((rank == rank2) && (s == whitePlayer))
							{
								moveMap |= squaresType::up(moveMap);
							}
							if ((rank == rank7) && (s == blackPlayer))
							{
								moveMap |= squaresType::down(moveMap);
							}

							for (int8_t importance = 1; importance <= maxSquareValue; importance++)
							{
								const squaresType relevant{ m_SquareImportance[importance] };
								imp += importance * (relevant & moveMap).count();
								imp += importance * (relevant & capMap).count();
							}
							m_Material[s][pawn][square] = ((s == whitePlayer) ? scoreType::one() : -scoreType::one()) * (m_LazyMaterial[pawn] * scoreType::one() + scoreType::atom() * imp);
						}
						moveMap = generatorType::movegenTable().knightMoveMap(square);
						capMap = generatorType::movegenTable().knightMoveMap(square);
						imp = 0;
						for (int8_t importance = 1; importance <= maxSquareValue; importance++)
						{
							const squaresType relevant{ m_SquareImportance[importance] };
							imp += importance * (relevant & moveMap).count();
							imp += importance * (relevant & capMap).count();
						}
						m_Material[s][knight][square] = ((s == whitePlayer) ? scoreType::one() : -scoreType::one()) * (m_LazyMaterial[knight] * scoreType::one() + scoreType::atom() * imp);
						moveMap = squaresType::none();
						capMap = squaresType::none();
						generatorType::movegenTable().sliderMoveMaps(true, square, squaresType::none(), squaresType::all(), moveMap, capMap);
						imp = 0;
						for (int8_t importance = 1; importance <= maxSquareValue; importance++)
						{
							const squaresType relevant{ m_SquareImportance[importance] };
							imp += importance * (relevant & moveMap).count();
							imp += importance * (relevant & capMap).count();
						}
						m_Material[s][bishop][square] = ((s == whitePlayer) ? scoreType::one() : -scoreType::one()) * (m_LazyMaterial[bishop] * scoreType::one() + scoreType::atom() * imp);
						moveMap = squaresType::none();
						capMap = squaresType::none();
						generatorType::movegenTable().sliderMoveMaps(false, square, squaresType::none(), squaresType::all(), moveMap, capMap);
						imp = 0;
						for (int8_t importance = 1; importance <= maxSquareValue; importance++)
						{
							const squaresType relevant{ m_SquareImportance[importance] };
							imp += importance * (relevant & moveMap).count();
							imp += importance * (relevant & capMap).count();
						}
						m_Material[s][rook][square] = ((s == whitePlayer) ? scoreType::one() : -scoreType::one()) * (m_LazyMaterial[rook] * scoreType::one() + scoreType::atom() * imp);
						moveMap = squaresType::none();
						capMap = squaresType::none();
						generatorType::movegenTable().sliderMoveMaps(false, square, squaresType::none(), squaresType::all(), moveMap, capMap);
						generatorType::movegenTable().sliderMoveMaps(true, square, squaresType::none(), squaresType::all(), moveMap, capMap);
						imp = 0;
						for (int8_t importance = 1; importance <= maxSquareValue; importance++)
						{
							const squaresType relevant{ m_SquareImportance[importance] };
							imp += importance * (relevant & moveMap).count();
							imp += importance * (relevant & capMap).count();
						}
						m_Material[s][queen][square] = ((s == whitePlayer) ? scoreType::one() : -scoreType::one()) * (m_LazyMaterial[queen] * scoreType::one() + scoreType::atom() * imp);
						moveMap = generatorType::movegenTable().kingMoveMap(square);
						capMap = generatorType::movegenTable().kingMoveMap(square);
						imp = 0;
						for (int8_t importance = 1; importance <= maxSquareValue; importance++)
						{
							const squaresType relevant{ m_SquareImportance[importance] };
							imp += importance * (relevant & moveMap).count();
							imp += importance * (relevant & capMap).count();
						}
						m_Material[s][king][square] = ((s == whitePlayer) ? scoreType::one() : -scoreType::one()) * (m_LazyMaterial[king] * scoreType::one() + scoreType::atom() * imp);
					}
				}
			}
			for (int rank = 1; rank < 7; rank++)
			{
				for (const auto side : playerType::range)
				{
					const rankType promotionrank{ (side == whitePlayer) ? rank8 : rank1 };
					const int dist{ (side == whitePlayer) ? promotionrank - rank : rank - promotionrank };
					for (const auto file : fileType::range)
					{
						score promotedscore = m_Material[side][queen][promotionrank & file] + m_Material[side][knight][promotionrank & file];
						for (int d = 0; d <= dist; d++)
						{
							promotedscore *= static_cast<scoreType>(0.5);
						}
						m_Material[side][pawn][rank & file] += m_PromotionStep * promotedscore;
					}
				}
			}
			for (const auto sq : squareType::range)
			{
				m_Material[blackPlayer][pawn][sq] = -m_Material[whitePlayer][pawn][(-sq.rank()) & sq.file()];
			}
		}
		~evaluationTables() noexcept = default;
		constexpr scoreType material(const playerType p, const pieceType pc, const squareType sq) const noexcept
		{
			assert(p.isValid());
			assert(pc.isValid());
			assert(sq.isValid());
			return m_Material[p][pc][sq];
		}
	};
}