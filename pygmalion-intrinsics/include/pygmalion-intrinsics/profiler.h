namespace pygmalion
{
	class profiler
	{
	public:
		using clockType = std::chrono::high_resolution_clock;
		using timepointType = std::chrono::time_point<clockType>;
		using durationType = std::chrono::nanoseconds;
		timepointType m_Begin;
		timepointType m_End;
		class speed
		{
		private:
			double m_OperationsCount;
			durationType m_Duration;
			std::string m_Unit;
		public:
			speed(const double operationsCount, const durationType duration, const std::string& unit) noexcept;
			~speed() noexcept = default;
			const std::string& operationUnit() const noexcept;
			double operationsCount() const noexcept;
			durationType duration() const noexcept;
			double operationsPerSec() const noexcept;
			operator std::string() const noexcept;
		};
	public:
		profiler() noexcept;
		~profiler() noexcept = default;
		void start() noexcept;
		void stop() noexcept;
		durationType duration() const noexcept;
		speed computeSpeed(const double operationCount, const std::string& unit) const noexcept;
	};

	std::ostream& operator<<(std::ostream& stream, const typename profiler::speed& speed) noexcept;
}