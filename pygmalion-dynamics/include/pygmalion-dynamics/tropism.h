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
		std::array<squaresType, MAXDIST + 1> m_King;
		std::array<squaresType, MAXDIST + 1> m_Knights;
		std::array<squaresType, MAXDIST + 1> m_Bishops;
		std::array<squaresType, MAXDIST + 1> m_Rooks;
		std::array<squaresType, MAXDIST + 1> m_Rooks;
	};
}