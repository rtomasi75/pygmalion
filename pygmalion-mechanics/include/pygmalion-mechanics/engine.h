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
			m_History.template makeMove<motorType>(this->position(), movebits);
		}
		constexpr void unmakeMove() noexcept
		{
			m_History.template unmakeMove<motorType>(this->position());
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
		virtual std::string version() const noexcept override
		{
			return "no game (mechanics only)";
		}
	};
}