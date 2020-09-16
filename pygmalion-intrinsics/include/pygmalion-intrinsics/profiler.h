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
			speed(const double operationsCount, const durationType duration, const std::string& unit) noexcept :
				m_OperationsCount{ operationsCount },
				m_Duration{ duration },
				m_Unit{ unit }
			{}
			~speed() noexcept = default;
			const std::string& operationUnit() const noexcept
			{
				return m_Unit;
			}
			constexpr double operationsCount() const noexcept
			{
				return m_OperationsCount;
			}
			constexpr durationType duration() const noexcept
			{
				return m_Duration;
			}
			constexpr double operationsPerSec() const noexcept
			{
				return (10000.0 * static_cast<double>(m_OperationsCount)) / (0.00001 * static_cast<double>(m_Duration.count()));
			}
			operator std::string() const noexcept
			{
				const double ups{ operationsPerSec() };
				std::stringstream sstr;
				sstr << std::fixed;
				sstr << std::setw(6);
				if (ups < 1000.0)
					sstr << std::setprecision(0) << 1.0 * ups << " " << operationUnit() << "/s";
				else if (ups < 10000)
					sstr << std::setprecision(2) << 0.001 * ups << " k" << operationUnit() << "/s";
				else if (ups < 100000)
					sstr << std::setprecision(1) << 0.001 * ups << " k" << operationUnit() << "/s";
				else if (ups < 1000000)
					sstr << std::setprecision(0) << 0.001 * ups << " k" << operationUnit() << "/s";
				else if (ups < 10000000)
					sstr << std::setprecision(2) << 0.000001 * ups << " M" << operationUnit() << "/s";
				else if (ups < 100000000)
					sstr << std::setprecision(1) << 0.000001 * ups << " M" << operationUnit() << "/s";
				else if (ups < 1000000000)
					sstr << std::setprecision(0) << 0.000001 * ups << " M" << operationUnit() << "/s";
				else if (ups < 10000000000)
					sstr << std::setprecision(2) << 0.000000001 * ups << " G" << operationUnit() << "/s";
				else if (ups < 10000000000)
					sstr << std::setprecision(1) << 0.000000001 * ups << " G" << operationUnit() << "/s";
				else
					sstr << std::setprecision(0) << 0.000000001 * ups << " G" << operationUnit() << "/s";
				return sstr.str();
			}
		};
	public:
		profiler() noexcept :
			m_Begin{ clockType::now() },
			m_End{ clockType::now() }
		{

		}
		~profiler() noexcept = default;
		void start() noexcept
		{
			m_Begin = clockType::now();
		}
		void stop() noexcept
		{
			m_End = clockType::now();
		}
		durationType duration() const noexcept
		{
			return m_End - m_Begin;
		}
		speed computeSpeed(const double operationCount, const std::string& unit) const noexcept
		{
			return speed(operationCount, duration(), unit);
		}
	};

	std::ostream& operator<<(std::ostream& stream, const typename profiler::speed& speed) noexcept
	{
		stream << static_cast<std::string>(speed);
		return stream;
	}
}