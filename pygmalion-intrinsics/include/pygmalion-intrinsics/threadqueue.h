namespace pygmalion
{
	class threadqueue
	{
	private:
		signal m_SigTerm;
		signal m_SigStart;
		std::thread* m_pThread;
		std::mutex m_Mutex;
		template<typename LAMBDA>
		void threadFunction(const LAMBDA& lambda)
		{
			lambda();
			m_SigTerm.raise();
		}
		void terminate() noexcept
		{
			m_SigStart.doIfHighAndLower([this]() {m_SigTerm.waitHighAndLower([this]() { PYGMALION_ASSERT(m_pThread != nullptr); m_pThread->join(); delete m_pThread; m_pThread = nullptr; }); });
		}
	public:
		threadqueue() noexcept :
			m_SigTerm{ signal(false) },
			m_SigStart{ signal(false) },
			m_pThread{ nullptr }
		{

		}
		~threadqueue() noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_SigStart.doIfHighAndLower(
				[this]()
				{
					m_SigTerm.waitHighAndLower(
						[this]()
						{
							PYGMALION_ASSERT(m_pThread != nullptr);
							m_pThread->join();
							delete m_pThread;
							m_pThread = nullptr;
						}
					);
				}
			);
		}
		void stop() noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_SigStart.doIfHighAndLower(
				[this]() 
				{
					m_SigTerm.waitHighAndLower(
						[this]() 
						{ 
							PYGMALION_ASSERT(m_pThread != nullptr); 
							m_pThread->join(); 
							delete m_pThread; 
							m_pThread = nullptr; 
						}
					); 
				}
			);
		}
		template<typename LAMBDA>
		void start(const LAMBDA& lambda) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_SigStart.doIfElse(
				[this, lambda]()
				{
					m_SigTerm.waitHighAndLower(
						[this, lambda]()
						{
							PYGMALION_ASSERT(m_pThread != nullptr);
							m_pThread->join(); delete m_pThread;
							m_pThread = new std::thread(
								[this, lambda]()
								{
									threadFunction(lambda);
								});
						}
					);
					return true;
				},
				[this, lambda]()
				{
					PYGMALION_ASSERT(m_pThread == nullptr);
					m_pThread = new std::thread(
						[this, lambda]()
						{
							threadFunction(lambda);
						}
					);
					return true;
				}
				);
		}
	};
}