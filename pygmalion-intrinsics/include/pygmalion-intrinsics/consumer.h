namespace pygmalion
{
	template<typename PRODUCT>
	class consumer
	{
	public:
		using productType = PRODUCT;
	private:
		std::condition_variable m_SignalProductAvailable;
		std::mutex m_Mutex;
		std::deque<productType> m_AvailableProducts;
		std::atomic_bool m_IsRunning;
		std::thread m_ConsumerThread;
		void consumerThread() noexcept
		{
			while (m_IsRunning)
			{
				std::unique_lock<std::mutex> lock(m_Mutex);
				m_SignalProductAvailable.wait_for(lock, std::chrono::milliseconds(100));
				if (m_AvailableProducts.size() > 0)
				{
					for (auto& product : m_AvailableProducts)
					{
						onConsume(product);
					}
				}
			}
		}
	protected:
		virtual void onConsume(const productType& product) noexcept
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_AvailableProducts.emplace_back(product);
			m_SignalProductAvailable.notify_one();
		}
		consumer() noexcept :
			m_SignalProductAvailable{ std::condition_variable() },
			m_Mutex{ std::mutex() },
			m_AvailableProducts{ std::deque<productType>() },
			m_IsRunning{ true },
			m_ConsumerThread{ std::thread([this]() { this->consumerThread(); }) }
		{
		}
		void consume(productType&& product) noexcept
		{

		}
		virtual ~consumer() noexcept
		{
			m_IsRunning = false;
			m_SignalProductAvailable.notify_one();
			m_ConsumerThread.join();
		}
	};
}