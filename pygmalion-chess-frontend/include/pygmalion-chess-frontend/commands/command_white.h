namespace pygmalion::chess::frontend
{
#if defined(PYGMALION_WB2)
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_white :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include <pygmalion-frontend/include_frontend.h>
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "white")&& this->front().isXBoard())
			{
				this->frontendEngine().cancelMove();
				this->front().enginePlayer() = descriptorFrontend::blackPlayer;
				this->searchEngine().currentGame().position().movingPlayer() = descriptorFrontend::whitePlayer;
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
			return "WHITE";
		}
	};
#endif
}