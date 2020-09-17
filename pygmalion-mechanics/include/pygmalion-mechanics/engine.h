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
		std::vector<boardType> m_PositionHistory;
	public:
		constexpr size_t historyLength() const noexcept
		{
			return m_PositionHistory.size();
		}
		constexpr void makeMove(const movebitsType& movebits) noexcept
		{
			m_PositionHistory.push_back(this->position());
			motorType::makeMove(this->position(), movebits);
		}
		constexpr void unmakeMove() noexcept
		{
			assert(m_PositionHistory.size() > 0);
			this->position() = m_PositionHistory[m_PositionHistory.size() - 1];
			m_PositionHistory.resize(m_PositionHistory.size() - 1);
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
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "no game (mechanics only)";
		}
	};
}