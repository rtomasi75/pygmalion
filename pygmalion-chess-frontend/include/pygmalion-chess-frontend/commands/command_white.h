namespace pygmalion::chess::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONTEND>
	class command_white :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONTEND>
	{
	public:
		using frontendType = FRONTEND;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include <pygmalion-frontend/include_frontend.h>
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "white")&& this->front().isXBoard())
			{
				this->front().enginePlayer() = blackPlayer;
				this->searchEngine().game().position().movingPlayer() = whitePlayer;
				for (const auto pl : playerType::range)
				{
					this->searchEngine().game().playerClock(pl).stop();
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "WHITE";
		}
	};

}