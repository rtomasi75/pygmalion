namespace pygmalion::chess::dynamics
{
	class command_debugResizePT :
		public pygmalion::dynamics::command<descriptor_dynamics, generator>
	{
	public:
		using generatorType = generator;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = descriptor_dynamics;
#include <pygmalion-dynamics/include_dynamics.h>
	private:
		template<size_t PLAYER>
		void process(const std::int64_t sizeInMegaBytes) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					generatorType::pawnTable().resize(sizeInMegaBytes * 1024 * 1024);
					this->output() << "Transposition table resized to " << std::setw(4) << parser::memoryToString(generatorType::pawnTable().memoryUsed(), "B") << std::endl;
				}
				else
					this->template process<PLAYER + 1>(sizeInMegaBytes);
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
			if (token == "debug-resizept")
			{
				this->output() << std::endl;
				std::int64_t sizeInMegaBytes = parser::parseInt(remainder);
				this->template process<0>(sizeInMegaBytes);
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-RESIZEPT";
		}
	};

}