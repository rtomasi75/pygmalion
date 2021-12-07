namespace pygmalion::chess::evaluation
{
	class command_debugSEE :
		public pygmalion::evaluation::command<descriptor_evaluation, evaluator>
	{
	public:
		using evaluatorType = evaluator;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorEvaluation = descriptor_evaluation;
#include <pygmalion-evaluation/include_evaluation.h>
	private:
		template<size_t PLAYER>
		void process(const std::string& token, const movebitsType movebits) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					typename generatorType::contextType context;
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), &context, this->stateEngine().materialTable(), this->dynamicsEngine().delta()) };
					if (generatorType::isMoveLegal(stack, movebits))
					{
						objectiveType score{ evaluatorType::template staticExchangeScore<PLAYER>(this->position(),movebits, this->stateEngine().materialTable()) };
						this->output() << "static exchange evaluation for " << motorType::moveToString(this->position(), movebits) << ":" << std::endl;
						this->output() << score;
					}
					else
						this->output() << token << " is not a legal move." << std::endl;
				}
				else
					this->template process<PLAYER + 1>(token, movebits);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override;
		virtual std::string help() noexcept override
		{
			return "DEBUG-SEE";
		}
	};

}