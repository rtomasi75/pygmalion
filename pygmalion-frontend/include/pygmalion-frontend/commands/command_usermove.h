namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_usermove :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	private:
		template<size_t PLAYER>
		void process(const movebitsType movebits) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					this->frontendEngine().cancelMove();
					this->frontendEngine().currentGame().playerClock(this->frontendEngine().currentGame().position().movingPlayer()).stop();
					this->frontendEngine().doMove(movebits);
					this->output() << std::endl;
					const typename descriptorFrontend::template stackType<PLAYER> stack{ typename descriptorFrontend::template stackType<PLAYER>(this->position(), this->history(), this->rootContext()) };
					bool allowStoreTT;
					const gamestateType result{ evaluatorType::template earlyResult<PLAYER, false>(stack, allowStoreTT) };
					if (!gamestateType::isOpen(result))
					{
						this->output() << "result " << frontType::gamestateToString(this->frontendEngine().currentGame().position(), result) << std::endl;
						return;
					}
					if (gamestateType::isOpen(this->position().arbitration()) && (!this->front().forceMode()))
					{
						this->frontendEngine().template thinkMove<static_cast<size_t>(player.next())>();
					}
				}
				else
					this->template process<PLAYER + 1>(movebits);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			movebitsType movebits;
			std::string token{ cmd };
			if (motorType::parseMove(this->position(), token, movebits) && this->front().isXBoard())
			{
				this->template process<0>(movebits);
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