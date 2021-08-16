namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONTEND>
	class command_debugFrontend :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONTEND>
	{
	public:
		using frontendType = FRONTEND;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-frontend")
			{
				this->output() << std::endl;
				this->output() << "frontend: " << std::setw(4) << sizeof(frontendType) << " = " << sizeof(frontendType) * CHAR_BIT << "bit" << std::endl;
				this->output() << std::endl;
				this->output() << "xboard mode:      " << (this->front().isXBoard() ? "enabled" : "disabled") << std::endl;
				this->output() << "protocol version: " << this->front().protocolVersion() << std::endl;
				this->output() << "opponent name:    " << this->front().opponentName() << std::endl;
				this->output() << "force mode:       " << (this->front().forceMode() ? "enabled" : "disabled") << std::endl;
				this->output() << "post mode:        " << (this->front().postMode() ? "enabled" : "disabled") << std::endl;
				this->output() << "ponder mode:      " << (this->front().ponderMode() ? "enabled" : "disabled") << std::endl;
				this->output() << "random mode:      " << (this->front().isRandom() ? "enabled" : "disabled") << std::endl;
				this->output() << "against computer: " << (this->front().playingComputer() ? "yes" : "no") << std::endl;
				if (this->front().isDepthLimited())
					this->output() << "depth limit:      " << static_cast<int>(this->front().depthLimit()) << std::endl;
				else
					this->output() << "depth limit:      none" << std::endl;
				if (this->front().isTimeLimited())
					this->output() << "time limit:       " << this->front().timeLimit().count() << "s" << std::endl;
				else
					this->output() << "time limit:       none" << std::endl;
				this->output() << "time control:     " << this->front().movesPerTimeControl() << " " << this->front().baseTime().count() << "s " << this->front().incrementTime().count() << "s" << std::endl;
				this->output() << "engine player:    " << boardType::playerToString(this->front().enginePlayer()) << std::endl;
				this->output() << std::endl;
				for (const auto pl : playerType::range)
				{
					this->output() << "player " << boardType::playerToString(pl) << " rating: " << static_cast<int>(this->front().playerRating(pl)) << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-FRONTEND";
		}
	};

}