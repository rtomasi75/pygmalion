#include <pygmalion-chess.h>

namespace pygmalion::chess
{
	board::movedata::movedata(const board& position, const player oldPlayer) noexcept :
		movedataBase(position, oldPlayer),
		m_OldHash{ position.getHash() },
		m_OldPawnstructureHash{ position.getPawnstructureHash() },
		m_OldMaterial{ position.getMaterial() },
		m_OldFlags{ position.getFlags() },
		m_OldDistanceToDraw{ position.getDistanceToDraw() },
		m_IsPromotion{ false },
		m_IsCapture{ false },
		m_IsDoublePush{ false },
		m_IsCastling{ false },
		m_FromSquare{ square::invalid },
		m_ToSquare{ square::invalid },
		m_OtherPlayer{ square::invalid },
		m_MovingPiece{ piece::invalid },
		m_TargetPiece{ piece::invalid },
		m_CaptureSquare{ square::invalid },
		m_CapturedPiece{ piece::invalid },
		m_RookFrom{ square::invalid },
		m_RookTo{ square::invalid },
		m_WhiteKing{ position.kingSquare(whitePlayer) },
		m_BlackKing{ position.kingSquare(blackPlayer) }
	{

	}

	board::movedata::movedata(const board& position, const move& mv) noexcept :
		movedataBase(position),
		m_OldHash{ position.getHash() },
		m_OldPawnstructureHash{ position.getPawnstructureHash() },
		m_OldMaterial{ position.getMaterial() },
		m_OldFlags{ position.getFlags() },
		m_IsPromotion{ mv.isPromotion() },
		m_IsCapture{ mv.isCapture() },
		m_IsDoublePush{ mv.isDoublePush() },
		m_IsCastling{ mv.isCastle() },
		m_FromSquare{ mv.from() },
		m_ToSquare{ mv.to() },
		m_OtherPlayer{ movingPlayer().next() },
		m_MovingPiece{ position.getPiece(m_FromSquare) },
		m_TargetPiece{ m_IsPromotion ? mv.get_PromotionPiece() : m_MovingPiece },
		m_CaptureSquare{ square::invalid },
		m_CapturedPiece{ piece::invalid },
		m_RookFrom{ square::invalid },
		m_RookTo{ square::invalid },
		m_WhiteKing{ position.kingSquare(whitePlayer) },
		m_BlackKing{ position.kingSquare(blackPlayer) }
	{
		if (m_IsCapture)
		{
			if (mv.isEnPassant())
			{
				m_CaptureSquare = fromRankFile(rankOfSquare(m_FromSquare), fileOfSquare(m_ToSquare));
				m_CapturedPiece = pawn;
			}
			else
			{
				m_CaptureSquare = m_ToSquare;
				m_CapturedPiece = position.getPiece(m_CaptureSquare);
			}
		}
		else if (m_IsCastling)
		{
			const bool bWhite{ movingPlayer() == whitePlayer };
			const bool bKingSide{ mv.isCastleKingside() };
			m_RookFrom = bKingSide ? (bWhite ? squareH1 : squareH8) : (bWhite ? squareA1 : squareA8);
			m_RookTo = bKingSide ? (bWhite ? squareF1 : squareF8) : (bWhite ? squareD1 : squareD8);
		}
	}

	board::boardStack::boardStack(const boardStack& parent, const move mv) noexcept :
		stack<movedata, move, boardStack>(parent, mv),
		m_AttackedSquaresValid{ false,false },
		m_IsCheckValid{ false },
		m_OtherPlayer{ movingPlayer().next() }
	{
	}

	board::boardStack::boardStack(instanceType& position, const player oldPlayer) noexcept :
		stack<movedata, move, boardStack>(position, oldPlayer),
		m_AttackedSquaresValid{ false,false },
		m_IsCheckValid{ false },
		m_OtherPlayer{ movingPlayer().next() }
	{
	}


	bool board::boardStack::isMoveLegal_Implementation(const moveType& move) const noexcept
	{
		return movegen::isMoveLegal(*this, move);
	}

	bool board::boardStack::generateMoves_Implementation(movelistType& moves, int& currentPass) const noexcept
	{
		return movegen::generateMoves(*this, moves, currentPass);
	}
	bool board::boardStack::generateTacticalMoves_Implementation(movelistType& moves, int& currentPass) const noexcept
	{
		return movegen::generateTacticalMoves(*this, moves, currentPass);
	}

	void board::boardStack::computeAttackSquares(const player p) const noexcept
	{
		m_AttackedSquares[p] = movegen::attackedSquares(position(), p);
		m_AttackedSquaresValid[p] = true;
	}

	void board::boardStack::computeIsCheck() const noexcept
	{
		m_IsCheck = movegen::isSquareAttackedByPlayer(position(), position().kingSquare(movingPlayer()), otherPlayer());
		m_IsCheckValid = true;
	}

	void board::makeMove_Implementation(board& position, const movedata& md) noexcept
	{
		hashValue newHash{ md.oldHash() };
		hashValue newPawnstructureHash{ md.oldPawnstructureHash() };
		flags newFlags{ md.oldFlags() };
		score newMaterial{ md.oldMaterial() };
		if (md.isCapture())
		{
			position.removePiece(md.capturedPiece(), md.captureSquare(), md.otherPlayer());
			const hashValue captureHashDelta{ pieceHash(md.otherPlayer(), md.capturedPiece(), md.captureSquare()) };
			newHash ^= captureHashDelta;
			position.setDistanceToDraw(DrawingDistance);
			newMaterial -= evaluator::material(md.otherPlayer(), md.capturedPiece(), md.captureSquare());
			switch (md.capturedPiece())
			{
			case rook:
				newFlags &= ~((md.otherPlayer() == blackPlayer) ? ((md.captureSquare() == squareA8) * castlerightQueensideBlack) | ((md.captureSquare() == squareH8) * castlerightKingsideBlack) : ((md.captureSquare() == squareA1) * castlerightQueensideWhite) | ((md.captureSquare() == squareH1) * castlerightKingsideWhite));
				break;
			case pawn:
				newPawnstructureHash ^= captureHashDelta;
				break;
			case king:
				newPawnstructureHash ^= captureHashDelta;
				position.m_KingSquare[md.otherPlayer()] = square::invalid;
				break;
			}
		}
		else
			position.setDistanceToDraw(position.getDistanceToDraw() - 1);
		const hashValue fromHashDelta{ pieceHash(md.movingPlayer(), md.movingPiece(), md.fromSquare()) };
		switch (md.movingPiece())
		{
		case king:
			newFlags &= ~(castlerightQueenside(md.movingPlayer()) | castlerightKingside(md.movingPlayer()));
			position.m_KingSquare[md.movingPlayer()] = md.toSquare();
			newPawnstructureHash ^= fromHashDelta;
			break;
		case rook:
			newFlags &= ~((md.movingPlayer() == blackPlayer) ? ((md.fromSquare() == squareA8) * castlerightQueensideBlack) | ((md.fromSquare() == squareH8) * castlerightKingsideBlack) : ((md.fromSquare() == squareA1) * castlerightQueensideWhite) | ((md.fromSquare() == squareH1) * castlerightKingsideWhite));
			break;
		case pawn:
			newPawnstructureHash ^= fromHashDelta;
			break;
		}
		position.removePiece(md.movingPiece(), md.fromSquare(), md.movingPlayer());
		newMaterial -= evaluator::material(md.movingPlayer(), md.movingPiece(), md.fromSquare());
		newHash ^= fromHashDelta;
		const hashValue toHashDelta{ pieceHash(md.movingPlayer(), md.targetPiece(), md.toSquare()) };
		position.addPiece(md.targetPiece(), md.toSquare(), md.movingPlayer());
		newMaterial += evaluator::material(md.movingPlayer(), md.targetPiece(), md.toSquare());
		newHash ^= toHashDelta;
		if ((md.targetPiece() == pawn) || (md.targetPiece() == king))
			newPawnstructureHash ^= toHashDelta;
		newFlags &= ~enPassantFlagsMask;
		if (md.isDoublePush())
			newFlags |= enPassantFlags(fileOfSquare(md.toSquare()));
		else if (md.isCastling())
		{
			newHash ^= pieceHash(md.movingPlayer(), rook, md.rookFrom()) ^ pieceHash(md.movingPlayer(), rook, md.rookTo());
			position.removePiece(rook, md.rookFrom(), md.movingPlayer());
			newMaterial -= evaluator::material(md.movingPlayer(), rook, md.rookFrom());
			position.addPiece(rook, md.rookTo(), md.movingPlayer());
			newMaterial += evaluator::material(md.movingPlayer(), rook, md.rookTo());
		}
		newFlags &= playerstencil;
		newFlags |= flagsFromPlayer(md.otherPlayer());
		position.setFlags(newFlags);
		const hashValue flagsHashDelta{ flagsHash(md.oldFlags() ^ newFlags) };
		newHash ^= flagsHashDelta;
		newPawnstructureHash ^= flagsHashDelta;
		position.setHash(newHash);
		position.setPawnstructureHash(newPawnstructureHash);
		position.setMaterial(newMaterial);
	}

	void board::unmakeMove_Implementation(board& position, const movedata& md) noexcept
	{
		if (md.isCastling())
		{
			position.removePiece(rook, md.rookTo(), md.movingPlayer());
			position.addPiece(rook, md.rookFrom(), md.movingPlayer());
		}
		position.removePiece(md.targetPiece(), md.toSquare(), md.movingPlayer());
		position.addPiece(md.movingPiece(), md.fromSquare(), md.movingPlayer());
		if (md.isCapture())
			position.addPiece(md.capturedPiece(), md.captureSquare(), md.otherPlayer());
		position.setMaterial(md.oldMaterial());
		position.setDistanceToDraw(md.oldDistanceToDraw());
		position.setFlags(md.oldFlags());
		position.setHash(md.oldHash());
		position.setPawnstructureHash(md.oldPawnstructureHash());
		position.m_KingSquare[whitePlayer] = md.whiteKing();
		position.m_KingSquare[blackPlayer] = md.blackKing();
	}

	board::board() noexcept :
		pygmalion::board<8, 8, 6, 2, 12, 64, 254, pygmalion::chess::board>(),
		m_Material{ score::zero() },
		m_DistanceToDraw{ DrawingDistance },
		m_PawnstructureHash{ 0 },
		m_KingSquare{ squareE1,squareE8 }
	{
		flags fl{ flagsFromPlayer(whitePlayer) };
		for (const auto f : file::range)
		{
			addPiece(pawn, fromRankFile(rank2, f), whitePlayer);
			m_Material += evaluator::material(whitePlayer, pawn, fromRankFile(rank2, f));
			setHash(getHash() ^ pieceHash(whitePlayer, pawn, fromRankFile(rank2, f)));
			addPiece(pawn, fromRankFile(rank7, f), blackPlayer);
			m_Material += evaluator::material(blackPlayer, pawn, fromRankFile(rank7, f));
			setHash(getHash() ^ pieceHash(blackPlayer, pawn, fromRankFile(rank7, f)));
		}
		setHash(getHash() ^ flagsHash(getFlags()));
		// kings
		addPiece(king, squareE1, whitePlayer);
		m_Material += evaluator::material(whitePlayer, king, squareE1);
		setHash(getHash() ^ pieceHash(whitePlayer, king, squareE1));
		addPiece(king, squareE8, blackPlayer);
		m_Material += evaluator::material(blackPlayer, king, squareE8);
		setHash(getHash() ^ pieceHash(blackPlayer, king, squareE8));
		m_PawnstructureHash = getHash();
		// rooks
		addPiece(rook, squareA1, whitePlayer);
		m_Material += evaluator::material(whitePlayer, rook, squareA1);
		setHash(getHash() ^ pieceHash(whitePlayer, rook, squareA1));
		addPiece(rook, squareH1, whitePlayer);
		m_Material += evaluator::material(whitePlayer, rook, squareH1);
		setHash(getHash() ^ pieceHash(whitePlayer, rook, squareH1));
		addPiece(rook, squareA8, blackPlayer);
		m_Material += evaluator::material(blackPlayer, rook, squareA8);
		setHash(getHash() ^ pieceHash(blackPlayer, rook, squareA8));
		addPiece(rook, squareH8, blackPlayer);
		m_Material += evaluator::material(blackPlayer, rook, squareH8);
		setHash(getHash() ^ pieceHash(blackPlayer, rook, squareH8));
		fl |= castlerightMask;
		// knights
		addPiece(knight, squareB1, whitePlayer);
		m_Material += evaluator::material(whitePlayer, knight, squareB1);
		setHash(getHash() ^ pieceHash(whitePlayer, knight, squareB1));
		addPiece(knight, squareG1, whitePlayer);
		m_Material += evaluator::material(whitePlayer, knight, squareG1);
		setHash(getHash() ^ pieceHash(whitePlayer, knight, squareG1));
		addPiece(knight, squareB8, blackPlayer);
		m_Material += evaluator::material(blackPlayer, knight, squareB8);
		setHash(getHash() ^ pieceHash(blackPlayer, knight, squareB8));
		addPiece(knight, squareG8, blackPlayer);
		m_Material += evaluator::material(blackPlayer, knight, squareG8);
		setHash(getHash() ^ pieceHash(blackPlayer, knight, squareG8));
		// bishops
		addPiece(bishop, squareC1, whitePlayer);
		m_Material += evaluator::material(whitePlayer, bishop, squareC1);
		setHash(getHash() ^ pieceHash(whitePlayer, bishop, squareC1));
		addPiece(bishop, squareF1, whitePlayer);
		m_Material += evaluator::material(whitePlayer, bishop, squareF1);
		setHash(getHash() ^ pieceHash(whitePlayer, bishop, squareF1));
		addPiece(bishop, squareC8, blackPlayer);
		m_Material += evaluator::material(blackPlayer, bishop, squareC8);
		setHash(getHash() ^ pieceHash(blackPlayer, bishop, squareC8));
		addPiece(bishop, squareF8, blackPlayer);
		m_Material += evaluator::material(blackPlayer, bishop, squareF8);
		setHash(getHash() ^ pieceHash(blackPlayer, bishop, squareF8));
		// queens
		addPiece(queen, squareD1, whitePlayer);
		m_Material += evaluator::material(whitePlayer, queen, squareD1);
		setHash(getHash() ^ pieceHash(whitePlayer, queen, squareD1));
		addPiece(queen, squareD8, blackPlayer);
		m_Material += evaluator::material(blackPlayer, queen, squareD8);
		setHash(getHash() ^ pieceHash(blackPlayer, queen, squareD8));
		setFlags(fl);
	}

}