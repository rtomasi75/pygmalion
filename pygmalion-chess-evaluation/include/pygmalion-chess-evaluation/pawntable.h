namespace pygmalion::chess
{
	class pawntable
	{
	public:
		using descriptorEvaluation = descriptor_evaluation;
#include <pygmalion-evaluation/include_evaluation.h>
		constexpr static inline const size_t countPawnHashBits{ /*16*/0 };
		constexpr static inline const size_t countPawnTableEntries{ static_cast<size_t>(1) << countPawnHashBits };
	private:
		constexpr static inline const hashType m_Mask{ hashType(countPawnTableEntries - 1) };
	public:
		class pawnentry
		{
		private:
			std::array<typename generatorType::tropismType, countPlayers> m_KingTropism;
			std::array<typename generatorType::tropismType, countPlayers> m_KingAreaTropism;
			std::array<squaresType, countPlayers> m_Pawns;
			std::array<squareType, countPlayers> m_KingSquare;
		public:
			constexpr const squaresType& pawns(const playerType& pl) const noexcept
			{
				return m_Pawns[pl];
			}
			constexpr const squareType& kingSquare(const playerType& pl) const noexcept
			{
				return m_KingSquare[pl];
			}
			constexpr const typename generatorType::tropismType& kingTropism(const playerType& pl) const noexcept
			{
				return m_KingTropism[pl];
			}
			constexpr const typename generatorType::tropismType& kingAreaTropism(const playerType& pl) const noexcept
			{
				return m_KingAreaTropism[pl];
			}
			pawnentry() noexcept :
				m_Pawns{ arrayhelper::make<countPlayers,squaresType>(squaresType::none()) },
				m_KingSquare{ arrayhelper::make<countPlayers,squareType>(squareType::invalid) },
				m_KingTropism{ arrayhelper::make<countPlayers,typename generatorType::tropismType>(typename generatorType::tropismType()) },
				m_KingAreaTropism{ arrayhelper::make<countPlayers,typename generatorType::tropismType>(typename generatorType::tropismType()) }
			{
			}
			~pawnentry() noexcept = default;
			template<size_t PLAYER>
			void update(const typename generatorType::template stackType<PLAYER>& stack) noexcept
			{
				const squaresType whitePawns{ stack.position().pieceOccupancy(descriptorEvaluation::pawn) & stack.position().playerOccupancy(descriptorEvaluation::whitePlayer) };
				const squaresType blackPawns{ stack.position().pieceOccupancy(descriptorEvaluation::pawn) & stack.position().playerOccupancy(descriptorEvaluation::blackPlayer) };
				const squareType whiteKing{ stack.kingSquare(descriptorEvaluation::whitePlayer) };
				const squareType blackKing{ stack.kingSquare(descriptorEvaluation::blackPlayer) };
				if ((m_Pawns[descriptorEvaluation::whitePlayer] == whitePawns) && (m_Pawns[descriptorEvaluation::blackPlayer] == blackPawns) && (m_KingSquare[descriptorEvaluation::whitePlayer] == whiteKing) && (m_KingSquare[descriptorEvaluation::blackPlayer] == blackKing))
					return;
				m_Pawns[descriptorEvaluation::whitePlayer] = whitePawns;
				m_Pawns[descriptorEvaluation::blackPlayer] = blackPawns;
				m_KingSquare[descriptorEvaluation::whitePlayer] = whiteKing;
				m_KingSquare[descriptorEvaluation::blackPlayer] = blackKing;

				const squaresType kingAreaWhite{ generatorType::movegenKing.attacks(whiteKing,squaresType::all()) & ~whitePawns };
				m_KingTropism[descriptorEvaluation::whitePlayer].compute(whiteKing, descriptorEvaluation::blackPlayer, blackPawns, whitePawns, blackKing, whiteKing);
				m_KingAreaTropism[descriptorEvaluation::whitePlayer].compute(kingAreaWhite, descriptorEvaluation::blackPlayer, blackPawns, whitePawns, blackKing, whiteKing);

				const squaresType kingAreaBlack{ generatorType::movegenKing.attacks(blackKing,squaresType::all()) & ~blackPawns };
				m_KingTropism[descriptorEvaluation::blackPlayer].compute(blackKing, descriptorEvaluation::whitePlayer, whitePawns, blackPawns, whiteKing, blackKing);
				m_KingAreaTropism[descriptorEvaluation::blackPlayer].compute(kingAreaBlack, descriptorEvaluation::whitePlayer, whitePawns, blackPawns, whiteKing, blackKing);

			}
		};
	private:
		static inline std::shared_ptr<std::array<pawnentry, countPawnTableEntries>> m_pEntries{ std::shared_ptr<std::array<pawnentry, countPawnTableEntries>>(new std::array<pawnentry, countPawnTableEntries>,[](std::array<pawnentry, countPawnTableEntries>* pMemory) { delete pMemory; }) };
	public:
		template<size_t PLAYER>
		static pawnentry& entry(const typename generatorType::template stackType<PLAYER>& stack) noexcept
		{
			const size_t index{ static_cast<size_t>(stack.position().pawnHash() & m_Mask) };
			(*m_pEntries)[index].update(stack);
			return (*m_pEntries)[index];
		}
	};
}