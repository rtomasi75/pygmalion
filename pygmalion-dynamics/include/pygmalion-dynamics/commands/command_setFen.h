namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_setFen :
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
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "set-fen")
			{
				this->output() << std::endl;
				if (this->position().setFen(remainder))
				{
					this->stateEngine().positionChanged();
					this->output() << "New position: " << this->position().getFen() << std::endl;
				}
				else
				{
					this->output() << "Error (invalid FEN): " << remainder << std::endl;
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "SET-FEN";
		}
	};

}