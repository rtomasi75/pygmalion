namespace pygmalion
{
	template<typename BOARDINFO, typename CUMULATION, size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	class descriptor_state
	{
	public:
		using boardinfoType = BOARDINFO;
		constexpr static inline const boardinfoType boardInfo{ boardinfoType() };
		constexpr static const size_t countPlayers{ boardinfoType::countPlayers };
		constexpr static const size_t countPieces{ boardinfoType::countPieces };
		constexpr static const size_t countPlayerpieces{ countPlayers * countPieces };
		constexpr static const size_t countRanks{ boardinfoType::countRanks };
		constexpr static const size_t countFiles{ boardinfoType::countFiles };
		constexpr static const size_t countSquares{ countRanks * countFiles };
		constexpr static const size_t countFlags{ boardinfoType::countFlags };
		constexpr static const size_t countHashBits{ std::min(sizeof(void*) * CHAR_BIT,boardinfoType::countHashBits) };
		using playerpieceType = pygmalion::state::playerpiece<descriptor_state>;
		using playerType = pygmalion::state::player<descriptor_state>;
		using pieceType = pygmalion::state::piece<descriptor_state>;
		using rankType = pygmalion::state::rank<descriptor_state>;
		using ranksType = pygmalion::state::ranks<descriptor_state>;
		using fileType = pygmalion::state::file<descriptor_state>;
		using filesType = pygmalion::state::files<descriptor_state>;
		using squareType = pygmalion::state::square<descriptor_state>;
		using squaresType = pygmalion::state::squares<descriptor_state>;
		using flagType = pygmalion::state::flag<descriptor_state>;
		using flagsType = pygmalion::state::flags<descriptor_state>;
		using gamestateType = pygmalion::state::gamestate<descriptor_state>;
		using signatureType = pygmalion::state::signature<descriptor_state>;
		using hashType = pygmalion::uint_t<countHashBits, false>;
		using cumulationType = CUMULATION;
		using scoreType = pygmalion::score<MANTISSA, SHIFT, MAXDIST>;
		using piecesType = pygmalion::state::pieces<descriptor_state>;
		using playersType = pygmalion::state::players<descriptor_state>;
		using playerpiecesType = pygmalion::state::playerpieces<descriptor_state>;
		using deltaType = pygmalion::state::delta<descriptor_state>;
		using objectiveType = objectivescore <scoreType, countPlayers>;
		constexpr static const size_t scoreMantissa{ MANTISSA };
		constexpr static const size_t scoreShift{ SHIFT };
		constexpr static const size_t scoreMaxDistance{ MAXDIST };
	};
}