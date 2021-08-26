namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugMoves :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		using stackType = typename generatorType::stackType;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
#include "../include_dynamics.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-moves")
			{
				this->output() << std::endl;
				movelistType moves;
				stackType stack(this->position(), this->history(), this->position().movingPlayer());
				movebitsType movebits;
				bool hasMoves{ false };
				while (stack.nextMove(movebits, this->history().length(), this->feedback()))
				{
					hasMoves = true;
					this->output() << motorType::move().toString(this->position(), movebits) << "\t";
					this->output() << std::endl;
				}
				if (!hasMoves)
				{
					this->output() << "(no moves possible)" << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-MOVES";
		}
	};

}