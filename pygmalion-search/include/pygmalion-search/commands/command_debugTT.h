namespace pygmalion::search
{
	template<typename DESCRIPTION_SEARCH, typename NODE>
	class command_debugTT :
		public pygmalion::search::command<DESCRIPTION_SEARCH, NODE>
	{
	public:
		using nodeType = NODE;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "../include_search.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-tt")
			{
				this->output() << std::endl;
				this->output() << "TT entry:   " << std::setw(4) << sizeof(typename transpositiontable<descriptorSearch>::transposition) << " = " << sizeof(typename transpositiontable<descriptorSearch>::transposition) * CHAR_BIT << "bit" << std::endl;
				this->output() << "TT bits:    " << std::setw(4) << this->searchEngine().transpositionTable().bitCount() << std::endl;
				this->output() << "TT memory:  " << std::setw(4) << parser::memoryToString(this->searchEngine().transpositionTable().memoryUsed(), "B") << std::endl;
				this->output() << "TT entries: " << std::setw(4) << this->searchEngine().transpositionTable().countEntries() << std::endl;
				this->output() << "TT used:    " << std::setw(4) << this->searchEngine().transpositionTable().countUsedEntries() << std::endl;
				this->output() << "TT range:   " << std::setw(4) << this->searchEngine().transpositionTable().countRangeEntries() << std::endl;
				this->output() << "TT exact:   " << std::setw(4) << this->searchEngine().transpositionTable().countExactEntries() << std::endl;
				this->output() << "TT move:    " << std::setw(4) << this->searchEngine().transpositionTable().countMoveEntries() << std::endl;
				this->output() << "TT lower:   " << std::setw(4) << this->searchEngine().transpositionTable().countLowerBoundEntries() << std::endl;
				this->output() << "TT upper:   " << std::setw(4) << this->searchEngine().transpositionTable().countUpperBoundEntries() << std::endl;
				this->output() << std::endl;
				this->output() << "Probes: " << std::setw(4) << this->searchEngine().transpositionTable().countProbes() << std::endl;
				this->output() << "Hits:   " << std::setw(4) << this->searchEngine().transpositionTable().countHits() << std::endl;
				this->output() << "Hits A: " << std::setw(4) << this->searchEngine().transpositionTable().countAlphaHits() << std::endl;
				this->output() << "Hits B: " << std::setw(4) << this->searchEngine().transpositionTable().countBetaHits() << std::endl;
				this->output() << "Hits E: " << std::setw(4) << this->searchEngine().transpositionTable().countExactHits() << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-TT";
		}
	};

}