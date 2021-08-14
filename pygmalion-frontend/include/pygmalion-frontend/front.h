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
		int m_ProtocolVersion;
		bool m_IsXBoard;
		bool m_IsRandom;
		bool m_PlayingComputer;
		depthType m_MaxDepth;
	public:
		constexpr depthType depthLimit() const noexcept
		{
			return m_MaxDepth;
		}
		constexpr bool isDepthLimited() const noexcept
		{
			return m_MaxDepth >= 0;
		}
		constexpr bool exceedsDepthLimit(const depthType depth) const noexcept
		{
			return depth > m_MaxDepth;
		}
		constexpr void setDepthLimit(const depthType limit) noexcept
		{
			m_MaxDepth = limit;
		}
		constexpr void clearDepthLimit() noexcept
		{
			m_MaxDepth = static_cast<depthType>(-1);
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
		constexpr bool& playingComputer() noexcept
		{
			return m_PlayingComputer;
		}
		constexpr bool playingComputer() const noexcept
		{
			return m_PlayingComputer;
		}
		constexpr front() noexcept :
			m_IsXBoard{ false },
			m_IsRandom{ false },
			m_PlayingComputer{ false },
			m_ProtocolVersion{ 1 },
			m_MaxDepth{ -1 }
		{

		}
	};
}