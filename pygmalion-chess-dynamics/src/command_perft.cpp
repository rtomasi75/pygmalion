#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_perft::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "perft")
		{
			size_t depth{ static_cast<size_t>(parser::parseInt(remainder)) };
			this->process<0>(depth);
			return true;
		}
		else
			return false;
	}

	typename command_perft::perftdata& command_perft::perftdata::operator+=(const typename command_perft::perftdata& data) noexcept
	{
		Leafs += data.Leafs;
		Nodes += data.Nodes;
		Captures += data.Captures;
		EnPassant += data.EnPassant;
		DoublePushes += data.DoublePushes;
		QueensideCastles += data.QueensideCastles;
		KingsideCastles += data.KingsideCastles;
		Castles += data.Castles;
		Checks += data.Checks;
		Checkmates += data.Checkmates;
		Promotions += data.Promotions;
		return *this;
	}
}