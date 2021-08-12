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
	public:
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
		constexpr front() noexcept :
			m_IsXBoard{ false },
			m_IsRandom{ false },
			m_ProtocolVersion{ 1 }
		{

		}
	};
}