namespace pygmalion::chess::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONTEND>
	class command_new :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONTEND>
	{
	public:
		using frontendType = FRONTEND;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include <pygmalion-frontend/include_frontend.h>
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "new")&& this->front().isXBoard())
			{
				this->stateEngine().currentGame().initialize();
				this->mechanicsEngine().history().clear();
				this->front().clearDepthLimit();
				this->front().forceMode() = false;
				this->front().enginePlayer() = descriptorFrontend::blackPlayer;
				for (const auto pl : playerType::range)
				{
					this->searchEngine().currentGame().playerClock(pl).stop();
				}
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "NEW";
		}
	};

}