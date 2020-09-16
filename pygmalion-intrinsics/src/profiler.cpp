#include <pygmalion-intrinsics.h>

namespace pygmalion
{
	profiler::profiler() noexcept :
		m_Begin{ clockType::now() },
		m_End{ clockType::now() }
	{

	}

	void profiler::start() noexcept
	{
		m_Begin = clockType::now();
	}

	void profiler::stop() noexcept
	{
		m_End = clockType::now();
	}

	typename profiler::durationType profiler::duration() const noexcept
	{
		return m_End - m_Begin;
	}

	typename profiler::speed profiler::computeSpeed(const double operationCount, const std::string & unit) const noexcept
	{
		return speed(operationCount, duration(), unit);
	}

	profiler::speed::speed(const double operationsCount, const durationType duration, const std::string& unit) noexcept :
		m_OperationsCount{ operationsCount },
		m_Duration{ duration },
		m_Unit{ unit }
	{}

	const std::string& profiler::speed::operationUnit() const noexcept
	{
		return m_Unit;
	}

	double profiler::speed::operationsCount() const noexcept
	{
		return m_OperationsCount;
	}

	typename profiler::durationType profiler::speed::duration() const noexcept
	{
		return m_Duration;
	}

	double profiler::speed::operationsPerSec() const noexcept
	{
		return (10000.0 * static_cast<double>(m_OperationsCount)) / (0.00001 * static_cast<double>(m_Duration.count()));
	}

	profiler::speed::operator std::string() const noexcept
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

	std::ostream& operator<<(std::ostream& stream, const typename profiler::speed& speed) noexcept
	{
		stream << static_cast<std::string>(speed);
		return stream;
	}

}