namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_go :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	private:
		template<size_t PLAYER>
		void process() noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					this->front().forceMode() = false;
					this->front().enginePlayer() = player;
					this->frontendEngine().template thinkMove<PLAYER>();
					this->output() << std::endl;
				}
				else
					this->template process<PLAYER + 1>();
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "go") && this->front().isXBoard())
			{
				this->template process<0>();
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "GO";
		}
	};

}