#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess
{
	std::deque<std::shared_ptr<pygmalion::intrinsics::command>> generator::commandsImplementation() noexcept
	{
		std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ std::deque<std::shared_ptr<pygmalion::intrinsics::command>>() };
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugMovegen>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugUntabled>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugMagics>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugAttacked>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugTargeted>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugCheck>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_perft>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_setFen>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_getFen>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_testMovegen>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugKingArea>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugTropism>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugMoveStats>(list);
		return list;
	}

	std::string generator::moveToString_Implementation(const stackType& stack, const movebitsType mv, const size_t depth) noexcept
	{
		const boardType& position{ stack.position() };
		const squareType from{ motorType::move().fromSquare(position,mv) };
		const squareType to{ motorType::move().toSquare(position,mv) };
		const pieceType piece{ position.getPiece(from) };
		const playerType side{ position.movingPlayer() };
		if (motorType::move().isKingsideCastle(mv))
			return "O-O";
		if (motorType::move().isQueensideCastle(mv))
			return "O-O-O";
		std::string ret = "";
		switch (piece)
		{
		default:
			assert(0);
			break;
		case pawn:
			break;
		case knight:
			ret += "N";
			break;
		case bishop:
			ret += "B";
			break;
		case rook:
			ret += "R";
			break;
		case queen:
			ret += "Q";
			break;
		case king:
			ret += "K";
			break;
		}
		int countamb{ 0 };
		for (const auto sq : squareType::range)
		{
			if ((position.pieceOccupancy(piece) & position.playerOccupancy(side))[sq])
			{
				squaresType captures{ squaresType::none() };
				squaresType moves{ squaresType::none() };
				generatorType::movesFromSquare(stack, sq, moves, captures, depth);
				if ((captures | moves)[to])
				{
					countamb++;
				}
			}
		}
		if (countamb > 1)
		{
			const auto file{ from.file() };
			countamb = 0;
			for (const auto sq : squareType::range)
			{
				if ((position.pieceOccupancy(piece) & position.playerOccupancy(side))[sq])
				{
					squaresType captures{ squaresType::none() };
					squaresType moves{ squaresType::none() };
					generatorType::movesFromSquare(stack, sq, moves, captures, depth);
					if ((captures | moves)[to])
					{
						if (sq.file() == file)
							countamb++;
					}
				}
			}
			if (countamb > 1)
			{
				const auto rank{ from.rank() };
				countamb = 0;
				for (const auto sq : squareType::range)
				{
					if ((position.pieceOccupancy(piece) & position.playerOccupancy(side))[sq])
					{
						squaresType captures{ squaresType::none() };
						squaresType moves{ squaresType::none() };
						generatorType::movesFromSquare(stack, sq, moves, captures, depth);
						if ((captures | moves)[to])
						{
							if (sq.rank() == rank)
								countamb++;
						}
					}
				}
				if (countamb > 1)
				{
					ret += boardType::squareToString(from);
				}
				else
				{
					switch (rank)
					{
					case 0:
						ret += "1";
						break;
					case 1:
						ret += "2";
						break;
					case 2:
						ret += "3";
						break;
					case 3:
						ret += "4";
						break;
					case 4:
						ret += "5";
						break;
					case 5:
						ret += "6";
						break;
					case 6:
						ret += "7";
						break;
					case 7:
						ret += "8";
						break;
					}
				}
			}
			else
			{
				switch (file)
				{
				case 0:
					ret += "a";
					break;
				case 1:
					ret += "b";
					break;
				case 2:
					ret += "c";
					break;
				case 3:
					ret += "d";
					break;
				case 4:
					ret += "e";
					break;
				case 5:
					ret += "f";
					break;
				case 6:
					ret += "g";
					break;
				case 7:
					ret += "h";
					break;
				}
			}
		}
		if (motorType::move().isCapture(mv))
		{
			ret += "x";
			if (motorType::move().isEnPassant(mv))
			{
				ret = ret + boardType::squareToString(motorType::move().captureSquare(position, mv));
				ret += "ep";
			}
			else
				ret = ret + boardType::squareToString(to);
		}
		else
			ret = ret + boardType::squareToString(to);
		if (motorType::move().isPromotion(mv))
		{
			switch (motorType::move().promotedPiece(mv))
			{
			case knight:
				ret += "=N";
				break;
			case bishop:
				ret += "=B";
				break;
			case rook:
				ret += "=R";
				break;
			case queen:
				ret += "=Q";
				break;
			}
		}
		return ret;
	}

	void generator::stack::control(squaresType& white, squaresType& black) const
	{
		if (!m_IsControlValid)
		{
			generatorType::control(*static_cast<const stackType*>(this), m_ControlledByPlayer[whitePlayer], m_ControlledByPlayer[blackPlayer]);
			m_IsControlValid = true;
		}
		white = m_ControlledByPlayer[whitePlayer];
		black = m_ControlledByPlayer[blackPlayer];
	}

	std::string generator::passToString_Implementation(const passType pass) noexcept
	{
		switch (static_cast<size_t>(pass))
		{
		default:
			assert(0);
			return "???";
		case 0:
			return "knight moves";
		case 1:
			return "pawn pushes";
		case 2:
			return "double pushes";
		case 3:
			return "knight captures";
		case 4:
			return "pawn captures";
		case 5:
			return "en Passant";
		case 6:
			return "slider moves h./v.";
		case 7:
			return "slider moves diag.";
		case 8:
			return "slider captures h./v.";
		case 9:
			return "slider captures diag.";
		case 10:
			return "king moves";
		case 11:
			return "king captures";
		case 12:
			return "castles";
		case 13:
			return "promotions";
		case 14:
			return "promotion captures";
		}
	}

	std::string generator::tacticalPassToString_Implementation(const passType tacticalPass) noexcept
	{
		switch (static_cast<size_t>(tacticalPass))
		{
		default:
			assert(0);
			return "???";
		case 0:
			return "knight captures";
		case 1:
			return "pawn captures";
		case 2:
			return "en Passant";
		case 3:
			return "slider captures h./v.";
		case 4:
			return "slider captures diag.";
		case 5:
			return "king captures";
		case 6:
			return "promotion captures";
		}
	}

	std::string generator::criticalPassToString_Implementation(const passType criticalPass) noexcept
	{
		switch (static_cast<size_t>(criticalPass))
		{
		default:
			assert(0);
			return "???";
		case 0:
			return "critical knight moves";
		case 1:
			return "critical pawn moves";
		case 2:
			return "critical slider moves h./v.";
		case 3:
			return "critical slider moves diag.";
		}
	}

	std::string generator::criticalEvasionPassToString_Implementation(const passType criticalPass) noexcept
	{
		switch (static_cast<size_t>(criticalPass))
		{
		default:
			assert(0);
			return "???";
		case 0:
			return "critical evasion moves";
		}
	}

	std::string generator::tacticalCriticalEvasionPassToString_Implementation(const passType tacticalCriticalEvasionPass) noexcept
	{
		switch (static_cast<size_t>(tacticalCriticalEvasionPass))
		{
		default:
			assert(0);
			return "???";
		case 0:
			return "tactical critical evasion moves";
		}
	}

	std::string generator::quietCriticalPassToString_Implementation(const passType quietCriticalPass) noexcept
	{
		switch (static_cast<size_t>(quietCriticalPass))
		{
		default:
			assert(0);
			return "???";
		case 0:
			return "quiet critical knight moves";
		case 1:
			return "quiet critical pawn moves";
		case 2:
			return "quiet critical slider moves h./v.";
		case 3:
			return "quiet critical slider moves diag.";
		}
	}
}