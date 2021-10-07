namespace pygmalion
{
	template<size_t COUNT_PIECES, size_t COUNT_RANKS, size_t COUNT_FILES, size_t COUNT_FLAGS, size_t COUNT_HASHBITS,bool CUSTOM_HASHING_ENABLED, typename CUMULATION>
	class descriptor_state
	{
	public:
		constexpr static const bool hasCustomHashing{ CUSTOM_HASHING_ENABLED };
		constexpr static const size_t countPlayers{ 2 };
		constexpr static const size_t countPieces{ COUNT_PIECES };
		constexpr static const size_t countRanks{ COUNT_RANKS };
		constexpr static const size_t countFiles{ COUNT_FILES };
		constexpr static const size_t countSquares{ countRanks * countFiles };
		constexpr static const size_t countFlags{ COUNT_FLAGS };
		constexpr static const size_t countHashBits{ std::min(sizeof(void*) * CHAR_BIT,COUNT_HASHBITS) };
		using playerType = pygmalion::state::player<descriptor_state>;
		using pieceType = pygmalion::state::piece<descriptor_state>;
		using rankType = pygmalion::state::rank<descriptor_state>;
		using fileType = pygmalion::state::file<descriptor_state>;
		using squareType = pygmalion::state::square<descriptor_state>;
		using squaresType = pygmalion::state::squares<descriptor_state>;
		using flagType = pygmalion::state::flag<descriptor_state>;
		using flagsType = pygmalion::state::flags<descriptor_state>;
		using gamestateType = pygmalion::state::gamestate<descriptor_state>;
		using signatureType = pygmalion::state::signature<descriptor_state>;
		using hashType = pygmalion::uint_t<countHashBits, false>;
		using cumulationType = CUMULATION;
	};
}