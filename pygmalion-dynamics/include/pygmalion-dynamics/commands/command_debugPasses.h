namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugPasses :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
#include "../include_dynamics.h"	
	private:
		template<size_t PLAYER>
		void process() noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					typename generatorType::contextType context;
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), &context) };
					this->output() << std::endl;
					this->output() << "normal passes:" << std::endl;
					for (size_t stage = 0; stage < stack.normalStagesCount(); stage++)
					{
						for (size_t i = 0; i < stack.normalPassesCount(stage); i++)
						{
							this->output() << "    " << std::setw(3) << stage << ", " << std::setw(3) << i << std::setw(8) << this->dynamicsEngine().feedback().counter(stack.normalStage(stage), stack.normalPass(this->dynamicsEngine().feedback(), stage, i), this->history().length()) << std::setw(12) << this->dynamicsEngine().feedback().score(stack.normalStage(stage), stack.normalPass(this->dynamicsEngine().feedback(), stage, i), this->history().length()) << " " << generatorType::passToString(stack.normalStage(stage), stack.normalPass(this->dynamicsEngine().feedback(), stage, i)) << std::endl;
						}
					}
					this->output() << std::endl;
					this->output() << "tactical passes:" << std::endl;
					for (size_t stage = 0; stage < stack.tacticalStagesCount(); stage++)
					{
						for (size_t i = 0; i < stack.tacticalPassesCount(stage); i++)
						{
							this->output() << "    " << std::setw(3) << stage << ", " << std::setw(3) << i << std::setw(8) << this->dynamicsEngine().feedback().counter(stack.tacticalStage(stage), stack.tacticalPass(this->dynamicsEngine().feedback(), stage, i), this->history().length()) << std::setw(12) << this->dynamicsEngine().feedback().score(stack.tacticalStage(stage), i, this->history().length()) << " " << generatorType::passToString(stack.tacticalStage(stage), stack.tacticalPass(this->dynamicsEngine().feedback(), stage, i)) << std::endl;
						}
					}
					this->output() << std::endl;
					this->output() << "critical passes:" << std::endl;
					for (size_t stage = 0; stage < stack.criticalStagesCount(); stage++)
					{
						for (size_t i = 0; i < stack.criticalPassesCount(stage); i++)
						{
							this->output() << "    " << std::setw(3) << stage << ", " << std::setw(3) << i << std::setw(8) << this->dynamicsEngine().feedback().counter(stack.criticalStage(stage), stack.criticalPass(this->dynamicsEngine().feedback(), stage, i), this->history().length()) << std::setw(12) << this->dynamicsEngine().feedback().score(stack.criticalStage(stage), i, this->history().length()) << " " << generatorType::passToString(stack.criticalStage(stage), stack.criticalPass(this->dynamicsEngine().feedback(), stage, i)) << std::endl;
						}
					}
					this->output() << std::endl;
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
			if (cmd == "debug-passes")
			{
				this->template process<0>();
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