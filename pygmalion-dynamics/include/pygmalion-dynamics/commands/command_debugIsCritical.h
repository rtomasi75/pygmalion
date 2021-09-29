namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugIsCritical :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		using stackType = typename generatorType::stackType;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
		using movegenFeedback = typename generatorType::movegenFeedback;
#include "../include_dynamics.h"
	private:
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-iscritical")
			{
				this->output() << std::endl;
				std::string remainder2;
				parser::parseTokenCaseSensitive(remainder, token, remainder2);
				movebitsType movebits;
				if (motorType::parseMove(this->position(), token, movebits))
				{
					typename generatorType::contextType context;
					stackType stack{ stackType(this->position(),this->history(), this->position().movingPlayer(), &context) };
					if (generatorType::isMoveCritical(stack, movebits))
						this->output() << generatorType::moveToString(stack, movebits, this->history().length()) << " is a critical move" << std::endl;
					else
						this->output() << generatorType::moveToString(stack, movebits, this->history().length()) << " is NOT a critical move" << std::endl;
				}
				else
					this->output() << token << " is not a possible move." << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-ISCRITICAL";
		}
	};

}