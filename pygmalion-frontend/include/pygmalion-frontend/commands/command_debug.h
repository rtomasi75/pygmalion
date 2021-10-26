namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_debug :
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
			if ((this->front().isUCI()) && (token == "debug"))
			{
				std::string remainder2;
				parser::parseToken(remainder, token, remainder2);
				if (token == "on")
				{
					this->front().isDebug() = true;
				}
				else if (token == "off")
				{
					this->front().isDebug() = false;
				}
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG";
		}
	};
}