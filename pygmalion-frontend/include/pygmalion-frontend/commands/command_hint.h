namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_hint :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if ((cmd == "hint") && this->front().isXBoard())
			{
				if (this->front().hasHint())
				{
					const std::string moveString{ motorType::moveToString(this->position(), this->front().hintMove()) };
					this->output() << "Hint: " << moveString << std::endl;
				}
				else
					this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "HINT";
		}
	};

}