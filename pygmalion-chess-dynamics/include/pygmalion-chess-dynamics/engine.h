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
		}
		virtual ~engine() noexcept = default;
	};
}