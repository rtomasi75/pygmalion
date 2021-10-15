namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_setBoard :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include <pygmalion-frontend/include_frontend.h>
	private:
		template<size_t PLAYER>
		void startAnalysis() noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					this->frontendEngine().template startAnalysis<PLAYER>();
				}
				else
					this->template startAnalysis<PLAYER + 1>();
			}
			else
				PYGMALION_ASSERT(false);
		}

		template<size_t PLAYER>
		void process(std::string remainder) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					std::string error;
					bool analyzeMode{ this->front().analyzeMode() };
					if (analyzeMode)
						this->frontendEngine().stopAnalysis();
					if (this->position().setPositionString(remainder))
					{
						this->stateEngine().positionChanged();
						if (analyzeMode)
							this->template startAnalysis<0>();
					}
					else
					{
						this->output() << "Error: Invalid position." << std::endl;
					}
				}
				else
					this->template process<PLAYER + 1>(remainder);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if ((token == "setboard") && (this->front().isXBoard()))
			{
				this->output() << std::endl;
				this->template process<0>(remainder);
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual void getXBoardFeatures(std::deque<std::string>& optionList) const noexcept override
		{
			const std::string feature{ "setboard=1" };
			optionList.emplace_back(feature);
		}
		virtual std::string help() noexcept override
		{
			return "SETBOARD";
		}
	};

}