namespace pygmalion
{
	template<typename FRONT>
	class engine
	{
	public:
		using frontType = FRONT;
		using stackType = typename frontType::stackType;

		using descriptorFrontend = typename frontType::descriptorFrontend;
#include "include_frontend.h"

		using commandType = command<engine<frontType>>;
	private:
		class command_quit : public commandType
		{
		protected:
			virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override
			{
				if (cmd == "quit")
				{
					eng.stop();
					return true;
				}
				else
					return false;
			}
		};
		class command_ver : public commandType
		{
		protected:
			virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override
			{
				if (cmd == "ver")
				{
					eng.outputStream() << "Pygmalion ver. 3.0" << std::endl;
					eng.outputStream() << "playing " << frontType::name() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugBoard : public commandType
		{
		protected:
			virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override
			{
				if (cmd == "debug-board")
				{
					frontType::dumpBoard(eng.board(), eng.outputStream());
					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugMoves : public commandType
		{
		protected:
			virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override
			{
				if (cmd == "debug-moves")
				{
					eng.outputStream() << std::endl;
					movelistType moves;
					stackType stack(eng.board(), eng.board().movingPlayer());
					auto score_old{ evaluationType::evaluate(stack) };
					moveType move;
					bool hasMoves{ false };
					while (stack.nextMove(move))
					{
						hasMoves = true;
						eng.outputStream() << frontType::moveToString(eng.board(), move) << "\t";
						stackType subStack(stack, move);
						auto score_new{ evaluationType::evaluate(subStack) };
						eng.outputStream() << FRONT::objectiveToString(score_new) << "\t";
						eng.outputStream() << std::endl;
					}
					if (!hasMoves)
					{
						eng.outputStream() << "(no moves possible)" << std::endl;
					}
					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugMove : public commandType
		{
		protected:
			virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-move")
				{
					eng.outputStream() << std::endl;
					std::string move;
					parser::parseToken(remainder, move, remainder);
					if (move != "")
					{
						moveType mv;
						std::string error;
						stackType stack(eng.board(), eng.board().movingPlayer());
						if (frontType::parseMove(move, stack, mv, error))
						{
							std::string mvstr{ frontType::moveToString(stack,mv) };
							if (eng.makeMove(mv))
								eng.outputStream() << "perforing move " << mvstr << "." << std::endl;
							else
								eng.outputStream() << "not performing illegal move " << mvstr << "." << std::endl;
						}
						else
						{
							eng.outputStream() << "ERROR: " << error << std::endl;
						}
					}
					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugBits : public commandType
		{
		protected:
			virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-bits")
				{
					eng.outputStream() << std::endl;
					std::string operation;
					parser::parseToken(remainder, operation, remainder);
					if (operation == "fh")
					{
						squaresType rnd = squaresType(squaresType::bitsType::random_sparse());
						frontType::dumpSquares(rnd, eng.outputStream());
					}
					else
						eng.outputStream() << "ERROR: invalid operation " << operation << std::endl;
					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugPVS : public commandType
		{
		protected:
			virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-pvs")
				{
					eng.outputStream() << std::endl;
					using depthType = typename searchType::depthType;
					depthType depth = parser::parseInt(remainder);
					for (depthType i = 0; i < depth; i++)
					{
						variationType principalVariation;
						heuristicsType heuristics;
						objectiveType score{ searchType::pvs(eng.board(), principalVariation, i, heuristics) };
						uint64_t nodeCount{ heuristics.nodeCount() };
						stackType stack(eng.board(), eng.board().movingPlayer());
						eng.outputStream() << static_cast<int>(i) << ": " << std::setw(12) << FRONT::objectiveToString(score) << " - " << FRONT::variationToString(stack, principalVariation) << std::endl;
						eng.outputStream() << heuristics.toString();
						eng.outputStream() << std::endl;
					}
					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugPerft : public commandType
		{
		protected:
			virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-perft")
				{
					eng.outputStream() << std::endl;
					using depthType = typename searchType::depthType;
					depthType depth = parser::parseInt(remainder);
					for (depthType i = 0; i < depth; i++)
					{
						typename searchType::variationType principalVariation;
						typename searchType::heuristicsType heuristics;
						searchType::perft(eng.board(), i, heuristics);
						uint64_t nodeCount{ heuristics.nodeCount() };
						eng.outputStream() << static_cast<int>(i) << ":" << std::endl;
						eng.outputStream() << heuristics.toString();
					}
					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugEval : public commandType
		{
		protected:
			virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-eval")
				{
					eng.outputStream() << std::endl;
					stackType stack(eng.board(), eng.board().movingPlayer());
					objectiveType score{ evaluationType::evaluate(stack) };
					eng.outputStream() << "eval obj.  = " << frontType::objectiveToString(score) << std::endl;
					eng.outputStream() << "eval subj. = " << frontType::subjectiveToString(evaluationType::makeSubjective(score, stack.position().movingPlayer())) << std::endl;
					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugMemory : public commandType
		{
		protected:
			virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-memory")
				{
					eng.outputStream() << std::endl;
					eng.outputStream() << "BOARD: " << std::endl;
					eng.outputStream() << "  playerType  = " << sizeof(playerType) << std::endl;
					eng.outputStream() << "  pieceType   = " << sizeof(pieceType) << std::endl;
					eng.outputStream() << "  rankType    = " << sizeof(rankType) << std::endl;
					eng.outputStream() << "  fileType    = " << sizeof(fileType) << std::endl;
					eng.outputStream() << "  squareType  = " << sizeof(squareType) << std::endl;
					eng.outputStream() << "  flagType    = " << sizeof(flagType) << std::endl;
					eng.outputStream() << "  flagsType   = " << sizeof(flagsType) << std::endl;
					eng.outputStream() << "  squaresType = " << sizeof(squaresType) << std::endl;
					eng.outputStream() << "  boardType   = " << sizeof(boardType) << std::endl;
					eng.outputStream() << std::endl;
					eng.outputStream() << "MECHANICS: " << std::endl;
					eng.outputStream() << "  moveflagsType   = " << sizeof(moveflagsType) << std::endl;
					eng.outputStream() << "  moveflagbitType = " << sizeof(moveflagbitType) << std::endl;
					eng.outputStream() << "  moveType        = " << sizeof(moveType) << std::endl;
					eng.outputStream() << std::endl;
					eng.outputStream() << "GENERATOR: " << std::endl;
					eng.outputStream() << "  movelistType = " << sizeof(movelistType) << std::endl;
					eng.outputStream() << "  indexType    = " << sizeof(indexType) << std::endl;
					eng.outputStream() << "  movedataType = " << sizeof(movedataType) << std::endl;
					eng.outputStream() << std::endl;
					eng.outputStream() << "EVALUATION: " << std::endl;
					eng.outputStream() << "  gamestateType  = " << sizeof(gamestateType) << std::endl;
					eng.outputStream() << "  objectiveType  = " << sizeof(objectiveType) << std::endl;
					eng.outputStream() << "  subjectiveType = " << sizeof(subjectiveType) << std::endl;
					eng.outputStream() << std::endl;
					eng.outputStream() << "SEARCH: " << std::endl;
					eng.outputStream() << "  variationType  = " << sizeof(variationType) << std::endl;
					eng.outputStream() << "  depthType      = " << sizeof(depthType) << std::endl;
					eng.outputStream() << "  heuristicsType = " << sizeof(heuristicsType) << std::endl;
					eng.outputStream() << "  multiscoreType = " << sizeof(multiscoreType) << std::endl;
					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugHardware : public commandType
		{
		protected:
			virtual bool onProcess(engine& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-hardware")
				{
					eng.outputStream() << std::endl;
					eng.outputStream() << "Compiler intrinsics:" << std::endl;
#if defined(PYGMALION_INTRINSICS_MSC)
					eng.outputStream() << "  Microsoft" << std::endl;
#endif
#if defined(PYGMALION_INTRINSICS_GNU)
					eng.outputStream() << "  GNU" << std::endl;
#endif
					eng.outputStream() << std::endl;
					eng.outputStream() << "CPU features:" << std::endl;
#if defined(PYGMALION_CPU_X86)
					eng.outputStream() << "  x86" << std::endl;
#endif
#if defined(PYGMALION_CPU_X64)
					eng.outputStream() << "  x64" << std::endl;
#endif
#if defined(PYGMALION_CPU_ARM)
					eng.outputStream() << "  ARM" << std::endl;
#endif
#if defined(PYGMALION_CPU_ALPHA)
					eng.outputStream() << "  alpha" << std::endl;
#endif
#if defined(PYGMALION_CPU_ALPHA)
					eng.outputStream() << "  ARM64" << std::endl;
#endif
#if defined(PYGMALION_CPU_MMX)
					eng.outputStream() << "  MMX" << std::endl;
#endif
#if defined(PYGMALION_CPU_SSE)
					eng.outputStream() << "  SSE" << std::endl;
#endif
#if defined(PYGMALION_CPU_SSE2)
					eng.outputStream() << "  SSE2" << std::endl;
#endif
#if defined(PYGMALION_CPU_SSE3)
					eng.outputStream() << "  SSE3" << std::endl;
#endif
#if defined(PYGMALION_CPU_SSSE3)
					eng.outputStream() << "  SSSE3" << std::endl;
#endif
#if defined(PYGMALION_CPU_BMI2)
					eng.outputStream() << "  BMI2" << std::endl;
#endif
#if defined(PYGMALION_CPU_AVX)
					eng.outputStream() << "  AVX" << std::endl;
#endif
#if defined(PYGMALION_CPU_AVX2)
					eng.outputStream() << "  AVX2" << std::endl;
#endif
#if defined(PYGMALION_CPU_AVX512)
					eng.outputStream() << "  AVX512" << std::endl;
#endif
					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		std::ostream& m_Output;
		std::istream& m_Input;
		boardType m_Board;
		std::atomic_bool m_IsRunning;
		std::recursive_mutex m_StartStopMutex;
		void mainloop() noexcept
		{
			while (m_IsRunning)
			{
				std::string input;
				std::getline(m_Input, input);
				bool processed{ false };
				for (auto& cmd : m_Commands)
				{
					processed |= cmd->process(*this, input);
					if (processed)
						break;
				}
				if (!processed)
				{
					m_Output << std::endl;
					m_Output << "invalid command." << std::endl;
					m_Output << std::endl;
				}
			}
		}
	private:
		std::deque<std::shared_ptr<commandType>> m_Commands;
	public:
		bool makeMove(const moveType move) noexcept
		{
			boardType newBoard{ m_Board };
			stackType stack(newBoard, newBoard.movingPlayer());
			if (stack.isMoveLegal(move))
			{
				stackType stack2(stack, move);
				m_Board = newBoard;
				return true;
			}
			else
			{
				return false;
			}
		}
		const auto& board() const noexcept
		{
			return m_Board;
		}
		auto& board() noexcept
		{
			return m_Board;
		}
		template<typename T>
		void addCommand()
		{
			auto delCmd = [](commandType* pCmd)
			{
				delete static_cast<T*>(pCmd);
			};
			std::shared_ptr<commandType> pCommand(static_cast<commandType*>(new T()), delCmd);
			m_Commands.emplace_back(std::move(pCommand));
		}
		std::istream& inputStream() noexcept
		{
			return m_Input;
		}
		std::ostream& outputStream() noexcept
		{
			return m_Output;
		}
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			m_Board(),
			m_IsRunning(false),
			m_Input(input),
			m_Output(output),
			m_Commands(),
			m_StartStopMutex()
		{
			addCommand<command_quit>();
			addCommand<command_ver>();
			addCommand<command_debugBoard>();
			addCommand<command_debugMoves>();
			addCommand<command_debugMove>();
			addCommand<command_debugEval>();
			addCommand<command_debugPVS>();
			addCommand<command_debugPerft>();
			addCommand<command_debugMemory>();
			addCommand<command_debugHardware>();
			addCommand<command_debugBits>();
			mechanicsType::initializePosition(m_Board);
		}
		~engine() noexcept = default;
		bool isRunning() const noexcept
		{
			return m_IsRunning;
		}
		void run() noexcept
		{
			std::lock_guard<std::recursive_mutex> lock(m_StartStopMutex);
			assert(!m_IsRunning);
			m_IsRunning = true;
			mainloop();
		}
		void stop() noexcept
		{
			std::lock_guard<std::recursive_mutex> lock(m_StartStopMutex);
			assert(m_IsRunning);
			m_IsRunning = false;
		}
	};
}