namespace pygmalion
{
	class autoresetevent
	{
	private:
		std::promise<void> m_Promise;
		std::mutex m_Mutex;
		bool m_IsSignalled;
	public:
		autoresetevent() noexcept :
			m_Promise{ std::promise<void>() },
			m_Mutex{ std::mutex() },
			m_IsSignalled{ false }
		{}
		void signal() noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_Promise.set_value();
			m_IsSignalled = true;
		}
		void wait() noexcept
		{
			 
		}
	};
}