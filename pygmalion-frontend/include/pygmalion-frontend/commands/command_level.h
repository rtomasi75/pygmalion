namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_level :
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
			if ((this->front().isXBoard()) && (token == "level"))
			{
				std::string mps;
				std::string remainder2;
				parser::parseToken(remainder, mps, remainder2);
				if (mps != "")
				{
					std::string basetime;
					std::string increment;
					parser::parseToken(remainder2, basetime, increment);
					if (basetime != "" && increment != "")
					{
						int movecount = parser::parseInt(mps);
						int incrementseconds = parser::parseInt(increment);
						std::chrono::seconds baseseconds = parser::parseDuration(basetime);
						this->front().setTimeControl(movecount, baseseconds, std::chrono::seconds(incrementseconds));
					}
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "LEVEL";
		}
	};

}