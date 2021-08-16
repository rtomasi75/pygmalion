namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONTEND>
	class command_hard :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONTEND>
	{
	public:
		using frontendType = FRONTEND;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "hard")&& this->front().isXBoard())
			{
				this->front().ponderMode() = true;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "HARD";
		}
	};

}