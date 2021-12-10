namespace pygmalion::evaluation
{
	template<typename DESCRIPTION_EVALUATION, typename EVALUATOR>
	class command_debugEvaluationDelta :
		public pygmalion::evaluation::command<DESCRIPTION_EVALUATION, EVALUATOR>
	{
	public:
		using evaluatorType = EVALUATOR;
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "../include_evaluation.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-evaluationdelta")
			{
				this->output() << std::endl;
				for (const auto mask : piecesType::range)
				{
					for (const auto spl : playerType::range)
					{
						for (const auto pl : playerType::range)
						{
							this->output() << boardType::playerToString(spl) << "=>" << boardType::piecesToString(mask, pl) << ": ";
							if constexpr (evaluatorType::countEvaluationStages > 0)
							{
								for (size_t i = 0; i < evaluatorType::countEvaluationStages; i++)
								{
									const auto& delta(this->evaluationEngine().evaluationDelta().stageDelta(i));
									this->output() << "\t" << delta.maxQuietChange(spl, pl, mask);
								}
								this->output() << std::endl;
								this->output() << boardType::playerToString(spl) << "=>" << boardType::piecesToString(mask, pl) << "=" << boardType::piecesToString(generatorType::promotionResults(pl), pl) << ": ";
								for (size_t i = 0; i < evaluatorType::countEvaluationStages; i++)
								{
									const auto& delta(this->evaluationEngine().evaluationDelta().stageDelta(i));
									this->output() << "\t" << delta.maxPromotionChange(spl, pl, mask);
								}
								this->output() << std::endl;
								for (const auto mask2 : piecesType::range)
								{
									this->output() << boardType::playerToString(spl) << "=>" << boardType::piecesToString(mask, pl) << "-" << boardType::piecesToString(mask2, pl.next()) << ": ";
									for (size_t i = 0; i < evaluatorType::countEvaluationStages; i++)
									{
										const auto& delta(this->evaluationEngine().evaluationDelta().stageDelta(i));
										this->output() << "\t" << delta.maxCaptureChange(spl, pl, mask, mask2);
									}
									this->output() << std::endl;
								}
								for (const auto mask2 : piecesType::range)
								{
									this->output() << boardType::playerToString(spl) << "=>" << boardType::piecesToString(mask, pl) << "-" << boardType::piecesToString(mask2, pl.next()) << "=" << boardType::piecesToString(generatorType::promotionResults(pl), pl) << ": ";
									for (size_t i = 0; i < evaluatorType::countEvaluationStages; i++)
									{
										const auto& delta(this->evaluationEngine().evaluationDelta().stageDelta(i));
										this->output() << "\t" << delta.maxPromoCaptureChange(spl, pl, mask, mask2);
									}
									this->output() << std::endl;
								}
							}
							this->output() << std::endl;
						}
					}
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-EVALUATIONDELTA";
		}
	};

}