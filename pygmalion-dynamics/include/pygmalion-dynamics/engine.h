namespace pygmalion::dynamics
{
	template<typename GENERATOR>
	class engine :
		public pygmalion::mechanics::engine<typename GENERATOR::motorType>,
		public GENERATOR::descriptorDynamics
	{
	public:
		using generatorType = GENERATOR;
		using descriptorDynamics = typename GENERATOR::descriptorDynamics;
#include "include_dynamics.h"
		using feedbackType = typename generatorType::movegenFeedback;
	private:
		feedbackType m_Feedback{ typename generatorType::movegenFeedback() };
	public:
		constexpr const feedbackType& feedback() const noexcept
		{
			return m_Feedback;
		}
		constexpr feedbackType& feedback() noexcept
		{
			return m_Feedback;
		}
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::mechanics::engine<typename GENERATOR::motorType>(input, output)
		{
			this->template addCommand<command_debugMoves<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugTacticalMoves<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugDynamics<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugPerft<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugPasses<descriptorDynamics, generatorType>>();
			this->template addCommand<command_setFen<descriptorDynamics, generatorType>>();
			this->template addCommand<command_getFen<descriptorDynamics, generatorType>>();
			std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ generatorType::commands() };
			for (auto& cmd : list)
			{
				this->addCommand(cmd);
			}
		}
		virtual ~engine() noexcept = default;
	};
}