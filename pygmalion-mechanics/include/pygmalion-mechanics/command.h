namespace pygmalion::mechanics
{
	template<typename DESCRIPTION_MECHANICS>
	class engine;

	template<typename DESCRIPTION_MECHANICS, typename MOTOR>
	class command :
		public pygmalion::state::command<typename DESCRIPTION_MECHANICS::descriptorState, typename DESCRIPTION_MECHANICS::boardType>,
		public DESCRIPTION_MECHANICS
	{
	public:
		using motorType = MOTOR;
		using parentType = pygmalion::state::command<typename DESCRIPTION_MECHANICS::descriptorState, typename DESCRIPTION_MECHANICS::boardType>;
		using descriptorMechanics = DESCRIPTION_MECHANICS;
#include "include_mechanics.h"	
	public:
		engine<motorType>& mechanicsEngine() noexcept
		{
			return *dynamic_cast<engine<motorType>*>(&(this->stateEngine()));
		}
		const engine<motorType>& mechanicsEngine() const noexcept
		{
			return *dynamic_cast<const engine<motorType>*>(&(this->stateEngine()));
		}
	};
}