namespace pygmalion::state
{
	template<typename BOARD>
	class engine;

	template<typename DESCRIPTION_STATE, typename BOARD>
	class command :
		public pygmalion::intrinsics::command,
		public DESCRIPTION_STATE
	{
	public:
		using boardType = BOARD;
	public:
		boardType& position() noexcept
		{
			return this->stateEngine().position();
		}
		const boardType& position() const noexcept
		{
			return this->stateEngine().position();
		}
		using parentType = pygmalion::intrinsics::command;
		using descriptorState = DESCRIPTION_STATE;
#include "include_state.h"	
	public:
		engine<boardType>& stateEngine() noexcept
		{
			return dynamic_cast<engine<boardType>&>(intrinsicsEngine());
		}
		const engine<boardType>& stateEngine() const noexcept
		{
			return dynamic_cast<const engine<boardType>&>(intrinsicsEngine());
		}
	};
}