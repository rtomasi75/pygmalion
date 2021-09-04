namespace pygmalion::search
{
	template<typename DESCRIPTION_SEARCH, typename NODE>
	class command_debugPvs :
		public pygmalion::search::command<DESCRIPTION_SEARCH, NODE>
	{
	public:
		using nodeType = NODE;
		using descriptorSearch = DESCRIPTION_SEARCH;
#include "../include_search.h"	
	private:
		using stackType = typename generatorType::stackType;
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-vpvs")
			{
				this->output() << std::endl;
				depthType depth = parser::parseInt(remainder);
				for (depthType i = -1; i <= depth - 1; ++i)
				{
					variationType principalVariation;
					scoreType score{ this->searchEngine().vpvs(principalVariation, i, this->output()) };
					uint64_t nodeCount{ this->searchEngine().heuristics().nodeCount() };
					this->output() << static_cast<int>(i + 1) << ": " << std::setw(12) << score << " - " << this->searchEngine().variationToString(principalVariation) << std::endl;
					this->output() << this->searchEngine().heuristics().toString();
					this->output() << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else if (token == "debug-pvs")
			{
				this->output() << std::endl;
				depthType depth = parser::parseInt(remainder);
				for (depthType i = - 1; i <= depth - 1; ++i)
				{
					variationType principalVariation;
					scoreType score{ this->searchEngine().pvs(principalVariation, i, this->output()) };
					uint64_t nodeCount{ this->searchEngine().heuristics().nodeCount() };
					this->output() << static_cast<int>(i + 1) << ": " << std::setw(12) << score << " - " << this->searchEngine().variationToString(principalVariation) << std::endl;
					this->output() << this->searchEngine().heuristics().toString();
					this->output() << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-(V)PVS";
		}
	};

}