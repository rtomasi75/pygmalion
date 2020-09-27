namespace pygmalion::chess::dynamics
{
	class engine :
		public pygmalion::dynamics::engine<generator>
	{
	public:
		using generatorType = generator;
		using descriptorDynamics = typename generator::descriptorDynamics;
#include <pygmalion-dynamics/include_dynamics.h>
	private:
	public:
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::dynamics::engine<generator>(input, output)
		{
			this->template addCommand<command_debugMovegen>();
			this->template addCommand<command_debugUntabled>();
			this->template addCommand<command_debugMagics>();
			this->template addCommand<command_perft>();
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "chess (dynamics only)";
		}
	};
}