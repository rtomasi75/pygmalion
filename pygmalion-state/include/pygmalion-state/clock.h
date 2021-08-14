namespace pygmalion
{
	class clock
	{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
		std::chrono::microseconds m_TimeRemaining;
		mutable std::shared_timed_mutex m_Mutex;
		bool m_IsRunning;
	public:
		clock() noexcept :
			m_StartTime{ std::chrono::high_resolution_clock::now() },
			m_TimeRemaining{ std::chrono::duration_cast<std::chrono::microseconds>(m_StartTime - m_StartTime) },
			m_IsRunning{ false },
			m_Mutex{ std::shared_timed_mutex() }
		{
		}
		void set(const std::chrono::microseconds timeRemaining) noexcept
		{
			std::unique_lock<std::shared_timed_mutex> lock(m_Mutex);
			m_TimeRemaining = timeRemaining;
		}
		bool isRunning() const noexcept
		{
			std::shared_lock<std::shared_timed_mutex> lock(m_Mutex);
			return m_IsRunning;
		}
		void start() noexcept
		{
			std::unique_lock<std::shared_timed_mutex> lock(m_Mutex);
			m_StartTime = std::chrono::high_resolution_clock::now();
			m_IsRunning = true;
		}
		void stop() noexcept
		{
			std::unique_lock<std::shared_timed_mutex> lock(m_Mutex);
			m_IsRunning = false;
			const auto  now{ std::chrono::high_resolution_clock::now() };
			m_TimeRemaining = m_TimeRemaining - std::chrono::duration_cast<std::chrono::microseconds>(now - m_StartTime);
			m_StartTime = now;
		}
		std::chrono::microseconds timeRemaining() const noexcept
		{
			std::shared_lock<std::shared_timed_mutex> lock(m_Mutex);
			if (m_IsRunning)
				return m_TimeRemaining - std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_StartTime);
			else
				return m_TimeRemaining;
		}
	};
}