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
		std::array<std::array<std::array<std::array<scoreType, countEntries>, countEntries>, countPlayers>, countPlayers> m_MaxCaptureChange;
		std::array<std::array<std::array<std::array<scoreType, countEntries>, countEntries>, countPlayers>, countPlayers> m_MaxPromoCaptureChange;
		std::array<std::array<std::array<scoreType, countEntries>, countPlayers>, countPlayers> m_MaxQuietChange;
		std::array<std::array<std::array<scoreType, countEntries>, countPlayers>, countPlayers> m_MaxPromotionChange;
		delta(bool) noexcept
		{
		}
	public:
		PYGMALION_INLINE const scoreType& maxCaptureChange(const playerType subjectPlayer, const playerType movingPlayer, const piecemaskType originPieces, const piecemaskType victimPieces) const noexcept
		{
			return this->m_MaxCaptureChange[subjectPlayer][movingPlayer][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxCaptureChange(const playerType subjectPlayer, const playerType movingPlayer, const piecemaskType originPieces, const piecemaskType victimPieces) noexcept
		{
			return this->m_MaxCaptureChange[subjectPlayer][movingPlayer][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE const scoreType& maxPromoCaptureChange(const playerType subjectPlayer, const playerType movingPlayer, const piecemaskType originPieces, const piecemaskType victimPieces) const noexcept
		{
			return this->m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxPromoCaptureChange(const playerType subjectPlayer, const playerType movingPlayer, const piecemaskType originPieces, const piecemaskType victimPieces) noexcept
		{
			return this->m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE const scoreType& maxQuietChange(const playerType subjectPlayer, const playerType movingPlayer, const piecemaskType originPieces) const noexcept
		{
			return this->m_MaxQuietChange[subjectPlayer][movingPlayer][originPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxQuietChange(const playerType subjectPlayer, const playerType movingPlayer, const piecemaskType originPieces) noexcept
		{
			return this->m_MaxQuietChange[subjectPlayer][movingPlayer][originPieces.toIndex()];
		}
		PYGMALION_INLINE const scoreType& maxPromotionChange(const playerType subjectPlayer, const playerType movingPlayer, const piecemaskType originPieces) const noexcept
		{
			return this->m_MaxPromotionChange[subjectPlayer][movingPlayer][originPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxPromotionChange(const playerType subjectPlayer, const playerType movingPlayer, const piecemaskType originPieces) noexcept
		{
			return this->m_MaxPromotionChange[subjectPlayer][movingPlayer][originPieces.toIndex()];
		}
		delta() noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
			for (const auto subjectPlayer : playerType::range)
			{
				for (const auto movingPlayer : playerType::range)
				{
					for (size_t i = 0; i < countEntries; i++)
					{
						this->m_MaxQuietChange[subjectPlayer][movingPlayer][i] = zero;
						this->m_MaxPromotionChange[subjectPlayer][movingPlayer][i] = zero;
						for (size_t j = 0; j < countEntries; j++)
						{
							this->m_MaxCaptureChange[subjectPlayer][movingPlayer][i][j] = zero;
							this->m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][i][j] = zero;
						}
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
			for (const auto subjectPlayer : playerType::range)
			{
				for (const auto movingPlayer : playerType::range)
				{
					for (size_t i = 0; i < countEntries; i++)
					{
						result.m_MaxQuietChange[subjectPlayer][movingPlayer][i] = m_MaxQuietChange[subjectPlayer][movingPlayer][i] + other.m_MaxQuietChange[subjectPlayer][movingPlayer][i];
						result.m_MaxPromotionChange[subjectPlayer][movingPlayer][i] = m_MaxPromotionChange[subjectPlayer][movingPlayer][i] + other.m_MaxPromotionChange[subjectPlayer][movingPlayer][i];
						for (size_t j = 0; j < countEntries; j++)
						{
							result.m_MaxCaptureChange[subjectPlayer][movingPlayer][i][j] = m_MaxCaptureChange[subjectPlayer][movingPlayer][i][j] + other.m_MaxCaptureChange[subjectPlayer][movingPlayer][i][j];
							result.m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][i][j] = m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][i][j] + other.m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][i][j];
						}
					}
				}
			}
			return result;
		}
		delta operator-(const delta& other) const noexcept
		{
			delta result(false);
			constexpr const scoreType zero{ scoreType::zero() };
			for (const auto subjectPlayer : playerType::range)
			{
				for (const auto movingPlayer : playerType::range)
				{
					for (size_t i = 0; i < countEntries; i++)
					{
						result.m_MaxQuietChange[subjectPlayer][movingPlayer][i] = m_MaxQuietChange[subjectPlayer][movingPlayer][i] - other.m_MaxQuietChange[subjectPlayer][movingPlayer][i];
						result.m_MaxPromotionChange[subjectPlayer][movingPlayer][i] = m_MaxPromotionChange[subjectPlayer][movingPlayer][i] - other.m_MaxPromotionChange[subjectPlayer][movingPlayer][i];
						for (size_t j = 0; j < countEntries; j++)
						{
							result.m_MaxCaptureChange[subjectPlayer][movingPlayer][i][j] = m_MaxCaptureChange[subjectPlayer][movingPlayer][i][j] - other.m_MaxCaptureChange[subjectPlayer][movingPlayer][i][j];
							result.m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][i][j] = m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][i][j] - other.m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][i][j];
						}
					}
				}
			}
			return result;
		}
		delta operator-() const noexcept
		{
			delta result(false);
			constexpr const scoreType zero{ scoreType::zero() };
			for (const auto subjectPlayer : playerType::range)
			{
				for (const auto movingPlayer : playerType::range)
				{
					for (size_t i = 0; i < countEntries; i++)
					{
						result.m_MaxQuietChange[subjectPlayer][movingPlayer][i] = -m_MaxQuietChange[subjectPlayer][movingPlayer][i];
						result.m_MaxPromotionChange[subjectPlayer][movingPlayer][i] = -m_MaxPromotionChange[subjectPlayer][movingPlayer][i];
						for (size_t j = 0; j < countEntries; j++)
						{
							result.m_MaxCaptureChange[subjectPlayer][movingPlayer][i][j] = -m_MaxCaptureChange[subjectPlayer][movingPlayer][i][j];
							result.m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][i][j] = -m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][i][j];
						}
					}
				}
			}
			return result;
		}
	};
}