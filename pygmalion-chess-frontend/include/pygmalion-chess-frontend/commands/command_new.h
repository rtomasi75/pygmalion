namespace pygmalion::chess::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_new :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include <pygmalion-frontend/include_frontend.h>
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "new") && this->front().isXBoard())
			{
				this->stateEngine().currentGame().initialize();
				this->mechanicsEngine().history().clear();
				this->front().clearDepthLimit();
				this->front().clearTimeLimit();
				this->front().forceMode() = false;
				this->front().enginePlayer() = descriptorFrontend::blackPlayer;
				for (const auto pl : playerType::range)
				{
					this->searchEngine().currentGame().playerClock(pl).stop();
					this->searchEngine().currentGame().playerClock(pl).set(std::chrono::duration_cast<std::chrono::microseconds>(this->front().baseTime()));
				}
				this->output() << std::endl;
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