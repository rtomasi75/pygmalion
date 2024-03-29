namespace pygmalion::chess::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_black :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include <pygmalion-frontend/include_frontend.h>
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "black")&& this->front().isXBoard())
			{
				this->frontendEngine().cancelMove();
				this->front().enginePlayer() = descriptorFrontend::whitePlayer;
				this->searchEngine().currentGame().position().movingPlayer() = descriptorFrontend::blackPlayer;
				for (const auto pl : playerType::range)
				{
					this->searchEngine().currentGame().playerClock(pl).stop();
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "BLACK";
		}
	};

}