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
		std::array<std::array<std::array<scoreType, countEntries>, countEntries>, countPlayers> m_MaxQuietChange;
		std::array<std::array<std::array<scoreType, countEntries>, countEntries>, countPlayers> m_MaxPromotionChange;
		delta(bool) noexcept
		{
		}
	public:
		PYGMALION_INLINE const scoreType& maxCaptureChange(const playerType subjectPlayer, const playerType movingPlayer, const piecesType originPieces, const piecesType victimPieces) const noexcept
		{
			return this->m_MaxCaptureChange[subjectPlayer][movingPlayer][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxCaptureChange(const playerType subjectPlayer, const playerType movingPlayer, const piecesType originPieces, const piecesType victimPieces) noexcept
		{
			return this->m_MaxCaptureChange[subjectPlayer][movingPlayer][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE const scoreType& maxPromoCaptureChange(const playerType subjectPlayer, const playerType movingPlayer, const piecesType originPieces, const piecesType victimPieces) const noexcept
		{
			return this->m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxPromoCaptureChange(const playerType subjectPlayer, const playerType movingPlayer, const piecesType originPieces, const piecesType victimPieces) noexcept
		{
			return this->m_MaxPromoCaptureChange[subjectPlayer][movingPlayer][originPieces.toIndex()][victimPieces.toIndex()];
		}
		PYGMALION_INLINE const scoreType& maxQuietChange(const playerType subjectPlayer, const playerType movingPlayer, const piecesType originPieces) const noexcept
		{
			return this->m_MaxQuietChange[subjectPlayer][movingPlayer][originPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxQuietChange(const playerType subjectPlayer, const playerType movingPlayer, const piecesType originPieces) noexcept
		{
			return this->m_MaxQuietChange[subjectPlayer][movingPlayer][originPieces.toIndex()];
		}
		PYGMALION_INLINE const scoreType& maxPromotionChange(const playerType subjectPlayer, const playerType movingPlayer, const piecesType originPieces) const noexcept
		{
			return this->m_MaxPromotionChange[subjectPlayer][movingPlayer][originPieces.toIndex()];
		}
		PYGMALION_INLINE scoreType& maxPromotionChange(const playerType subjectPlayer, const playerType movingPlayer, const piecesType originPieces) noexcept
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
					for (const auto i : piecesType::range)
					{
						maxQuietChange(subjectPlayer, movingPlayer, i) = zero;
						maxPromotionChange(subjectPlayer, movingPlayer, i) = zero;
						for (const auto j : piecesType::range)
						{
							maxCaptureChange(subjectPlayer, movingPlayer, i, j) = zero;
							maxPromoCaptureChange(subjectPlayer, movingPlayer, i, j) = zero;
						}
					}
				}
			}
		}
		~delta() noexcept = default;
		delta(const delta&) noexcept = default;
		delta& operator=(const delta&) noexcept = default;
		delta(delta&&) noexcept = default;
		delta& operator=(delta&&) noexcept = default;
		delta& operator+=(const delta& other) noexcept
		{
			for (const auto subjectPlayer : playerType::range)
			{
				for (const auto movingPlayer : playerType::range)
				{
					for (const auto i : piecesType::range)
					{
						maxQuietChange(subjectPlayer, movingPlayer, i) += other.maxQuietChange(subjectPlayer, movingPlayer, i);
						maxPromotionChange(subjectPlayer, movingPlayer, i) += other.maxPromotionChange(subjectPlayer, movingPlayer, i);
						for (const auto j : piecesType::range)
						{
							maxCaptureChange(subjectPlayer, movingPlayer, i, j) += other.maxCaptureChange(subjectPlayer, movingPlayer, i, j);
							maxPromoCaptureChange(subjectPlayer, movingPlayer, i, j) += other.maxPromoCaptureChange(subjectPlayer, movingPlayer, i, j);
						}
					}
				}
			}
			return *this;
		}
	};
}