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
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				if (m_Flag)
				{
					lambda();
				}
			}
			m_Condition.notify_all();
		}
		template<typename LAMBDA>
		void doIfLow(const LAMBDA& lambda) noexcept
		{
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				if (!m_Flag)
				{
					lambda();
				}
			}
			m_Condition.notify_all();
		}
		template<typename LAMBDA1, typename LAMBDA2>
		void doIfElse(const LAMBDA1& lambdaIf, const LAMBDA2& lambdaElse) noexcept
		{
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				if (m_Flag)
				{
					m_Flag = lambdaIf();
				}
				else
				{
					m_Flag = lambdaElse();
				}
			}
			m_Condition.notify_all();
		}
		template<typename LAMBDA>
		void doIfHighAndLower(const LAMBDA& lambda) noexcept
		{
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				if (m_Flag)
				{
					lambda();
					m_Flag = false;
				}
			}
			m_Condition.notify_all();
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
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				while (!m_Flag)
					m_Condition.wait(lock);
				lambda();
			}
			m_Condition.notify_all();
		}
		template<typename LAMBDA>
		void waitHighAndLower(const LAMBDA& lambda) noexcept
		{
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				while (!m_Flag)
					m_Condition.wait(lock);
				lambda();
				m_Flag = false;
			}
			m_Condition.notify_all();
		}
		template<typename LAMBDA>
		void waitLowAndRaise(const LAMBDA& lambda) noexcept
		{
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				while (m_Flag)
					m_Condition.wait(lock);
				lambda();
				m_Flag = true;
			}
			m_Condition.notify_all();
		}
		void wait(const bool flag) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			while (m_Flag != flag)
				m_Condition.wait(lock);
		}
		bool flag() noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			return m_Flag;
		}
		template<typename LAMBDA>
		void wait(const bool flag, const LAMBDA& lambda) noexcept
		{
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				while (m_Flag != flag)
					m_Condition.wait(lock);
				lambda();
			}
			m_Condition.notify_all();
		}
		void raise() noexcept
		{
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				m_Flag = true;
			}
			m_Condition.notify_all();
		}
		template<typename LAMBDA>
		void raise(const LAMBDA& lambda) noexcept
		{
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				m_Flag = true;
				lambda();
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