#include <pygmalion-chess-evaluation.h>
namespace pygmalion::chess
{
	std::deque<std::shared_ptr<pygmalion::intrinsics::command>> evaluator::commandsImplementation() noexcept
	{
		std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ std::deque<std::shared_ptr<pygmalion::intrinsics::command>>() };
		evaluatorType::addCommand<pygmalion::chess::evaluation::command_debugControl>(list);
		evaluatorType::addCommand<pygmalion::chess::evaluation::command_debugSEE>(list);
		return list;
	}

	evaluator::gamestateType evaluator::lateResult_Implementation(const typename generatorType::stackType& stack) noexcept
	{
		if (stack.isPositionCritical())
			return gamestateType::loss(stack.position().movingPlayer());
		else
			return gamestateType::draw();
	}
}