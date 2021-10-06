namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_analyze :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	private:
		template<size_t PLAYER>
		void processAnalyze() noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					this->front().enginePlayer() = player;
					this->frontendEngine().template startAnalysis<PLAYER>();
					this->output() << std::endl;
				}
				else
					this->template processAnalyze<PLAYER + 1>();
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "analyze") && this->front().isXBoard())
			{
				this->template processAnalyze<0>();
				return true;
			}
			else if (this->front().analyzeMode() && this->front().isXBoard())
			{
				if (cmd == "exit")
				{
					this->frontendEngine().stopAnalysis();
					return true;
				}
				else if (cmd == ".")
				{
					this->output() << "stat01: ";
					const std::chrono::milliseconds milliseconds{ std::chrono::duration_cast<std::chrono::milliseconds>(this->frontendEngine().heuristics().duration()) };
					const int centiseconds{ static_cast<int>(milliseconds.count() / 10) };
					this->output() << centiseconds << " ";
					this->output() << this->frontendEngine().heuristics().nodeCount() << " ";
					this->output() << static_cast<std::uint64_t>(this->frontendEngine().currentDepth()) << " ";
					this->output() << static_cast<std::uint64_t>(this->frontendEngine().countMoves()-this->frontendEngine().currentMove()) << " ";
					this->output() << static_cast<std::uint64_t>(this->frontendEngine().countMoves());
					this->output() << std::endl;
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "ANALYZE";
		}
	};

}