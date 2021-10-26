namespace pygmalion::search
{
	template<typename DESCRIPTION_SEARCH, typename GAMETREE>
	class command_debugPvs :
		public pygmalion::search::command<DESCRIPTION_SEARCH, GAMETREE>
	{
	public:
		using gametreeType = GAMETREE;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "../include_search.h"	
	private:
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		template<size_t PLAYER>
		void process(const depthType depth) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), this->searchEngine().rootContext()) };
					scoreType scoreFromPreviousDepth{ descriptorSearch::evaluatorType::evaluate(scoreType::minimum(), scoreType::maximum(), stack) };
					for (depthType i = -1; i <= depth - 1; ++i)
					{
						variationType principalVariation;
						scoreType score{ this->searchEngine().template pvs<0>(principalVariation, i,scoreFromPreviousDepth) };
						uint64_t nodeCount{ this->searchEngine().heuristics().nodeCount() };
						this->output() << static_cast<int>(i + 1) << ": " << std::setw(12) << score << " - " << this->searchEngine().template variationToString<PLAYER>(principalVariation) << std::endl;
						this->output() << this->searchEngine().heuristics().toString();
						this->output() << std::endl;
						this->flushOutput();
						scoreFromPreviousDepth = score;
					}
				}
				else
					this->template process<PLAYER + 1>(depth);
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
			if (token == "debug-pvs")
			{
				this->output() << std::endl;
				depthType depth = parser::parseInt(remainder);
				this->template process<0>(depth);
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-PVS";
		}
	};

}