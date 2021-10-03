namespace pygmalion::chess::dynamics
{
	class command_perft :
		public pygmalion::dynamics::command<descriptor_dynamics, generator>
	{
	public:
		using generatorType = generator;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = descriptor_dynamics;
#include <pygmalion-dynamics/include_dynamics.h>
	private:
		struct perftdata
		{
			std::uintmax_t Nodes;
			std::uintmax_t Leafs;
			std::uintmax_t Captures;
			std::uintmax_t EnPassant;
			std::uintmax_t DoublePushes;
			std::uintmax_t QueensideCastles;
			std::uintmax_t KingsideCastles;
			std::uintmax_t Castles;
			std::uintmax_t Checks;
			std::uintmax_t Checkmates;
			std::uintmax_t Promotions;
			constexpr perftdata() :
				Nodes{ 0 },
				Leafs{ 0 },
				Captures{ 0 },
				EnPassant{ 0 },
				DoublePushes{ 0 },
				QueensideCastles{ 0 },
				KingsideCastles{ 0 },
				Checks{ 0 },
				Checkmates{ 0 },
				Castles{ 0 },
				Promotions{ 0 }
			{}
			perftdata& operator+=(const perftdata& data) noexcept;
		};
		template<size_t PLAYER>
		static void perft(const stackType<PLAYER>& stack, const size_t depth, const size_t maxDepth, perftdata& data, typename generatorType::movegenFeedback& feedback) noexcept
		{
			constexpr const playerType player{ static_cast<playerType>(PLAYER) };
			movebitsType moveBits;
			data.Nodes++;
			if (depth == maxDepth)
			{
				while (stack.nextMove(moveBits, depth, feedback))
				{
					data.Leafs++;
					if (motorType::move().isCapture(moveBits))
						data.Captures++;
					if (motorType::move().isEnPassant(moveBits))
						data.EnPassant++;
					if (motorType::move().isDoublePush(moveBits))
						data.DoublePushes++;
					if (motorType::move().isQueensideCastle(moveBits))
						data.QueensideCastles++;
					if (motorType::move().isKingsideCastle(moveBits))
						data.KingsideCastles++;
					if (motorType::move().isCastle(moveBits))
						data.Castles++;
					if (motorType::move().isPromotion(moveBits))
						data.Promotions++;
					{
						const stackType<static_cast<size_t>(player.next())> substack{ stackType<static_cast<size_t>(player.next())>(stack,moveBits) };
						if (substack.isPositionCritical())
						{
							data.Checks++;
							movebitsType moveBits2;
							if (!substack.nextMove(moveBits2, depth + 1, feedback))
								data.Checkmates++;
						}
					}
				}
			}
			else
			{
				while (stack.nextMove(moveBits, depth, feedback))
				{
					const stackType<static_cast<size_t>(player.next())> substack{ stackType<static_cast<size_t>(player.next())>(stack,moveBits) };
					perft<static_cast<size_t>(player.next())>(substack, depth + 1, maxDepth, data, feedback);
				}
			}
		}
		template<size_t PLAYER>
		void process(const size_t depth) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					if (depth > 0)
					{
						this->output() << std::endl;
						perftdata data;
						typename generatorType::contextType* pContext = new typename generatorType::contextType[depth];
						profiler p;
						p.start();
						stackType<PLAYER> stack{ stackType<PLAYER>(this->position(),this->history(),pContext) };
						movebitsType moveBits;
						while (stack.nextMove(moveBits, 0, this->feedback()))
						{
							data.Nodes++;
							if (depth == 1)
							{
								data.Leafs++;
								if (motorType::move().isCapture(moveBits))
									data.Captures++;
								if (motorType::move().isEnPassant(moveBits))
									data.EnPassant++;
								if (motorType::move().isDoublePush(moveBits))
									data.DoublePushes++;
								if (motorType::move().isQueensideCastle(moveBits))
									data.QueensideCastles++;
								if (motorType::move().isKingsideCastle(moveBits))
									data.KingsideCastles++;
								if (motorType::move().isCastle(moveBits))
									data.Castles++;
								if (motorType::move().isPromotion(moveBits))
									data.Promotions++;
								{
									const stackType<static_cast<size_t>(player.next())> substack{ stackType<static_cast<size_t>(player.next())>(stack,moveBits) };
									if (substack.isPositionCritical())
									{
										data.Checks++;
										movebitsType moveBits2;
										if (!substack.nextMove(moveBits2, 1, this->feedback()))
											data.Checkmates++;
									}
								}
								this->output() << "  " << motorType::move().toString(this->position(), moveBits) << std::endl;
							}
							else
							{
								perftdata data2;
								{
									const stackType<static_cast<size_t>(player.next())> substack{ stackType<static_cast<size_t>(player.next())>(stack,moveBits) };
									perft(substack, 1, depth - 1, data2, this->feedback());
								}
								this->output() << "  " << motorType::move().toString(this->position(), moveBits) << "\t: " << data2.Leafs << std::endl;
								data += data2;
							}
						}
						p.stop();
						delete[] pContext;
						this->output() << std::endl;
						this->output() << "depth: " << std::setw(2) << static_cast<int>(depth) << " nodes: " << parser::valueToString(static_cast<double>(data.Nodes), "N") << " time: " << parser::durationToString(p.duration()) << " speed: " << p.computeSpeed(data.Nodes, "N") << std::endl;
						this->output() << std::endl;
						this->output() << " Leafs:             " << data.Leafs << std::endl;
						this->output() << " Captures:          " << data.Captures << std::endl;
						this->output() << " En passant:        " << data.EnPassant << std::endl;
						this->output() << " Castles:           " << data.Castles << std::endl;
						this->output() << " Promotions:        " << data.Promotions << std::endl;
						this->output() << " Checks:            " << data.Checks << std::endl;
						this->output() << " Checkmates:        " << data.Checkmates << std::endl;
						this->output() << " Double pushes:     " << data.DoublePushes << std::endl;
						this->output() << " Queenside castles: " << data.QueensideCastles << std::endl;
						this->output() << " Kingside castles:  " << data.KingsideCastles << std::endl;
						this->output() << std::endl;
					}
				}
				else
					this->process<PLAYER + 1>(depth);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual std::string help() noexcept override
		{
			return "PERFT";
		}
		virtual bool onProcess(const std::string& cmd) noexcept override;
	};

}