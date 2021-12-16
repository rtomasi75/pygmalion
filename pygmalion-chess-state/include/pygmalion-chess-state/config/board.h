namespace pygmalion::config::chess
{
	class standardboardInfo :
		public boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>
	{
	public:
		constexpr static inline const size_t knight_Index{ 0 };
		constexpr static inline const size_t bishop_Index{ 1 };
		constexpr static inline const size_t rook_Index{ 2 };
		constexpr static inline const size_t queen_Index{ 3 };
		constexpr static inline const size_t pawn_Index{ 4 };
		constexpr static inline const size_t king_Index{ 5 };
		constexpr static inline const size_t whitePlayer_Index{ 0 };
		constexpr static inline const size_t blackPlayer_Index{ 1 };
		constexpr static inline const size_t whiteKnight_Index{ 0 };
		constexpr static inline const size_t whiteBishop_Index{ 1 };
		constexpr static inline const size_t whiteRook_Index{ 2 };
		constexpr static inline const size_t whiteQueen_Index{ 3 };
		constexpr static inline const size_t whitePawn_Index{ 4 };
		constexpr static inline const size_t whiteKing_Index{ 5 };
		constexpr static inline const size_t blackKnight_Index{ 6 };
		constexpr static inline const size_t blackBishop_Index{ 7 };
		constexpr static inline const size_t blackRook_Index{ 8 };
		constexpr static inline const size_t blackQueen_Index{ 9 };
		constexpr static inline const size_t blackPawn_Index{ 10 };
		constexpr static inline const size_t blackKing_Index{ 11 };
		constexpr static inline const size_t castleRightKingsideWhite_Index{ 0 };
		constexpr static inline const size_t castleRightQueensideWhite_Index{ 1 };
		constexpr static inline const size_t castleRightKingsideBlack_Index{ 2 };
		constexpr static inline const size_t castleRightQueensideBlack_Index{ 3 };
		constexpr static inline const size_t fileA_Index{ 0 };
		constexpr static inline const size_t fileB_Index{ 1 };
		constexpr static inline const size_t fileC_Index{ 2 };
		constexpr static inline const size_t fileD_Index{ 3 };
		constexpr static inline const size_t fileE_Index{ 4 };
		constexpr static inline const size_t fileF_Index{ 5 };
		constexpr static inline const size_t fileG_Index{ 6 };
		constexpr static inline const size_t fileH_Index{ 7 };
		constexpr static inline const size_t rank1_Index{ 0 };
		constexpr static inline const size_t rank2_Index{ 1 };
		constexpr static inline const size_t rank3_Index{ 2 };
		constexpr static inline const size_t rank4_Index{ 3 };
		constexpr static inline const size_t rank5_Index{ 4 };
		constexpr static inline const size_t rank6_Index{ 5 };
		constexpr static inline const size_t rank7_Index{ 6 };
		constexpr static inline const size_t rank8_Index{ 7 };
		constexpr static inline const size_t squareA1_Index{ 0 };
		constexpr static inline const size_t squareB1_Index{ 1 };
		constexpr static inline const size_t squareC1_Index{ 2 };
		constexpr static inline const size_t squareD1_Index{ 3 };
		constexpr static inline const size_t squareE1_Index{ 4 };
		constexpr static inline const size_t squareF1_Index{ 5 };
		constexpr static inline const size_t squareG1_Index{ 6 };
		constexpr static inline const size_t squareH1_Index{ 7 };
		constexpr static inline const size_t squareA2_Index{ 8 + 0 };
		constexpr static inline const size_t squareB2_Index{ 8 + 1 };
		constexpr static inline const size_t squareC2_Index{ 8 + 2 };
		constexpr static inline const size_t squareD2_Index{ 8 + 3 };
		constexpr static inline const size_t squareE2_Index{ 8 + 4 };
		constexpr static inline const size_t squareF2_Index{ 8 + 5 };
		constexpr static inline const size_t squareG2_Index{ 8 + 6 };
		constexpr static inline const size_t squareH2_Index{ 8 + 7 };
		constexpr static inline const size_t squareA3_Index{ 2 * 8 + 0 };
		constexpr static inline const size_t squareB3_Index{ 2 * 8 + 1 };
		constexpr static inline const size_t squareC3_Index{ 2 * 8 + 2 };
		constexpr static inline const size_t squareD3_Index{ 2 * 8 + 3 };
		constexpr static inline const size_t squareE3_Index{ 2 * 8 + 4 };
		constexpr static inline const size_t squareF3_Index{ 2 * 8 + 5 };
		constexpr static inline const size_t squareG3_Index{ 2 * 8 + 6 };
		constexpr static inline const size_t squareH3_Index{ 2 * 8 + 7 };
		constexpr static inline const size_t squareA4_Index{ 3 * 8 + 0 };
		constexpr static inline const size_t squareB4_Index{ 3 * 8 + 1 };
		constexpr static inline const size_t squareC4_Index{ 3 * 8 + 2 };
		constexpr static inline const size_t squareD4_Index{ 3 * 8 + 3 };
		constexpr static inline const size_t squareE4_Index{ 3 * 8 + 4 };
		constexpr static inline const size_t squareF4_Index{ 3 * 8 + 5 };
		constexpr static inline const size_t squareG4_Index{ 3 * 8 + 6 };
		constexpr static inline const size_t squareH4_Index{ 3 * 8 + 7 };
		constexpr static inline const size_t squareA5_Index{ 4 * 8 + 0 };
		constexpr static inline const size_t squareB5_Index{ 4 * 8 + 1 };
		constexpr static inline const size_t squareC5_Index{ 4 * 8 + 2 };
		constexpr static inline const size_t squareD5_Index{ 4 * 8 + 3 };
		constexpr static inline const size_t squareE5_Index{ 4 * 8 + 4 };
		constexpr static inline const size_t squareF5_Index{ 4 * 8 + 5 };
		constexpr static inline const size_t squareG5_Index{ 4 * 8 + 6 };
		constexpr static inline const size_t squareH5_Index{ 4 * 8 + 7 };
		constexpr static inline const size_t squareA6_Index{ 5 * 8 + 0 };
		constexpr static inline const size_t squareB6_Index{ 5 * 8 + 1 };
		constexpr static inline const size_t squareC6_Index{ 5 * 8 + 2 };
		constexpr static inline const size_t squareD6_Index{ 5 * 8 + 3 };
		constexpr static inline const size_t squareE6_Index{ 5 * 8 + 4 };
		constexpr static inline const size_t squareF6_Index{ 5 * 8 + 5 };
		constexpr static inline const size_t squareG6_Index{ 5 * 8 + 6 };
		constexpr static inline const size_t squareH6_Index{ 5 * 8 + 7 };
		constexpr static inline const size_t squareA7_Index{ 6 * 8 + 0 };
		constexpr static inline const size_t squareB7_Index{ 6 * 8 + 1 };
		constexpr static inline const size_t squareC7_Index{ 6 * 8 + 2 };
		constexpr static inline const size_t squareD7_Index{ 6 * 8 + 3 };
		constexpr static inline const size_t squareE7_Index{ 6 * 8 + 4 };
		constexpr static inline const size_t squareF7_Index{ 6 * 8 + 5 };
		constexpr static inline const size_t squareG7_Index{ 6 * 8 + 6 };
		constexpr static inline const size_t squareH7_Index{ 6 * 8 + 7 };
		constexpr static inline const size_t squareA8_Index{ 7 * 8 + 0 };
		constexpr static inline const size_t squareB8_Index{ 7 * 8 + 1 };
		constexpr static inline const size_t squareC8_Index{ 7 * 8 + 2 };
		constexpr static inline const size_t squareD8_Index{ 7 * 8 + 3 };
		constexpr static inline const size_t squareE8_Index{ 7 * 8 + 4 };
		constexpr static inline const size_t squareF8_Index{ 7 * 8 + 5 };
		constexpr static inline const size_t squareG8_Index{ 7 * 8 + 6 };
		constexpr static inline const size_t squareH8_Index{ 7 * 8 + 7 };
	private:
		static double materialKingSquare(const size_t fileIndex, const size_t rankIndex, const size_t playerIndex) noexcept
		{
			constexpr const double PST_King[64]
			{
				-0.32, -0.064, -0.064, -0.064, -0.064, -0.064, -0.064, -0.32,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.064, 0.32, 0.32, 0.32, 0.32, 0.32, 0.32, -0.064,
				-0.32, -0.064, -0.064, -0.064, -0.064, -0.064, -0.064, -0.32,
			};
			if (playerIndex == whitePlayer_Index)
				return PST_King[rankIndex * countFiles + fileIndex];
			else
				return PST_King[(countRanks - 1 - rankIndex) * countFiles + fileIndex];
		}
		static double materialBishopSquare(const size_t fileIndex, const size_t rankIndex, const size_t playerIndex) noexcept
		{
			constexpr const double PST_Bishop[64]
			{
				-0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384,
				-0.384, -0.128, -0.128, -0.128, -0.128, -0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.384, 0.384, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.384, 0.384, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.384,
				-0.384, -0.128, -0.128, -0.128, -0.128, -0.128, -0.128, -0.384,
				-0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384,
			};
			if (playerIndex == whitePlayer_Index)
				return PST_Bishop[rankIndex * countFiles + fileIndex];
			else
				return PST_Bishop[(countRanks - 1 - rankIndex) * countFiles + fileIndex];
		}
		static double materialRookSquare(const size_t fileIndex, const size_t rankIndex, const size_t playerIndex) noexcept
		{
			constexpr const double PST_Rook[64]
			{
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
			};
			if (playerIndex == whitePlayer_Index)
				return PST_Rook[rankIndex * countFiles + fileIndex];
			else
				return PST_Rook[(countRanks - 1 - rankIndex) * countFiles + fileIndex];
		}
		static double materialQueenSquare(const size_t fileIndex, const size_t rankIndex, const size_t playerIndex) noexcept
		{
			constexpr const double PST_Queen[64]
			{
				-0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384,
				-0.384, -0.128, -0.128, -0.128, -0.128, -0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.384, 0.384, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.384, 0.384, 0.128, -0.128, -0.384,
				-0.384, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.384,
				-0.384, -0.128, -0.128, -0.128, -0.128, -0.128, -0.128, -0.384,
				-0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384, -0.384,
			};
			if (playerIndex == whitePlayer_Index)
				return PST_Queen[rankIndex * countFiles + fileIndex];
			else
				return PST_Queen[(countRanks - 1 - rankIndex) * countFiles + fileIndex];
		}
		static double materialKnightSquare(const size_t fileIndex, const size_t rankIndex, const size_t playerIndex) noexcept
		{
			constexpr const double PST_Knight[64]
			{
				-0.384, -0.256, -0.128, -0.128, -0.128, -0.128, -0.256, -0.384,
				-0.256, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.256,
				-0.128, 0.128, 0.384, 0.384, 0.384, 0.384, 0.128, -0.128,
				-0.128, 0.128, 0.384, 0.384, 0.384, 0.384, 0.128, -0.128,
				-0.128, 0.128, 0.384, 0.384, 0.384, 0.384, 0.128, -0.128,
				-0.128, 0.128, 0.384, 0.384, 0.384, 0.384, 0.128, -0.128,
				-0.256, -0.128, 0.128, 0.128, 0.128, 0.128, -0.128, -0.256,
				-0.384, -0.256, -0.128, -0.128, -0.128, -0.128, -0.256, -0.384,
			};
			if (playerIndex == whitePlayer_Index)
				return PST_Knight[rankIndex * countFiles + fileIndex];
			else
				return PST_Knight[(countRanks - 1 - rankIndex) * countFiles + fileIndex];
		}
		static double materialPawnSquare(const size_t fileIndex, const size_t rankIndex, const size_t playerIndex) noexcept
		{
			constexpr const double PST_Pawn[64]
			{
				0, 0, 0, 0, 0, 0, 0, 0,
				-0.288, -0.224, -0.224, -0.224, -0.224, -0.224, -0.224, -0.288,
				-0.224, -0.16, -0.16, -0.16, -0.16, -0.16, -0.16, -0.224,
				-0.096, -0.032, -0.032, -0.032, -0.032, -0.032, -0.032, -0.096,
				0.032, 0.096, 0.096, 0.096, 0.096, 0.096, 0.096, 0.032,
				0.16, 0.224, 0.224, 0.224, 0.224, 0.224, 0.224, 0.16,
				0.224, 0.288, 0.288, 0.288, 0.288, 0.288, 0.288, 0.224,
				0, 0, 0, 0, 0, 0, 0, 0,
			};
			if (playerIndex == whitePlayer_Index)
				return PST_Pawn[rankIndex * countFiles + fileIndex];
			else
				return PST_Pawn[(countRanks - 1 - rankIndex) * countFiles + fileIndex];
		}
	public:
		virtual bool initialFlag(const size_t flagIndex) const noexcept override
		{
			switch (flagIndex)
			{
			case castleRightKingsideBlack_Index:
				return true;
			case castleRightKingsideWhite_Index:
				return true;
			case castleRightQueensideBlack_Index:
				return true;
			case castleRightQueensideWhite_Index:
				return true;
			default:
				PYGMALION_UNREACHABLE;
				return false;
			}
		}
		virtual size_t initialPlayerIndex() const noexcept override
		{
			return whitePlayer_Index;
		}
		virtual bool initialEnPassant(size_t& victimSquareIndex, list<size_t, countSquares>& targetSquareIndices) const noexcept override
		{
			return false;
		}
		virtual bool initialPlayerPieceOnSquare(const size_t squareIndex, size_t& playerpieceIndex) const noexcept override
		{
			switch (squareIndex)
			{
			case squareA2_Index:
			case squareB2_Index:
			case squareC2_Index:
			case squareD2_Index:
			case squareE2_Index:
			case squareF2_Index:
			case squareG2_Index:
			case squareH2_Index:
				playerpieceIndex = whitePawn_Index;
				return true;
			case squareA7_Index:
			case squareB7_Index:
			case squareC7_Index:
			case squareD7_Index:
			case squareE7_Index:
			case squareF7_Index:
			case squareG7_Index:
			case squareH7_Index:
				playerpieceIndex = blackPawn_Index;
				return true;
			case squareD1_Index:
				playerpieceIndex = whiteQueen_Index;
				return true;
			case squareD8_Index:
				playerpieceIndex = blackQueen_Index;
				return true;
			case squareE1_Index:
				playerpieceIndex = whiteKing_Index;
				return true;
			case squareE8_Index:
				playerpieceIndex = blackKing_Index;
				return true;
			case squareA1_Index:
				playerpieceIndex = whiteRook_Index;
				return true;
			case squareH1_Index:
				playerpieceIndex = whiteRook_Index;
				return true;
			case squareA8_Index:
				playerpieceIndex = blackRook_Index;
				return true;
			case squareH8_Index:
				playerpieceIndex = blackRook_Index;
				return true;
			case squareB1_Index:
				playerpieceIndex = whiteKnight_Index;
				return true;
			case squareG1_Index:
				playerpieceIndex = whiteKnight_Index;
				return true;
			case squareB8_Index:
				playerpieceIndex = blackKnight_Index;
				return true;
			case squareG8_Index:
				playerpieceIndex = blackKnight_Index;
				return true;
			case squareC1_Index:
				playerpieceIndex = whiteBishop_Index;
				return true;
			case squareF1_Index:
				playerpieceIndex = whiteBishop_Index;
				return true;
			case squareC8_Index:
				playerpieceIndex = blackBishop_Index;
				return true;
			case squareF8_Index:
				playerpieceIndex = blackBishop_Index;
				return true;
			}
			return false;
		}
		virtual double materialPiece(const size_t pieceIndex) const noexcept override
		{
			switch (pieceIndex)
			{
			default:
				PYGMALION_UNREACHABLE;
				return 0.0;
			case knight_Index:
				return 3.0;
			case bishop_Index:
				return 3.3;
			case rook_Index:
				return 5.5;
			case queen_Index:
				return 10.0;
			case pawn_Index:
				return 1.0;
			case king_Index:
				return 0.0;
			}
		}
		virtual double materialPieceSquare(const size_t playerIndex, const size_t pieceIndex, const size_t fileIndex, const size_t rankIndex) const noexcept override
		{
			switch (pieceIndex)
			{
			default:
				PYGMALION_UNREACHABLE;
				return 0.0;
			case knight_Index:
				return materialKnightSquare(fileIndex, rankIndex, playerIndex);
			case bishop_Index:
				return materialBishopSquare(fileIndex, rankIndex, playerIndex);
			case rook_Index:
				return materialRookSquare(fileIndex, rankIndex, playerIndex);
			case queen_Index:
				return materialQueenSquare(fileIndex, rankIndex, playerIndex);
			case pawn_Index:
				return materialPawnSquare(fileIndex, rankIndex, playerIndex);
			case king_Index:
				return materialKingSquare(fileIndex, rankIndex, playerIndex);
			}
		}
		constexpr standardboardInfo() noexcept :
			boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>(
				32,
				standardplayersInfo(),
				standardpiecesInfo(),
				standardfilesInfo(),
				standardranksInfo(),
				standardflagsInfo(),
				{
					UINT64_C(0xF8D626AAAF278509),
					UINT64_C(0x0000000000000000)
				},
				arrayhelper::generate<boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countSquares, std::uint64_t>(
					[](const size_t squareIndex)
					{
						constexpr const std::uint64_t epHash[boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countFiles]
						{
							UINT64_C(0x70CC73D90BC26E24),
							UINT64_C(0xE21A6B35DF0C3AD7),
							UINT64_C(0x003A93D8B2806962),
							UINT64_C(0x1C99DED33CB890A1),
							UINT64_C(0xCF3145DE0ADD4289),
							UINT64_C(0xD0E4427A5514FB72),
							UINT64_C(0x77C621CC9FB3A483),
							UINT64_C(0x67A34DAC4356550B)
						};
						const size_t fileIndex{ squareIndex % boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countFiles };
						return epHash[fileIndex];
					}
					),
					{
						UINT64_C(0x31D71DCE64B2C310),
						UINT64_C(0xF165B587DF898190),
						UINT64_C(0xA57E6339DD2CF3A0),
						UINT64_C(0x1EF6E6DBB1961EC9)
					},
						arrayhelper::generate<boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countPlayers, std::array<std::array<std::uint64_t, boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countSquares>, boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countPieces>>(
							[](const size_t player)
							{
								return arrayhelper::generate<boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countPieces, std::array<std::uint64_t, boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countSquares>>(
									[player](const size_t piece)
									{
										return arrayhelper::generate<boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countSquares, std::uint64_t>(
											[player, piece](const size_t square)
											{
												constexpr const std::array<std::uint64_t, boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countSquares* boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countPieces* boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countPlayers> pieceHash
												{
													UINT64_C(0x9D39247E33776D41), UINT64_C(0x2AF7398005AAA5C7), UINT64_C(0x44DB015024623547), UINT64_C(0x9C15F73E62A76AE2),
													UINT64_C(0x75834465489C0C89), UINT64_C(0x3290AC3A203001BF), UINT64_C(0x0FBBAD1F61042279), UINT64_C(0xE83A908FF2FB60CA),
													UINT64_C(0x0D7E765D58755C10), UINT64_C(0x1A083822CEAFE02D), UINT64_C(0x9605D5F0E25EC3B0), UINT64_C(0xD021FF5CD13A2ED5),
													UINT64_C(0x40BDF15D4A672E32), UINT64_C(0x011355146FD56395), UINT64_C(0x5DB4832046F3D9E5), UINT64_C(0x239F8B2D7FF719CC),
													UINT64_C(0x05D1A1AE85B49AA1), UINT64_C(0x679F848F6E8FC971), UINT64_C(0x7449BBFF801FED0B), UINT64_C(0x7D11CDB1C3B7ADF0),
													UINT64_C(0x82C7709E781EB7CC), UINT64_C(0xF3218F1C9510786C), UINT64_C(0x331478F3AF51BBE6), UINT64_C(0x4BB38DE5E7219443),
													UINT64_C(0xAA649C6EBCFD50FC), UINT64_C(0x8DBD98A352AFD40B), UINT64_C(0x87D2074B81D79217), UINT64_C(0x19F3C751D3E92AE1),
													UINT64_C(0xB4AB30F062B19ABF), UINT64_C(0x7B0500AC42047AC4), UINT64_C(0xC9452CA81A09D85D), UINT64_C(0x24AA6C514DA27500),
													UINT64_C(0x4C9F34427501B447), UINT64_C(0x14A68FD73C910841), UINT64_C(0xA71B9B83461CBD93), UINT64_C(0x03488B95B0F1850F),
													UINT64_C(0x637B2B34FF93C040), UINT64_C(0x09D1BC9A3DD90A94), UINT64_C(0x3575668334A1DD3B), UINT64_C(0x735E2B97A4C45A23),
													UINT64_C(0x18727070F1BD400B), UINT64_C(0x1FCBACD259BF02E7), UINT64_C(0xD310A7C2CE9B6555), UINT64_C(0xBF983FE0FE5D8244),
													UINT64_C(0x9F74D14F7454A824), UINT64_C(0x51EBDC4AB9BA3035), UINT64_C(0x5C82C505DB9AB0FA), UINT64_C(0xFCF7FE8A3430B241),
													UINT64_C(0x3253A729B9BA3DDE), UINT64_C(0x8C74C368081B3075), UINT64_C(0xB9BC6C87167C33E7), UINT64_C(0x7EF48F2B83024E20),
													UINT64_C(0x11D505D4C351BD7F), UINT64_C(0x6568FCA92C76A243), UINT64_C(0x4DE0B0F40F32A7B8), UINT64_C(0x96D693460CC37E5D),
													UINT64_C(0x42E240CB63689F2F), UINT64_C(0x6D2BDCDAE2919661), UINT64_C(0x42880B0236E4D951), UINT64_C(0x5F0F4A5898171BB6),
													UINT64_C(0x39F890F579F92F88), UINT64_C(0x93C5B5F47356388B), UINT64_C(0x63DC359D8D231B78), UINT64_C(0xEC16CA8AEA98AD76),
													UINT64_C(0x5355F900C2A82DC7), UINT64_C(0x07FB9F855A997142), UINT64_C(0x5093417AA8A7ED5E), UINT64_C(0x7BCBC38DA25A7F3C),
													UINT64_C(0x19FC8A768CF4B6D4), UINT64_C(0x637A7780DECFC0D9), UINT64_C(0x8249A47AEE0E41F7), UINT64_C(0x79AD695501E7D1E8),
													UINT64_C(0x14ACBAF4777D5776), UINT64_C(0xF145B6BECCDEA195), UINT64_C(0xDABF2AC8201752FC), UINT64_C(0x24C3C94DF9C8D3F6),
													UINT64_C(0xBB6E2924F03912EA), UINT64_C(0x0CE26C0B95C980D9), UINT64_C(0xA49CD132BFBF7CC4), UINT64_C(0xE99D662AF4243939),
													UINT64_C(0x27E6AD7891165C3F), UINT64_C(0x8535F040B9744FF1), UINT64_C(0x54B3F4FA5F40D873), UINT64_C(0x72B12C32127FED2B),
													UINT64_C(0xEE954D3C7B411F47), UINT64_C(0x9A85AC909A24EAA1), UINT64_C(0x70AC4CD9F04F21F5), UINT64_C(0xF9B89D3E99A075C2),
													UINT64_C(0x87B3E2B2B5C907B1), UINT64_C(0xA366E5B8C54F48B8), UINT64_C(0xAE4A9346CC3F7CF2), UINT64_C(0x1920C04D47267BBD),
													UINT64_C(0x87BF02C6B49E2AE9), UINT64_C(0x092237AC237F3859), UINT64_C(0xFF07F64EF8ED14D0), UINT64_C(0x8DE8DCA9F03CC54E),
													UINT64_C(0x9C1633264DB49C89), UINT64_C(0xB3F22C3D0B0B38ED), UINT64_C(0x390E5FB44D01144B), UINT64_C(0x5BFEA5B4712768E9),
													UINT64_C(0x1E1032911FA78984), UINT64_C(0x9A74ACB964E78CB3), UINT64_C(0x4F80F7A035DAFB04), UINT64_C(0x6304D09A0B3738C4),
													UINT64_C(0x2171E64683023A08), UINT64_C(0x5B9B63EB9CEFF80C), UINT64_C(0x506AACF489889342), UINT64_C(0x1881AFC9A3A701D6),
													UINT64_C(0x6503080440750644), UINT64_C(0xDFD395339CDBF4A7), UINT64_C(0xEF927DBCF00C20F2), UINT64_C(0x7B32F7D1E03680EC),
													UINT64_C(0xB9FD7620E7316243), UINT64_C(0x05A7E8A57DB91B77), UINT64_C(0xB5889C6E15630A75), UINT64_C(0x4A750A09CE9573F7),
													UINT64_C(0xCF464CEC899A2F8A), UINT64_C(0xF538639CE705B824), UINT64_C(0x3C79A0FF5580EF7F), UINT64_C(0xEDE6C87F8477609D),
													UINT64_C(0x799E81F05BC93F31), UINT64_C(0x86536B8CF3428A8C), UINT64_C(0x97D7374C60087B73), UINT64_C(0xA246637CFF328532),
													UINT64_C(0x043FCAE60CC0EBA0), UINT64_C(0x920E449535DD359E), UINT64_C(0x70EB093B15B290CC), UINT64_C(0x73A1921916591CBD),
													UINT64_C(0x56436C9FE1A1AA8D), UINT64_C(0xEFAC4B70633B8F81), UINT64_C(0xBB215798D45DF7AF), UINT64_C(0x45F20042F24F1768),
													UINT64_C(0x930F80F4E8EB7462), UINT64_C(0xFF6712FFCFD75EA1), UINT64_C(0xAE623FD67468AA70), UINT64_C(0xDD2C5BC84BC8D8FC),
													UINT64_C(0x7EED120D54CF2DD9), UINT64_C(0x22FE545401165F1C), UINT64_C(0xC91800E98FB99929), UINT64_C(0x808BD68E6AC10365),
													UINT64_C(0xDEC468145B7605F6), UINT64_C(0x1BEDE3A3AEF53302), UINT64_C(0x43539603D6C55602), UINT64_C(0xAA969B5C691CCB7A),
													UINT64_C(0xA87832D392EFEE56), UINT64_C(0x65942C7B3C7E11AE), UINT64_C(0xDED2D633CAD004F6), UINT64_C(0x21F08570F420E565),
													UINT64_C(0xB415938D7DA94E3C), UINT64_C(0x91B859E59ECB6350), UINT64_C(0x10CFF333E0ED804A), UINT64_C(0x28AED140BE0BB7DD),
													UINT64_C(0xC5CC1D89724FA456), UINT64_C(0x5648F680F11A2741), UINT64_C(0x2D255069F0B7DAB3), UINT64_C(0x9BC5A38EF729ABD4),
													UINT64_C(0xEF2F054308F6A2BC), UINT64_C(0xAF2042F5CC5C2858), UINT64_C(0x480412BAB7F5BE2A), UINT64_C(0xAEF3AF4A563DFE43),
													UINT64_C(0x19AFE59AE451497F), UINT64_C(0x52593803DFF1E840), UINT64_C(0xF4F076E65F2CE6F0), UINT64_C(0x11379625747D5AF3),
													UINT64_C(0xBCE5D2248682C115), UINT64_C(0x9DA4243DE836994F), UINT64_C(0x066F70B33FE09017), UINT64_C(0x4DC4DE189B671A1C),
													UINT64_C(0x51039AB7712457C3), UINT64_C(0xC07A3F80C31FB4B4), UINT64_C(0xB46EE9C5E64A6E7C), UINT64_C(0xB3819A42ABE61C87),
													UINT64_C(0x21A007933A522A20), UINT64_C(0x2DF16F761598AA4F), UINT64_C(0x763C4A1371B368FD), UINT64_C(0xF793C46702E086A0),
													UINT64_C(0xD7288E012AEB8D31), UINT64_C(0xDE336A2A4BC1C44B), UINT64_C(0x0BF692B38D079F23), UINT64_C(0x2C604A7A177326B3),
													UINT64_C(0x4850E73E03EB6064), UINT64_C(0xCFC447F1E53C8E1B), UINT64_C(0xB05CA3F564268D99), UINT64_C(0x9AE182C8BC9474E8),
													UINT64_C(0xA4FC4BD4FC5558CA), UINT64_C(0xE755178D58FC4E76), UINT64_C(0x69B97DB1A4C03DFE), UINT64_C(0xF9B5B7C4ACC67C96),
													UINT64_C(0xFC6A82D64B8655FB), UINT64_C(0x9C684CB6C4D24417), UINT64_C(0x8EC97D2917456ED0), UINT64_C(0x6703DF9D2924E97E),
													UINT64_C(0xC547F57E42A7444E), UINT64_C(0x78E37644E7CAD29E), UINT64_C(0xFE9A44E9362F05FA), UINT64_C(0x08BD35CC38336615),
													UINT64_C(0x9315E5EB3A129ACE), UINT64_C(0x94061B871E04DF75), UINT64_C(0xDF1D9F9D784BA010), UINT64_C(0x3BBA57B68871B59D),
													UINT64_C(0xD2B7ADEEDED1F73F), UINT64_C(0xF7A255D83BC373F8), UINT64_C(0xD7F4F2448C0CEB81), UINT64_C(0xD95BE88CD210FFA7),
													UINT64_C(0x336F52F8FF4728E7), UINT64_C(0xA74049DAC312AC71), UINT64_C(0xA2F61BB6E437FDB5), UINT64_C(0x4F2A5CB07F6A35B3),
													UINT64_C(0x87D380BDA5BF7859), UINT64_C(0x16B9F7E06C453A21), UINT64_C(0x7BA2484C8A0FD54E), UINT64_C(0xF3A678CAD9A2E38C),
													UINT64_C(0x39B0BF7DDE437BA2), UINT64_C(0xFCAF55C1BF8A4424), UINT64_C(0x18FCF680573FA594), UINT64_C(0x4C0563B89F495AC3),
													UINT64_C(0x40E087931A00930D), UINT64_C(0x8CFFA9412EB642C1), UINT64_C(0x68CA39053261169F), UINT64_C(0x7A1EE967D27579E2),
													UINT64_C(0x9D1D60E5076F5B6F), UINT64_C(0x3810E399B6F65BA2), UINT64_C(0x32095B6D4AB5F9B1), UINT64_C(0x35CAB62109DD038A),
													UINT64_C(0xA90B24499FCFAFB1), UINT64_C(0x77A225A07CC2C6BD), UINT64_C(0x513E5E634C70E331), UINT64_C(0x4361C0CA3F692F12),
													UINT64_C(0xD941ACA44B20A45B), UINT64_C(0x528F7C8602C5807B), UINT64_C(0x52AB92BEB9613989), UINT64_C(0x9D1DFA2EFC557F73),
													UINT64_C(0x722FF175F572C348), UINT64_C(0x1D1260A51107FE97), UINT64_C(0x7A249A57EC0C9BA2), UINT64_C(0x04208FE9E8F7F2D6),
													UINT64_C(0x5A110C6058B920A0), UINT64_C(0x0CD9A497658A5698), UINT64_C(0x56FD23C8F9715A4C), UINT64_C(0x284C847B9D887AAE),
													UINT64_C(0x04FEABFBBDB619CB), UINT64_C(0x742E1E651C60BA83), UINT64_C(0x9A9632E65904AD3C), UINT64_C(0x881B82A13B51B9E2),
													UINT64_C(0x506E6744CD974924), UINT64_C(0xB0183DB56FFC6A79), UINT64_C(0x0ED9B915C66ED37E), UINT64_C(0x5E11E86D5873D484),
													UINT64_C(0xF678647E3519AC6E), UINT64_C(0x1B85D488D0F20CC5), UINT64_C(0xDAB9FE6525D89021), UINT64_C(0x0D151D86ADB73615),
													UINT64_C(0xA865A54EDCC0F019), UINT64_C(0x93C42566AEF98FFB), UINT64_C(0x99E7AFEABE000731), UINT64_C(0x48CBFF086DDF285A),
													UINT64_C(0x7F9B6AF1EBF78BAF), UINT64_C(0x58627E1A149BBA21), UINT64_C(0x2CD16E2ABD791E33), UINT64_C(0xD363EFF5F0977996),
													UINT64_C(0x0CE2A38C344A6EED), UINT64_C(0x1A804AADB9CFA741), UINT64_C(0x907F30421D78C5DE), UINT64_C(0x501F65EDB3034D07),
													UINT64_C(0x37624AE5A48FA6E9), UINT64_C(0x957BAF61700CFF4E), UINT64_C(0x3A6C27934E31188A), UINT64_C(0xD49503536ABCA345),
													UINT64_C(0x088E049589C432E0), UINT64_C(0xF943AEE7FEBF21B8), UINT64_C(0x6C3B8E3E336139D3), UINT64_C(0x364F6FFA464EE52E),
													UINT64_C(0xD60F6DCEDC314222), UINT64_C(0x56963B0DCA418FC0), UINT64_C(0x16F50EDF91E513AF), UINT64_C(0xEF1955914B609F93),
													UINT64_C(0x565601C0364E3228), UINT64_C(0xECB53939887E8175), UINT64_C(0xBAC7A9A18531294B), UINT64_C(0xB344C470397BBA52),
													UINT64_C(0x65D34954DAF3CEBD), UINT64_C(0xB4B81B3FA97511E2), UINT64_C(0xB422061193D6F6A7), UINT64_C(0x071582401C38434D),
													UINT64_C(0x7A13F18BBEDC4FF5), UINT64_C(0xBC4097B116C524D2), UINT64_C(0x59B97885E2F2EA28), UINT64_C(0x99170A5DC3115544),
													UINT64_C(0x6F423357E7C6A9F9), UINT64_C(0x325928EE6E6F8794), UINT64_C(0xD0E4366228B03343), UINT64_C(0x565C31F7DE89EA27),
													UINT64_C(0x30F5611484119414), UINT64_C(0xD873DB391292ED4F), UINT64_C(0x7BD94E1D8E17DEBC), UINT64_C(0xC7D9F16864A76E94),
													UINT64_C(0x947AE053EE56E63C), UINT64_C(0xC8C93882F9475F5F), UINT64_C(0x3A9BF55BA91F81CA), UINT64_C(0xD9A11FBB3D9808E4),
													UINT64_C(0x0FD22063EDC29FCA), UINT64_C(0xB3F256D8ACA0B0B9), UINT64_C(0xB03031A8B4516E84), UINT64_C(0x35DD37D5871448AF),
													UINT64_C(0xE9F6082B05542E4E), UINT64_C(0xEBFAFA33D7254B59), UINT64_C(0x9255ABB50D532280), UINT64_C(0xB9AB4CE57F2D34F3),
													UINT64_C(0x693501D628297551), UINT64_C(0xC62C58F97DD949BF), UINT64_C(0xCD454F8F19C5126A), UINT64_C(0xBBE83F4ECC2BDECB),
													UINT64_C(0xDC842B7E2819E230), UINT64_C(0xBA89142E007503B8), UINT64_C(0xA3BC941D0A5061CB), UINT64_C(0xE9F6760E32CD8021),
													UINT64_C(0x09C7E552BC76492F), UINT64_C(0x852F54934DA55CC9), UINT64_C(0x8107FCCF064FCF56), UINT64_C(0x098954D51FFF6580),
													UINT64_C(0x23B70EDB1955C4BF), UINT64_C(0xC330DE426430F69D), UINT64_C(0x4715ED43E8A45C0A), UINT64_C(0xA8D7E4DAB780A08D),
													UINT64_C(0x0572B974F03CE0BB), UINT64_C(0xB57D2E985E1419C7), UINT64_C(0xE8D9ECBE2CF3D73F), UINT64_C(0x2FE4B17170E59750),
													UINT64_C(0x11317BA87905E790), UINT64_C(0x7FBF21EC8A1F45EC), UINT64_C(0x1725CABFCB045B00), UINT64_C(0x964E915CD5E2B207),
													UINT64_C(0x3E2B8BCBF016D66D), UINT64_C(0xBE7444E39328A0AC), UINT64_C(0xF85B2B4FBCDE44B7), UINT64_C(0x49353FEA39BA63B1),
													UINT64_C(0x1DD01AAFCD53486A), UINT64_C(0x1FCA8A92FD719F85), UINT64_C(0xFC7C95D827357AFA), UINT64_C(0x18A6A990C8B35EBD),
													UINT64_C(0xCCCB7005C6B9C28D), UINT64_C(0x3BDBB92C43B17F26), UINT64_C(0xAA70B5B4F89695A2), UINT64_C(0xE94C39A54A98307F),
													UINT64_C(0xB7A0B174CFF6F36E), UINT64_C(0xD4DBA84729AF48AD), UINT64_C(0x2E18BC1AD9704A68), UINT64_C(0x2DE0966DAF2F8B1C),
													UINT64_C(0xB9C11D5B1E43A07E), UINT64_C(0x64972D68DEE33360), UINT64_C(0x94628D38D0C20584), UINT64_C(0xDBC0D2B6AB90A559),
													UINT64_C(0xD2733C4335C6A72F), UINT64_C(0x7E75D99D94A70F4D), UINT64_C(0x6CED1983376FA72B), UINT64_C(0x97FCAACBF030BC24),
													UINT64_C(0x7B77497B32503B12), UINT64_C(0x8547EDDFB81CCB94), UINT64_C(0x79999CDFF70902CB), UINT64_C(0xCFFE1939438E9B24),
													UINT64_C(0x829626E3892D95D7), UINT64_C(0x92FAE24291F2B3F1), UINT64_C(0x63E22C147B9C3403), UINT64_C(0xC678B6D860284A1C),
													UINT64_C(0x5873888850659AE7), UINT64_C(0x0981DCD296A8736D), UINT64_C(0x9F65789A6509A440), UINT64_C(0x9FF38FED72E9052F),
													UINT64_C(0xE479EE5B9930578C), UINT64_C(0xE7F28ECD2D49EECD), UINT64_C(0x56C074A581EA17FE), UINT64_C(0x5544F7D774B14AEF),
													UINT64_C(0x7B3F0195FC6F290F), UINT64_C(0x12153635B2C0CF57), UINT64_C(0x7F5126DBBA5E0CA7), UINT64_C(0x7A76956C3EAFB413),
													UINT64_C(0x3D5774A11D31AB39), UINT64_C(0x8A1B083821F40CB4), UINT64_C(0x7B4A38E32537DF62), UINT64_C(0x950113646D1D6E03),
													UINT64_C(0x4DA8979A0041E8A9), UINT64_C(0x3BC36E078F7515D7), UINT64_C(0x5D0A12F27AD310D1), UINT64_C(0x7F9D1A2E1EBE1327),
													UINT64_C(0xDA3A361B1C5157B1), UINT64_C(0xDCDD7D20903D0C25), UINT64_C(0x36833336D068F707), UINT64_C(0xCE68341F79893389),
													UINT64_C(0xAB9090168DD05F34), UINT64_C(0x43954B3252DC25E5), UINT64_C(0xB438C2B67F98E5E9), UINT64_C(0x10DCD78E3851A492),
													UINT64_C(0xDBC27AB5447822BF), UINT64_C(0x9B3CDB65F82CA382), UINT64_C(0xB67B7896167B4C84), UINT64_C(0xBFCED1B0048EAC50),
													UINT64_C(0xA9119B60369FFEBD), UINT64_C(0x1FFF7AC80904BF45), UINT64_C(0xAC12FB171817EEE7), UINT64_C(0xAF08DA9177DDA93D),
													UINT64_C(0x1B0CAB936E65C744), UINT64_C(0xB559EB1D04E5E932), UINT64_C(0xC37B45B3F8D6F2BA), UINT64_C(0xC3A9DC228CAAC9E9),
													UINT64_C(0xF3B8B6675A6507FF), UINT64_C(0x9FC477DE4ED681DA), UINT64_C(0x67378D8ECCEF96CB), UINT64_C(0x6DD856D94D259236),
													UINT64_C(0xA319CE15B0B4DB31), UINT64_C(0x073973751F12DD5E), UINT64_C(0x8A8E849EB32781A5), UINT64_C(0xE1925C71285279F5),
													UINT64_C(0x74C04BF1790C0EFE), UINT64_C(0x4DDA48153C94938A), UINT64_C(0x9D266D6A1CC0542C), UINT64_C(0x7440FB816508C4FE),
													UINT64_C(0x13328503DF48229F), UINT64_C(0xD6BF7BAEE43CAC40), UINT64_C(0x4838D65F6EF6748F), UINT64_C(0x1E152328F3318DEA),
													UINT64_C(0x8F8419A348F296BF), UINT64_C(0x72C8834A5957B511), UINT64_C(0xD7A023A73260B45C), UINT64_C(0x94EBC8ABCFB56DAE),
													UINT64_C(0x9FC10D0F989993E0), UINT64_C(0xDE68A2355B93CAE6), UINT64_C(0xA44CFE79AE538BBE), UINT64_C(0x9D1D84FCCE371425),
													UINT64_C(0x51D2B1AB2DDFB636), UINT64_C(0x2FD7E4B9E72CD38C), UINT64_C(0x65CA5B96B7552210), UINT64_C(0xDD69A0D8AB3B546D),
													UINT64_C(0x604D51B25FBF70E2), UINT64_C(0x73AA8A564FB7AC9E), UINT64_C(0x1A8C1E992B941148), UINT64_C(0xAAC40A2703D9BEA0),
													UINT64_C(0x764DBEAE7FA4F3A6), UINT64_C(0x1E99B96E70A9BE8B), UINT64_C(0x2C5E9DEB57EF4743), UINT64_C(0x3A938FEE32D29981),
													UINT64_C(0x26E6DB8FFDF5ADFE), UINT64_C(0x469356C504EC9F9D), UINT64_C(0xC8763C5B08D1908C), UINT64_C(0x3F6C6AF859D80055),
													UINT64_C(0x7F7CC39420A3A545), UINT64_C(0x9BFB227EBDF4C5CE), UINT64_C(0x89039D79D6FC5C5C), UINT64_C(0x8FE88B57305E2AB6),
													UINT64_C(0xA09E8C8C35AB96DE), UINT64_C(0xFA7E393983325753), UINT64_C(0xD6B6D0ECC617C699), UINT64_C(0xDFEA21EA9E7557E3),
													UINT64_C(0xB67C1FA481680AF8), UINT64_C(0xCA1E3785A9E724E5), UINT64_C(0x1CFC8BED0D681639), UINT64_C(0xD18D8549D140CAEA),
													UINT64_C(0x4ED0FE7E9DC91335), UINT64_C(0xE4DBF0634473F5D2), UINT64_C(0x1761F93A44D5AEFE), UINT64_C(0x53898E4C3910DA55),
													UINT64_C(0x734DE8181F6EC39A), UINT64_C(0x2680B122BAA28D97), UINT64_C(0x298AF231C85BAFAB), UINT64_C(0x7983EED3740847D5),
													UINT64_C(0x66C1A2A1A60CD889), UINT64_C(0x9E17E49642A3E4C1), UINT64_C(0xEDB454E7BADC0805), UINT64_C(0x50B704CAB602C329),
													UINT64_C(0x4CC317FB9CDDD023), UINT64_C(0x66B4835D9EAFEA22), UINT64_C(0x219B97E26FFC81BD), UINT64_C(0x261E4E4C0A333A9D),
													UINT64_C(0x1FE2CCA76517DB90), UINT64_C(0xD7504DFA8816EDBB), UINT64_C(0xB9571FA04DC089C8), UINT64_C(0x1DDC0325259B27DE),
													UINT64_C(0xCF3F4688801EB9AA), UINT64_C(0xF4F5D05C10CAB243), UINT64_C(0x38B6525C21A42B0E), UINT64_C(0x36F60E2BA4FA6800),
													UINT64_C(0xEB3593803173E0CE), UINT64_C(0x9C4CD6257C5A3603), UINT64_C(0xAF0C317D32ADAA8A), UINT64_C(0x258E5A80C7204C4B),
													UINT64_C(0x8B889D624D44885D), UINT64_C(0xF4D14597E660F855), UINT64_C(0xD4347F66EC8941C3), UINT64_C(0xE699ED85B0DFB40D),
													UINT64_C(0x2472F6207C2D0484), UINT64_C(0xC2A1E7B5B459AEB5), UINT64_C(0xAB4F6451CC1D45EC), UINT64_C(0x63767572AE3D6174),
													UINT64_C(0xA59E0BD101731A28), UINT64_C(0x116D0016CB948F09), UINT64_C(0x2CF9C8CA052F6E9F), UINT64_C(0x0B090A7560A968E3),
													UINT64_C(0xABEEDDB2DDE06FF1), UINT64_C(0x58EFC10B06A2068D), UINT64_C(0xC6E57A78FBD986E0), UINT64_C(0x2EAB8CA63CE802D7),
													UINT64_C(0x14A195640116F336), UINT64_C(0x7C0828DD624EC390), UINT64_C(0xD74BBE77E6116AC7), UINT64_C(0x804456AF10F5FB53),
													UINT64_C(0xEBE9EA2ADF4321C7), UINT64_C(0x03219A39EE587A30), UINT64_C(0x49787FEF17AF9924), UINT64_C(0xA1E9300CD8520548),
													UINT64_C(0x5B45E522E4B1B4EF), UINT64_C(0xB49C3B3995091A36), UINT64_C(0xD4490AD526F14431), UINT64_C(0x12A8F216AF9418C2),
													UINT64_C(0x001F837CC7350524), UINT64_C(0x1877B51E57A764D5), UINT64_C(0xA2853B80F17F58EE), UINT64_C(0x993E1DE72D36D310),
													UINT64_C(0xB3598080CE64A656), UINT64_C(0x252F59CF0D9F04BB), UINT64_C(0xD23C8E176D113600), UINT64_C(0x1BDA0492E7E4586E),
													UINT64_C(0x21E0BD5026C619BF), UINT64_C(0x3B097ADAF088F94E), UINT64_C(0x8D14DEDB30BE846E), UINT64_C(0xF95CFFA23AF5F6F4),
													UINT64_C(0x3871700761B3F743), UINT64_C(0xCA672B91E9E4FA16), UINT64_C(0x64C8E531BFF53B55), UINT64_C(0x241260ED4AD1E87D),
													UINT64_C(0x106C09B972D2E822), UINT64_C(0x7FBA195410E5CA30), UINT64_C(0x7884D9BC6CB569D8), UINT64_C(0x0647DFEDCD894A29),
													UINT64_C(0x63573FF03E224774), UINT64_C(0x4FC8E9560F91B123), UINT64_C(0x1DB956E450275779), UINT64_C(0xB8D91274B9E9D4FB),
													UINT64_C(0xA2EBEE47E2FBFCE1), UINT64_C(0xD9F1F30CCD97FB09), UINT64_C(0xEFED53D75FD64E6B), UINT64_C(0x2E6D02C36017F67F),
													UINT64_C(0xA9AA4D20DB084E9B), UINT64_C(0xB64BE8D8B25396C1), UINT64_C(0x70CB6AF7C2D5BCF0), UINT64_C(0x98F076A4F7A2322E),
													UINT64_C(0xBF84470805E69B5F), UINT64_C(0x94C3251F06F90CF3), UINT64_C(0x3E003E616A6591E9), UINT64_C(0xB925A6CD0421AFF3),
													UINT64_C(0x61BDD1307C66E300), UINT64_C(0xBF8D5108E27E0D48), UINT64_C(0x240AB57A8B888B20), UINT64_C(0xFC87614BAF287E07),
													UINT64_C(0xEF02CDD06FFDB432), UINT64_C(0xA1082C0466DF6C0A), UINT64_C(0x8215E577001332C8), UINT64_C(0xD39BB9C3A48DB6CF),
													UINT64_C(0x2738259634305C14), UINT64_C(0x61CF4F94C97DF93D), UINT64_C(0x1B6BACA2AE4E125B), UINT64_C(0x758F450C88572E0B),
													UINT64_C(0x959F587D507A8359), UINT64_C(0xB063E962E045F54D), UINT64_C(0x60E8ED72C0DFF5D1), UINT64_C(0x7B64978555326F9F),
													UINT64_C(0xFD080D236DA814BA), UINT64_C(0x8C90FD9B083F4558), UINT64_C(0x106F72FE81E2C590), UINT64_C(0x7976033A39F7D952),
													UINT64_C(0xA4EC0132764CA04B), UINT64_C(0x733EA705FAE4FA77), UINT64_C(0xB4D8F77BC3E56167), UINT64_C(0x9E21F4F903B33FD9),
													UINT64_C(0x9D765E419FB69F6D), UINT64_C(0xD30C088BA61EA5EF), UINT64_C(0x5D94337FBFAF7F5B), UINT64_C(0x1A4E4822EB4D7A59),
													UINT64_C(0x6FFE73E81B637FB3), UINT64_C(0xDDF957BC36D8B9CA), UINT64_C(0x64D0E29EEA8838B3), UINT64_C(0x08DD9BDFD96B9F63),
													UINT64_C(0x087E79E5A57D1D13), UINT64_C(0xE328E230E3E2B3FB), UINT64_C(0x1C2559E30F0946BE), UINT64_C(0x720BF5F26F4D2EAA),
													UINT64_C(0xB0774D261CC609DB), UINT64_C(0x443F64EC5A371195), UINT64_C(0x4112CF68649A260E), UINT64_C(0xD813F2FAB7F5C5CA),
													UINT64_C(0x660D3257380841EE), UINT64_C(0x59AC2C7873F910A3), UINT64_C(0xE846963877671A17), UINT64_C(0x93B633ABFA3469F8),
													UINT64_C(0xC0C0F5A60EF4CDCF), UINT64_C(0xCAF21ECD4377B28C), UINT64_C(0x57277707199B8175), UINT64_C(0x506C11B9D90E8B1D),
													UINT64_C(0xD83CC2687A19255F), UINT64_C(0x4A29C6465A314CD1), UINT64_C(0xED2DF21216235097), UINT64_C(0xB5635C95FF7296E2),
													UINT64_C(0x22AF003AB672E811), UINT64_C(0x52E762596BF68235), UINT64_C(0x9AEBA33AC6ECC6B0), UINT64_C(0x944F6DE09134DFB6),
													UINT64_C(0x6C47BEC883A7DE39), UINT64_C(0x6AD047C430A12104), UINT64_C(0xA5B1CFDBA0AB4067), UINT64_C(0x7C45D833AFF07862),
													UINT64_C(0x5092EF950A16DA0B), UINT64_C(0x9338E69C052B8E7B), UINT64_C(0x455A4B4CFE30E3F5), UINT64_C(0x6B02E63195AD0CF8),
													UINT64_C(0x6B17B224BAD6BF27), UINT64_C(0xD1E0CCD25BB9C169), UINT64_C(0xDE0C89A556B9AE70), UINT64_C(0x50065E535A213CF6),
													UINT64_C(0x9C1169FA2777B874), UINT64_C(0x78EDEFD694AF1EED), UINT64_C(0x6DC93D9526A50E68), UINT64_C(0xEE97F453F06791ED),
													UINT64_C(0x32AB0EDB696703D3), UINT64_C(0x3A6853C7E70757A7), UINT64_C(0x31865CED6120F37D), UINT64_C(0x67FEF95D92607890),
													UINT64_C(0x1F2B1D1F15F6DC9C), UINT64_C(0xB69E38A8965C6B65), UINT64_C(0xAA9119FF184CCCF4), UINT64_C(0xF43C732873F24C13),
													UINT64_C(0xFB4A3D794A9A80D2), UINT64_C(0x3550C2321FD6109C), UINT64_C(0x371F77E76BB8417E), UINT64_C(0x6BFA9AAE5EC05779),
													UINT64_C(0xCD04F3FF001A4778), UINT64_C(0xE3273522064480CA), UINT64_C(0x9F91508BFFCFC14A), UINT64_C(0x049A7F41061A9E60),
													UINT64_C(0xFCB6BE43A9F2FE9B), UINT64_C(0x08DE8A1C7797DA9B), UINT64_C(0x8F9887E6078735A1), UINT64_C(0xB5B4071DBFC73A66),
													UINT64_C(0x230E343DFBA08D33), UINT64_C(0x43ED7F5A0FAE657D), UINT64_C(0x3A88A0FBBCB05C63), UINT64_C(0x21874B8B4D2DBC4F),
													UINT64_C(0x1BDEA12E35F6A8C9), UINT64_C(0x53C065C6C8E63528), UINT64_C(0xE34A1D250E7A8D6B), UINT64_C(0xD6B04D3B7651DD7E),
													UINT64_C(0x5E90277E7CB39E2D), UINT64_C(0x2C046F22062DC67D), UINT64_C(0xB10BB459132D0A26), UINT64_C(0x3FA9DDFB67E2F199),
													UINT64_C(0x0E09B88E1914F7AF), UINT64_C(0x10E8B35AF3EEAB37), UINT64_C(0x9EEDECA8E272B933), UINT64_C(0xD4C718BC4AE8AE5F),
													UINT64_C(0x81536D601170FC20), UINT64_C(0x91B534F885818A06), UINT64_C(0xEC8177F83F900978), UINT64_C(0x190E714FADA5156E),
													UINT64_C(0xB592BF39B0364963), UINT64_C(0x89C350C893AE7DC1), UINT64_C(0xAC042E70F8B383F2), UINT64_C(0xB49B52E587A1EE60),
													UINT64_C(0xFB152FE3FF26DA89), UINT64_C(0x3E666E6F69AE2C15), UINT64_C(0x3B544EBE544C19F9), UINT64_C(0xE805A1E290CF2456),
													UINT64_C(0x24B33C9D7ED25117), UINT64_C(0xE74733427B72F0C1), UINT64_C(0x0A804D18B7097475), UINT64_C(0x57E3306D881EDB4F),
													UINT64_C(0x4AE7D6A36EB5DBCB), UINT64_C(0x2D8D5432157064C8), UINT64_C(0xD1E649DE1E7F268B), UINT64_C(0x8A328A1CEDFE552C),
													UINT64_C(0x07A3AEC79624C7DA), UINT64_C(0x84547DDC3E203C94), UINT64_C(0x990A98FD5071D263), UINT64_C(0x1A4FF12616EEFC89),
													UINT64_C(0xF6F7FD1431714200), UINT64_C(0x30C05B1BA332F41C), UINT64_C(0x8D2636B81555A786), UINT64_C(0x46C9FEB55D120902),
													UINT64_C(0xCCEC0A73B49C9921), UINT64_C(0x4E9D2827355FC492), UINT64_C(0x19EBB029435DCB0F), UINT64_C(0x4659D2B743848A2C),
													UINT64_C(0x963EF2C96B33BE31), UINT64_C(0x74F85198B05A2E7D), UINT64_C(0x5A0F544DD2B1FB18), UINT64_C(0x03727073C2E134B1),
													UINT64_C(0xC7F6AA2DE59AEA61), UINT64_C(0x352787BAA0D7C22F), UINT64_C(0x9853EAB63B5E0B35), UINT64_C(0xABBDCDD7ED5C0860),
													UINT64_C(0xCF05DAF5AC8D77B0), UINT64_C(0x49CAD48CEBF4A71E), UINT64_C(0x7A4C10EC2158C4A6), UINT64_C(0xD9E92AA246BF719E),
													UINT64_C(0x13AE978D09FE5557), UINT64_C(0x730499AF921549FF), UINT64_C(0x4E4B705B92903BA4), UINT64_C(0xFF577222C14F0A3A),
													UINT64_C(0x55B6344CF97AAFAE), UINT64_C(0xB862225B055B6960), UINT64_C(0xCAC09AFBDDD2CDB4), UINT64_C(0xDAF8E9829FE96B5F),
													UINT64_C(0xB5FDFC5D3132C498), UINT64_C(0x310CB380DB6F7503), UINT64_C(0xE87FBB46217A360E), UINT64_C(0x2102AE466EBB1148),
													UINT64_C(0xF8549E1A3AA5E00D), UINT64_C(0x07A69AFDCC42261A), UINT64_C(0xC4C118BFE78FEAAE), UINT64_C(0xF9F4892ED96BD438),
													UINT64_C(0x1AF3DBE25D8F45DA), UINT64_C(0xF5B4B0B0D2DEEEB4), UINT64_C(0x962ACEEFA82E1C84), UINT64_C(0x046E3ECAAF453CE9),
													UINT64_C(0xF05D129681949A4C), UINT64_C(0x964781CE734B3C84), UINT64_C(0x9C2ED44081CE5FBD), UINT64_C(0x522E23F3925E319E),
													UINT64_C(0x177E00F9FC32F791), UINT64_C(0x2BC60A63A6F3B3F2), UINT64_C(0x222BBFAE61725606), UINT64_C(0x486289DDCC3D6780),
													UINT64_C(0x7DC7785B8EFDFC80), UINT64_C(0x8AF38731C02BA980), UINT64_C(0x1FAB64EA29A2DDF7), UINT64_C(0xE4D9429322CD065A),
													UINT64_C(0x9DA058C67844F20C), UINT64_C(0x24C0E332B70019B0), UINT64_C(0x233003B5A6CFE6AD), UINT64_C(0xD586BD01C5C217F6),
													UINT64_C(0x5E5637885F29BC2B), UINT64_C(0x7EBA726D8C94094B), UINT64_C(0x0A56A5F0BFE39272), UINT64_C(0xD79476A84EE20D06),
													UINT64_C(0x9E4C1269BAA4BF37), UINT64_C(0x17EFEE45B0DEE640), UINT64_C(0x1D95B0A5FCF90BC6), UINT64_C(0x93CBE0B699C2585D),
													UINT64_C(0x65FA4F227A2B6D79), UINT64_C(0xD5F9E858292504D5), UINT64_C(0xC2B5A03F71471A6F), UINT64_C(0x59300222B4561E00),
													UINT64_C(0xCE2F8642CA0712DC), UINT64_C(0x7CA9723FBB2E8988), UINT64_C(0x2785338347F2BA08), UINT64_C(0xC61BB3A141E50E8C),
													UINT64_C(0x150F361DAB9DEC26), UINT64_C(0x9F6A419D382595F4), UINT64_C(0x64A53DC924FE7AC9), UINT64_C(0x142DE49FFF7A7C3D),
													UINT64_C(0x0C335248857FA9E7), UINT64_C(0x0A9C32D5EAE45305), UINT64_C(0xE6C42178C4BBB92E), UINT64_C(0x71F1CE2490D20B07),
													UINT64_C(0xF1BCC3D275AFE51A), UINT64_C(0xE728E8C83C334074), UINT64_C(0x96FBF83A12884624), UINT64_C(0x81A1549FD6573DA5),
													UINT64_C(0x5FA7867CAF35E149), UINT64_C(0x56986E2EF3ED091B), UINT64_C(0x917F1DD5F8886C61), UINT64_C(0xD20D8C88C8FFE65F)
												};
												constexpr const size_t piecePlayerIndex[2][8]
												{
													{
														3,
														5,
														7,
														9,
														1,
														11,
													},
													{
														2,
														4,
														6,
														8,
														9,
														10,
													}
												};
												const size_t rank{ square / boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countFiles };
												const size_t file{ square % boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countFiles };
												const size_t kind_of_piece{ piecePlayerIndex[player][piece] };
												const size_t offset_piece{ boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countSquares * kind_of_piece + boardInfo<standardplayersInfo, standardpiecesInfo, standardfilesInfo, standardranksInfo, standardflagsInfo>::countFiles * rank + file };
												return pieceHash[offset_piece];
											}
										);
									}
								);
							}
							),
						materialScoreInfo()
								)
		{
		}
	};
}