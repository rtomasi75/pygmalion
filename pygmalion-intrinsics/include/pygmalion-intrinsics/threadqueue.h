namespace pygmalion
{
	class threadqueue
	{
	private:
		signal m_SigRunning;
		signal m_SigTerm;
		signal m_SigStart;
		std::thread* m_pThread;
		std::mutex m_Mutex;
		template<typename LAMBDA>
		void threadFunction(const LAMBDA& lambda)
		{
			m_SigStart.raise();
			lambda();
			m_SigTerm.raise();
		}
		void terminate() noexcept
		{
			m_SigRunning.doIfHighAndLower([this]() {m_SigTerm.waitHighAndLower([this]() { PYGMALION_ASSERT(m_pThread != nullptr); m_pThread->join(); delete m_pThread; m_pThread = nullptr; }); });
		}
	public:
		threadqueue() noexcept :
			m_SigRunning{ signal(false) },
			m_SigTerm{ signal(false) },
			m_SigStart{ signal(false) },
			m_pThread{ nullptr }
		{

		}
		~threadqueue() noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			terminate();
		}
		void stop() noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			terminate();
		}
		template<typename LAMBDA>
		void start(const LAMBDA& lambda) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			terminate();
			m_SigRunning.waitLowAndRaise([this, lambda]() { PYGMALION_ASSERT(m_pThread == nullptr); m_SigTerm.lower(); m_SigStart.lower(); m_pThread = new std::thread([this, lambda]() { threadFunction(lambda); }); m_SigStart.wait(); });
		}
	};
}