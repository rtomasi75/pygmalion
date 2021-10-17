namespace pygmalion::frontend
{
#if defined(PYGMALION_UCI)
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_stop :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	private:
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "stop") && this->front().isUCI())
			{
				bool analyzeMode{ this->front().analyzeMode() };
				this->frontendEngine().currentGame().playerClock(this->frontendEngine().currentGame().position().movingPlayer()).stop();
				if (analyzeMode)
					this->frontendEngine().stopAnalysis();
				else
				{
					this->frontendEngine().ponderHit();
					this->frontendEngine().cancelMove();
				}
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "STOP";
		}
	};
#endif
}