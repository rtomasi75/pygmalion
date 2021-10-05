namespace pygmalion::mechanics
{
	template<typename MOTOR>
	class engine :
		public pygmalion::state::engine<typename MOTOR::boardType>,
		public MOTOR::descriptorMechanics
	{
	public:
		using motorType = MOTOR;
		using descriptorMechanics = typename MOTOR::descriptorMechanics;
#include "include_mechanics.h"
	private:
		historyType m_History;
	public:
		virtual void onMakeMove(const movebitsType movebits) noexcept
		{

		}
		virtual void onUnMakeMove() noexcept
		{

		}
		constexpr const historyType& history() const noexcept
		{
			return m_History;
		}
		constexpr historyType& history() noexcept
		{
			return m_History;
		}
		constexpr void makeMove(const movebitsType& movebits) noexcept
		{
			this->onMakeMove(movebits);
			this->currentGame().makeMove(this->position().movingPlayer());
			m_History.template makeMove<motorType>(this->position(), movebits);
		}
		constexpr void unmakeMove() noexcept
		{
			this->currentGame().unmakeMove(this->position().movingPlayer());
			m_History.template unmakeMove<motorType>(this->position());
			this->onUnMakeMove();
		}
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::state::engine<boardType>(input, output)
		{
			this->template addCommand<command_debugMechanics<descriptorMechanics, motorType>>();
			this->template addCommand<command_debugMove<descriptorMechanics, motorType>>();
			this->template addCommand<command_debugUnmove<descriptorMechanics, motorType>>();
			this->template addCommand<command_debugHistory<descriptorMechanics, motorType>>();
		}
		virtual ~engine() noexcept = default;
	};
}