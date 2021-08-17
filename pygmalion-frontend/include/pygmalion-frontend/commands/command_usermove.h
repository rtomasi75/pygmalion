namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONTEND>
	class command_usermove :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONTEND>
	{
	public:
		using frontendType = FRONTEND;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			movebitsType movebits;
			std::string token{ cmd };
			if (motorType::parseMove(this->position(), token, movebits) && this->front().isXBoard())
			{
				this->frontendEngine().currentGame().playerClock(this->frontendEngine().currentGame().position().movingPlayer()).stop();
				this->frontendEngine().doMove(movebits);
				this->output() << std::endl;
				const typename descriptorFrontend::stackType stack{ typename descriptorFrontend::stackType(this->position(), this->history(),  this->position().movingPlayer()) };
				const gamestateType result{ evaluatorType::earlyResult(stack) };
				if (!gamestateType::isOpen(result))
				{
					this->output() << "result " << frontType::gamestateToString(this->frontendEngine().currentGame().position(), result) << std::endl;
					return true;
				}
				if (gamestateType::isOpen(this->position().arbitration()) && (!this->front().forceMode()))
				{
					this->frontendEngine().thinkMove();
				}
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "USERMOVE";
		}
	};

}