namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_ucinewgame :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((this->front().isUCI()) && (cmd == "ucinewgame"))
			{
				this->mechanicsEngine().history().clear();
				this->dynamicsEngine().feedback().reset();
				this->searchEngine().heuristics().clear();
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "UCINEWGAME";
		}
	};

}