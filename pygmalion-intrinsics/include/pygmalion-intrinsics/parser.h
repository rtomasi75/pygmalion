class parser
{
public:
	using durationType = typename profiler::durationType;
	static std::string durationToString(const durationType duration) noexcept
	{
		std::stringstream sstr;
		auto ctr = duration.count();
		sstr << std::fixed;
		sstr << std::setw(6);
		if (std::abs(ctr) < 1)
			sstr << std::setprecision(3) << 1.0 * static_cast<double>(ctr) << " ns";
		else if (std::abs(ctr) < 10)
			sstr << std::setprecision(2) << 1.0 * static_cast<double>(ctr) << " ns";
		else if (std::abs(ctr) < 100)
			sstr << std::setprecision(1) << 1.0 * static_cast<double>(ctr) << " ns";
		else if (std::abs(ctr) < 1000)
			sstr << std::setprecision(0) << 1.0 * static_cast<double>(ctr) << " ns";
		else if (std::abs(ctr) < 10000)
			sstr << std::setprecision(2) << 0.001 * static_cast<double>(ctr) << " mcs";
		else if (std::abs(ctr) < 100000)
			sstr << std::setprecision(1) << 0.001 * static_cast<double>(ctr) << " mcs";
		else if (std::abs(ctr) < 1000000)
			sstr << std::setprecision(0) << 0.001 * static_cast<double>(ctr) << " mcs";
		else if (std::abs(ctr) < 10000000)
			sstr << std::setprecision(2) << 0.000001 * static_cast<double>(ctr) << " ms";
		else if (std::abs(ctr) < 100000000)
			sstr << std::setprecision(1) << 0.000001 * static_cast<double>(ctr) << " ms";
		else if (std::abs(ctr) < 10000000000)
			sstr << std::setprecision(0) << 0.000001 * static_cast<double>(ctr) << " ms";
		else if (std::abs(ctr) < 100000000000)
			sstr << std::setprecision(2) << 0.000000001 * static_cast<double>(ctr) << " s";
		else if (std::abs(ctr) < 1000000000000)
			sstr << std::setprecision(1) << 0.000000001 * static_cast<double>(ctr) << " s";
		else
			sstr << std::setprecision(0) << 0.000000001 * static_cast<double>(ctr) << " s";
		return sstr.str();
	}

	static auto speedToString(const profiler::speed& spd) noexcept
	{
		const double ups{ spd.operationsPerSec() };
		std::stringstream sstr;
		sstr << std::fixed;
		sstr << std::setw(6);
		if (ups < 1000.0)
			sstr << std::setprecision(0) << 1.0 * ups << " "<< spd.operationUnit()<< "/s";
		else if (ups < 10000)
			sstr << std::setprecision(2) << 0.001 * ups << " k" << spd.operationUnit() << "/s";
		else if (ups < 100000)
			sstr << std::setprecision(1) << 0.001 * ups << " k" << spd.operationUnit() << "/s";
		else if (ups < 1000000)
			sstr << std::setprecision(0) << 0.001 * ups << " k" << spd.operationUnit() << "/s";
		else if (ups < 10000000)
			sstr << std::setprecision(2) << 0.000001 * ups << " M" << spd.operationUnit() << "/s";
		else if (ups < 100000000)
			sstr << std::setprecision(1) << 0.000001 * ups << " M" << spd.operationUnit() << "/s";
		else if (ups < 1000000000)
			sstr << std::setprecision(0) << 0.000001 * ups << " M" << spd.operationUnit() << "/s";
		else if (ups < 10000000000)
			sstr << std::setprecision(2) << 0.000000001 * ups << " G" << spd.operationUnit() << "/s";
		else if (ups < 10000000000)
			sstr << std::setprecision(1) << 0.000000001 * ups << " G" << spd.operationUnit() << "/s";
		else
			sstr << std::setprecision(0) << 0.000000001 * ups << " G" << spd.operationUnit() << "/s";
		return sstr.str();
	}
};