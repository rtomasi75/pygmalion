namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONTEND>
	class command_debugFrontend :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONTEND>
	{
	public:
		using frontendType = FRONTEND;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-frontend")
			{
				this->output() << std::endl;
				this->output() << "frontend: " << std::setw(4) << sizeof(frontendType) << " = " << sizeof(frontendType) * CHAR_BIT << "bit" << std::endl;
				this->output() << std::endl;
				this->output() << "xboard mode: " << (this->front().isXBoard() ? "enabled" : "disabled") << std::endl;
				this->output() << "random mode: " << (this->front().isRandom() ? "enabled" : "disabled") << std::endl;
				this->output() << "protocol version: " << this->front().protocolVersion() << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-FRONTEND";
		}
	};

}