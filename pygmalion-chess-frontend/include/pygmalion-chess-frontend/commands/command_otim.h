namespace pygmalion::chess::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_otim :
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
			if ((this->front().isXBoard()) && (token == "otim"))
			{
				const std::chrono::milliseconds timeRemaining{ 10 * parser::parseInt(remainder) };
				this->searchEngine().currentGame().playerClock(this->front().enginePlayer().next()).set(std::chrono::duration_cast<durationType>(timeRemaining));
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "OTIM";
		}
	};

}