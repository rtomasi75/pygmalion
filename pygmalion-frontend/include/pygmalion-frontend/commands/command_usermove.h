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
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
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
					this->front().clearHintMove();
					if (analyzeMode)
						this->frontendEngine().stopAnalysis();
					else
						this->frontendEngine().cancelMove();
					this->frontendEngine().currentGame().playerClock(this->frontendEngine().currentGame().position().movingPlayer()).stop();
					typename generatorType::contextType context;
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), &context) };
					if (generatorType::isMoveLegal(stack, movebits))
					{
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
					{
						const std::string moveString{ motorType::moveToString(this->position(), movebits) };
						this->output() << "Illegal move: " << moveString << std::endl;
						if (gamestateType::isOpen(this->position().arbitration()) && (!this->front().forceMode()))
						{
							if (analyzeMode)
								this->frontendEngine().template startAnalysis<static_cast<size_t>(player)>();
							else
								this->frontendEngine().template thinkMove<static_cast<size_t>(player)>();
						}
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
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			size_t count{ 0 };
			if (token == "usermove")
			{
				if (motorType::parseMove(this->position(), remainder, movebits, count) && this->front().isXBoard())
				{
					this->template process<0>(movebits);
					return true;
				}
				else
				{
					this->output() << "Illegal move: " << remainder << std::endl;
					return true;
				}
			}
			else
			{
				if (motorType::parseMove(this->position(), token, movebits, count) && this->front().isXBoard())
				{
					this->template process<0>(movebits);
					return true;
				}
				else
					return false;
			}
		}
		virtual void getXBoardFeatures(std::deque<std::string>& optionList) const noexcept override
		{
			const std::string feature{ "usermove=1" };
			optionList.emplace_back(feature);
		}
		virtual std::string help() noexcept override
		{
			return "USERMOVE";
		}
	};

}