namespace pygmalion::chess::dynamics
{
	class command_debugMoveStats :
		public pygmalion::dynamics::command<descriptor_dynamics, generator>
	{
	public:
		using generatorType = generator;
		using stackType = typename generatorType::stackType;
		using descriptorDynamics = descriptor_dynamics;
#include <pygmalion-dynamics/include_dynamics.h>
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-movestats")
			{
				this->output() << std::endl;
#if defined(PYGMALION_MOVESTATISTICS)
				for (size_t i = 0; i < moveType::countChannels; i++)
				{
					this->output() << moveType::channel(i) << ": \t" << parser::valueToString(moveType::statistics(i), "") << std::endl;
				}
#else
				this->output() << "ERROR: not supported."<< std::endl;
#endif
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-MOVESTATS";
		}
	};

}