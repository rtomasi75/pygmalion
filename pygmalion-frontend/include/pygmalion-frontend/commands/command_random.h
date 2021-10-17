namespace pygmalion::frontend
{
#if defined(PYGMALION_WB2)
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_random :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "random")&& this->front().isXBoard())
			{
				this->front().isRandom() = !this->front().isRandom();
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "RANDOM";
		}
	};
#endif
}