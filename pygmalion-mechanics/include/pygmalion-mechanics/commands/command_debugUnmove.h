namespace pygmalion::mechanics
{
	template<typename DESCRIPTION_MECHANICS, typename MOTOR>
	class command_debugUnmove :
		public pygmalion::mechanics::command<DESCRIPTION_MECHANICS, MOTOR>
	{
	public:
		using motorType = MOTOR;
		using descriptorMechanics = DESCRIPTION_MECHANICS;
#include "../include_mechanics.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-unmove")
			{
				this->output() << std::endl;
				if (this->mechanicsEngine().history().length() > 0)
				{
					this->output() << "restored previous position." << std::endl;
					this->mechanicsEngine().unmakeMove();
				}
				else
					this->output() << "no move to undo." << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-UNMOVE";
		}
	};

}