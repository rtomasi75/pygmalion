namespace pygmalion::mechanics
{
	template<typename DESCRIPTION_MECHANICS, typename MOTOR>
	class command_debugMove :
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
			if (token == "debug-move")
			{
				this->output() << std::endl;
				std::string remainder2;
				parser::parseTokenCaseSensitive(remainder, token, remainder2);
				movebitsType movebits;
				size_t count{ 0 };
				if (motorType::parseMove(this->position(), token, movebits, count))
				{
					this->output() << "performed move " << motorType::moveToString(this->position(), movebits) << std::endl;
					this->mechanicsEngine().makeMove(movebits);
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
			return "DEBUG-MOVE";
		}
	};

}