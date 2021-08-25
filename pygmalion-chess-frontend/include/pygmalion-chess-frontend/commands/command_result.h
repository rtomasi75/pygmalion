namespace pygmalion::chess::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_result :
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
			if ((this->front().isXBoard()) && (token == "result"))
			{
				std::string remainder2;
				std::string result;
				parser::parseToken(remainder, token, remainder2);
				if (result == "1-0")
					this->position().arbitration() = gamestateType::win(0);
				else if (result == "0-1")
					this->position().arbitration() = gamestateType::win(1);
				else if (result == "1/2-1/2")
					this->position().arbitration() = gamestateType::draw();
				else if (result == "*")
					this->position().arbitration() = gamestateType::draw();
				else
					return false;
				this->frontendEngine().cancelMove();
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "RESULT";
		}
	};
}