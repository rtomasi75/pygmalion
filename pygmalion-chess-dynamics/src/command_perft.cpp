#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	void command_perft::perft(const stackType& stack, const size_t depth, const size_t maxDepth, perftdata& data, typename generatorType::movegenFeedback& feedback) noexcept
	{
		movebitsType moveBits;
		data.Nodes++;
		if (depth == maxDepth)
		{
			while (stack.nextMove(moveBits, depth, feedback))
			{
				data.Leafs++;
				if (motorType::move().isCapture(moveBits))
					data.Captures++;
				if (motorType::move().isEnPassant(moveBits))
					data.EnPassant++;
				if (motorType::move().isDoublePush(moveBits))
					data.DoublePushes++;
				if (motorType::move().isQueensideCastle(moveBits))
					data.QueensideCastles++;
				if (motorType::move().isKingsideCastle(moveBits))
					data.KingsideCastles++;
				if (motorType::move().isCastle(moveBits))
					data.Castles++;
				if (motorType::move().isPromotion(moveBits))
					data.Promotions++;
				{
					const stackType substack{ stackType(stack,moveBits) };
					if (substack.isPositionCritical())
					{
						data.Checks++;
						movebitsType moveBits2;
						if (!substack.nextMove(moveBits2, depth + 1, feedback))
							data.Checkmates++;
					}
				}
			}
		}
		else
		{
			while (stack.nextMove(moveBits, depth, feedback))
			{
				const stackType substack{ stackType(stack,moveBits) };
				perft(substack, depth + 1, maxDepth, data, feedback);
			}
		}
	}

	bool command_perft::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "perft")
		{
			size_t depth{ static_cast<size_t>(parser::parseInt(remainder)) };
			profiler p;
			this->output() << std::endl;
			if (depth > 0)
			{
				perftdata data;
				p.start();
				stackType stack{ stackType(this->position(),this->history(), this->position().movingPlayer()) };
				movebitsType moveBits;
				while (stack.nextMove(moveBits, 0, this->feedback()))
				{
					data.Nodes++;
					if (depth == 1)
					{
						data.Leafs++;
						if (motorType::move().isCapture(moveBits))
							data.Captures++;
						if (motorType::move().isEnPassant(moveBits))
							data.EnPassant++;
						if (motorType::move().isDoublePush(moveBits))
							data.DoublePushes++;
						if (motorType::move().isQueensideCastle(moveBits))
							data.QueensideCastles++;
						if (motorType::move().isKingsideCastle(moveBits))
							data.KingsideCastles++;
						if (motorType::move().isCastle(moveBits))
							data.Castles++;
						if (motorType::move().isPromotion(moveBits))
							data.Promotions++;
						{
							const stackType substack{ stackType(stack,moveBits) };
							if (substack.isPositionCritical())
							{
								data.Checks++;
								movebitsType moveBits2;
								if (!substack.nextMove(moveBits2, 1, this->feedback()))
									data.Checkmates++;
							}
						}
						this->output() << "  " << motorType::move().toString(this->position(), moveBits) << std::endl;
					}
					else
					{
						perftdata data2;
						{
							const stackType substack{ stackType(stack,moveBits) };
							perft(substack, 1, depth - 1, data2, this->feedback());
						}
						this->output() << "  " << motorType::move().toString(this->position(), moveBits) << "\t: " << data2.Leafs << std::endl;
						data += data2;
					}
				}
				p.stop();
				this->output() << std::endl;
				this->output() << "depth: " << std::setw(2) << static_cast<int>(depth) << " nodes: " << parser::valueToString(static_cast<double>(data.Nodes), "N") << " time: " << parser::durationToString(p.duration()) << " speed: " << p.computeSpeed(data.Nodes, "N") << std::endl;
				this->output() << std::endl;
				this->output() << " Leafs:             " << data.Leafs << std::endl;
				this->output() << " Captures:          " << data.Captures << std::endl;
				this->output() << " En passant:        " << data.EnPassant << std::endl;
				this->output() << " Castles:           " << data.Castles << std::endl;
				this->output() << " Promotions:        " << data.Promotions << std::endl;
				this->output() << " Checks:            " << data.Checks << std::endl;
				this->output() << " Checkmates:        " << data.Checkmates << std::endl;
				this->output() << " Double pushes:     " << data.DoublePushes << std::endl;
				this->output() << " Queenside castles: " << data.QueensideCastles << std::endl;
				this->output() << " Kingside castles:  " << data.KingsideCastles << std::endl;
				this->output() << std::endl;
			}
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