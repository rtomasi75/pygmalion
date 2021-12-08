namespace pygmalion::search
{
	template<typename DESCRIPTION_SEARCH, typename GAMETREE>
	class command_debugNode :
		public pygmalion::search::command<DESCRIPTION_SEARCH, GAMETREE>
	{
	public:
		using gametreeType = GAMETREE;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "../include_search.h"	
	private:
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		template<size_t PLAYERINDEX>
		bool debugSubNode(const depthType depth, typename gametreeType::template nodeType<static_cast<size_t>(static_cast<playerType>(PLAYERINDEX).previous())>& parentNode, const std::string& remainder, scoreType& score, variationType& principalVariation)
		{
			std::string token;
			std::string newRemainder;
			parser::parseTokenCaseSensitive(remainder, token, newRemainder);
			using nodeType = typename gametreeType::template nodeType<PLAYERINDEX>;
			if (token != "")
			{
				movebitsType movebits;
				size_t count{ 0 };
				if (motorType::parseMove(parentNode.stack().position(), token, movebits, count))
				{
					this->output() << "performed move " << motorType::moveToString(parentNode.stack().position(), movebits) << ", hash=" << std::hex << static_cast<std::uint64_t>(parentNode.stack().position().hash()) << std::dec << std::endl;
					nodeType node{ nodeType(parentNode, movebits) };
					return this->template debugSubNode<static_cast<size_t>(static_cast<playerType>(PLAYERINDEX).next())>(depth, node, newRemainder, score, principalVariation);
				}
				else
				{
					this->output() << token << " is not a possible move." << std::endl;
					return false;
				}
			}
			else
			{
				indexType currentMove;
				indexType countMoves;
				score = parentNode.template searchRoot<false>(depth, principalVariation, scoreType::zero(), currentMove, countMoves);
				return true;
			}
		}
		template<size_t PLAYERINDEX>
		void debugNode(const depthType depth, const std::string& remainder) noexcept
		{
			if constexpr (PLAYERINDEX < countPlayers)
			{
				constexpr const playerType indexedPlayer{ static_cast<playerType>(PLAYERINDEX) };
				using nodeType = typename gametreeType::template nodeType<PLAYERINDEX>;
				if (this->position().movingPlayer() == indexedPlayer)
				{
					signal terminate{ signal(false) };
					this->searchEngine().heuristics().beginSearch();
					stackType<PLAYERINDEX> stack{ stackType<PLAYERINDEX>(this->position(), this->history(), this->rootContext(), this->stateEngine().materialTable(), this->dynamicsEngine().delta()) };
					nodeType node{ nodeType(stack, terminate, this->searchEngine().heuristics(), this->history().length(), this->evaluationEngine().parameters(), this->evaluationEngine().evaluationDelta()) };
					variationType principalVariation;
					scoreType score;
					bool bOk{ debugSubNode<static_cast<size_t>(static_cast<playerType>(PLAYERINDEX).next())>(depth, node,remainder,score,principalVariation) };
					if (bOk)
					{
						uint64_t nodeCount{ this->searchEngine().heuristics().nodeCount() };
						this->output() << static_cast<int>(depth) << ": " << std::setw(12) << score << " - " << this->searchEngine().template variationToString<PLAYERINDEX>(principalVariation) << std::endl;
						this->output() << std::endl;
					}
					this->searchEngine().heuristics().endSearch();
				}
				else
				{
					debugNode<PLAYERINDEX + 1>(depth, remainder);
				}
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-node")
			{
				this->output() << std::endl;
				std::string remainder2;
				parser::parseTokenCaseSensitive(remainder, token, remainder2);
				if (token != "")
				{
					depthType depth = parser::parseInt(token);
					debugNode<0>(depth, token);
					this->output() << std::endl;
					return true;
				}
				else
				{
					this->output() << "No depth specificed." << std::endl;
					return true;
				}
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-NODE";
		}
	};

}