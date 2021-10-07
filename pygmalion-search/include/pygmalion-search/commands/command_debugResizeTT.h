namespace pygmalion::search
{
	template<typename DESCRIPTION_SEARCH, typename GAMETREE>
	class command_debugResizeTT :
		public pygmalion::search::command<DESCRIPTION_SEARCH, GAMETREE>
	{
	public:
		using gametreeType = GAMETREE;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "../include_search.h"	
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
	private:
		template<size_t PLAYER>
		void process(const size_t sizeInMegaBytes) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					this->searchEngine().heuristics().transpositionTable().resize(sizeInMegaBytes * 1024 * 1024);
				}
				else
					this->template process<PLAYER + 1>(sizeInMegaBytes);
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
			if (token == "debug-resizett")
			{
				this->output() << std::endl;
				size_t sizeInMegaBytes = parser::parseInt(remainder);
				this->template process<0>(sizeInMegaBytes);
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