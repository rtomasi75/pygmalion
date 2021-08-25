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
	private:
		typename generatorType::movegenFeedback m_Feedback{ typename generatorType::movegenFeedback() };
	public:
		constexpr const typename generatorType::movegenFeedback& feedback() const noexcept
		{
			return m_Feedback;
		}
		constexpr typename generatorType::movegenFeedback& feedback() noexcept
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
			this->template addCommand<command_debugDynamics<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugPerft<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugPasses<descriptorDynamics, generatorType>>();
			std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ generatorType::commands() };
			for (auto& cmd : list)
			{
				this->addCommand(cmd);
			}
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "no game (dynamics only)";
		}
	};
}