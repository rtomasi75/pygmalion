namespace pygmalion
{
	class timer
	{
	private:
		durationType m_Period;
		std::atomic_bool m_IsRunning;
		std::thread m_Thread;
	public:
		template<typename LAMBDA>
		timer(const durationType period, LAMBDA lambda) :
			m_Period{ period },
			m_IsRunning{ false },
			m_Thread{
			std::thread([this]()
			{
				const timeType start{ chronographType::now() };
				bool isElapsed{ false };
				while (m_IsRunning && !isElapsed)
				{
					const timeType end{ chronographType::now() + std::chrono::duration_cast<durationType>(std::chrono::milliseconds(10)) };
					std::this_thread::sleep_until(end);
					if ((chronographType::now() - start) > m_Period)
						m_IsElapsed = true;
				}
				if (isElapsed)
					lambda();
				m_IsRunning = false;
			}) }

		{
		}
			constexpr durationType period() const noexcept
			{
				return m_Period;
			}
			bool isRunning() const noexcept
			{
				return m_IsRunning;
			}
			void abort() noexcept
			{
				m_IsRunning = false;
			}
			~timer()
			{
				abort();
				m_Thread.join();
			}

	};
}