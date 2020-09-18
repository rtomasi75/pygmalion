namespace pygmalion::chess::state
{
	class descriptor_state :
		public pygmalion::descriptor_state<2, 6, 8, 8, 12, 64>
	{
	public:
		constexpr static const playerType whitePlayer{ 0 };
		constexpr static const playerType blackPlayer{ 1 };
		constexpr static const pieceType knight{ 0x0 };
		constexpr static const pieceType bishop{ 0x1 };
		constexpr static const pieceType rook{ 0x2 };
		constexpr static const pieceType queen{ 0x3 };
		constexpr static const pieceType pawn{ 0x4 };
		constexpr static const pieceType king{ 0x5 };
		constexpr static const rankType rank1{ 0 };
		constexpr static const rankType rank2{ 1 };
		constexpr static const rankType rank3{ 2 };
		constexpr static const rankType rank4{ 3 };
		constexpr static const rankType rank5{ 4 };
		constexpr static const rankType rank6{ 5 };
		constexpr static const rankType rank7{ 6 };
		constexpr static const rankType rank8{ 7 };
		constexpr static const fileType fileA{ 0 };
		constexpr static const fileType fileB{ 1 };
		constexpr static const fileType fileC{ 2 };
		constexpr static const fileType fileD{ 3 };
		constexpr static const fileType fileE{ 4 };
		constexpr static const fileType fileF{ 5 };
		constexpr static const fileType fileG{ 6 };
		constexpr static const fileType fileH{ 7 };
		constexpr static const squareType squareA1{ (rank1 & fileA) };
		constexpr static const squareType squareA2{ (rank2 & fileA) };
		constexpr static const squareType squareA3{ (rank3 & fileA) };
		constexpr static const squareType squareA4{ (rank4 & fileA) };
		constexpr static const squareType squareA5{ (rank5 & fileA) };
		constexpr static const squareType squareA6{ (rank6 & fileA) };
		constexpr static const squareType squareA7{ (rank7 & fileA) };
		constexpr static const squareType squareA8{ (rank8 & fileA) };
		constexpr static const squareType squareB1{ (rank1 & fileB) };
		constexpr static const squareType squareB2{ (rank2 & fileB) };
		constexpr static const squareType squareB3{ (rank3 & fileB) };
		constexpr static const squareType squareB4{ (rank4 & fileB) };
		constexpr static const squareType squareB5{ (rank5 & fileB) };
		constexpr static const squareType squareB6{ (rank6 & fileB) };
		constexpr static const squareType squareB7{ (rank7 & fileB) };
		constexpr static const squareType squareB8{ (rank8 & fileB) };
		constexpr static const squareType squareC1{ (rank1 & fileC) };
		constexpr static const squareType squareC2{ (rank2 & fileC) };
		constexpr static const squareType squareC3{ (rank3 & fileC) };
		constexpr static const squareType squareC4{ (rank4 & fileC) };
		constexpr static const squareType squareC5{ (rank5 & fileC) };
		constexpr static const squareType squareC6{ (rank6 & fileC) };
		constexpr static const squareType squareC7{ (rank7 & fileC) };
		constexpr static const squareType squareC8{ (rank8 & fileC) };
		constexpr static const squareType squareD1{ (rank1 & fileD) };
		constexpr static const squareType squareD2{ (rank2 & fileD) };
		constexpr static const squareType squareD3{ (rank3 & fileD) };
		constexpr static const squareType squareD4{ (rank4 & fileD) };
		constexpr static const squareType squareD5{ (rank5 & fileD) };
		constexpr static const squareType squareD6{ (rank6 & fileD) };
		constexpr static const squareType squareD7{ (rank7 & fileD) };
		constexpr static const squareType squareD8{ (rank8 & fileD) };
		constexpr static const squareType squareE1{ (rank1 & fileE) };
		constexpr static const squareType squareE2{ (rank2 & fileE) };
		constexpr static const squareType squareE3{ (rank3 & fileE) };
		constexpr static const squareType squareE4{ (rank4 & fileE) };
		constexpr static const squareType squareE5{ (rank5 & fileE) };
		constexpr static const squareType squareE6{ (rank6 & fileE) };
		constexpr static const squareType squareE7{ (rank7 & fileE) };
		constexpr static const squareType squareE8{ (rank8 & fileE) };
		constexpr static const squareType squareF1{ (rank1 & fileF) };
		constexpr static const squareType squareF2{ (rank2 & fileF) };
		constexpr static const squareType squareF3{ (rank3 & fileF) };
		constexpr static const squareType squareF4{ (rank4 & fileF) };
		constexpr static const squareType squareF5{ (rank5 & fileF) };
		constexpr static const squareType squareF6{ (rank6 & fileF) };
		constexpr static const squareType squareF7{ (rank7 & fileF) };
		constexpr static const squareType squareF8{ (rank8 & fileF) };
		constexpr static const squareType squareG1{ (rank1 & fileG) };
		constexpr static const squareType squareG2{ (rank2 & fileG) };
		constexpr static const squareType squareG3{ (rank3 & fileG) };
		constexpr static const squareType squareG4{ (rank4 & fileG) };
		constexpr static const squareType squareG5{ (rank5 & fileG) };
		constexpr static const squareType squareG6{ (rank6 & fileG) };
		constexpr static const squareType squareG7{ (rank7 & fileG) };
		constexpr static const squareType squareG8{ (rank8 & fileG) };
		constexpr static const squareType squareH1{ (rank1 & fileH) };
		constexpr static const squareType squareH2{ (rank2 & fileH) };
		constexpr static const squareType squareH3{ (rank3 & fileH) };
		constexpr static const squareType squareH4{ (rank4 & fileH) };
		constexpr static const squareType squareH5{ (rank5 & fileH) };
		constexpr static const squareType squareH6{ (rank6 & fileH) };
		constexpr static const squareType squareH7{ (rank7 & fileH) };
		constexpr static const squareType squareH8{ (rank8 & fileH) };
		constexpr static const squaresType queensideCastleInterestWhite{ squareD1 | squareC1 | squareB1 };
		constexpr static const squaresType queensideCastleInterestBlack{ squareD8 | squareC8 | squareB8 };
		constexpr static const squaresType kingsideCastleInterestWhite{ squareF1 | squareG1 };
		constexpr static const squaresType kingsideCastleInterestBlack{ squareF8 | squareG8 };
		constexpr static const squaresType queensideCastleWalkWhite{ squareE1 | squareD1 | squareC1 };
		constexpr static const squaresType queensideCastleWalkBlack{ squareE8 | squareD8 | squareC8 };
		constexpr static const squaresType kingsideCastleWalkWhite{ squareE1 | squareF1 | squareG1 };
		constexpr static const squaresType kingsideCastleWalkBlack{ squareE8 | squareF8 | squareG8 };
		constexpr static const flagType castleRightQueensideWhite{ 0 };
		constexpr static const flagType castleRightQueensideBlack{ 1 };
		constexpr static const flagType castleRightKingsideWhite{ 2 };
		constexpr static const flagType castleRightKingsideBlack{ 3 };
		constexpr static const flagType enPassantFileA{ 4 };
		constexpr static const flagType enPassantFileB{ 5 };
		constexpr static const flagType enPassantFileC{ 6 };
		constexpr static const flagType enPassantFileD{ 7 };
		constexpr static const flagType enPassantFileE{ 8 };
		constexpr static const flagType enPassantFileF{ 9 };
		constexpr static const flagType enPassantFileG{ 10 };
		constexpr static const flagType enPassantFileH{ 11 };
		constexpr static flagType enPassantFlag(const fileType file)
		{
			return 4 + file;
		}
		constexpr static const flagsType enPassantFlags{ enPassantFileA | enPassantFileB | enPassantFileC | enPassantFileD | enPassantFileE | enPassantFileF | enPassantFileG | enPassantFileH };
		constexpr static const flagsType castleFlags{ castleRightQueensideWhite | castleRightQueensideBlack | castleRightKingsideWhite | castleRightKingsideBlack };
		constexpr static const flagsType castleFlagsWhite{ castleRightQueensideWhite | castleRightKingsideWhite };
		constexpr static const flagsType castleFlagsBlack{ castleRightQueensideBlack | castleRightKingsideBlack };
	};
}