namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugMaterialParameters :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
#include "../include_dynamics.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-materialparameters")
			{
				this->output() << std::endl;
				std::vector<scoreType> current;
				this->dynamicsEngine().materialTable().getParameters(current);
				std::vector<scoreType> standard;
				materialTableType::defaultParameters(standard);
				constexpr const size_t n{ materialTableType::countParameters };
				for (size_t i = 0; i < n; i++)
					this->output() << materialTableType::getParameterName(i) << ": \t" << current[i] << " [" << standard[i] << "]" << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-MATERIALPARAMETERS";
		}
	};

}