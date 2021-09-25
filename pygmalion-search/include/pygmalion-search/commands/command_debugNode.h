namespace pygmalion::search
{
	template<typename DESCRIPTION_SEARCH, typename NODE>
	class command_debugNode :
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
			if (token == "debug-node")
			{
				this->output() << std::endl;
				std::string remainder2;
				parser::parseTokenCaseSensitive(remainder, token, remainder2);
				if (token != "")
				{
					depthType depth = parser::parseInt(token);
					parser::parseTokenCaseSensitive(remainder2, token, remainder);
					std::atomic_bool isRunning{ true };
					this->searchEngine().heuristics().beginSearch();
					stackType stack{ stackType(this->position(), this->history(),  this->position().movingPlayer()) };
					std::array<nodeType*, countSearchPlies> nodes{ arrayhelper::make<countSearchPlies,nodeType*>(nullptr) };
					nodes[0] = new nodeType(stack, isRunning, this->searchEngine().heuristics());
					size_t i = 1;
					bool bOk{ true };
					while (token != "")
					{
						movebitsType movebits;
						if (motorType::parseMove(stack.position(), token, movebits))
						{
							this->output() << "performed move " << motorType::moveToString(stack.position(), movebits) << ", hash=" << std::hex << static_cast<std::uint64_t>(stack.position().hash()) << std::dec << std::endl;
							nodes[i] = new nodeType(*(nodes[i - 1]), movebits);
							i++;
						}
						else
						{
							this->output() << token << " is not a possible move." << std::endl;
							bOk = false;
							break;
						}
						remainder2 = remainder;
						parser::parseTokenCaseSensitive(remainder2, token, remainder);
					}
					if (bOk)
					{
						variationType principalVariation;
						const scoreType score{ nodes[i - 1]->template searchRoot<false>(depth, this->history().length() + i - 1, principalVariation, this->output()) };
						uint64_t nodeCount{ this->searchEngine().heuristics().nodeCount() };
						this->output() << static_cast<int>(depth) << ": " << std::setw(12) << score << " - " << this->searchEngine().variationToString(principalVariation) << std::endl;
						this->output() << std::endl;
					}
					for (; i > 0; i--)
					{
						delete nodes[i - 1];
					}
					this->searchEngine().heuristics().endSearch();
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