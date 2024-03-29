namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugIsCritical :
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
		void process(const movebitsType movebits) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					typename generatorType::contextType context;
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(),this->history(), &context) };
					if (generatorType::template isMoveCritical<PLAYER, stackType<PLAYER>>(stack, movebits))
						this->output() << generatorType::moveToString(stack, movebits, this->history().length()) << " is a critical move" << std::endl;
					else
						this->output() << generatorType::moveToString(stack, movebits, this->history().length()) << " is NOT a critical move" << std::endl;
				}
				else
					this->template process<PLAYER + 1>(movebits);
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
			if (token == "debug-iscritical")
			{
				this->output() << std::endl;
				std::string remainder2;
				parser::parseTokenCaseSensitive(remainder, token, remainder2);
				movebitsType movebits;
				if (motorType::parseMove(this->position(), token, movebits))
				{
					this->template process<0>(movebits);
				}
				else
					this->output() << token << " is not a possible move." << std::endl;
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-ISCRITICAL";
		}
	};

}