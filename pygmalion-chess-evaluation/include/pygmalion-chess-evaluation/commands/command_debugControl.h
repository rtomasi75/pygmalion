namespace pygmalion::chess::evaluation
{
	class command_debugControl :
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
		void process(const playerType p) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					typename generatorType::contextType context;
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), &context) };
					constexpr const squaresType none{ squaresType::none() };
					squaresType controlWhite{ none };
					squaresType controlBlack{ none };
					stack.control(controlWhite, controlBlack);
					if (p == whitePlayer)
					{
						dumpSquares(controlWhite);
					}
					else
					{
						dumpSquares(controlBlack);
					}
				}
				else
					this->template process<PLAYER + 1>(p);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override;
		virtual std::string help() noexcept override
		{
			return "DEBUG-CONTROL";
		}
	};

}