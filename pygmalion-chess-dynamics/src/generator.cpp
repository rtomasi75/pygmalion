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

	std::string generator::passToString_Implementation(const passType pass) noexcept
	{
		switch (static_cast<size_t>(pass))
		{
		default:
			PYGMALION_UNREACHABLE;
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