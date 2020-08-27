namespace pygmalion
{
	template<typename FRONTEND>
	class engine
	{
	public:
		using frontendType = FRONTEND;
		using movegenType = typename frontendType::movegenType;
		using movedataType = typename movegenType::movedataType;
		using variationType = typename frontendType::variationType;
		using evaluatorType = typename frontendType::evaluatorType;
		using searchType = typename frontendType::searchType;
		using subjectiveType = typename frontendType::subjectiveType;
		using objectiveType = typename frontendType::objectiveType;
		using commandType = command<engine>;
		using moveType = typename frontendType::moveType;

		using boardType = typename movegenType::boardType;
		using playerType = typename movegenType::playerType;
		using squareType = typename movegenType::squareType;
		using pieceType = typename movegenType::pieceType;
		using flagsType = typename movegenType::flagsType;
		using indexType = typename movegenType::indexType;
		using movelistType = typename movegenType::movelistType;
		using gamestateType = typename movegenType::gamestateType;
		using stackType = typename boardType::stackType;

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
					eng.outputStream() << "playing " << movegenType::name() << std::endl;
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
					frontendType::dumpBoard(eng.board(), eng.outputStream());
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
					auto score_old{ evaluatorType::evaluate(stack) };
					moveType move;
					bool hasMoves{ false };
					while (stack.nextMove(move))
					{
						hasMoves = true;
						eng.outputStream() << frontendType::moveToString(eng.board(), move) << "\t";
						stackType subStack(stack, move);
						auto score_new{ evaluatorType::evaluate(subStack) };
						eng.outputStream() << FRONTEND::objectiveToString(score_new) << "\t";
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
						if (frontendType::parseMove(move, eng.board(), mv, error))
						{
							std::string mvstr{ frontendType::moveToString(eng.board(),mv) };
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
						auto start = std::chrono::high_resolution_clock::now();
						typename searchType::variationType principalVariation;
						uint64_t nodeCount{ 0 };
						typename evaluatorType::objectiveType score{ searchType::pvs(eng.board(), principalVariation, i, nodeCount) };
						auto end = std::chrono::high_resolution_clock::now();
						auto elapsed = end - start;
						eng.outputStream() << std::setw(2) << static_cast<int>(i) << " " << std::setw(9) << parser::nodesCountToString(nodeCount) << " " << std::setw(12) << parser::durationToString(elapsed) << " " << std::setw(8) << parser::nodesPerSecondToString(engine::computeNodesPerSec(nodeCount, elapsed)) << std::setw(12) << FRONTEND::objectiveToString(score) << "  " << FRONTEND::variationToString(eng.board(), principalVariation) << std::endl;
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
						auto start = std::chrono::high_resolution_clock::now();
						typename searchType::variationType principalVariation;
						uint64_t nodeCount{ 0 };
						searchType::perft(eng.board(), i, nodeCount);
						auto end = std::chrono::high_resolution_clock::now();
						auto elapsed = end - start;
						eng.outputStream() << std::setw(2) << static_cast<int>(i) << " " << std::setw(9) << parser::nodesCountToString(nodeCount) << " " << std::setw(12) << parser::durationToString(elapsed) << " " << std::setw(8) << parser::nodesPerSecondToString(engine::computeNodesPerSec(nodeCount, elapsed)) << std::endl;
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
					typename movegenType::stackType stack(eng.board(), eng.board().movingPlayer());
					typename evaluatorType::objectiveType score{ evaluatorType::evaluate(stack) };
					eng.outputStream() << "eval obj.  = " << frontendType::objectiveToString(score) << std::endl;
					eng.outputStream() << "eval subj. = " << frontendType::subjectiveToString(evaluatorType::makeSubjective(score, stack.position().movingPlayer())) << std::endl;
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
					eng.outputStream() << "sizeof(size_t) = " << sizeof(size_t) << std::endl;
					eng.outputStream() << "sizeof(int)    = " << sizeof(int) << std::endl;
					eng.outputStream() << "sizeof(bool)   = " << sizeof(bool) << std::endl;
					eng.outputStream() << std::endl;
					eng.outputStream() << "sizeof(boardType)    = " << sizeof(boardType) << std::endl;
					eng.outputStream() << "sizeof(moveType)     = " << sizeof(moveType) << std::endl;
					eng.outputStream() << "sizeof(movedataType) = " << sizeof(movedataType) << std::endl;
					eng.outputStream() << "sizeof(stackType)    = " << sizeof(typename movegenType::stackType) << std::endl;
					eng.outputStream() << "sizeof(hashValue)    = " << sizeof(typename boardType::hashValue) << std::endl;
					eng.outputStream() << "sizeof(bitsType)     = " << sizeof(typename boardType::bitsType) << std::endl;
					eng.outputStream() << "sizeof(gamestate)    = " << sizeof(typename boardType::gamestate) << std::endl;
					eng.outputStream() << "sizeof(playerType)   = " << sizeof(playerType) << std::endl;
					eng.outputStream() << "sizeof(squareType)   = " << sizeof(squareType) << std::endl;
					eng.outputStream() << "sizeof(pieceType)    = " << sizeof(pieceType) << std::endl;
					eng.outputStream() << "sizeof(flagsType)    = " << sizeof(flagsType) << std::endl;
					eng.outputStream() << std::endl;
					eng.outputStream() << "sizeof(indexType)    = " << sizeof(indexType) << std::endl;
					eng.outputStream() << "sizeof(movelistType) = " << sizeof(movelistType) << std::endl;
					eng.outputStream() << std::endl;
					eng.outputStream() << "sizeof(subjectiveType) = " << sizeof(subjectiveType) << std::endl;
					eng.outputStream() << "sizeof(objectiveType)  = " << sizeof(objectiveType) << std::endl;
					eng.outputStream() << std::endl;
					eng.outputStream() << "sizeof(depthType)      = " << sizeof(typename searchType::depthType) << std::endl;
					eng.outputStream() << "sizeof(variationType)  = " << sizeof(variationType) << std::endl;
					eng.outputStream() << "sizeof(multiscoreType) = " << sizeof(typename searchType::multiscoreType) << std::endl;
					eng.outputStream() << "sizeof(nodeType)       = " << sizeof(typename searchType::nodeType) << std::endl;
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
#if defined(PYGMALION_CPU_BMI2)
					eng.outputStream() << "  BMI2" << std::endl;
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
		static double computeNodesPerSec(const uint64_t nodeCount, const std::chrono::nanoseconds duration) noexcept
		{
			return (10000.0 * static_cast<double>(nodeCount)) / (0.00001 * static_cast<double>(duration.count()));
		}
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