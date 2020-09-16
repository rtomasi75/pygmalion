namespace pygmalion
{
	template<typename DESCRIPTION_STATE> class squares;

	template<size_t COUNT_PLAYERS, size_t COUNT_PIECES, size_t COUNT_RANKS, size_t COUNT_FILES, size_t COUNT_FLAGS, size_t COUNT_HASHBITS>
	class descriptor_state
	{
	public:
		constexpr static const size_t countPlayers{ COUNT_PLAYERS };
		constexpr static const size_t countPieces{ COUNT_PIECES };
		constexpr static const size_t countRanks{ COUNT_RANKS };
		constexpr static const size_t countFiles{ COUNT_FILES };
		constexpr static const size_t countSquares{ countRanks * countFiles };
		constexpr static const size_t countFlags{ COUNT_FLAGS };
		constexpr static const size_t countHashBits{ COUNT_HASHBITS };
		using playerType = pygmalion::state::player<descriptor_state>;
		using pieceType = pygmalion::state::piece<descriptor_state>;
		using rankType = pygmalion::state::rank<descriptor_state>;
		using fileType = pygmalion::state::file<descriptor_state>;
		using squareType = pygmalion::state::square<descriptor_state>;
		using squaresType = pygmalion::state::squares<descriptor_state>;
		using flagType = pygmalion::state::flag<descriptor_state>;
		using flagsType = pygmalion::state::flags<descriptor_state>;
		using gamestateType = pygmalion::state::gamestate<descriptor_state>;
	};
}