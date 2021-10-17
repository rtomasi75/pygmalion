namespace pygmalion::frontend
{
#if defined(PYGMALION_WB2)
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_ping :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if ((token == "ping") && this->front().isXBoard())
			{
				this->output() << "pong " << remainder << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "PING";
		}
		virtual void getXBoardFeatures(std::deque<std::string>& optionList) const noexcept override
		{
			const std::string feature{ "ping=1" };
			optionList.emplace_back(feature);
		}

	};
#endif
}