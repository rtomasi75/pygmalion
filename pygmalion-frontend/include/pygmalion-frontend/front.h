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
		boardType m_PonderBoard;
		durationType m_TimeAvailable;
		bool m_IsPondering;
		std::chrono::seconds m_MaxTime;
		std::array<std::uint16_t, countPlayers> m_Rating;
		int m_ProtocolVersion;
		depthType m_MaxDepth;
		playerType m_EnginePlayer;
		bool m_IsXBoard;
		bool m_IsUCI;
		bool m_IsDebug;
		bool m_IsRandom;
		bool m_PlayingComputer;
		bool m_ForceMode;
		bool m_PostMode;
		bool m_PonderMode;
		bool m_AnalyzeMode;
		bool m_HasHint;
		movebitsType m_HintMove;
		std::string m_HintMoveString;
		std::string m_OpponentName;
	public:
		durationType getTimeAvailable() const noexcept
		{
			return m_TimeAvailable;
		}
		void setTimeAvailable(const durationType timeAvailable) noexcept
		{
			m_TimeAvailable = timeAvailable;
			m_IsPondering = false;
		}
		void startPondering(const boardType& ponderBoard) noexcept
		{
			m_PonderBoard = ponderBoard;
			m_IsPondering = true;
		}
		boardType& ponderBoard() noexcept
		{
			return m_PonderBoard;
		}
		void stopPondering()
		{
			m_IsPondering = false;
		}
		bool isPondering() const noexcept
		{
			return m_IsPondering;
		}
		static std::string gamestateToString(const boardType& position, const gamestateType& gs) noexcept
		{
			return frontType::gamestateToString_Implementation(position, gs);
		}
		const std::string& opponentName() const noexcept
		{
			return m_OpponentName;
		}
		std::string& opponentName() noexcept
		{
			return m_OpponentName;
		}
		std::uint16_t playerRating(const playerType& pl) const noexcept
		{
			return m_Rating[pl];
		}
		std::uint16_t& playerRating(const playerType& pl) noexcept
		{
			return m_Rating[pl];
		}
		depthType depthLimit() const noexcept
		{
			return m_MaxDepth;
		}
		std::chrono::seconds timeLimit() const noexcept
		{
			return m_MaxTime;
		}
		bool isDepthLimited() const noexcept
		{
			return m_MaxDepth >= 0;
		}
		bool isTimeLimited() const noexcept
		{
			return m_MaxTime >= std::chrono::seconds(0);
		}
		bool exceedsDepthLimit(const depthType& depth) const noexcept
		{
			return isDepthLimited() && (depth > m_MaxDepth);
		}
		bool exceedsTimeLimit(const std::chrono::seconds duration) const noexcept
		{
			return isTimeLimited() && (duration > timeLimit());
		}
		void setDepthLimit(const depthType& limit) noexcept
		{
			m_MaxDepth = limit;
		}
		void setTimeLimit(const std::chrono::seconds limit) noexcept
		{
			m_MaxTime = limit;
		}
		void clearDepthLimit() noexcept
		{
			m_MaxDepth = static_cast<depthType>(-1);
		}
		void clearTimeLimit() noexcept
		{
			m_MaxTime = std::chrono::seconds(-1);
		}
		int& protocolVersion() noexcept
		{
			return m_ProtocolVersion;
		}
		int protocolVersion() const noexcept
		{
			return m_ProtocolVersion;
		}
		bool& isXBoard() noexcept
		{
			return m_IsXBoard;
		}
		bool& isUCI() noexcept
		{
			return m_IsUCI;
		}
		bool& isDebug() noexcept
		{
			return m_IsDebug;
		}
		bool hasHint() const noexcept
		{
			return m_HasHint;
		}
		void clearHintMove()
		{
			m_HasHint = false;
		}
		void setHintMove(const movebitsType hint, const std::string& hintString) noexcept
		{
			m_HasHint = true;
			m_HintMove = hint;
			m_HintMoveString = hintString;
		}
		const movebitsType& hintMove() const noexcept
		{
			return m_HintMove;
		}
		const std::string& hintMoveString() const noexcept
		{
			return m_HintMoveString;
		}
		bool isXBoard() const noexcept
		{
			return m_IsXBoard;
		}
		bool& isRandom() noexcept
		{
			return m_IsRandom;
		}
		bool isRandom() const noexcept
		{
			return m_IsRandom;
		}
		bool ponderMode() const noexcept
		{
			return m_PonderMode;
		}
		bool& ponderMode() noexcept
		{
			return m_PonderMode;
		}
		bool analyzeMode() const noexcept
		{
			return m_AnalyzeMode;
		}
		bool& analyzeMode() noexcept
		{
			return m_AnalyzeMode;
		}
		bool forceMode() const noexcept
		{
			return m_ForceMode;
		}
		bool& forceMode() noexcept
		{
			return m_ForceMode;
		}
		bool postMode() const noexcept
		{
			return m_PostMode;
		}
		bool& postMode() noexcept
		{
			return m_PostMode;
		}
		bool& playingComputer() noexcept
		{
			return m_PlayingComputer;
		}
		bool playingComputer() const noexcept
		{
			return m_PlayingComputer;
		}
		playerType enginePlayer() const noexcept
		{
			return m_EnginePlayer;
		}
		playerType& enginePlayer() noexcept
		{
			return m_EnginePlayer;
		}
		front() noexcept :
			m_IsXBoard{ false },
			m_IsDebug{ false },
			m_IsUCI{ false },
			m_IsRandom{ false },
			m_ForceMode{ false },
			m_PostMode{ false },
			m_PonderMode{ false },
			m_AnalyzeMode{ false },
			m_PlayingComputer{ false },
			m_ProtocolVersion{ 1 },
			m_MaxDepth{ -1 },
			m_MaxTime{ -1 },
			m_EnginePlayer{ 0 },
			m_Rating{ arrayhelper::make<countPlayers,std::uint16_t>(0) },
			m_OpponentName{ std::string("<unknown>") },
			m_HasHint{ false },
			m_IsPondering{ false }
		{

		}
	};
}