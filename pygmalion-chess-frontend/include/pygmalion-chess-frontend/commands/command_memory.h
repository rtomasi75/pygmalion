namespace pygmalion::chess::frontend
{
#if defined(PYGMALION_WB2)
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_memory :
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
			if ((this->front().isXBoard()) && (token == "memory"))
			{
				std::int64_t sizeInMegaBytes = parser::parseInt(remainder);
				std::int64_t sizeInBytes = sizeInMegaBytes * 1024 * 1024;
				this->frontendEngine().resizeHashTables(sizeInBytes);
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "MEMORY";
		}
		virtual void getXBoardFeatures(std::deque<std::string>& optionList) const noexcept override
		{
			const std::string feature{ "memory=1" };
			optionList.emplace_back(feature);
		}
	};
#endif
}