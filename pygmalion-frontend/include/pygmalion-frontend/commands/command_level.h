namespace pygmalion::frontend
{
#if defined(PYGMALION_WB2)
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
						std::array<durationType, countPlayers> basesecondsOfPlayers{ arrayhelper::make <countPlayers, durationType>(std::chrono::duration_cast<durationType>(baseseconds)) };
						std::array<durationType, countPlayers> incrementOfPlayers{ arrayhelper::make <countPlayers, durationType>(std::chrono::milliseconds(incrementseconds * 1000)) };
						this->frontendEngine().currentGame().setTimeControl(movecount, basesecondsOfPlayers, incrementOfPlayers);
						for (const auto pl : playerType::range)
						{
							this->searchEngine().currentGame().playerClock(pl).set(basesecondsOfPlayers[pl]);
						}
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
#endif
}