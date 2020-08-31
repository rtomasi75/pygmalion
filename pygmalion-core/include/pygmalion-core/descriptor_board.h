namespace pygmalion
{
	template<typename DESCRIPTION_BOARD> class squares;

	template<int COUNT_PLAYERS, int COUNT_PIECES, int COUNT_RANKS, int COUNT_FILES, int COUNT_FLAGS, int COUNT_HASHBITS>
	class descriptor_board
	{
	public:
		constexpr static const int countPlayers{ COUNT_PLAYERS };
		constexpr static const int countPieces{ COUNT_PIECES };
		constexpr static const int countRanks{ COUNT_RANKS };
		constexpr static const int countFiles{ COUNT_FILES };
		constexpr static const int countSquares{ countRanks * countFiles };
		constexpr static const int countFlags{ COUNT_FLAGS };
		constexpr static const int countHashBits{ COUNT_HASHBITS };
		using playerType = player<countPlayers>;
		using pieceType = piece <countPieces>;
		using rankType = rank<countRanks>;
		using fileType = file<countFiles>;
		using squareType = square<countRanks, countFiles>;
		using flagType = flag<countFlags>;
		using flagsType = bitfield<countFlags>;
		using squaresType = squares<descriptor_board>;
	};
}