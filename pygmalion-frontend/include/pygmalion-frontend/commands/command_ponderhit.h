namespace pygmalion::frontend
{
#if defined(PYGMALION_UCI)
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_ponderhit :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
	private:
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			movebitsType movebits;
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			size_t count{ 0 };
			if (cmd == "ponderhit"&&this->front().isUCI())
			{
				this->frontendEngine().ponderHit();
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "PONDERHIT";
		}
	};
#endif
}