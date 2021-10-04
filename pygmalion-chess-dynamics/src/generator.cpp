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

	std::string generator::passToString_Implementation(const stageType stage, const passType pass) noexcept
	{
		switch (static_cast<size_t>(stage))
		{
		case movegenStage_AllMoves:
			switch (static_cast<size_t>(pass))
			{
			case 0:
				return "knight quiet moves";
			case 1:
				return "pawn pushes";
			case 2:
				return "pawn double pushes";
			case 3:
				return "knight captures";
			case 4:
				return "pawn captures";
			case 5:
				return "en passant captures";
			case 6:
				return "h./v. slider quiet moves";
			case 7:
				return "diag. slider quiet moves";
			case 8:
				return "h./v. slider captures";
			case 9:
				return "diag. slider captures";
			case 10:
				return "king quiet moves";
			case 11:
				return "king captures";
			case 12:
				return "castles";
			case 13:
				return "quiet promotions";
			case 14:
				return "capture promotions";
			default:
				PYGMALION_UNREACHABLE;
				return "???";
			}
			break;
		case movegenStage_TacticalMoves:
			switch (static_cast<size_t>(pass))
			{
			case 0:
				return "knight captures";
			case 1:
				return "pawn captures";
			case 2:
				return "en passant captures";
			case 3:
				return "h./v. slider captures";
			case 4:
				return "diag. slider captures";
			case 5:
				return "king captures";
			case 6:
				return "capture promotions";
			default:
				PYGMALION_UNREACHABLE;
				return "???";
			};
			break;
		case movegenStage_CriticalMoves:
			switch (static_cast<size_t>(pass))
			{
			case 0:
				return "critical knight moves";
			case 1:
				return "critical pawn moves";
			case 2:
				return "critical h./v. slider moves";
			case 3:
				return "critical diag. slider moves";
			default:
				PYGMALION_UNREACHABLE;
				return "???";
			};
			break;
		case movegenStage_QuietCriticalMoves:
			switch (static_cast<size_t>(pass))
			{
			case 0:
				return "critical quiet knight moves";
			case 1:
				return "critical quiet pawn moves";
			case 2:
				return "critical quiet h./v. slider moves";
			case 3:
				return "critical quiet diag. slider moves";
			default:
				PYGMALION_UNREACHABLE;
				return "???";
			}
			break;
		case movegenStage_CriticalEvasionMoves:
			return "criticality evasion moves";
		case movegenStage_TacticalCriticalEvasionMoves:
			return "tactical criticality evasion moves";
		case movegenStage_WinningMoves:
			switch (static_cast<size_t>(pass))
			{
			case 0:
				return "winning knight captures";
			case 1:
				return "winning pawn captures";
			case 2:
				return "winning h./v. slider captures";
			case 3:
				return "winning diag. slider captures";
			case 4:
				return "king captures";
			case 5:
				return "capture promotions";
			default:
				PYGMALION_UNREACHABLE;
				return "???";
			};
			break;
		case movegenStage_EqualMoves:
			switch (static_cast<size_t>(pass))
			{
			case 0:
				return "equal knight captures";
			case 1:
				return "equal pawn captures";
			case 2:
				return "equal h./v. slider captures";
			case 3:
				return "equal diag. slider captures";
			case 4:
				return "en passant captures";
			default:
				PYGMALION_UNREACHABLE;
				return "???";
			};
			break;
		case movegenStage_LosingMoves:
			switch (static_cast<size_t>(pass))
			{
			case 0:
				return "losing knight captures";
			case 1:
				return "losing h./v. slider captures";
			case 2:
				return "losing diag. slider captures";
			default:
				PYGMALION_UNREACHABLE;
				return "???";
			};
			break;
		case movegenStage_QuietMoves:
			switch (static_cast<size_t>(pass))
			{
			case 0:
				return "knight quiet moves";
			case 1:
				return "pawn pushes";
			case 2:
				return "pawn double pushes";
			case 3:
				return "h./v. slider quiet moves";
			case 4:
				return "diag. slider quiet moves";
			case 5:
				return "king quiet moves";
			case 6:
				return "castles";
			case 7:
				return "quiet promotions";
			default:
				PYGMALION_UNREACHABLE;
				return "???";
			}
			break;
		default:
			PYGMALION_UNREACHABLE;
			return "???";
		}
	}

	std::string generator::tacticalPassToString_Implementation(const passType tacticalPass) noexcept
	{
		switch (static_cast<size_t>(tacticalPass))
		{
		default:
			PYGMALION_UNREACHABLE;
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
			PYGMALION_UNREACHABLE;
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
			PYGMALION_UNREACHABLE;
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
			PYGMALION_UNREACHABLE;
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
			PYGMALION_UNREACHABLE;
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