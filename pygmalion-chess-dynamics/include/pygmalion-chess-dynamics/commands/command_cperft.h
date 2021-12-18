namespace pygmalion::chess::dynamics
{
	class command_cperft :
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
			perftdata& operator+=(const perftdata& data) noexcept
			{
				Leafs += data.Leafs;
				Nodes += data.Nodes;
				Captures += data.Captures;
				EnPassant += data.EnPassant;
				DoublePushes += data.DoublePushes;
				QueensideCastles += data.QueensideCastles;
				KingsideCastles += data.KingsideCastles;
				Castles += data.Castles;
				Checks += data.Checks;
				Checkmates += data.Checkmates;
				Promotions += data.Promotions;
				return *this;
			}
		};
		template<size_t PLAYER>
		void perft(const stackType<PLAYER>& stack, const size_t depth, const size_t maxDepth, perftdata& data) noexcept
		{
			constexpr const playerType player{ static_cast<playerType>(PLAYER) };
			movebitsType moveBits;
			data.Nodes++;
			if (depth == maxDepth)
			{
				while (stack.nextMove(moveBits))
				{
					bool bOk{ motorType::move().isCapture(moveBits) };
					if (motorType::move().isPromotion(moveBits))
					{
						if (motorType::move().promotedPiece(moveBits) == queen)
							bOk |= true;
					}
					if (bOk)
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
						const std::string fen{ stack.position().getFen() };
						const hashType oldHash{ stack.position().hash() };
						{
							const stackType<static_cast<size_t>(player.next())> substack{ stackType<static_cast<size_t>(player.next())>(stack,moveBits) };
							if (substack.isPositionCritical())
							{
								data.Checks++;
								movebitsType moveBits2;
								if (!substack.nextMove(moveBits2))
									data.Checkmates++;
							}
						}
						const hashType newHash{ stack.position().hash() };
						if (oldHash != newHash)
						{
							this->position().setFen(fen, this->dynamicsEngine().materialTable());
							this->output() << "ERROR: hash before/after move does not match: " << motorType::move().toString(stack.position(), moveBits) << " | " << generatorType::moveToSAN(stack, moveBits) << " | " << fen << std::endl;
						}
					}
				}
			}
			else
			{
				while (stack.nextMove(moveBits))
				{
					const std::string fen{ stack.position().getFen() };
					const hashType oldHash{ stack.position().hash() };
					{
						const stackType<static_cast<size_t>(player.next())> substack{ stackType<static_cast<size_t>(player.next())>(stack,moveBits) };
						perft<static_cast<size_t>(player.next())>(substack, depth + 1, maxDepth, data);
					}
					const hashType newHash{ stack.position().hash() };
					if (oldHash != newHash)
					{
						this->position().setFen(fen, this->dynamicsEngine().materialTable());
						this->output() << "ERROR: hash before/after move does not match: " << motorType::move().toString(stack.position(), moveBits) << " | " << generatorType::moveToSAN(stack, moveBits) << " | " << fen << std::endl;
					}
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
						typename generatorType::contextType* pContext = new typename generatorType::contextType[depth + 1];
						profiler p;
						p.start();
						stackType<PLAYER> stack{ stackType<PLAYER>(this->position(),this->history(),pContext, this->stateEngine().materialTable(), this->dynamicsEngine().delta()) };
						movebitsType moveBits;
						if (depth == 1)
						{
							while (stack.nextMove(moveBits))
							{
								bool bOk{ motorType::move().isCapture(moveBits) };
								if (motorType::move().isPromotion(moveBits))
								{
									if (motorType::move().promotedPiece(moveBits) == queen)
										bOk |= true;
								}
								if (bOk)
								{
									data.Nodes++;
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
									const std::string fen{ stack.position().getFen() };
									const hashType oldHash{ stack.position().hash() };
									{
										const stackType<static_cast<size_t>(player.next())> substack{ stackType<static_cast<size_t>(player.next())>(stack,moveBits) };
										if (substack.isPositionCritical())
										{
											data.Checks++;
											movebitsType moveBits2;
											if (!substack.nextMove(moveBits2))
												data.Checkmates++;
										}
									}
									const hashType newHash{ stack.position().hash() };
									if (oldHash != newHash)
									{
										this->position().setFen(fen, this->dynamicsEngine().materialTable());
										this->output() << std::endl << "ERROR: hash before/after move does not match: " << motorType::move().toString(stack.position(), moveBits) << " | " << generatorType::moveToSAN(stack, moveBits) << " | " << fen << std::endl;
									}
									else
										this->output() << "  " << motorType::move().toString(this->position(), moveBits) << std::endl;
								}
							}
						}
						else
						{
							while (stack.nextMove(moveBits))
							{
								data.Nodes++;
								perftdata data2;
								const std::string fen{ stack.position().getFen() };
								const hashType oldHash{ stack.position().hash() };
								{
									const stackType<static_cast<size_t>(player.next())> substack{ stackType<static_cast<size_t>(player.next())>(stack,moveBits) };
									perft(substack, 1, depth - 1, data2);
								}
								const hashType newHash{ stack.position().hash() };
								if (oldHash != newHash)
								{
									this->position().setFen(fen, this->dynamicsEngine().materialTable());
									this->output() << std::endl << "ERROR: hash before/after move does not match: " << motorType::move().toString(stack.position(), moveBits) << " | " << generatorType::moveToSAN(stack, moveBits) << " | " << fen << std::endl;
								}
								else
									this->output() << "  " << motorType::move().toString(this->position(), moveBits) << "\t: " << data2.Leafs << std::endl;
								data += data2;
							}
						}
						p.stop();
						delete[] pContext;
						this->output() << std::endl;
						this->output() << "depth: " << std::setw(2) << static_cast<int>(depth) << " nodes: " << parser::valueToString(static_cast<double>(data.Nodes), "N") /* << " time: " << parser::durationToString(p.duration()) << " speed: " << p.computeSpeed(data.Nodes, "N")*/ << std::endl;
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
				return "CPERFT";
			}
			virtual bool onProcess(const std::string & cmd) noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "cperft")
				{
					size_t depth{ static_cast<size_t>(parser::parseInt(remainder)) };
					this->process<0>(depth);
					return true;
				}
				else
					return false;
			}
	};

	}