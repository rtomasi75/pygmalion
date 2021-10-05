namespace pygmalion::search
{
	template<typename DESCRIPTION_SEARCH, typename GAMETREE>
	class command_debugSearch :
		public pygmalion::search::command<DESCRIPTION_SEARCH, GAMETREE>
	{
	public:
		using gametreeType = GAMETREE;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "../include_search.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-search")
			{
				this->output() << std::endl;
				this->output() << "depth:               " << std::setw(4) << sizeof(depthType) << " = " << sizeof(depthType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "variation:           " << std::setw(4) << sizeof(variationType) << " = " << sizeof(variationType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "transposition:       " << std::setw(4) << sizeof(typename transpositiontable<descriptorSearch>::transposition) << " = " << sizeof(typename transpositiontable<descriptorSearch>::transposition) * CHAR_BIT << "bit" << std::endl;
				this->output() << "killerslots:         " << std::setw(4) << sizeof(typename heuristicsType::killerslots) << " = " << sizeof(typename heuristicsType::killerslots) * CHAR_BIT << "bit" << std::endl;
				this->output() << "heuristics:          " << std::setw(4) << sizeof(heuristicsType) << " = " << sizeof(heuristicsType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "quiet killemoves:    " << std::setw(4) << sizeof(quietKillermovesType) << " = " << sizeof(quietKillermovesType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "tactical killemoves: " << std::setw(4) << sizeof(tacticalKillermovesType) << " = " << sizeof(tacticalKillermovesType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "TTmoves:             " << std::setw(4) << sizeof(ttmovesType) << " = " << sizeof(ttmovesType) * CHAR_BIT << "bit" << std::endl;
//				this->output() << "node:                " << std::setw(4) << sizeof(nodeType) << " = " << sizeof(nodeType) * CHAR_BIT << "bit" << std::endl;
				this->output() << std::endl;
				this->output() << "max. depth: " << std::setw(4) << countSearchPlies << std::endl;
				this->output() << "TT bits:    " << std::setw(4) << this->searchEngine().transpositionTable().bitCount() << std::endl;
				this->output() << "TT entries: " << std::setw(4) << this->searchEngine().transpositionTable().countEntries() << std::endl;
				this->output() << "TT memory:  " << std::setw(4) << parser::valueToString(this->searchEngine().transpositionTable().memoryUsed(), "B") << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-SEARCH";
		}
	};

}