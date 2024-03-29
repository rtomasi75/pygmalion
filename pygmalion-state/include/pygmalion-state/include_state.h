
constexpr static const size_t countPlayers{ descriptorState::countPlayers };
constexpr static const size_t countPieces{ descriptorState::countPieces };
constexpr static const size_t countRanks{ descriptorState::countRanks };
constexpr static const size_t countFiles{ descriptorState::countFiles };
constexpr static const size_t countSquares{ descriptorState::countSquares };
constexpr static const size_t countFlags{ descriptorState::countFlags };
constexpr static const size_t countHashBits{ descriptorState::countHashBits };
constexpr static const bool hasCustomHashing{ descriptorState::hasCustomHashing };
using playerType = typename descriptorState::playerType;
using pieceType = typename descriptorState::pieceType;
using rankType = typename descriptorState::rankType;
using fileType = typename descriptorState::fileType;
using squareType = typename descriptorState::squareType;
using flagType = typename descriptorState::flagType;
using flagsType = typename descriptorState::flagsType;
using squaresType = typename descriptorState::squaresType;
using gamestateType = typename descriptorState::gamestateType;
using cumulationType = typename descriptorState::cumulationType;
using hashType = typename descriptorState::hashType;
using signatureType = typename descriptorState::signatureType;

