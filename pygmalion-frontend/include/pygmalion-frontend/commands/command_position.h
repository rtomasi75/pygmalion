namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_position :
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
					std::string remainder2;
					std::string token;
					parser::parseToken(remainder, token, remainder2);
					this->mechanicsEngine().history().clear();
					if (token == "startpos")
					{
						this->stateEngine().currentGame().position().initialize();
					}
					else if (token == "fen")
					{
						std::string fen1;
						std::string fen2;
						std::string fen3;
						std::string fen4;
						std::string fen5;
						std::string fen6;
						parser::parseToken(remainder2, fen1, remainder);
						parser::parseToken(remainder, fen2, remainder2);
						parser::parseToken(remainder2, fen3, remainder);
						parser::parseToken(remainder, fen4, remainder2);
						parser::parseToken(remainder2, fen5, remainder);
						parser::parseToken(remainder, fen6, remainder2);
						std::string fen = fen1 + " " + fen2 + " " + fen3 + " " + fen4 + " " + fen5 + " " + fen6;
						if (!this->stateEngine().currentGame().position().setPositionString(fen))
						{
							return;
						}
					}
					this->stateEngine().positionChanged();
					while (remainder2 != "")
					{
						parser::parseTokenCaseSensitive(remainder2, token, remainder);
						remainder2 = remainder;
						movebitsType movebits;
						if (motorType::parseMove(this->position(), token, movebits))
						{
							this->mechanicsEngine().makeMove(movebits);
						}
						else
							return;
					}
					if (analyzeMode)
						this->template startAnalysis<0>();
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
			if ((this->front().isUCI()) && (token == "position"))
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