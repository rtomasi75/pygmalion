namespace pygmalion::dynamics
{
	template<typename DYNAMICS>
	class engine :
		public pygmalion::mechanics::engine<typename DYNAMICS::descriptorMechanics>,
		public DYNAMICS::descriptorDynamics
	{
	public:
		using dynamicsType = DYNAMICS;
		using descriptorDynamics = typename DYNAMICS::descriptorDynamics;
#include "include_dynamics.h"
	private:
	public:
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::state::engine<boardType>(input, output)
		{
		//	this->template addCommand<command_debugMechanics<descriptorMechanics, motorType>>();
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "no game (dynamics only)";
		}
	};
}