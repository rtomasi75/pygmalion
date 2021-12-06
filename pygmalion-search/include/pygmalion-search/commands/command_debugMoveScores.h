namespace pygmalion::search
{
	template<typename DESCRIPTION_SEARCH, typename GAMETREE>
	class command_debugMoveScores :
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
		using nodeType = typename gametreeType::template nodeType<PLAYER>;
		template<size_t PLAYER>
		void process() noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					movelistType moves;
					typename generatorType::contextType context;
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), &context, this->stateEngine().materialTable(), this->dynamicsEngine().delta()) };
					signal terminate{ signal(false) };
					nodeType<static_cast<size_t>(static_cast<playerType>(PLAYER))> node(stack, terminate, this->searchEngine().heuristics(), this->searchEngine().history().length(), this->evaluationEngine().parameters());
					movebitsType movebits;
					bool hasMoves{ false };
					bool fromStack;
					this->output() << "Generated:" << std::endl;
					while (node.template nextMove<false, false>(0, movebits))
					{
						this->output() << "    ";
						hasMoves = true;
						this->output() << generatorType::moveToSAN(node.stack(), movebits) << "\t";
						if constexpr (staticMoveScores)
							this->output() << this->searchEngine().heuristics().staticMoveScore(node.stack(), movebits, this->searchEngine().history().length()) << "\t";
						if (node.lastMoveFromTT())
							this->output() << "hash move\t";
						else if (node.lastMoveIsTacticalKiller())
							this->output() << "tactical killer\t";
						else if (node.lastMoveIsKiller())
							this->output() << "quiet killer\t";
						else
						{
							const stageType stage{ node.stack().lastNormalStage() };
							const passType pass{ node.stack().lastNormalPass() };
							const std::string movestring{ generatorType::moveToSAN(node.stack(), movebits) };
							this->output() << movestring << "\t";
							this->output() << node.stack().lastNormalScore() << "\t";
							this->output() << generatorType::passToString(stage, pass) << "\t";
						}
						this->output() << std::endl;
						this->output() << std::endl;
						this->flushOutput();
					}
					if (!hasMoves)
					{
						this->output() << "(no moves possible)" << std::endl;
					}
				}
				else
					this->template process<PLAYER + 1>();
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-movescores")
			{
				this->output() << std::endl;
				this->template process<0>();
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-MOVESCORES";
		}
	};

}