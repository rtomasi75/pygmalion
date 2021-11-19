namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugSAN :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
		using movegenFeedback = typename generatorType::movegenFeedback;
#include "../include_dynamics.h"
	private:
		template<size_t PLAYER>
		void process(const std::string& remainder2) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					typename generatorType::contextType context;
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(),this->history(), &context) };
					movebitsType movebits;
					size_t count{ 0 };
					if (generatorType::parseSAN(remainder2, stack, movebits, count))
					{
						this->output() << "Performed move " << generatorType::moveToSAN(stack, movebits) << std::endl;
						this->mechanicsEngine().makeMove(movebits);
					}
					else
						this->output() << "\'" << remainder2 << "\' is not a valid move in SAN." << std::endl;
				}
				else
					this->template process<PLAYER + 1>(remainder2);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "debug-san")
			{
				this->output() << std::endl;
				this->template process<0>(remainder);
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-SAN";
		}
	};

}