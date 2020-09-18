namespace pygmalion::mechanics
{
	template<typename DESCRIPTION_MECHANICS, typename MOTOR>
	class command_debugMechanics :
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
			if (token == "debug-mechanics")
			{
				this->output() << std::endl;
				this->output() << moveType::name() << std::endl;
				this->output() << std::endl;
				this->output() << "movebits: " << std::setw(4) << sizeof(movebitsType) << " = " << sizeof(movebitsType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "movedata: " << std::setw(4) << sizeof(movedataType) << " = " << sizeof(movedataType) * CHAR_BIT << "bit" << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
	};

}