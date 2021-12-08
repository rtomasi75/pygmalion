namespace pygmalion::chess
{
	class gametree :
		public pygmalion::gametree<descriptor_search, gametree>
	{
	public:
		using descriptorSearch = descriptor_search;
#include <pygmalion-search/include_search.h>
		template<size_t PLAYER>
		class node :
			public pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>
		{
		public:
			constexpr static inline const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			constexpr static inline const playerType otherPlayer{ movingPlayer.next() };
			using parentType = node< static_cast<size_t>(movingPlayer.previous())>;
			using childType = node< static_cast<size_t>(movingPlayer.next())>;
			using stackType = typename generatorType::template stackType<PLAYER>;
			PYGMALION_INLINE ~node() noexcept = default;
			PYGMALION_INLINE node(const stackType& stack, signal& terminate, heuristicsType& heuristics, const size_t depth, const std::vector<scoreType>& parameters, const evaluationDeltaType& evaluationDelta) noexcept :
				pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>(stack, terminate, heuristics, depth, parameters, evaluationDelta)
			{

			}
			PYGMALION_INLINE node(const parentType& parent, const movebitsType moveBits) noexcept :
				pygmalion::gametree<descriptor_search, gametree>::node<PLAYER, node<PLAYER>>(parent, moveBits)
			{
			}
			PYGMALION_INLINE constexpr static depthType nullMoveReduction_Implementation(const size_t depthRemaining) noexcept
			{
				return depthType(2) + ((depthRemaining - depthType(2)) / depthType(2));
			}
			PYGMALION_INLINE bool nullMoveAllowed_Implementation() const noexcept
			{
				const squaresType pieces{ this->stack().position().pieceOccupancy(descriptorSearch::knight) | this->stack().position().pieceOccupancy(descriptorSearch::bishop) | this->stack().position().pieceOccupancy(descriptorSearch::rook) | this->stack().position().pieceOccupancy(descriptorSearch::queen) };
				const squaresType playerPieces{ pieces & this->stack().position().playerOccupancy(movingPlayer) };
				return playerPieces;
			}
		};
		template<size_t PLAYER>
		using nodeType = node<PLAYER>;
	};
}