namespace pygmalion
{
	class signal
	{
	private:
		bool m_Flag;
		std::mutex m_Mutex;
		std::condition_variable m_Condition;
	public:
		signal(const bool initialFlag) noexcept :
			m_Flag{ initialFlag },
			m_Mutex{ std::mutex() },
			m_Condition{ std::condition_variable() }
		{

		}
		template<typename LAMBDA>
		void doIfHigh(const LAMBDA& lambda) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			if (m_Flag)
				lambda();
		}
		template<typename LAMBDA>
		void doIfLow(const LAMBDA& lambda) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			if (!m_Flag)
				lambda();
		}
		template<typename LAMBDA>
		void doIfHighAndLower(const LAMBDA& lambda) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			if (m_Flag)
			{
				lambda();
				m_Flag = false;
			}
		}
		void wait() noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			while (!m_Flag)
				m_Condition.wait(lock);
		}
		template<typename LAMBDA>
		void wait(const LAMBDA& lambda) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			while (!m_Flag)
				m_Condition.wait(lock);
			lambda();
		}
		template<typename LAMBDA>
		void waitHighAndLower(const LAMBDA& lambda) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			while (!m_Flag)
				m_Condition.wait(lock);
			lambda();
			m_Flag = false;
		}
		template<typename LAMBDA>
		void waitLowAndRaise(const LAMBDA& lambda) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			while (m_Flag)
				m_Condition.wait(lock);
			lambda();
			m_Flag = true;
		}
		void wait(const bool flag) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			while (m_Flag != flag)
				m_Condition.wait(lock);
		}
		template<typename LAMBDA>
		void wait(const bool flag, const LAMBDA& lambda) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			while (m_Flag != flag)
				m_Condition.wait(lock);
			lambda();
		}
		void raise() noexcept
		{
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				m_Flag = true;
			}
			m_Condition.notify_all();
		}
		void lower() noexcept
		{
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				m_Flag = false;
			}
			m_Condition.notify_all();
		}
	};
}