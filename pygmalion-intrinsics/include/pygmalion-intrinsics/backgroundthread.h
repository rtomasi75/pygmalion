namespace pygmalion
{
	template<typename LAMBDA>
	class backgroundthread
	{
	private:
		std::condition_variable m_Scheduled;
		std::mutex m_ScheduledMutex;
		bool m_ScheduledFlag;
		std::atomic_bool m_IsRunning;
		const LAMBDA& m_Lambda;
		std::thread m_Thread;
		void loop() noexcept
		{
			while (m_IsRunning)
			{
				bool bInvoke{ false };
				{
					std::unique_lock<std::mutex> scheduledLock(m_ScheduledMutex);
					m_Scheduled.wait_until(chronographType::now() + std::chrono::duration_cast<durationType>(std::chrono::milliseconds(10)), [this]() { return (m_ScheduledFlag && !m_BusyFlag); });
					if (m_ScheduledFlag && !m_BusyFlag)
					{
						bInvoke = true;
						m_ScheduledFlag = false;
					}
				}
				m_Scheduled.notify_all();
				if (bInvoke)
					m_Lambda();
			}
		}
	public:
		backgroundthread(const LAMBDA& lambda) noexcept :
			m_IsRunning{ true },
			m_BusyFlag{ false },
			m_Lambda{ lambda },
			m_ScheduledFlag{ false },
			m_Thread{ std::thread([]() { loop(); }) }
		{

		}
		~backgroundthread() noexcept
		{
			m_IsRunning = false;
			m_Thread.join();
		}
		void invoke() noexcept
		{
			{
				std::unique_lock<std::mutex> scheduledLock(m_ScheduledMutex);
				m_Scheduled.wait_until(chronographType::now() + std::chrono::duration_cast<durationType>(std::chrono::milliseconds(10)), [this]() { return !m_ScheduledFlag; });
				m_ScheduledFlag = true;
			}
			m_Scheduled.notify_one();
		}
	};
}