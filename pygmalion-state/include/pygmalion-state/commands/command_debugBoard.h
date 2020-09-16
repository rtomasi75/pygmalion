namespace pygmalion::state
{
	template<typename DESCRIPTION_STATE, typename BOARD>
	class command_debugBoard :
		public pygmalion::state::command<DESCRIPTION_STATE, BOARD>
	{
	public:
		using boardType = BOARD;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-board")
			{
				this->output() << std::endl;
				for (const auto r : rankType::range)
				{
					const rankType rank{ -r };
					this->output() << boardType::rankToString(rank) << "|";
					for (const auto file : fileType::range)
					{
						const squareType square{ rank & file };
						if (this->position().totalOccupancy()[square])
						{
							const pieceType piece{ this->position().getPiece(square) };
							const playerType player{ this->position().getPlayer(square) };
							this->output() << boardType::pieceToString(piece, player);
						}
						else
							this->output() << ".";
					}
					this->output() << std::endl;
				}
				this->output() << "-+";
				for (const auto file : fileType::range)
				{
					this->output() << "-";
				}
				this->output() << std::endl;
				this->output() << " |";
				for (const auto file : fileType::range)
				{
					this->output() << boardType::fileToString(file);
				}
				this->output() << std::endl;
				this->output() << std::endl;
				this->output() << "Flags:" << std::endl;
				for (const auto flag : flagType::range)
				{
					if (this->position().checkFlag(flag))
						this->output() << boardType::flagToString(flag);
					else
						this->output() << "_";
				}
				this->output() << std::endl;
				this->output() << std::endl;
				this->output() << "Player " << boardType::playerToString(this->position().movingPlayer()) << " is on the move." << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
	};

}