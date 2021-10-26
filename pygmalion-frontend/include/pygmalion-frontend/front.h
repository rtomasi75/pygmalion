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
		durationType m_MaxTime;
		std::array<std::uint16_t, countPlayers> m_Rating;
		depthType m_MaxDepth;
		bool m_IsUCI;
		bool m_IsDebug;
		bool m_AnalyzeMode;
		bool m_HasHint;
		bool m_PlayingComputer;
		std::string m_OpponentName;
		movebitsType m_HintMove;
		std::string m_HintMoveString;
	public:
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
		bool& playingComputer() noexcept
		{
			return m_PlayingComputer;
		}
		bool playingComputer() const noexcept
		{
			return m_PlayingComputer;
		}
		durationType getTimeAvailable() const noexcept
		{
			return m_TimeAvailable;
		}
		void setTimeAvailable(const durationType timeAvailable) noexcept
		{
			m_TimeAvailable = timeAvailable;
			m_IsPondering = false;
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
		durationType timeLimit() const noexcept
		{
			return m_MaxTime;
		}
		bool isDepthLimited() const noexcept
		{
			return m_MaxDepth >= 0;
		}
		bool isTimeLimited() const noexcept
		{
			return m_MaxTime >= static_cast<durationType>(std::chrono::seconds(0));
		}
		bool exceedsDepthLimit(const depthType& depth) const noexcept
		{
			return isDepthLimited() && (depth > m_MaxDepth);
		}
		bool exceedsTimeLimit(const durationType duration) const noexcept
		{
			return isTimeLimited() && (duration > timeLimit());
		}
		void setDepthLimit(const depthType& limit) noexcept
		{
			m_MaxDepth = limit;
		}
		void setTimeLimit(const std::chrono::seconds limit) noexcept
		{
			m_MaxTime = std::chrono::duration_cast<durationType>(limit);
		}
		void setTimeLimit(const durationType limit) noexcept
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
		bool analyzeMode() const noexcept
		{
			return m_AnalyzeMode;
		}
		bool& analyzeMode() noexcept
		{
			return m_AnalyzeMode;
		}
		front() noexcept :
			m_OpponentName{ std::string("<unknown>") },
			m_IsDebug{ false },
			m_IsUCI{ false },
			m_AnalyzeMode{ false },
			m_MaxDepth{ -1 },
			m_MaxTime{ -1 },
			m_Rating{ arrayhelper::make<countPlayers,std::uint16_t>(0) },
			m_HasHint{ false },
			m_IsPondering{ false }
		{

		}
	};
}