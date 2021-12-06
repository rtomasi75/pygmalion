namespace pygmalion::chess::dynamics
{
	class command_debugCheck :
		public pygmalion::dynamics::command<descriptor_dynamics, generator>
	{
	public:
		using generatorType = generator;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = descriptor_dynamics;
#include <pygmalion-dynamics/include_dynamics.h>
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
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), &context, this->stateEngine().materialTable(), this->dynamicsEngine().delta()) };
					if (stack.isPositionCritical())
					{
						movebitsType moveBits;
						if (stack.nextMove(moveBits))
							this->output() << "Check." << std::endl;
						else
							this->output() << "Checkmate." << std::endl;
					}
					else
						this->output() << "Not in check." << std::endl;
				}
				else
					this->template process<PLAYER + 1>();
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override;
		virtual std::string help() noexcept override
		{
			return "DEBUG-CHECK";
		}
	};

}