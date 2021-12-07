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
		deltaType m_MaterialDelta;
	public:
		PYGMALION_INLINE const deltaType& materialDelta() const noexcept
		{
			return m_MaterialDelta;
		}
		virtual deltaType delta() const noexcept
		{
			return materialDelta();
		}
		std::vector<scoreType> materialParameters() const noexcept
		{
			std::vector<scoreType> materialParameters;
			this->materialTable().getParameters(materialParameters);
			return materialParameters;
		}
		virtual std::vector<scoreType> parameters() const noexcept
		{
			return this->materialParameters();
		}
		void setMaterialParameters(const std::vector<scoreType>& materialParameters) noexcept
		{
			std::string fen = this->position().getFen();
			this->materialTable().setParameters(materialParameters);
			m_MaterialDelta = generatorType::computeMaterialDelta(this->materialTable());
			this->initialize();
			this->position().setFen(fen, this->materialTable());
			this->positionChanged();
		}
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::mechanics::engine<typename GENERATOR::motorType>(input, output)
		{
			std::vector<scoreType> params;
			materialTableType::defaultParameters(params);
			setMaterialParameters(params);
			this->template addCommand<command_debugMoves<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugTacticalMoves<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugDynamics<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugPerft<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugPasses<descriptorDynamics, generatorType>>();
			this->template addCommand<command_setFen<descriptorDynamics, generatorType>>();
			this->template addCommand<command_getFen<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugSAN<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugPromoCaptureTargets<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugCaptureTargets<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugQuietTargets<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugPromotionTargets<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugPromoCaptureOrigins<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugCaptureOrigins<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugQuietOrigins<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugPromotionOrigins<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugDelta<descriptorDynamics, generatorType>>();
			this->template addCommand<command_debugMaterialParameters<descriptorDynamics, generatorType>>();
			std::deque<std::shared_ptr<pygmalion::intrinsics::command>> list{ generatorType::commands() };
			for (auto& cmd : list)
			{
				this->addCommand(cmd);
			}
		}
		virtual ~engine() noexcept = default;
	};
}