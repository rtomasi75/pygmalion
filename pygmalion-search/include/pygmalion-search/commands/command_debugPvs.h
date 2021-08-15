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
		static std::string variationToStringFromDepth(const stackType& stack, const variationType& variation, const depthType depth) noexcept
		{
			if (variation.length() > depth)
			{
				std::stringstream sstr;
				sstr << stack.moveToString(variation[depth]) << " ";
				stackType subStack(stack, variation[depth]);
				sstr << variationToStringFromDepth(subStack, variation, depth + 1);
				return sstr.str();
			}
			return "";
		}
		static std::string variationToString(const stackType& stack, const variationType& variation) noexcept
		{
			return variationToStringFromDepth(stack, variation, 0);
		}
		objectiveType pvs(const stackType& stack, variationType& principalVariation, const depthType depthRemaining, heuristicsType& heuristics, std::ostream& str) noexcept
		{
			std::atomic_bool isRunning{ true };
			nodeType node(stack, isRunning);
			principalVariation.clear();
			multiscoreType alphabeta;
			heuristics.beginSearch();
			const objectiveType score{ node.template search<false>(alphabeta, depthRemaining, 0, principalVariation, heuristics, str) };
			heuristics.endSearch();
			return score;
		}
		objectiveType vpvs(const stackType& stack, variationType& principalVariation, const depthType depthRemaining, heuristicsType& heuristics, std::ostream& str) noexcept
		{
			std::atomic_bool isRunning{ true };
			nodeType node(stack, isRunning);
			principalVariation.clear();
			multiscoreType alphabeta;
			heuristics.beginSearch();
			const objectiveType score{ node.template search<true>(alphabeta, depthRemaining, 0, principalVariation, heuristics, str) };
			heuristics.endSearch();
			return score;
		}
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
				for (depthType i = -1; i <= depth - 1; i++)
				{
					variationType principalVariation;
					heuristicsType heuristics;
					stackType stack{ stackType(this->position(), this->history(),  this->position().movingPlayer()) };
					objectiveType score{ vpvs(stack, principalVariation, i, heuristics, this->output()) };
					uint64_t nodeCount{ heuristics.nodeCount() };
					this->output() << static_cast<int>(i + 1) << ": " << std::setw(12) << score << " - " << variationToString(stack, principalVariation) << std::endl;
					this->output() << heuristics.toString();
					this->output() << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else if (token == "debug-pvs")
			{
				this->output() << std::endl;
				depthType depth = parser::parseInt(remainder);
				for (depthType i = -1; i <= depth - 1; i++)
				{
					variationType principalVariation;
					heuristicsType heuristics;
					stackType stack{ stackType(this->position(), this->history(), this->position().movingPlayer()) };
					objectiveType score{ pvs(stack, principalVariation, i, heuristics, this->output()) };
					uint64_t nodeCount{ heuristics.nodeCount() };
					this->output() << static_cast<int>(i + 1) << ": " << std::setw(12) << score << " - " << variationToString(stack, principalVariation) << std::endl;
					this->output() << heuristics.toString();
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