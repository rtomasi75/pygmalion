namespace pygmalion::chess::dynamics
{
	class command_debugTropism :
		public pygmalion::dynamics::command<descriptor_dynamics, generator>
	{
	public:
		using generatorType = generator;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = descriptor_dynamics;
#include <pygmalion-dynamics/include_dynamics.h>
	private:
		template<size_t PLAYER>
		void process(const playerType pl, const squareType sq, const pieceType pc) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					typename generatorType::contextType context;
					stackType<PLAYER> stack{ stackType<PLAYER>(this->position(), this->history(), &context) };
					const squaresType whitePawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(whitePlayer) };
					const squaresType blackPawns{ stack.position().pieceOccupancy(pawn) & stack.position().playerOccupancy(blackPlayer) };
					const squareType whiteKing{ stack.kingSquare(whitePlayer) };
					const squareType blackKing{ stack.kingSquare(blackPlayer) };
					typename generatorType::tropismType tropism;
					if (pl == whitePlayer)
						tropism.compute(sq, whitePlayer, whitePawns, blackPawns, whiteKing, blackKing);
					else
						tropism.compute(sq, blackPlayer, blackPawns, whitePawns, blackKing, whiteKing);
					tropism.dumpDistances(pc, this->output());
				}
				else
					this->template process<PLAYER + 1>(pl, sq, pc);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override;
		virtual std::string help() noexcept override
		{
			return "DEBUG-TROPISM";
		}
	};

}