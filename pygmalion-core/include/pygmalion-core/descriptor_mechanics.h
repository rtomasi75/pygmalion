namespace pygmalion
{
	template<typename BOARD, int COUNT_MOVE_SQUARES, int COUNT_MOVE_PIECES, int COUNT_MOVE_FLAGS>
	class descriptor_mechanics :
		public base_board<typename BOARD::descriptorBoard>
	{
	public:
		constexpr static int countMoveSquares{ COUNT_MOVE_SQUARES };
		constexpr static int countMovePieces{ COUNT_MOVE_PIECES };
		constexpr static int countMoveFlags{ COUNT_MOVE_FLAGS };
		using boardType = BOARD;
		using moveType = move<typename BOARD::descriptorBoard, COUNT_MOVE_SQUARES, COUNT_MOVE_PIECES, COUNT_MOVE_FLAGS>;
		using moveflagsType = typename moveType::moveflagsType;
		using moveflagbitType = typename moveType::moveflagbitType;
	};

}