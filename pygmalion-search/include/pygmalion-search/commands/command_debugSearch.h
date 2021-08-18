namespace pygmalion::search
{
	template<typename DESCRIPTION_SEARCH, typename NODE>
	class command_debugSearch :
		public pygmalion::search::command<DESCRIPTION_SEARCH, NODE>
	{
	public:
		using nodeType = NODE;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "../include_search.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-search")
			{
				this->output() << std::endl;
				this->output() << "depth:      " << std::setw(4) << sizeof(depthType) << " = " << sizeof(depthType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "variation:  " << std::setw(4) << sizeof(variationType) << " = " << sizeof(variationType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "heuristics: " << std::setw(4) << sizeof(heuristicsType) << " = " << sizeof(heuristicsType) * CHAR_BIT << "bit" << std::endl;
				this->output() << std::endl;
				this->output() << "countSearchPlies: " << std::setw(4) << countSearchPlies << std::endl;
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