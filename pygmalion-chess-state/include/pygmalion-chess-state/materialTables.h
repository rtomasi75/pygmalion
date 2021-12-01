namespace pygmalion::chess::state
{
	template<typename DESCRIPTION_STATE>
	class materialTables :
		public DESCRIPTION_STATE
	{
	public:
		using descriptorState = DESCRIPTION_STATE;
#include <pygmalion-state/include_state.h>
	private:
		PYGMALION_TUNABLE static inline double m_PST_King[64]
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
		PYGMALION_TUNABLE static inline double m_PST_Knight[64]
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
		PYGMALION_TUNABLE static inline double m_PST_Bishop[64]
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
		PYGMALION_TUNABLE static inline double m_PST_Rook[64]
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
		PYGMALION_TUNABLE static inline double m_PST_Queen[64]
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
		PYGMALION_TUNABLE static inline double m_PST_Pawn[64]
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
		PYGMALION_TUNABLE static inline double m_LazyMaterial[6]
		{
			3.0,  //knight
			3.3,  //bishop
			5.5,  //rook
			10.0, //queen
			1.0,  //pawn
			0.0   //king
		};
		constexpr static inline const auto m_PSTLambda
		{
			[](const size_t plIdx)
			{
				const playerType pl{static_cast<playerType>(plIdx)};
				return arrayhelper::generate<countPieces, std::array<materialScore, countSquares>>(
					[pl](const size_t pcIdx)
					{
						const pieceType pc{ static_cast<pieceType>(pcIdx) };
						return arrayhelper::generate<countSquares, materialScore>(
							[pl, pc](const size_t sqIdx)
							{
								const squareType sq{ static_cast<squareType>(sqIdx) };
								if (pl == descriptorState::whitePlayer)
								{
									switch (pc)
									{
									case descriptorState::pawn:
										return static_cast<materialScore>(m_PST_Pawn[sq] + m_LazyMaterial[pc]);
									case descriptorState::knight:
										return static_cast<materialScore>(m_PST_Knight[sq] + m_LazyMaterial[pc]);
									case descriptorState::rook:
										return static_cast<materialScore>(m_PST_Rook[sq] + m_LazyMaterial[pc]);
									case descriptorState::queen:
										return static_cast<materialScore>(m_PST_Queen[sq] + m_LazyMaterial[pc]);
									case descriptorState::king:
										return static_cast<materialScore>(-m_PST_King[sq] + m_LazyMaterial[pc]);
									case descriptorState::bishop:
										return static_cast<materialScore>(m_PST_Bishop[sq] + m_LazyMaterial[pc]);
									default:
										return materialScore::zero();
									}
								}
								else
								{
									switch (pc)
									{
									case descriptorState::pawn:
										return static_cast<materialScore>(m_PST_Pawn[sq.flipRank()] + m_LazyMaterial[pc]);
									case descriptorState::knight:
										return static_cast<materialScore>(m_PST_Knight[sq.flipRank()] + m_LazyMaterial[pc]);
									case descriptorState::rook:
										return static_cast<materialScore>(m_PST_Rook[sq.flipRank()] + m_LazyMaterial[pc]);
									case descriptorState::queen:
										return static_cast<materialScore>(m_PST_Queen[sq.flipRank()] + m_LazyMaterial[pc]);
									case descriptorState::king:
										return static_cast<materialScore>(-m_PST_King[sq.flipRank()] + m_LazyMaterial[pc]);
									case descriptorState::bishop:
										return static_cast<materialScore>(m_PST_Bishop[sq.flipRank()] + m_LazyMaterial[pc]);
									default:
										return materialScore::zero();
									}
								}
							}
						);
					}
				);
			}
		};
		PYGMALION_TUNABLE static inline std::array<std::array<std::array<materialScore, countSquares>, countPieces>, countPlayers> m_PST
		{
			arrayhelper::generate< countPlayers,std::array<std::array<materialScore, countSquares>, countPieces>>(m_PSTLambda)
		};
		constexpr static inline const auto m_UpperBoundLambda
		{
			[](const size_t pcIdx)
			{
				materialScore best{materialScore::minimum()};
				for (const auto sq : squareType::range)
				{
					if (best < m_PST[descriptorState::whitePlayer][pcIdx][sq])
						best = m_PST[descriptorState::whitePlayer][pcIdx][sq];
				}
				return best;
			}
		};
		constexpr static inline const auto m_LowerBoundLambda
		{
			[](const size_t pcIdx)
			{
				materialScore best{materialScore::maximum()};
				for (const auto sq : squareType::range)
				{
					if (best > m_PST[descriptorState::whitePlayer][pcIdx][sq])
						best = m_PST[descriptorState::whitePlayer][pcIdx][sq];
				}
				return best;
			}
		};
		PYGMALION_TUNABLE static inline std::array<materialScore, 6> m_MaterialUpperBound
		{
			arrayhelper::generate<6,materialScore>(m_UpperBoundLambda)
		};
		PYGMALION_TUNABLE static inline std::array<materialScore, 6> m_MaterialLowerBound
		{
			arrayhelper::generate<6,materialScore>(m_LowerBoundLambda)
		};
		PYGMALION_TUNABLE static inline materialScore m_PST_Delta{ static_cast<materialScore>(0.768) };
#if defined(PYGMALION_TUNE)&&(PYGMALION_TUNE==1)
		static void recomputePSTs() noexcept
		{
			m_PST = arrayhelper::generate< countPlayers, std::array<std::array<materialScore, countSquares>, countPieces>>(m_PSTLambda);
			m_MaterialUpperBound = arrayhelper::generate<6, materialScore>(m_UpperBoundLambda);
			m_MaterialLowerBound = arrayhelper::generate<6, materialScore>(m_LowerBoundLambda);
		}
#endif
	public:
		PYGMALION_INLINE PYGMALION_TUNABLE materialScore materialDelta() const noexcept
		{
			return m_PST_Delta;
		}
		constexpr materialTables() noexcept
		{
		}
		~materialTables() noexcept = default;
		PYGMALION_INLINE PYGMALION_TUNABLE materialScore absoluteMaterial(const playerType p, const pieceType pc, const squareType sq) const noexcept
		{
			return p == descriptorState::whitePlayer ? m_PST[p][pc][sq] : -m_PST[p][pc][sq];
		}
		PYGMALION_INLINE PYGMALION_TUNABLE materialScore relativeMaterial(const playerType p, const pieceType pc, const squareType sq) const noexcept
		{
			return m_PST[p][pc][sq];
		}
		PYGMALION_INLINE PYGMALION_TUNABLE materialScore materialUpperBound(const pieceType pc) const noexcept
		{
			return m_MaterialUpperBound[pc];
		}
		PYGMALION_INLINE PYGMALION_TUNABLE materialScore materialLowerBound(const pieceType pc) const noexcept
		{
			return m_MaterialLowerBound[pc];
		}
		PYGMALION_INLINE PYGMALION_TUNABLE int minorPieceKnightOffset() const noexcept
		{
			if (m_LazyMaterial[0x0] < m_LazyMaterial[0x1])
			{
				return -1;
			}
			else
			{
				if (m_LazyMaterial[0x0] == m_LazyMaterial[0x1])
					return 0;
				else
					return 1;
			}
		}
		static double getTunedMaterial(const pieceType pc) noexcept
		{
			return m_LazyMaterial[pc];
		}
		static double getTunedPST(const pieceType pc, const squareType sq) noexcept
		{
			switch (pc)
			{
			case descriptorState::pawn:
				return m_PST_Pawn[sq];
			case descriptorState::rook:
				return m_PST_Rook[sq];
			case descriptorState::bishop:
				return m_PST_Bishop[sq];
			case descriptorState::knight:
				return m_PST_Knight[sq];
			case descriptorState::queen:
				return m_PST_Queen[sq];
			case descriptorState::king:
				return m_PST_King[sq];
			default:
				PYGMALION_UNREACHABLE;
				return 0.0;
			}
		}
#if defined(PYGMALION_TUNE)&&(PYGMALION_TUNE==1)
		static void setTunedMaterial(const pieceType pc, const double whiteValue) noexcept
		{
			m_LazyMaterial[pc] = whiteValue;
			recomputePSTs();
		}
		static void setTunedPST(const pieceType pc, const squareType sq, const double whiteValue) noexcept
		{
			switch (pc)
			{
			case descriptorState::pawn:
				m_PST_Pawn[sq]=whiteValue;
			case descriptorState::rook:
				m_PST_Rook[sq] = whiteValue;
			case descriptorState::bishop:
				m_PST_Bishop[sq] = whiteValue;
			case descriptorState::knight:
				m_PST_Knight[sq] = whiteValue;
			case descriptorState::queen:
				m_PST_Queen[sq] = whiteValue;
			case descriptorState::king:
				m_PST_King[sq] = whiteValue;
			default:
				PYGMALION_UNREACHABLE;
				break;
			}
			recomputePSTs();
		}
#endif

	};
}