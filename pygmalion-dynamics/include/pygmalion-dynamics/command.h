namespace pygmalion::dynamics
{
	template<typename GENERATOR>
	class engine;

	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command :
		public pygmalion::mechanics::command<typename DESCRIPTION_DYNAMICS::descriptorMechanics, typename DESCRIPTION_DYNAMICS::motorType>,
		public DESCRIPTION_DYNAMICS
	{
	public:
		using generatorType = GENERATOR;
	public:
		using parentType = pygmalion::mechanics::command<typename DESCRIPTION_DYNAMICS::descriptorMechanics, typename DESCRIPTION_DYNAMICS::motorType>;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
#include "include_dynamics.h"	
	public:
		engine<generatorType>& dynamicsEngine() noexcept
		{
			return dynamic_cast<engine<generatorType>&>(this->mechanicsEngine());
		}
		const engine<generatorType>& dynamicsEngine() const noexcept
		{
			return dynamic_cast<const engine<generatorType>&>(this->mechanicsEngine());
		}
	protected:
	};
}