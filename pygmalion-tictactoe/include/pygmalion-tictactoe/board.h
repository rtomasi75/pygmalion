namespace pygmalion::tictactoe
{

	class board : public pygmalion::board<descriptor_board, board>
	{
	public:
		void onClear_Implementation() noexcept
		{
		}
		void onAddedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
		{
		}
		void onRemovedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
		{
		}
		void onSetFlag_Implementation(const flagType flag) noexcept
		{
		}
		void onClearedFlag_Implementation(const flagType flag) noexcept
		{
		}
	};

}