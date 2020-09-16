namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugPieces :
		public pygmalion::state::command<DESCRIPTION_STATE, BOARD>
	{
	public:
		using boardType = BOARD;
		using descriptorState = DESCRIPTION_STATE;
#include "../include_state.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-pieces")
			{
				this->output() << std::endl;
				for (const auto player : playerType::range)
				{
					this->output() << "  player " << boardType::playerToString(player) << ":";
					for (const auto piece : pieceType::range)
						this->output() << " " << boardType::pieceToString(piece, player);
					this->output() << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
	};

}