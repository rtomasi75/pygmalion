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
		generatorType::addCommand<pygmalion::chess::dynamics::command_debugCheck>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_perft>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_setFen>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_getFen>(list);
		generatorType::addCommand<pygmalion::chess::dynamics::command_testMovegen>(list);
		return list;
	}
}