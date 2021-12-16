namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class materialTables :
		public DESCRIPTION_STATE
	{
	public:
		using boardType = BOARD;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"
		class movegenHints
		{
		private:
			piecesType m_AllowedPieces;
			std::array<squaresType, countPieces> m_AllowedSquares;
		public:
			movegenHints(const piecesType allowedPieces, const std::array<squaresType, countPieces>& allowedSquares) noexcept :
				m_AllowedPieces{ allowedPieces },
				m_AllowedSquares{ allowedSquares }
			{

			}
			movegenHints() noexcept :
				m_AllowedPieces{ piecesType::none() },
				m_AllowedSquares{ arrayhelper::make<countPieces>(squaresType::none()) }
			{

			}
			~movegenHints() noexcept = default;
			movegenHints(movegenHints&&) noexcept = default;
			movegenHints(const movegenHints&) noexcept = default;
			movegenHints& operator=(movegenHints&&) noexcept = default;
			movegenHints& operator=(const movegenHints&) noexcept = default;
			PYGMALION_INLINE piecesType allowedPieces() const noexcept
			{
				return m_AllowedPieces;
			}
			PYGMALION_INLINE squaresType allowedSquares(const pieceType pc) const noexcept
			{
				return m_AllowedSquares[pc];
			}
		};
	private:
		std::array< std::array<std::array<scoreType, countSquares>, countPieces>, countPlayers> m_PST_Parameters
		{
			arrayhelper::make < countPlayers, std::array<std::array<scoreType, countSquares>, countPieces>>(arrayhelper::make<countPieces, std::array<scoreType, countSquares>>(arrayhelper::make<countSquares, scoreType>(scoreType::zero())))
		};
		std::array<scoreType, countPieces> m_LazyMaterial
		{
			arrayhelper::make<countPieces,scoreType>(scoreType::zero())
		};
		std::array<std::array<std::array<objectiveType, countSquares>, countPieces>, countPlayers> m_PST
		{
			arrayhelper::make<countPlayers,std::array<std::array<objectiveType, countSquares>, countPieces>>(arrayhelper::make<countPieces,std::array<objectiveType, countSquares>>(arrayhelper::make<countSquares,objectiveType>(objectiveType::zero())))
		};
		std::array<scoreType, countPieces> m_MaterialScore
		{
			arrayhelper::make<countPieces,scoreType>(scoreType::zero())
		};
		std::array<std::array<movegenHints, countPieces>, countPlayers> m_WeakerMovegenHints;
		std::array<std::array<movegenHints, countPieces>, countPlayers> m_EqualMovegenHints;
		std::array<std::array<movegenHints, countPieces>, countPlayers> m_StrongerMovegenHints;
		void recomputePSTs() noexcept
		{
			for (const auto pl : playerType::range)
			{
				for (const auto pc : pieceType::range)
				{
					for (const auto sq : squareType::range)
					{
						m_PST[pl][pc][sq] = objectiveType::makeObjective(this->m_LazyMaterial[pc] + this->m_PST_Parameters[pl][pc][sq], pl);
					}
				}
			}
			for (const auto pl : playerType::range)
			{
				for (const auto pc : pieceType::range)
				{
					std::array<squaresType, countPieces> weakerSquares{ arrayhelper::make<countPieces,squaresType>(squaresType::none()) };
					std::array<squaresType, countPieces> strongerSquares{ arrayhelper::make<countPieces,squaresType>(squaresType::none()) };
					std::array<squaresType, countPieces> equalSquares{ arrayhelper::make<countPieces,squaresType>(squaresType::none()) };
					constexpr const piecesType noPieces{ piecesType::none() };
					constexpr const squaresType noSquares{ squaresType::none() };
					piecesType weakerPieces{ noPieces };
					piecesType strongerPieces{ noPieces };
					piecesType equalPieces{ noPieces };
					for (const auto pc2 : pieceType::range)
					{
						for (const auto sq : squareType::range)
						{
							const scoreType sc1{ material(pl,pc,sq).makeSubjective(pl) };
							const scoreType sc2{ material(pl,pc2,sq).makeSubjective(pl) };
							if (sc1 == sc2)
								equalSquares[pc2] |= sq;
							else if (sc1 > sc2)
								weakerSquares[pc2] |= sq;
							else
								strongerSquares[pc2] |= sq;
						}
						weakerPieces.checkElement(pc2, weakerSquares[pc2]);
						strongerPieces.checkElement(pc2, strongerSquares[pc2]);
						equalPieces.checkElement(pc2, equalSquares[pc2]);
					}
					m_WeakerMovegenHints[pl][pc] = movegenHints(weakerPieces, weakerSquares);
					m_StrongerMovegenHints[pl][pc] = movegenHints(strongerPieces, strongerSquares);
					m_EqualMovegenHints[pl][pc] = movegenHints(equalPieces, equalSquares);
				}
			}
		}
	public:
		PYGMALION_INLINE const movegenHints& equalHints(const playerType pl, const pieceType pc) const noexcept
		{
			return m_EqualMovegenHints[pl][pc];
		}
		PYGMALION_INLINE const movegenHints& weakerHints(const playerType pl, const pieceType pc) const noexcept
		{
			return m_WeakerMovegenHints[pl][pc];
		}
		PYGMALION_INLINE const movegenHints& strongerHints(const playerType pl, const pieceType pc) const noexcept
		{
			return m_StrongerMovegenHints[pl][pc];
		}
		constexpr static size_t countParameters{ countPieces + countPlayers * countPieces * countSquares };
		constexpr materialTables() noexcept
		{
		}
		~materialTables() noexcept = default;
		PYGMALION_INLINE objectiveType material(const playerType p, const pieceType pc, const squareType sq) const noexcept
		{
			return m_PST[p][pc][sq];
		}
		static std::string getParameterName(const size_t parameterIndex) noexcept
		{
			PYGMALION_ASSERT(parameterIndex < countParameters);
			if (parameterIndex < countPieces)
				return (static_cast<pieceType>(parameterIndex) & static_cast<playerType>(0)).toShortString() + "_lazy";
			else
			{
				const size_t indexPST{ parameterIndex - countPieces };
				const size_t indexSQ{ indexPST % countSquares };
				const size_t indexPST2{ indexPST / countSquares };
				const size_t indexPC{ indexPST2 % countPieces };
				const size_t indexPL{ indexPST2 / countPieces };
				const squareType sq{ static_cast<squareType>(indexSQ) };
				const pieceType pc{ static_cast<pieceType>(indexPC) };
				const playerType pl{ static_cast<playerType>(indexPL) };
				return (pc & pl).toShortString() + sq.toShortString() + "_pst";
			}
		}
		void getParameterRange(const size_t parameterIndex, double& minimum, double& maximum) const noexcept
		{
			PYGMALION_ASSERT(parameterIndex < countParameters);
			if (parameterIndex < countPieces)
			{
				minimum = 0.0;
				maximum = 12.0;
			}
			else
			{
				minimum = -2.0;
				maximum = 2.0;
			}
		}
		static void defaultParameters(std::vector<scoreType>& parameters) noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
			parameters.resize(countParameters);
			for (size_t parameterIndex = 0; parameterIndex < countParameters; parameterIndex++)
			{
				if (parameterIndex < countPieces)
					parameters[parameterIndex] = static_cast<scoreType>(boardInfo.materialPiece(parameterIndex));
				else
				{
					const size_t indexPST{ parameterIndex - countPieces };
					const size_t indexSQ{ indexPST % countSquares };
					const size_t indexPST2{ indexPST / countSquares };
					const size_t indexPC{ indexPST2 % countPieces };
					const size_t indexPL{ indexPST2 / countPieces };
					const squareType sq{ static_cast<squareType>(indexSQ) };
					const pieceType pc{ static_cast<pieceType>(indexPC) };
					const playerType pl{ static_cast<playerType>(indexPL) };
					parameters[parameterIndex] = static_cast<scoreType>(boardInfo.materialPieceSquare(indexPL, indexPC, static_cast<size_t>(sq.file()), static_cast<size_t>(sq.rank())));
				}
			}
		}
		void setParameters(const std::vector<scoreType>& parameters) noexcept
		{
			PYGMALION_ASSERT(parameters.size() == countParameters);
			for (size_t parameterIndex = 0; parameterIndex < countParameters; parameterIndex++)
			{
				if (parameterIndex < countPieces)
					m_LazyMaterial[parameterIndex] = parameters[parameterIndex];
				else
				{
					const size_t indexPST{ parameterIndex - countPieces };
					const size_t indexSQ{ indexPST % countSquares };
					const size_t indexPST2{ indexPST / countSquares };
					const size_t indexPC{ indexPST2 % countPieces };
					const size_t indexPL{ indexPST2 / countPieces };
					m_PST_Parameters[indexPL][indexPC][indexSQ] = parameters[parameterIndex];
				}
			}
			recomputePSTs();
		}
		void getParameters(std::vector<scoreType>& parameters) const noexcept
		{
			parameters.resize(countParameters);
			for (size_t parameterIndex = 0; parameterIndex < countParameters; parameterIndex++)
			{
				if (parameterIndex < countPieces)
					parameters[parameterIndex] = m_LazyMaterial[parameterIndex];
				else
				{
					const size_t indexPST{ parameterIndex - countPieces };
					const size_t indexSQ{ indexPST % countSquares };
					const size_t indexPST2{ indexPST / countSquares };
					const size_t indexPC{ indexPST2 % countPieces };
					const size_t indexPL{ indexPST2 / countPieces };
					parameters[parameterIndex] = m_PST_Parameters[indexPL][indexPC][indexSQ];
				}
			}
		}
	};
}