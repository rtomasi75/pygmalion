namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONTEND>
	class command_debugClocks :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONTEND>
	{
	public:
		using frontendType = FRONTEND;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-clocks")
			{
				for (const auto pl : playerType::range)
				{
					this->output() << "player " << boardType::playerToString(pl) << " time left: " << this->searchEngine().currentGame().playerClock(pl).timeRemaining().count() << "mcs" << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-CLOCKS";
		}
	};

}