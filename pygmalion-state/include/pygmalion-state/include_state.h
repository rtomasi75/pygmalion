
constexpr static const size_t countPlayers{ descriptorState::countPlayers };
constexpr static const size_t countPieces{ descriptorState::countPieces };
constexpr static const size_t countRanks{ descriptorState::countRanks };
constexpr static const size_t countFiles{ descriptorState::countFiles };
constexpr static const size_t countSquares{ descriptorState::countSquares };
constexpr static const size_t countFlags{ descriptorState::countFlags };
constexpr static const size_t countHashBits{ descriptorState::countHashBits };
constexpr static const size_t scoreMantissa{ descriptorState::scoreMantissa };
constexpr static const size_t scoreShift{ descriptorState::scoreShift };
constexpr static const size_t scoreMaxDistance{ descriptorState::scoreMaxDistance };
constexpr static const size_t countPlayerpieces{ descriptorState::countPlayerpieces };
constexpr static const size_t countRoyalPieces{ descriptorState::countRoyalPieces };
constexpr static const size_t countStructuralPieces{ descriptorState::countStructuralPieces };
using scoreType = typename descriptorState::scoreType;
using playerType = typename descriptorState::playerType;
using pieceType = typename descriptorState::pieceType;
using rankType = typename descriptorState::rankType;
using ranksType = typename descriptorState::ranksType;
using fileType = typename descriptorState::fileType;
using filesType = typename descriptorState::filesType;
using squareType = typename descriptorState::squareType;
using flagType = typename descriptorState::flagType;
using flagsType = typename descriptorState::flagsType;
using squaresType = typename descriptorState::squaresType;
using gamestateType = typename descriptorState::gamestateType;
using cumulationType = typename descriptorState::cumulationType;
using hashType = typename descriptorState::hashType;
using signatureType = typename descriptorState::signatureType;
using piecesType = typename descriptorState::piecesType;
using deltaType = typename descriptorState::deltaType;
using objectiveType = typename descriptorState::objectiveType;
using playersType = typename descriptorState::playersType;
using playerpieceType = typename descriptorState::playerpieceType;
using playerpiecesType = typename descriptorState::playerpiecesType;
using boardinfoType = typename descriptorState::boardinfoType;
using royalpieceType = typename descriptorState::royalpieceType;
using royalpiecesType = typename descriptorState::royalpiecesType;
using structuralpieceType = typename descriptorState::structuralpieceType;
using structuralpiecesType = typename descriptorState::structuralpiecesType;
constexpr static const boardinfoType& boardInfo{ descriptorState::boardInfo };
