#include <pygmalion-chess.h>

namespace pygmalion::chess
{
	void board::boardStack::computeAttackSquares(const playerType p) const noexcept
	{
		m_AttackedSquares[p] = movegen::attackedSquares(position(), p);
		m_AttackedSquaresValid[p] = true;
	}

	void board::boardStack::computeIsCheck() const noexcept
	{
		m_IsCheck = movegen::position_isCheck(position());
		m_IsCheckValid = true;
	}

	void board::makeMove_Implementation(board& position, const movedata& md) noexcept
	{
		score newMaterial{ md.oldMaterial() };
		if (md.isCapture())
		{
			position.removePiece(md.capturedPiece(), md.captureSquare(), md.otherPlayer());
			position.setDistanceToDraw(DrawingDistance);
			newMaterial -= evaluator::material(md.otherPlayer(), md.capturedPiece(), md.captureSquare());
			switch (md.capturedPiece())
			{
			case movegen::rook:
				if (md.otherPlayer() == movegen::blackPlayer)
				{
					if (md.captureSquare() == movegen::squareA8)
						movegen::position_clearCastlerightQueensideBlack(position);
					else if (md.captureSquare() == movegen::squareH8)
						movegen::position_clearCastlerightKingsideBlack(position);
				}
				else
				{
					if (md.captureSquare() == movegen::squareA1)
						movegen::position_clearCastlerightQueensideWhite(position);
					else if (md.captureSquare() == movegen::squareH1)
						movegen::position_clearCastlerightKingsideWhite(position);
				}
				break;
			}
		}
		else
			position.setDistanceToDraw(position.getDistanceToDraw() - 1);
		switch (md.movingPiece())
		{
		case movegen::king:
			if (md.movingPlayer() == movegen::blackPlayer)
			{
				movegen::position_clearCastlerightKingsideBlack(position);
				movegen::position_clearCastlerightQueensideBlack(position);
			}
			else
			{
				movegen::position_clearCastlerightKingsideWhite(position);
				movegen::position_clearCastlerightQueensideWhite(position);
			}
		case movegen::rook:
			if (md.movingPlayer() == movegen::blackPlayer)
			{
				if (md.fromSquare() == movegen::squareA8)
					movegen::position_clearCastlerightQueensideBlack(position);
				else if (md.fromSquare() == movegen::squareH8)
					movegen::position_clearCastlerightKingsideBlack(position);
			}
			else
			{
				if (md.fromSquare() == movegen::squareA1)
					movegen::position_clearCastlerightQueensideWhite(position);
				else if (md.fromSquare() == movegen::squareH1)
					movegen::position_clearCastlerightKingsideWhite(position);
			}
			break;
		}
		position.removePiece(md.movingPiece(), md.fromSquare(), md.movingPlayer());
		newMaterial -= evaluator::material(md.movingPlayer(), md.movingPiece(), md.fromSquare());
		position.addPiece(md.targetPiece(), md.toSquare(), md.movingPlayer());
		newMaterial += evaluator::material(md.movingPlayer(), md.targetPiece(), md.toSquare());
		movegen::position_clearEnPassantFlags(position);
		if (md.isDoublePush())
			movegen::position_setEnPassantFlag(position, md.toSquare().file());
		else if (md.isCastling())
		{
			position.removePiece(movegen::rook, md.rookFrom(), md.movingPlayer());
			newMaterial -= evaluator::material(md.movingPlayer(), movegen::rook, md.rookFrom());
			position.addPiece(movegen::rook, md.rookTo(), md.movingPlayer());
			newMaterial += evaluator::material(md.movingPlayer(), movegen::rook, md.rookTo());
		}
		position.setMovingPlayer(md.otherPlayer());
		position.setMaterial(newMaterial);
	}

	void board::unmakeMove_Implementation(board& position, const movedata& md) noexcept
	{
		if (md.isCastling())
		{
			position.removePiece(movegen::rook, md.rookTo(), md.movingPlayer());
			position.addPiece(movegen::rook, md.rookFrom(), md.movingPlayer());
		}
		position.removePiece(md.targetPiece(), md.toSquare(), md.movingPlayer());
		position.addPiece(md.movingPiece(), md.fromSquare(), md.movingPlayer());
		if (md.isCapture())
			position.addPiece(md.capturedPiece(), md.captureSquare(), md.otherPlayer());
		position.setMaterial(md.oldMaterial());
		position.setDistanceToDraw(md.oldDistanceToDraw());
		position.setMovingPlayer(md.movingPlayer());
		position.setFlags(md.oldFlags());
	}

	board::board() noexcept :
		pygmalion::board<descriptor_board, descriptor_move, 64, 255, pygmalion::chess::board>(),
		m_Material{ score::zero() },
		m_DistanceToDraw{ DrawingDistance }
	{
	}

}