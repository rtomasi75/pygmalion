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
	private:
		std::array< std::array<std::array<scoreType, countSquares>, countPieces>, countPlayers> m_PST_Parameters
		{
			arrayhelper::make < countPlayers, std::array<std::array<scoreType, countSquares>, countPieces>>(arrayhelper::make<countPieces, std::array<scoreType, countSquares>>(arrayhelper::make<countSquares, scoreType>(scoreType::zero())))
		};
		std::array<scoreType, countPieces> m_LazyMaterial
		{
			arrayhelper::make<countPieces,scoreType>(scoreType::zero())
		};
		std::array<std::array<std::array<scoreType, countSquares>, countPieces>, countPlayers> m_PST
		{
			arrayhelper::make<countPlayers,std::array<std::array<scoreType, countSquares>, countPieces>>(arrayhelper::make<countPieces,std::array<scoreType, countSquares>>(arrayhelper::make<countSquares,scoreType>(scoreType::zero())))
		};
		std::array<scoreType, countPieces> m_MaterialUpperBound
		{
			arrayhelper::make<countPieces,scoreType>(scoreType::zero())
		};
		std::array<scoreType, countPieces> m_MaterialLowerBound
		{
			arrayhelper::make<countPieces,scoreType>(scoreType::zero())
		};
		std::array<scoreType, countPieces> m_MaterialScore
		{
			arrayhelper::make<countPieces,scoreType>(scoreType::zero())
		};
	public:
		PYGMALION_INLINE scoreType materialScore(const pieceType pc) const noexcept
		{
			return m_MaterialScore[pc];
		}
		constexpr materialTables() noexcept
		{
		}
		~materialTables() noexcept = default;
		template<size_t RELATIVE_TO_PLAYER>
		PYGMALION_INLINE scoreType materialRelative(const playerType p, const pieceType pc, const squareType sq) const noexcept
		{
			if constexpr (RELATIVE_TO_PLAYER == 0)
				return m_PST[p][pc][sq];
			else
				return -m_PST[p][pc][sq];
		}
		PYGMALION_INLINE scoreType materialRelative(const playerType pl_relative, const playerType p, const pieceType pc, const squareType sq) const noexcept
		{
			if (static_cast<size_t>(pl_relative) == 0)
				return m_PST[p][pc][sq];
			else
				return -m_PST[p][pc][sq];
		}
		PYGMALION_INLINE scoreType materialAbsolute(const playerType p, const pieceType pc, const squareType sq) const noexcept
		{
			return m_PST[p][pc][sq];
		}
		PYGMALION_INLINE scoreType materialUpperBound(const pieceType pc) const noexcept
		{
			return m_MaterialUpperBound[pc];
		}
		PYGMALION_INLINE scoreType materialLowerBound(const pieceType pc) const noexcept
		{
			return m_MaterialLowerBound[pc];
		}
		constexpr static size_t countParameters{ countPieces + countPlayers * countPieces * countSquares };
		void recomputePSTs() noexcept
		{
			const auto PSTLambda
			{
				[this](const size_t plIdx)
				{
					const playerType pl{static_cast<playerType>(plIdx)};
					return arrayhelper::generate<countPieces, std::array<scoreType, countSquares>>(
						[this,pl](const size_t pcIdx)
						{
							const pieceType pc{ static_cast<pieceType>(pcIdx) };
							return arrayhelper::generate<countSquares, scoreType>(
								[this, pl, pc](const size_t sqIdx)
								{
									const squareType sq{ static_cast<squareType>(sqIdx) };
									return boardType::makeSubjective(pl, this->m_LazyMaterial[pc] + this->m_PST_Parameters[pl][pc][sq]);
								}
							);
						}
					);
				}
			};
			m_PST = arrayhelper::generate< countPlayers, std::array<std::array<scoreType, countSquares>, countPieces>>(PSTLambda);
			const auto UpperBoundLambda
			{
				[this](const size_t pcIdx)
				{
					scoreType best{scoreType::minimum()};
					const pieceType pc{ static_cast<pieceType>(pcIdx) };
					for (const auto pl : playerType::range)
					{
						for (const auto sq : squareType::range)
						{
							if (best < this->materialRelative(pl, pl, pc, sq))
								best = this->materialRelative(pl, pl, pc, sq);
						}
					}
					return best;
				}
			};
			m_MaterialUpperBound = arrayhelper::generate<countPieces, scoreType>(UpperBoundLambda);
			const auto LowerBoundLambda
			{
				[this](const size_t pcIdx)
				{
					scoreType best{scoreType::maximum()};
					const pieceType pc{ static_cast<pieceType>(pcIdx) };
					for (const auto pl : playerType::range)
					{
						for (const auto sq : squareType::range)
						{
							if (best > this->materialRelative(pl, pl, pc, sq))
								best = this->materialRelative(pl, pl, pc, sq);
						}
					}
					return best;
				}
			};
			m_MaterialLowerBound = arrayhelper::generate<countPieces, scoreType>(LowerBoundLambda);
			m_MaterialScore = arrayhelper::generate<countPieces, scoreType>
				(
					[this](const size_t pieceIndex)
					{
						const pieceType pc{ static_cast<pieceType>(pieceIndex) };
						double value = 0.0;
						for (const auto sq : squareType::range)
						{
							for (const auto pl : playerType::range)
							{
								value += static_cast<double>(this->materialRelative(pl, pl, pc, sq));
							}
						}
						return static_cast<scoreType>(value / (countSquares * countPlayers));
					}
			);
		}
		std::string getParameterName(const size_t parameterIndex) const noexcept
		{
			PYGMALION_ASSERT(parameterIndex < countParameters);
			if (parameterIndex < countPieces)
				return boardType::pieceToString(static_cast<pieceType>(parameterIndex), static_cast<playerType>(0)) + "_lazy";
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
				return boardType::pieceToString(static_cast<pieceType>(parameterIndex), pl) + boardType::squareToString() + "_pst";
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
		template<typename LAMBDA>
		PYGMALION_INLINE void forStrongerPieces(const pieceType pc, const LAMBDA& lambda) const noexcept
		{
			for (const auto pc2 : pieceType::range)
			{
				if (this->materialScore(pc) < this->materialScore(pc2))
					lambda(pc2);
			}
		}
		template<typename LAMBDA>
		PYGMALION_INLINE void forWeakerPieces(const pieceType pc, const LAMBDA& lambda) const noexcept
		{
			for (const auto pc2 : pieceType::range)
			{
				if (this->materialScore(pc) > this->materialScore(pc2))
					lambda(pc2);
			}
		}
		template<typename LAMBDA>
		PYGMALION_INLINE void forEqualPieces(const pieceType pc, const LAMBDA& lambda) const noexcept
		{
			for (const auto pc2 : pieceType::range)
			{
				if (this->materialScore(pc) == this->materialScore(pc2))
					lambda(pc2);
			}
		}
		static void defaultParameters(std::vector<scoreType>& parameters) noexcept
		{
			constexpr const scoreType zero{ scoreType::zero() };
			parameters.resize(countParameters);
			for (size_t parameterIndex = 0; parameterIndex < countParameters; parameterIndex++)
			{
				if (parameterIndex < countPieces)
					parameters[parameterIndex] = boardType::defaultLazyMaterial(static_cast<pieceType>(parameterIndex));
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
					parameters[parameterIndex] = boardType::defaultMaterial(pl, pc, sq);
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
		}
	};
}