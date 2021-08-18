namespace pygmalion
{
	template<typename DESCRIPTION_FRONTEND, typename INSTANCE>
	class front :
		public DESCRIPTION_FRONTEND
	{
	public:
		using frontType = INSTANCE;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "include_frontend.h"	
	private:
		std::chrono::seconds m_MaxTime;
		std::array<std::uint16_t, countPlayers> m_Rating;
		int m_ProtocolVersion;
		depthType m_MaxDepth;
		playerType m_EnginePlayer;
		bool m_IsXBoard;
		bool m_IsRandom;
		bool m_PlayingComputer;
		bool m_ForceMode;
		bool m_PostMode;
		bool m_PonderMode;
		std::string m_OpponentName;
	public:
		static std::string gamestateToString(const boardType& position, const gamestateType gs) noexcept
		{
			return frontType::gamestateToString_Implementation(position, gs);
		}
		constexpr const std::string& opponentName() const noexcept
		{
			return m_OpponentName;
		}
		constexpr std::string& opponentName() noexcept
		{
			return m_OpponentName;
		}
		constexpr std::uint16_t playerRating(const playerType pl) const noexcept
		{
			return m_Rating[pl];
		}
		constexpr std::uint16_t& playerRating(const playerType pl) noexcept
		{
			return m_Rating[pl];
		}
		constexpr depthType depthLimit() const noexcept
		{
			return m_MaxDepth;
		}
		constexpr std::chrono::seconds timeLimit() const noexcept
		{
			return m_MaxTime;
		}
		constexpr bool isDepthLimited() const noexcept
		{
			return m_MaxDepth >= 0;
		}
		constexpr bool isTimeLimited() const noexcept
		{
			return m_MaxTime >= std::chrono::seconds(0);
		}
		constexpr bool exceedsDepthLimit(const depthType depth) const noexcept
		{
			return isDepthLimited() && (depth > m_MaxDepth);
		}
		constexpr bool exceedsTimeLimit(const std::chrono::seconds duration) const noexcept
		{
			return isTimeLimited() && (duration > timeLimit());
		}
		constexpr void setDepthLimit(const depthType limit) noexcept
		{
			m_MaxDepth = limit;
		}
		constexpr void setTimeLimit(const std::chrono::seconds limit) noexcept
		{
			m_MaxTime = limit;
		}
		constexpr void clearDepthLimit() noexcept
		{
			m_MaxDepth = static_cast<depthType>(-1);
		}
		constexpr void clearTimeLimit() noexcept
		{
			m_MaxTime = std::chrono::seconds(-1);
		}
		constexpr int& protocolVersion() noexcept
		{
			return m_ProtocolVersion;
		}
		constexpr int protocolVersion() const noexcept
		{
			return m_ProtocolVersion;
		}
		constexpr bool& isXBoard() noexcept
		{
			return m_IsXBoard;
		}
		constexpr bool isXBoard() const noexcept
		{
			return m_IsXBoard;
		}
		constexpr bool& isRandom() noexcept
		{
			return m_IsRandom;
		}
		constexpr bool isRandom() const noexcept
		{
			return m_IsRandom;
		}
		constexpr bool ponderMode() const noexcept
		{
			return m_PonderMode;
		}
		constexpr bool& ponderMode() noexcept
		{
			return m_PonderMode;
		}
		constexpr bool forceMode() const noexcept
		{
			return m_ForceMode;
		}
		constexpr bool& forceMode() noexcept
		{
			return m_ForceMode;
		}
		constexpr bool postMode() const noexcept
		{
			return m_PostMode;
		}
		constexpr bool& postMode() noexcept
		{
			return m_PostMode;
		}
		constexpr bool& playingComputer() noexcept
		{
			return m_PlayingComputer;
		}
		constexpr bool playingComputer() const noexcept
		{
			return m_PlayingComputer;
		}
		constexpr playerType enginePlayer() const noexcept
		{
			return m_EnginePlayer;
		}
		constexpr playerType& enginePlayer() noexcept
		{
			return m_EnginePlayer;
		}
		constexpr front() noexcept :
			m_IsXBoard{ false },
			m_IsRandom{ false },
			m_ForceMode{ false },
			m_PonderMode{ false },
			m_PlayingComputer{ false },
			m_ProtocolVersion{ 1 },
			m_MaxDepth{ -1 },
			m_MaxTime{ -1 },
			m_EnginePlayer{ 0 },
			m_Rating{ arrayhelper::make<countPlayers,std::uint16_t>(0) },
			m_OpponentName{ std::string("<unknown>") }
		{

		}
	};
}