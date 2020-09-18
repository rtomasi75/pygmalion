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
		std::vector<typename motorType::moveinfoType> m_MovedataHistory;
		std::vector<movebitsType> m_MoveHistory;
	public:
		constexpr size_t historyLength() const noexcept
		{
			return m_PositionHistory.size();
		}
		constexpr void makeMove(const movebitsType& movebits) noexcept
		{
			m_PositionHistory.push_back(this->position());
			m_MovedataHistory.push_back(motorType::makeMove(this->position(), movebits));
			m_MoveHistory.push_back(movebits);
		}
		constexpr void unmakeMove() noexcept
		{
			assert(m_PositionHistory.size() > 0);
			//	this->position() = m_PositionHistory[m_PositionHistory.size() - 1];
			motorType::unmakeMove(this->position(), m_MovedataHistory[m_MovedataHistory.size() - 1]);
			m_PositionHistory.resize(m_PositionHistory.size() - 1);
			m_MovedataHistory.resize(m_MovedataHistory.size() - 1);
			m_MoveHistory.resize(m_MoveHistory.size() - 1);
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