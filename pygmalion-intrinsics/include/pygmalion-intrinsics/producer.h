namespace pygmalion
{
	template<typename PRODUCT>
	class producer
	{
	public:
		using productType = PRODUCT;
		std::atomic_bool m_SignalRunning;
		consumer<productType>& m_Consumer;
	private:
		void productionThread()
		{
			while (m_SignalRunning)
			{
				productType product;
				onProduce(product);
				m_Consumer.consume(std::move(product));
			}
		}
	protected:
		virtual void onProduce(productType& product) noexcept
		{

		}
	public:
		producer(consumer<productType>& consumer) :
			m_SignalRunning{ signal(false) },
			m_Consumer{ consumer }
		{

		}
	};
}