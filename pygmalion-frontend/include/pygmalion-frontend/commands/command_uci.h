namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_uci :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "uci")
			{
				this->front().isXBoard() = false;
				this->front().isUCI() = true;
				this->output() << "id name " << this->frontendEngine().version() << std::endl;
				this->output() << "id author " << this->frontendEngine().author() << std::endl;
				this->output() << "uciok" << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "UCI";
		}
	};

}