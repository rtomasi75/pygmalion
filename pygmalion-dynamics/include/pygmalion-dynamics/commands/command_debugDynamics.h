namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugDynamics :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		using stackType = typename generatorType::stackType;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
#include "../include_dynamics.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-dynamics")
			{
				this->output() << std::endl;
				this->output() << "movelist: " << std::setw(4) << sizeof(movelistType) << " = " << sizeof(movelistType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "index:    " << std::setw(4) << sizeof(indexType) << " = " << sizeof(indexType) * CHAR_BIT << "bit" << std::endl;
				this->output() << "stack:    " << std::setw(4) << sizeof(stackType) << " = " << sizeof(stackType) * CHAR_BIT << "bit" << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
	};

}