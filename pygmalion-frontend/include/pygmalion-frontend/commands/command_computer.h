namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_computer :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "computer")&& this->front().isXBoard())
			{
				this->front().playingComputer() = true;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "COMPUTER";
		}
	};

}