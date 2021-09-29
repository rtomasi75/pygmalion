namespace pygmalion
{
	template<unsigned MAXDIST, typename GENERATOR>
	class tropism
	{
	public:
		using generatorType = GENERATOR;
		using descriptorMechanics = typename GENERATOR::descriptorMechanics;
#include "pygmalion-mechanics/include_mechanics.h"
	private:
		std::array<std::array<squaresType, MAXDIST + 1>, countPieces> m_DistanceSquares;
	public:
		tropism() noexcept
		{

		}
		~tropism() noexcept = default;
		constexpr const squaresType& distanceSquares(const pieceType& pc, const unsigned int distance) const noexcept
		{
			return m_DistanceSquares[pc][distance];
		}
		template<typename stackType>
		void compute(const squareType& seed, const playerType& pl, const stackType& stack) noexcept
		{
			generatorType::template attackTropismKing<MAXDIST>(seed, pl, stack, m_DistanceSquares[descriptorMechanics::king]);
			generatorType::template attackTropismKnight<MAXDIST>(seed, pl, stack, m_DistanceSquares[descriptorMechanics::knight]);
			generatorType::template attackTropismBishop<MAXDIST>(seed, pl, stack, m_DistanceSquares[descriptorMechanics::bishop]);
			generatorType::template attackTropismRook<MAXDIST>(seed, pl, stack, m_DistanceSquares[descriptorMechanics::rook]);
			generatorType::template attackTropismQueen<MAXDIST>(seed, pl, stack, m_DistanceSquares[descriptorMechanics::queen]);
			generatorType::template attackTropismPawn<MAXDIST>(seed, pl, stack, m_DistanceSquares[descriptorMechanics::knight], m_DistanceSquares[descriptorMechanics::bishop], m_DistanceSquares[descriptorMechanics::rook], m_DistanceSquares[descriptorMechanics::queen], m_DistanceSquares[descriptorMechanics::queen]);
		}
	};
}