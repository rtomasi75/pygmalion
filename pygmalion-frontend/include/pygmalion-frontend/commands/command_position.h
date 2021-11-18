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
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if ((this->front().isUCI()) && (token == "position"))
			{
				this->frontendEngine().waitForSearchToFinish();
				std::string error;
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
					parser::parseTokenCaseSensitive(remainder2, fen1, remainder);
					parser::parseTokenCaseSensitive(remainder, fen2, remainder2);
					parser::parseTokenCaseSensitive(remainder2, fen3, remainder);
					parser::parseTokenCaseSensitive(remainder, fen4, remainder2);
					parser::parseTokenCaseSensitive(remainder2, fen5, remainder);
					parser::parseTokenCaseSensitive(remainder, fen6, remainder2);
					std::string fen = fen1 + " " + fen2 + " " + fen3 + " " + fen4 + " " + fen5 + " " + fen6;
					if (!this->stateEngine().currentGame().position().setFen(fen))
					{
						return false;
					}
					this->stateEngine().positionChanged();
				}
				parser::parseToken(remainder2, token, remainder);
				if (token == "moves")
				{
					remainder2 = remainder;
					while (remainder2 != "")
					{
						parser::parseTokenCaseSensitive(remainder2, token, remainder);
						remainder2 = remainder;
						movebitsType movebits;
						size_t count{ 0 };
						if (motorType::parseMove(this->position(), token, movebits, count))
						{
							this->frontendEngine().makeMove(movebits);
						}
						else
							return false;
					}
				}
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "POSITION";
		}
	};
}