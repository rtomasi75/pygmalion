namespace pygmalion
{
	class parser
	{
	public:
		parser() = delete;
		~parser() = delete;
		static double computeNodesPerSec(const uint64_t nodeCount, const std::chrono::nanoseconds duration) noexcept
		{
			return (10000.0 * static_cast<double>(nodeCount)) / (0.00001 * static_cast<double>(duration.count()));
		}
		static std::string toString(const std::uint64_t val) noexcept
		{
			std::stringstream sstr;
			sstr << "0x" << std::setfill('0') << std::setw(sizeof(std::uint64_t) * 2) << std::hex << val;
			return sstr.str();
		}
		static std::string toString(const std::uint32_t val) noexcept
		{
			std::stringstream sstr;
			sstr << "0x" << std::setfill('0') << std::setw(sizeof(std::uint32_t) * 2) << std::hex << val;
			return sstr.str();
		}
		static std::string toString(const std::uint16_t val) noexcept
		{
			std::stringstream sstr;
			sstr << "0x" << std::setfill('0') << std::setw(sizeof(std::uint16_t) * 2) << std::hex << val;
			return sstr.str();
		}
		static std::string toString(const std::uint8_t val) noexcept
		{
			std::stringstream sstr;
			sstr << "0x" << std::setfill('0') << std::setw(sizeof(std::uint8_t) * 2) << std::hex << (int)val;
			return sstr.str();
		}
		template<int BITS>
		static std::string toString(const bitfield<BITS>& val) noexcept
		{
			return toString(val.bits());
		}
		static auto nodesCountToString(const std::uint64_t nodeCount) noexcept
		{
			std::stringstream sstr;
			sstr << std::fixed;
			sstr << std::setw(6);
			const double nc{ static_cast<double>(nodeCount) };
			if (nc < 1000.0)
				sstr << std::setprecision(0) << 1.0 * nc << " n";
			else if (nc < 10000)
				sstr << std::setprecision(2) << 0.001 * nc << " kn";
			else if (nc < 100000)
				sstr << std::setprecision(1) << 0.001 * nc << " kn";
			else if (nc < 1000000)
				sstr << std::setprecision(0) << 0.001 * nc << " kn";
			else if (nc < 10000000)
				sstr << std::setprecision(2) << 0.000001 * nc << " Mn";
			else if (nc < 100000000)
				sstr << std::setprecision(1) << 0.000001 * nc << " Mn";
			else if (nc < 1000000000)
				sstr << std::setprecision(0) << 0.000001 * nc << " Mn";
			else if (nc < 10000000000)
				sstr << std::setprecision(2) << 0.000000001 * nc << " Gn";
			else if (nc < 10000000000)
				sstr << std::setprecision(1) << 0.000000001 * nc << " Gn";
			else
				sstr << std::setprecision(0) << 0.000000001 * nc << " Gn";
			return sstr.str();
		}
		static auto nodesPerSecondToString(const double nps) noexcept
		{
			std::stringstream sstr;
			sstr << std::fixed;
			sstr << std::setw(6);
			if (nps < 1000.0)
				sstr << std::setprecision(0) << 1.0 * nps << " nps";
			else if (nps < 10000)
				sstr << std::setprecision(2) << 0.001 * nps << " knps";
			else if (nps < 100000)
				sstr << std::setprecision(1) << 0.001 * nps << " knps";
			else if (nps < 1000000)
				sstr << std::setprecision(0) << 0.001 * nps << " knps";
			else if (nps < 10000000)
				sstr << std::setprecision(2) << 0.000001 * nps << " Mnps";
			else if (nps < 100000000)
				sstr << std::setprecision(1) << 0.000001 * nps << " Mnps";
			else if (nps < 1000000000)
				sstr << std::setprecision(0) << 0.000001 * nps << " Mnps";
			else if (nps < 10000000000)
				sstr << std::setprecision(2) << 0.000000001 * nps << " Gnps";
			else if (nps < 10000000000)
				sstr << std::setprecision(1) << 0.000000001 * nps << " Gnps";
			else
				sstr << std::setprecision(0) << 0.000000001 * nps << " Gnps";
			return sstr.str();
		}
		static auto durationToString(const std::chrono::nanoseconds duration) noexcept
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
		static std::int64_t parseInt(const std::string& str) noexcept
		{
			try
			{
#if defined _MSC_VER
				return _strtoui64(str.c_str(), NULL, 10);
#else
				return strtoll(str.c_str(), NULL, 10);
#endif
			}
			catch (...)
			{
				return 0;
			}
		}
		static auto toLower(std::string s) noexcept
		{
			std::transform(s.begin(), s.end(), s.begin(), ::tolower);
			return s;
		}
		static auto toUpper(std::string s) noexcept
		{
			std::transform(s.begin(), s.end(), s.begin(), ::toupper);
			return s;
		}
		static auto rightTrimString(std::string s) noexcept
		{
			s.erase(std::find_if(s.rbegin(), s.rend(), [](char c) {return !std::isspace(c); }).base(), s.end());
			return s;
		}
		static auto leftTrimString(std::string s) noexcept
		{
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](char c) {return !std::isspace(c); }));
			return s;
		}
		static auto trimString(std::string s) noexcept
		{
			return leftTrimString(rightTrimString(s));
		}
		static void parseToken(const std::string text, std::string& token, std::string& remainder) noexcept
		{
			size_t lenCommand = text.length();
			std::string token_raw = "";
			size_t i;
			for (i = 0; i < lenCommand; i++)
			{
				if (text[i] == ' ')
					break;
				else
					token_raw += text[i];
			}
			token = toLower(token_raw);
			remainder = trimString(remainder = text.substr(i, lenCommand - i));
		}

	};
}