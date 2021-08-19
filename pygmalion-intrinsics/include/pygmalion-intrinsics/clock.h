namespace pygmalion
{
	class clock
	{
	private:
		timeType m_StartTime;
		typename chronographType::duration m_TimeRemaining;
		mutable std::shared_timed_mutex m_Mutex;
		bool m_IsRunning;
	public:
		clock() noexcept :
			m_StartTime{ chronographType::now() },
			m_TimeRemaining{ m_StartTime - m_StartTime },
			m_IsRunning{ false },
			m_Mutex{ std::shared_timed_mutex() }
		{
		}
		void set(const durationType timeRemaining) noexcept
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
			m_StartTime = chronographType::now();
			m_IsRunning = true;
		}
		void stop() noexcept
		{
			std::unique_lock<std::shared_timed_mutex> lock(m_Mutex);
			m_IsRunning = false;
			const timeType now{ chronographType::now() };
			m_TimeRemaining = m_TimeRemaining - (now - m_StartTime);
			m_StartTime = now;
		}
		durationType timeRemaining() const noexcept
		{
			std::shared_lock<std::shared_timed_mutex> lock(m_Mutex);
			if (m_IsRunning)
				return std::chrono::duration_cast<durationType>(m_TimeRemaining - (chronographType::now() - m_StartTime));
			else
				return std::chrono::duration_cast<durationType>(m_TimeRemaining);
		}
	};
}