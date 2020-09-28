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
			bool bPassed{ true };
			constexpr const size_t n{ sizeof(m_Sets) / sizeof(testset) };
			std::uintmax_t nodes{ 0 };
			typename profiler::durationType duration{ 0 };
			for (size_t i = 0; i < n; i++)
			{
				if (m_Sets[i].depth() <= maxdepth)
				{
					bPassed &= test(m_Sets[i], nodes, duration);
					this->output() << std::endl;
					if (!bPassed)
						break;
				}
			}
			if (bPassed)
				this->output() << "ALL PASSED." << std::endl;
			else
				this->output() << "SOME FAILED." << std::endl;
			this->output() << std::endl;
			const profiler::speed spd(static_cast<double>(nodes), duration, "N");
			this->output() << parser::valueToString(static_cast<double>(nodes), "N") << " in " << parser::durationToString(duration) << " => " << spd << std::endl;
			return true;
		}
		else
			return false;
	}

	bool command_testMovegen::test(const testset& set, std::uintmax_t& nodes, typename profiler::durationType& duration) noexcept
	{
		this->output() << "Position: " << set.fen() << std::endl;
		this->output() << "Depth:    " << set.depth() << std::endl;
		this->output() << "Expected: " << set.expected() << std::endl;
		boardType position;
		std::string error;
		if (!position.setFen(set.fen(), error))
		{
			this->output() << "Invalid FEN: " << error << std::endl;
		}
		this->output() << "Computed: ";
		stackType stack(position, position.movingPlayer().next());
		profiler p;
		p.start();
		std::uintmax_t computed{ generatorType::perft(stack, set.depth(), nodes) };
		p.stop();
		duration += p.duration();
		this->output() << computed << std::endl;
		this->output() << std::endl;
		if (computed == set.expected())
		{
			this->output() << " => PASSED" << std::endl;
			return true;
		}
		else
		{
			this->output() << " => FAILED" << std::endl;
			return false;
		}
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