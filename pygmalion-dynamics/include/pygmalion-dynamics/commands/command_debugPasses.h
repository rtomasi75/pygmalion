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
					this->dynamicsEngine().feedback().expandToDepth(this->history().length());
					this->dynamicsEngine().feedback().sortPasses(this->history().length());
					//				this->dynamicsEngine().feedback().sortPasses(this->history().length());
					typename generatorType::contextType context;
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), &context) };
					this->output() << std::endl;
					this->output() << "normal passes:" << std::endl;
					for (size_t stage = 0; stage < stack.normalStagesCount(); stage++)
					{
						for (size_t i = 0; i < stack.normalPassesCount(stage); i++)
						{
							const auto index{ this->dynamicsEngine().feedback().index(stage,i, this->history().length()) };
							auto& fb{ this->dynamicsEngine().feedback() };
							this->output() << "    " << std::setw(3) << stage << ", " << std::setw(3) << i << std::setw(8) << fb.counterRaw(stack.normalStage(stage), index, this->history().length()) << std::setw(12) << fb.scoreRaw(stack.normalStage(stage), index, this->history().length()) << " " << generatorType::passToString(stack.normalStage(stage), stack.normalPass(fb, stage, i)) << std::endl;
						}
					}
					this->output() << std::endl;
				/*	this->output() << "tactical passes:" << std::endl;
					for (size_t stage = 0; stage < stack.tacticalStagesCount(); stage++)
					{
						for (size_t i = 0; i < stack.tacticalPassesCount(stage); i++)
						{
							const auto index{ this->dynamicsEngine().feedback().index(stage,i, this->history().length()) };
							this->output() << "    " << std::setw(3) << stage << ", " << std::setw(3) << i << std::setw(8) << this->dynamicsEngine().feedback().counterRaw(stack.tacticalStage(stage), index, this->history().length()) << std::setw(12) << this->dynamicsEngine().feedback().scoreRaw(stack.tacticalStage(stage), index, this->history().length()) << " " << generatorType::passToString(stack.tacticalStage(stage), stack.tacticalPass(this->dynamicsEngine().feedback(), stage, i)) << std::endl;
						}
					}
					this->output() << std::endl;
					this->output() << "critical passes:" << std::endl;
					for (size_t stage = 0; stage < stack.criticalStagesCount(); stage++)
					{
						for (size_t i = 0; i < stack.criticalPassesCount(stage); i++)
						{
							const auto index{ this->dynamicsEngine().feedback().index(stage,i, this->history().length()) };
							this->output() << "    " << std::setw(3) << stage << ", " << std::setw(3) << i << std::setw(8) << this->dynamicsEngine().feedback().counterRaw(stack.criticalStage(stage), index, this->history().length()) << std::setw(12) << this->dynamicsEngine().feedback().scoreRaw(stack.criticalStage(stage), index, this->history().length()) << " " << generatorType::passToString(stack.criticalStage(stage), stack.criticalPass(this->dynamicsEngine().feedback(), stage, i)) << std::endl;
						}
					}
					this->output() << std::endl;*/
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