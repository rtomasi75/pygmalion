namespace pygmalion
{
	class parser
	{
	public:
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
		static void parseTokenCaseSensitive(const std::string text, std::string& token, std::string& remainder) noexcept
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
			token = token_raw;
			remainder = trimString(remainder = text.substr(i, lenCommand - i));
		}
		static std::string fromInt(const std::uintmax_t value) noexcept
		{
			std::stringstream sstr;
			sstr << value;
			return sstr.str();
		}
		static std::string valueToString(const double value, const std::string& unit) noexcept
		{
			std::stringstream sstr;
			sstr << std::fixed;
			sstr << std::setw(6);
			if (value < 0.00000000001)
				sstr << std::setprecision(2) << 1000000000000.0 * value << " f" << unit << " ";
			else if (value < 0.0000000001)
				sstr << std::setprecision(1) << 1000000000000.0 * value << " f" << unit << " ";
			else if (value < 0.000000001)
				sstr << std::setprecision(0) << 1000000000000.0 * value << " f" << unit << " ";
			else if (value < 0.00000001)
				sstr << std::setprecision(2) << 1000000000.0 * value << " n" << unit << " ";
			else if (value < 0.0000001)
				sstr << std::setprecision(1) << 1000000000.0 * value << " n" << unit << " ";
			else if (value < 0.000001)
				sstr << std::setprecision(0) << 1000000000.0 * value << " n" << unit << " ";
			else if (value < 0.00001)
				sstr << std::setprecision(2) << 1000000.0 * value << " mc" << unit << "";
			else if (value < 0.0001)
				sstr << std::setprecision(1) << 1000000.0 * value << " mc" << unit << "";
			else if (value < 0.001)
				sstr << std::setprecision(0) << 1000000.0 * value << " mc" << unit << "";
			else if (value < 0.01)
				sstr << std::setprecision(2) << 1000.0 * value << " m" << unit << " ";
			else if (value < 0.1)
				sstr << std::setprecision(1) << 1000.0 * value << " m" << unit << " ";
			else if (value < 1.0)
				sstr << std::setprecision(0) << 1000.0 * value << " m" << unit << " ";
			else if (value < 10.0)
				sstr << std::setprecision(2) << 1.0 * value << " " << unit << "  ";
			else if (value < 100.0)
				sstr << std::setprecision(1) << 1.0 * value << " " << unit << "  ";
			else if (value < 1000.0)
				sstr << std::setprecision(0) << 1.0 * value << " " << unit << "  ";
			else if (value < 10000)
				sstr << std::setprecision(2) << 0.001 * value << " k" << unit << " ";
			else if (value < 100000)
				sstr << std::setprecision(1) << 0.001 * value << " k" << unit << " ";
			else if (value < 1000000)
				sstr << std::setprecision(0) << 0.001 * value << " k" << unit << " ";
			else if (value < 10000000)
				sstr << std::setprecision(2) << 0.000001 * value << " M" << unit << " ";
			else if (value < 100000000)
				sstr << std::setprecision(1) << 0.000001 * value << " M" << unit << " ";
			else if (value < 1000000000)
				sstr << std::setprecision(0) << 0.000001 * value << " M" << unit << " ";
			else if (value < 10000000000)
				sstr << std::setprecision(2) << 0.000000001 * value << " G" << unit << " ";
			else if (value < 100000000000)
				sstr << std::setprecision(1) << 0.000000001 * value << " G" << unit << " ";
			else if (value < 1000000000000)
				sstr << std::setprecision(0) << 0.000000001 * value << " G" << unit << " ";
			else if (value < 10000000000000)
				sstr << std::setprecision(2) << 0.000000000001 * value << " T" << unit << " ";
			else if (value < 100000000000000)
				sstr << std::setprecision(1) << 0.000000000001 * value << " T" << unit << " ";
			else
				sstr << std::setprecision(0) << 0.000000000001 * value << " T" << unit << " ";
			return sstr.str();
		}
		using durationType = typename profiler::durationType;
		static std::string durationToString(const durationType duration) noexcept
		{
			auto ctr = duration.count();
			return valueToString(static_cast<double>(ctr) / 1000000000.0, "s");
		}

		static auto speedToString(const profiler::speed& spd) noexcept
		{
			const double ups{ spd.operationsPerSec() };
			return valueToString(ups, spd.operationUnit() + "/s");
		}

		static long long int parseInt(const std::string& str) noexcept
		{
			try
			{
#if defined _MSC_VER
				return _strtoui64(str.c_str(), nullptr, 10);
#else
				return strtoll(str.c_str(), nullptr, 10);
#endif
			}
			catch (...)
			{
				return 0;
			}
	}
};
}
