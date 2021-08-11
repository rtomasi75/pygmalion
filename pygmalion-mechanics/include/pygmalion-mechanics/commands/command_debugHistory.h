namespace pygmalion::mechanics
{
	template<typename DESCRIPTION_MECHANICS, typename MOTOR>
	class command_debugHistory :
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
			if (token == "debug-history")
			{
				this->output() << std::endl;
				for (size_t i = 0; i < this->mechanicsEngine().history().length(); i++)
				{
					this->output() << std::setw(4) << i << " " << std::setw(8) << std::hex << static_cast<std::uint64_t>(this->mechanicsEngine().history().board(i).hash()) << " " << std::setw(8) << motorType::moveToString(this->mechanicsEngine().history().board(i), this->mechanicsEngine().history().movebits(i)) << std::endl;
				}
				this->output() << std::endl;
				this->output() << std::setw(8) << std::hex << static_cast<std::uint64_t>(this->position().hash()) << (this->mechanicsEngine().history().occurs(this->position(), 1) ? " repeating, " : " not repeating, ");
				this->output() << (this->mechanicsEngine().history().occurs(this->position(), 2) ? "repeating twice" : "not repeating twice");
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-HISTORY";
		}
	};

}