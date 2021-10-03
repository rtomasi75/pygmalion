namespace pygmalion::chess
{
	template<unsigned MAXDIST, typename GENERATOR>
	class tropism
	{
	public:
		using generatorType = GENERATOR;
		using descriptorMechanics = typename GENERATOR::descriptorMechanics;
#include "pygmalion-mechanics/include_mechanics.h"
		constexpr static inline const unsigned int maxDistance{ MAXDIST };
	private:
		std::array<std::array<squaresType, maxDistance + 1>, countPieces> m_DistanceSquares;
	public:
		tropism() noexcept
		{

		}
		~tropism() noexcept = default;
		const squaresType& distanceSquares(const pieceType pc, const unsigned int distance) const noexcept
		{
			PYGMALION_ASSERT(distance <= maxDistance);
			return m_DistanceSquares[pc][distance];
		}
		void compute(const squareType seed, const playerType pl, const squaresType playerPawns, const squaresType& otherPawns, const squareType playerKing, const squareType otherKing) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			squaresType attacked{ generatorType::movegenKing.attacks(otherKing,all) };
			if (pl == descriptorMechanics::whitePlayer)
			{
				const squaresType pawnsTemp{ otherPawns.down() };
				attacked |= pawnsTemp.left() | pawnsTemp.right();
			}
			else
			{
				const squaresType pawnsTemp{ otherPawns.up() };
				attacked |= pawnsTemp.left() | pawnsTemp.right();
			}
			const squaresType forbidden{ playerPawns | playerKing | otherKing };
			const squaresType unoccupied{ ~(otherPawns | forbidden) };
			const squaresType allowedKing{ ~(attacked | forbidden) };
			const squaresType allowed{ ~forbidden };
			generatorType::template attackTropismKing<maxDistance>(seed, pl, allowedKing, m_DistanceSquares[descriptorMechanics::king]);
			generatorType::template attackTropismKnight<maxDistance>(seed, pl, allowed, m_DistanceSquares[descriptorMechanics::knight]);
			generatorType::template attackTropismBishop<maxDistance>(seed, pl, allowed, unoccupied, m_DistanceSquares[descriptorMechanics::bishop]);
			generatorType::template attackTropismRook<maxDistance>(seed, pl, allowed, unoccupied, m_DistanceSquares[descriptorMechanics::rook]);
			generatorType::template attackTropismQueen<maxDistance>(seed, pl, allowed, unoccupied, m_DistanceSquares[descriptorMechanics::queen]);
			generatorType::template attackTropismPawn<maxDistance>(seed, pl, allowed, unoccupied, otherPawns, m_DistanceSquares[descriptorMechanics::knight], m_DistanceSquares[descriptorMechanics::bishop], m_DistanceSquares[descriptorMechanics::rook], m_DistanceSquares[descriptorMechanics::queen], m_DistanceSquares[descriptorMechanics::pawn]);
		}
		void compute(const squaresType& seeds, const playerType pl, const squaresType& playerPawns, const squaresType& otherPawns, const squareType playerKing, const squareType otherKing) noexcept
		{
			constexpr const squaresType all{ squaresType::all() };
			squaresType attacked{ generatorType::movegenKing.attacks(otherKing,all) };
			if (pl == descriptorMechanics::whitePlayer)
			{
				const squaresType pawnsTemp{ otherPawns.down() };
				attacked |= pawnsTemp.left() | pawnsTemp.right();
			}
			else
			{
				const squaresType pawnsTemp{ otherPawns.up() };
				attacked |= pawnsTemp.left() | pawnsTemp.right();
			}
			const squaresType forbidden{ playerPawns | playerKing | otherKing };
			const squaresType unoccupied{ ~(otherPawns | forbidden) };
			const squaresType allowedKing{ ~(attacked | forbidden) };
			const squaresType allowed{ ~forbidden };
			generatorType::template attackTropismKing<maxDistance>(seeds, pl, allowedKing, m_DistanceSquares[descriptorMechanics::king]);
			generatorType::template attackTropismKnight<maxDistance>(seeds, pl, allowed, m_DistanceSquares[descriptorMechanics::knight]);
			generatorType::template attackTropismBishop<maxDistance>(seeds, pl, allowed, unoccupied, m_DistanceSquares[descriptorMechanics::bishop]);
			generatorType::template attackTropismRook<maxDistance>(seeds, pl, allowed, unoccupied, m_DistanceSquares[descriptorMechanics::rook]);
			generatorType::template attackTropismQueen<maxDistance>(seeds, pl, allowed, unoccupied, m_DistanceSquares[descriptorMechanics::queen]);
			generatorType::template attackTropismPawn<maxDistance>(seeds, pl, allowed, unoccupied, otherPawns, m_DistanceSquares[descriptorMechanics::knight], m_DistanceSquares[descriptorMechanics::bishop], m_DistanceSquares[descriptorMechanics::rook], m_DistanceSquares[descriptorMechanics::queen], m_DistanceSquares[descriptorMechanics::pawn]);
		}
		void dumpDistances(const pieceType pc, std::ostream& str) const noexcept
		{
			for (const auto r : rankType::range)
			{
				const rankType rank{ -r };
				for (const auto file : fileType::range)
				{
					const squareType sq{ rank & file };
					bool bDone{ false };
					int d{ -1 };
					for (unsigned int i = 0; i <= maxDistance; i++)
					{
						if (distanceSquares(pc, i)[sq])
						{
							if (bDone)
								d = -1;
							else
							{
								d = static_cast<int>(i);
								bDone = true;
							}
						}
					}
					if (bDone)
					{
						if (d < 0)
							str << "E";
						else
							str << d;
					}
					else
						str << ".";
				}
				str << std::endl;
			}
		}
	};
}