namespace pygmalion::chess
{
	class rays :
		public descriptor_dynamics
	{
	public:
		using descriptorDynamics = descriptor_dynamics;
#include "pygmalion-dynamics/include_dynamics.h"
	private:
		std::array<std::array<squaresType, countSquares>, 8> m_Ray;
	public:
		constexpr static inline int rayUp{ 0 };
		constexpr static inline int rayUpLeft{ 1 };
		constexpr static inline int rayLeft{ 2 };
		constexpr static inline int rayUpRight{ 3 };
		constexpr static inline int rayDownLeft{ 4 };
		constexpr static inline int rayRight{ 5 };
		constexpr static inline int rayDownRight{ 6 };
		constexpr static inline int rayDown{ 7 };
		constexpr rays() noexcept :
			m_Ray{ arrayhelper::make<8,std::array<squaresType, countSquares>>(arrayhelper::make<countSquares,squaresType>(squaresType::none())) }
		{
			for (const auto i : squareType::range)
			{
				const int file0{ i.file() };
				const int rank0{ i.rank() };
				for (int k = 1; k < 8; k++)
				{
					const int file{ file0 + k };
					const int rank{ rank0 + k };
					if ((file >= 8) || (rank >= 8))
						break;
					const squareType sq{ fileType(file) & rankType(rank) };
					this->m_Ray[rayUpRight][i] |= sq;
				}
				for (int k = 1; k < 8; k++)
				{
					const int file{ file0 - k };
					const int rank{ rank0 + k };
					if ((file < 0) || (rank >= 8))
						break;
					const squareType sq{ fileType(file) & rankType(rank) };
					this->m_Ray[rayUpLeft][i] |= sq;
				}
				for (int k = 1; k < 8; k++)
				{
					const int file{ file0 + k };
					const int rank{ rank0 - k };
					if ((file >= 8) || (rank < 0))
						break;
					const squareType sq{ fileType(file) & rankType(rank) };
					this->m_Ray[rayDownRight][i] |= sq;
				}
				for (int k = 1; k < 8; k++)
				{
					const int file{ file0 - k };
					const int rank{ rank0 - k };
					if ((file < 0) || (rank < 0))
						break;
					const squareType sq{ fileType(file) & rankType(rank) };
					this->m_Ray[rayDownLeft][i] |= sq;
				}
				for (int k = 1; k < 8; k++)
				{
					const int file{ file0 };
					const int rank{ rank0 + k };
					if (rank >= 8)
						break;
					const squareType sq{ fileType(file) & rankType(rank) };
					this->m_Ray[rayUp][i] |= sq;
				}
				for (int k = 1; k < 8; k++)
				{
					const int file{ file0 };
					const int rank{ rank0 - k };
					if (rank < 0)
						break;
					const squareType sq{ fileType(file) & rankType(rank) };
					this->m_Ray[rayDown][i] |= sq;
				}
				for (int k = 1; k < 8; k++)
				{
					const int file{ file0 + k };
					const int rank{ rank0 };
					if (file >= 8)
						break;
					const squareType sq{ fileType(file) & rankType(rank) };
					this->m_Ray[rayRight][i] |= sq;
				}
				for (int k = 1; k < 8; k++)
				{
					const int file{ file0 - k };
					const int rank{ rank0 };
					if (file < 0)
						break;
					const squareType sq{ fileType(file) & rankType(rank) };
					this->m_Ray[rayLeft][i] |= sq;
				}
			}
		}
		constexpr const squaresType& getRay(const int ray, const squareType square) const noexcept
		{
			return m_Ray[ray][square];
		}
		constexpr static int invertRay(const int ray) noexcept
		{
			assert(ray >= 0);
			assert(ray < 8);
			return 7 - ray;
		}
	};
}