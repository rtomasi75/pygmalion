#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_testMovegen::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "test-movegen")
		{
			std::string remainder2;
			parser::parseTokenCaseSensitive(remainder, token, remainder2);
			size_t maxdepth{ 256 };
			if (token != "")
				maxdepth = parser::parseInt(token);
			this->output() << std::endl;
			this->template process<0>(maxdepth);
			this->output() << std::endl;
			return true;
		}
		else
			return false;
	}

	const std::string& command_testMovegen::testset::fen() const noexcept
	{
		return m_Fen;
	}

	std::uintmax_t command_testMovegen::testset::expected() const noexcept
	{
		return m_Expected;
	}

	size_t command_testMovegen::testset::depth() const noexcept
	{
		return m_Depth;
	}

	command_testMovegen::testset::testset(const std::string& fen, const size_t depth, const std::uintmax_t expected) noexcept :
		m_Fen{ fen },
		m_Depth{ depth },
		m_Expected{ expected }
	{}
}