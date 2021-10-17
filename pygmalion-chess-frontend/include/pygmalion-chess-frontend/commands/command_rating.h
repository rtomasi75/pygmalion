namespace pygmalion::chess::frontend
{
#if defined(PYGMALION_WB2)
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_rating :
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
			if ((this->front().isXBoard()) && (token == "rating"))
			{
				std::string rating1;
				std::string rating2;
				parser::parseToken(remainder, rating1, rating2);
				const std::uint16_t ratingEngine{ static_cast<std::uint16_t>(parser::parseInt(rating1)) };
				const std::uint16_t ratingOpponent{ static_cast<std::uint16_t>(parser::parseInt(rating2)) };
				this->front().playerRating(this->front().enginePlayer()) = ratingEngine;
				this->front().playerRating(this->front().enginePlayer().next()) = ratingOpponent;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "RATING";
		}
	};
#endif
}