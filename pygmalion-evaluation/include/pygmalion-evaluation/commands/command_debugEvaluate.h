namespace pygmalion::evaluation
{
	template<typename DESCRIPTION_EVALUATION, typename EVALUATOR>
	class command_debugEvaluate :
		public pygmalion::evaluation::command<DESCRIPTION_EVALUATION, EVALUATOR>
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "../include_evaluation.h"	
	private:
		template<size_t PLAYER>
		void process() noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					typename generatorType::contextType context;
					typename generatorType::template stackType<PLAYER> stack{ typename generatorType::template stackType<PLAYER>(this->position(), this->history(), &context, this->stateEngine().materialTable(), this->dynamicsEngine().delta()) };
					this->output() << "material: \t" << stack.position().template materialRelative<PLAYER>() << std::endl;
					typename evaluatorType::dataType data;
					evaluatorType::createData(data);
					for (size_t i = 0; i < evaluatorType::countStages; i++)
					{
						const scoreType value{ evaluatorType::template stage<PLAYER>(i,stack,data, this->evaluationEngine().evaluationParameters()) };
						this->output() << evaluatorType::stageName(i) << ": \t" << value << std::endl;
					}
					this->output() << "___________________________________________" << std::endl;
					scoreType eval{ evaluatorType::template evaluate<PLAYER>(scoreType::minimum(), scoreType::maximum(),stack,data, this->evaluationEngine().evaluationParameters()) };
					this->output() << "total: \t\t" << eval << std::endl;
				}
				else
					this->template process<PLAYER + 1>();
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-evaluate")
			{
				this->output() << std::endl;
				this->template process<0>();
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-EVALUATE";
		}
	};

}