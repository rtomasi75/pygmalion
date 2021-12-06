namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugTacticalMoves :
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
					movelistType moves;
					typename generatorType::contextType context;
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), &context, this->stateEngine().materialTable(), this->dynamicsEngine().delta()) };
					movebitsType movebits;
					bool hasMoves{ false };
					while (stack.nextQSPhase1Move(movebits))
					{
						hasMoves = true;
						this->output() << motorType::move().toString(this->position(), movebits) << "\t";
						this->output() << std::endl;
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
			if (cmd == "debug-tacticalmoves")
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
			return "DEBUG-TACTICALMOVES";
		}
	};

}