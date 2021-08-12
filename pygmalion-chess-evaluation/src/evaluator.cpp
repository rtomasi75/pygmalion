#include <pygmalion-chess-evaluation.h>
namespace pygmalion::chess
{
	std::deque<std::shared_ptr<pygmalion::intrinsics::command>> evaluator::commandsImplementation() noexcept
	{
		std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ std::deque<std::shared_ptr<pygmalion::intrinsics::command>>() };
		evaluatorType::addCommand<pygmalion::chess::evaluation::command_debugControl>(list);
		return list;
	}

	evaluator::objectiveType evaluator::mobility(const generatorType::stackType& stack) noexcept
	{
		const squaresType targetedByBlack{ stack.squaresTargetedByPlayer(blackPlayer) };
		const squaresType targetedByWhite{ stack.squaresTargetedByPlayer(whitePlayer) };
		const int targets{ static_cast<int>(targetedByWhite.count()) - static_cast<int>(targetedByBlack.count()) };
		const objectiveType scoreTargets{ targets * m_MobilityFactor };
		return scoreTargets;
	}

	evaluator::objectiveType evaluator::attack(const generatorType::stackType& stack) noexcept
	{
		const squaresType attackedByBlack{ stack.squaresAttackedByPlayer(blackPlayer) };
		const squaresType attackedByWhite{ stack.squaresAttackedByPlayer(whitePlayer) };
		const int attacks{ static_cast<int>(attackedByWhite.count()) - static_cast<int>(attackedByBlack.count()) };
		const objectiveType scoreAttacks{ attacks * m_AttackFactor };
		return scoreAttacks;
	}

	evaluator::objectiveType evaluator::control(const generatorType::stackType& stack) noexcept
	{
		squaresType controlledByBlack;
		squaresType controlledByWhite;
		stack.control(controlledByWhite, controlledByBlack);
		const int control{ static_cast<int>(controlledByWhite.count()) - static_cast<int>(controlledByBlack.count()) };
		const objectiveType scoreControl{ control * m_ControlFactor };
		return scoreControl;
	}

	evaluator::gamestateType evaluator::earlyResult_Implementation(const generatorType::stackType& stack) noexcept
	{
		if (stack.position().cumulation().reversiblePlies() >= 100)
			return gamestateType::draw();
		if (stack.occurs(stack.position(), 2, 4, 4))
			return gamestateType::draw();
		if (stack.position().playerOccupancy(whitePlayer) == squaresType(stack.kingSquare(whitePlayer)))
		{
			if (stack.position().playerOccupancy(blackPlayer) == squaresType(stack.kingSquare(blackPlayer)))
				return gamestateType::draw();
			if (stack.position().playerOccupancy(blackPlayer) & (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen) | stack.position().pieceOccupancy(pawn)) == squaresType::none())
			{
				if ((stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(bishop)) == squaresType::none())
				{
					if ((stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(knight)).count() == 1)
						return gamestateType::draw();
				}
				if ((stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(knight)) == squaresType::none())
				{
					if ((stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(bishop)).count() == 1)
						return gamestateType::draw();
				}
			}
		}
		else if (stack.position().playerOccupancy(blackPlayer) == squaresType(stack.kingSquare(blackPlayer)))
		{
			if (stack.position().playerOccupancy(whitePlayer) & (stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(queen) | stack.position().pieceOccupancy(pawn)) == squaresType::none())
			{
				if ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)) == squaresType::none())
				{
					if ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(knight)).count() == 1)
						return gamestateType::draw();
				}
				if ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(knight)) == squaresType::none())
				{
					if ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).count() == 1)
						return gamestateType::draw();
				}
			}
		}
		else if ((stack.position().pieceOccupancy(queen) | stack.position().pieceOccupancy(rook) | stack.position().pieceOccupancy(knight) | stack.position().pieceOccupancy(pawn)) == squaresType::none())
		{
			if (((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).count() == 1) && ((stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).count() == 1))
			{
				const squareType whiteBishop{ *(stack.position().playerOccupancy(whitePlayer) & stack.position().pieceOccupancy(bishop)).begin() };
				const squareType blackBishop{ *(stack.position().playerOccupancy(blackPlayer) & stack.position().pieceOccupancy(bishop)).begin() };
				if (whiteBishop.isDark() == blackBishop.isDark())
					return gamestateType::draw();
			}
		}
		return gamestateType::open();
	}

	evaluator::gamestateType evaluator::lateResult_Implementation(const typename generatorType::stackType& stack) noexcept
	{
		if (stack.isCheck())
			return gamestateType::loss(stack.position().movingPlayer());
		else
			return gamestateType::draw();
	}

	evaluator::objectiveType evaluator::evaluate_Implementation(const multiscoreType& score, const generatorType::stackType& stack) noexcept
	{
		const objectiveType mat{ static_cast<objectiveType>(stack.position().material()) };
		objectiveType sc{ mat };
		const playerType movingPlayer{ stack.movingPlayer() };
		if (!score.isFutile(movingPlayer, sc, m_DeltaMobility + m_DeltaAttack + m_DeltaControl))
		{
			const objectiveType mob{ mobility(stack) };
			sc += mob;
			if (!score.isFutile(movingPlayer, sc, m_DeltaAttack + m_DeltaControl))
			{
				const objectiveType att{ attack(stack) };
				sc += att;
				if (!score.isFutile(movingPlayer, sc, m_DeltaControl))
				{
					const objectiveType ctrl{ control(stack) };
					sc += ctrl;
				}
			}
		}
		return sc;
	}
}