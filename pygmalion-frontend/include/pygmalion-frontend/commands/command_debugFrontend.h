namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_debugFrontend :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-frontend")
			{
				this->output() << std::endl;
				this->output() << "frontend: " << std::setw(4) << sizeof(frontType) << " = " << sizeof(frontType) * CHAR_BIT << "bit" << std::endl;
				this->output() << std::endl;
				this->output() << "UCI mode:         " << (this->front().isUCI() ? "enabled" : "disabled") << std::endl;
				this->output() << "opponent name:    " << this->front().opponentName() << std::endl;
				this->output() << "against computer: " << (this->front().playingComputer() ? "yes" : "no") << std::endl;
				if (this->front().isDepthLimited())
					this->output() << "depth limit:      " << static_cast<int>(this->front().depthLimit()) << std::endl;
				else
					this->output() << "depth limit:      none" << std::endl;
				if (this->front().isTimeLimited())
					this->output() << "time limit:       " << this->front().timeLimit().count() << "s" << std::endl;
				else
					this->output() << "time limit:       none" << std::endl;
				this->output() << "time control:     " << this->frontendEngine().currentGame().movesPerTimeControl() << " ";
				for (const auto pl : playerType::range)
				{
					this->output() << this->frontendEngine().currentGame().baseTime(pl).count() << "ms+" << this->frontendEngine().currentGame().incrementTime(pl).count() << "ms ";
				}
				this->output() << std::endl;
				this->output() << std::endl;
				for (const auto pl : playerType::range)
				{
					this->output() << "player " << pl.toShortString() << " rating: " << static_cast<int>(this->front().playerRating(pl)) << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-FRONT";
		}
	};

}