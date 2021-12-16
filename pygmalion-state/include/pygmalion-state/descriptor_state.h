namespace pygmalion
{
	template<typename BOARDINFO, typename CUMULATION, size_t MANTISSA, size_t SHIFT, size_t MAXDIST>
	class descriptor_state
	{
	public:
		using boardinfoType = BOARDINFO;
		constexpr static inline const boardinfoType boardInfo{ boardinfoType() };
		constexpr static inline const size_t countPlayers{ boardinfoType::countPlayers };
		constexpr static inline const size_t countPieces{ boardinfoType::countPieces };
		constexpr static inline const size_t countPlayerpieces{ countPlayers * countPieces };
		constexpr static inline const size_t countRanks{ boardinfoType::countRanks };
		constexpr static inline const size_t countFiles{ boardinfoType::countFiles };
		constexpr static inline const size_t countSquares{ countRanks * countFiles };
		constexpr static inline const size_t countFlags{ boardinfoType::countFlags };
		constexpr static inline const size_t countHashBits{ std::min(sizeof(void*) * CHAR_BIT,boardinfoType::countHashBits) };
		constexpr static inline const size_t countRoyalPieces{ boardInfo.playerpieces().pieces().countRoyalPieces() };
		constexpr static inline const size_t countStructuralPieces{ boardInfo.playerpieces().pieces().countStructuralPieces() };
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
		using royalpieceType = pygmalion::state::royalpiece<descriptor_state>;
		using royalpiecesType = pygmalion::state::royalpiece<descriptor_state>;
		using structuralpieceType = pygmalion::state::structuralpiece<descriptor_state>;
		using structuralpiecesType = pygmalion::state::structuralpiece<descriptor_state>;
		constexpr static inline const size_t scoreMantissa{ MANTISSA };
		constexpr static inline const size_t scoreShift{ SHIFT };
		constexpr static inline const size_t scoreMaxDistance{ MAXDIST };
	};
}