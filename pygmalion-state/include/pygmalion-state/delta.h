namespace pygmalion::state
{
	template<typename DESCRIPTOR_STATE>
	class delta :
		public DESCRIPTOR_STATE
	{
	public:
		using descriptorState = DESCRIPTOR_STATE;
#include "include_state.h"
	private:
		constexpr static const inline size_t countEntries{ 1 << countPieces };
		std::array< std::array<std::array<scoreType, countEntries>, countEntries>, countPlayers> m_MaxCaptureChange;
		std::array< std::array<std::array<scoreType, countEntries>, countEntries>, countPlayers> m_MaxPromoCaptureChange;
		std::array<std::array<scoreType, countEntries>, countPlayers> m_MaxQuietChange;
		std::array<std::array<scoreType, countEntries>, countPlayers> m_MaxPromotionChange;
		delta(bool) noexcept
		{
		}
	public:
		PYGMALION_INLINE const scoreType& maxCaptureChange(const playerType pl, const piecemaskType originPieces, const piecemaskType victimPieces) const noexcept
		{
			return this->m_MaxCaptureChange[pl][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxCaptureChange(const playerType pl, const piecemaskType originPieces, const piecemaskType victimPieces) noexcept
		{
			return this->m_MaxCaptureChange[pl][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE const scoreType& maxPromoCaptureChange(const playerType pl, const piecemaskType originPieces, const piecemaskType victimPieces) const noexcept
		{
			return this->m_MaxPromoCaptureChange[pl][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxPromoCaptureChange(const playerType pl, const piecemaskType originPieces, const piecemaskType victimPieces) noexcept
		{
			return this->m_MaxPromoCaptureChange[pl][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE const scoreType& maxQuietChange(const playerType pl, const piecemaskType originPieces) const noexcept
		{
			return this->m_MaxQuietChange[pl][originPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxQuietChange(const playerType pl, const piecemaskType originPieces) noexcept
		{
			return this->m_MaxQuietChange[pl][originPieces.toIndex()];
		}
		PYGMALION_INLINE const scoreType& maxPromotionChange(const playerType pl, const piecemaskType originPieces) const noexcept
		{
			return this->m_MaxPromotionChange[pl][originPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxPromotionChange(const playerType pl, const piecemaskType originPieces) noexcept
		{
			return this->m_MaxPromotionChange[pl][originPieces.toIndex()];
		}
		delta() noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
			for (const auto pl : playerType::range)
			{
				for (size_t i = 0; i < countEntries; i++)
				{
					this->m_MaxQuietChange[pl][i] = zero;
					this->m_MaxPromotionChange[pl][i] = zero;
					for (size_t j = 0; j < countEntries; j++)
					{
						this->m_MaxCaptureChange[pl][i][j] = zero;
						this->m_MaxPromoCaptureChange[pl][i][j] = zero;
					}
				}
			}
		}
		~delta() noexcept = default;
		delta(delta&&) noexcept = default;
		delta(const delta&) noexcept = default;
		delta& operator=(delta&&) noexcept = default;
		delta& operator=(const delta&) noexcept = default;
		delta operator+(const delta& other) const noexcept
		{
			delta result(false);
			constexpr const scoreType zero{ scoreType::zero() };
			for (const auto pl : playerType::range)
			{
				for (size_t i = 0; i < countEntries; i++)
				{
					result.m_MaxQuietChange[pl][i] = m_MaxQuietChange[pl][i] + other.m_MaxQuietChange[pl][i];
					result.m_MaxPromotionChange[pl][i] = m_MaxPromotionChange[pl][i] + other.m_MaxPromotionChange[pl][i];
					for (size_t j = 0; j < countEntries; j++)
					{
						result.m_MaxCaptureChange[pl][i][j] = m_MaxCaptureChange[pl][i][j] + other.m_MaxCaptureChange[pl][i][j];
						result.m_MaxPromoCaptureChange[pl][i][j] = m_MaxPromoCaptureChange[pl][i][j] + other.m_MaxPromoCaptureChange[pl][i][j];
					}
				}
			}
			return result;
		}
		delta operator-(const delta& other) const noexcept
		{
			delta result(false);
			constexpr const scoreType zero{ scoreType::zero() };
			for (const auto pl : playerType::range)
			{
				for (size_t i = 0; i < countEntries; i++)
				{
					result.m_MaxChange[pl][i] = m_MaxChange[pl][i] - other.m_MaxChange[pl][i];
				}
			}
			return result;
		}
		delta operator-() const noexcept
		{
			delta result(false);
			constexpr const scoreType zero{ scoreType::zero() };
			for (const auto pl : playerType::range)
			{
				for (size_t i = 0; i < countEntries; i++)
				{
					result.m_MaxChange[pl][i] = -m_MaxChange[pl][i];
				}
			}
			return result;
		}
	};
}