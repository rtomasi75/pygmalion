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
				constexpr const playerType nextPlayer{ player.next() };
				if (player == this->position().movingPlayer())
				{
					bool analyzeMode{ this->front().analyzeMode() };
					this->front().hasHint() = false;
					if (analyzeMode)
						this->frontendEngine().stopAnalysis();
					else
						this->frontendEngine().cancelMove();
					this->frontendEngine().currentGame().playerClock(this->frontendEngine().currentGame().position().movingPlayer()).stop();
					this->frontendEngine().doMove(movebits);
					this->output() << std::endl;
					const typename descriptorFrontend::template stackType<static_cast<size_t>(nextPlayer)> stack{ typename descriptorFrontend::template stackType<static_cast<size_t>(nextPlayer)>(this->position(), this->history(), this->rootContext()) };
					bool allowStoreTT;
					const gamestateType result{ evaluatorType::template earlyResult<static_cast<size_t>(nextPlayer), false>(stack, allowStoreTT) };
					if (!gamestateType::isOpen(result))
					{
						this->output() << "result " << frontType::gamestateToString(this->frontendEngine().currentGame().position(), result) << std::endl;
						return;
					}
					if (gamestateType::isOpen(this->position().arbitration()) && (!this->front().forceMode()))
					{
						if (analyzeMode)
							this->frontendEngine().template startAnalysis<static_cast<size_t>(nextPlayer)>();
						else
							this->frontendEngine().template thinkMove<static_cast<size_t>(nextPlayer)>();
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