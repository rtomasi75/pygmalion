namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugPasses :
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
			if (cmd == "debug-passes")
			{
				this->output() << std::endl;
				this->output() << "move passes:" << std::endl;
				for (size_t i = 0; i < countPasses; i++)
				{
					this->output() << "    " << std::setw(3) << i << std::setw(8) << this->dynamicsEngine().feedback().counter(i, this->history().length()) << std::setw(12) << this->dynamicsEngine().feedback().score(i, this->history().length()) << " " << generatorType::passToString(this->dynamicsEngine().feedback().index(i, this->history().length())) << std::endl;
				}
				this->output() << std::endl;
				this->output() << "tactical passes:" << std::endl;
				for (size_t i = 0; i < countTacticalPasses; i++)
				{
					this->output() << "    " << std::setw(3) << i << std::setw(8) << this->dynamicsEngine().feedback().tacticalCounter(i, this->history().length()) << std::setw(12) << this->dynamicsEngine().feedback().tacticalScore(i, this->history().length()) << " " << generatorType::tacticalPassToString(this->dynamicsEngine().feedback().tacticalIndex(i, this->history().length())) << std::endl;
				}
				this->output() << std::endl;
				this->output() << "critical passes:" << std::endl;
				for (size_t i = 0; i < countCriticalPasses; i++)
				{
					this->output() << "    " << std::setw(3) << i << std::setw(8) << this->dynamicsEngine().feedback().counter(i, this->history().length()) << std::setw(12) << this->dynamicsEngine().feedback().score(i, this->history().length()) << " " << generatorType::criticalPassToString(this->dynamicsEngine().feedback().index(i, this->history().length())) << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-PASSES";
		}
	};

}