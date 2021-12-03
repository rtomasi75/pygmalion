namespace pygmalion::chess::dynamics
{
	class command_testMovegen :
		public pygmalion::dynamics::command<descriptor_dynamics, generator>
	{
	public:
		using generatorType = generator;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = descriptor_dynamics;
#include <pygmalion-dynamics/include_dynamics.h>
	private:
		template<class T, size_t N>
		constexpr static size_t size(T(&)[N]) noexcept
		{
			return N;
		}
		struct testset
		{
		private:
			std::string m_Fen;
			std::uintmax_t m_Expected;
			size_t m_Depth;
		public:
			const std::string& fen() const noexcept;
			std::uintmax_t expected() const noexcept;
			size_t depth() const noexcept;
			testset(const std::string& fen, const size_t depth, const std::uintmax_t expected) noexcept;
		};
		static inline testset m_Sets[]
		{
			testset("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 1, UINTMAX_C(20)),
			testset("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 2, UINTMAX_C(400)),
			testset("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 3, UINTMAX_C(8902)),
			testset("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 4, UINTMAX_C(197281)),
			testset("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 5, UINTMAX_C(4865609)),
			testset("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 6, UINTMAX_C(119060324)),
			//	testset("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 7, UINTMAX_C(3195901860)),
			//	testset("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 8, UINTMAX_C(84998978956)),
			//	testset("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 9, UINTMAX_C(2439530234167)),
				testset("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0",1, UINTMAX_C(48)),
				testset("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0",2, UINTMAX_C(2039)),
				testset("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0",3, UINTMAX_C(97862)),
				testset("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0",4, UINTMAX_C(4085603)),
				testset("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0",5, UINTMAX_C(193690690)),
			//	testset("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0",6, UINTMAX_C(8031647685)),
				testset("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 0", 1, UINTMAX_C(14)),
				testset("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 0", 2, UINTMAX_C(191)),
				testset("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 0", 3, UINTMAX_C(2812)),
				testset("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 0", 4, UINTMAX_C(43238)),
				testset("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 0", 5, UINTMAX_C(674624)),
				testset("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 0", 6, UINTMAX_C(11030083)),
				//	testset("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 0", 7, UINTMAX_C(178633661)),
				//	testset("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 0", 8, UINTMAX_C(3009794393)),
					testset("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1", 1, UINTMAX_C(6)),
					testset("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1", 2, UINTMAX_C(264)),
					testset("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1", 3, UINTMAX_C(9467)),
					testset("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1", 4, UINTMAX_C(422333)),
					testset("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1", 5, UINTMAX_C(15833292)),
					//testset("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1", 6, UINTMAX_C(706045033)),
					testset("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 1, UINTMAX_C(6)),
					testset("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 2, UINTMAX_C(264)),
					testset("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 3, UINTMAX_C(9467)),
					testset("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 4, UINTMAX_C(422333)),
					testset("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 5, UINTMAX_C(15833292)),
					//testset("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", 6, UINTMAX_C(706045033)),
					testset("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 ", 1, UINTMAX_C(44)),
					testset("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 ", 2, UINTMAX_C(1486)),
					testset("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 ", 3, UINTMAX_C(62379)),
					testset("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 ", 4, UINTMAX_C(2103487)),
					testset("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 ", 5, UINTMAX_C(89941194)),
					testset("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", 1, UINTMAX_C(46)),
					testset("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", 2, UINTMAX_C(2079)),
					testset("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", 3, UINTMAX_C(89890)),
					testset("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", 4, UINTMAX_C(3894594)),
					testset("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", 5, UINTMAX_C(164075551)),
					//testset("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", 6, UINTMAX_C(6923051137)),
					//		testset("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", 7, UINTMAX_C(287188994746)),
					//		testset("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", 8, UINTMAX_C(11923589843526)),
					//		testset("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", 9, UINTMAX_C(490154852788714))
		};
		template<size_t PLAYER>
		bool test(const testset& set, std::uintmax_t& nodes, typename profiler::durationType& duration) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				historyType history;
				boardType position;
				if (!position.setFen(set.fen()))
				{
					this->output() << "Invalid FEN: " << set.fen() << std::endl;
					this->flushOutput();
					return false;
				}
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == position.movingPlayer())
				{
					this->output() << "Position: " << set.fen() << std::endl;
					this->output() << "Depth:    " << set.depth() << std::endl;
					this->output() << "Expected: " << set.expected() << std::endl;
					this->output() << "Computed: ";
					typename generatorType::contextType* pContext = new typename generatorType::contextType[set.depth() + 1];
					profiler p;
					p.start();
					stackType<PLAYER> stack{ stackType<PLAYER>(position, history, pContext) };
					std::uintmax_t computed{ generatorType::template perft<PLAYER,stackType<PLAYER>>(stack, set.depth(),0, nodes) };
					p.stop();
					delete[] pContext;
					duration += p.duration();
					this->output() << computed << std::endl;
					this->output() << std::endl;
					if (computed == set.expected())
					{
						this->output() << " => PASSED" << std::endl;
						this->flushOutput();
						return true;
					}
					else
					{
						this->output() << " => FAILED" << std::endl;
						this->flushOutput();
						return false;
					}
				}
				else
					return this->template test<PLAYER + 1>(set, nodes, duration);
			}
			else
			{
				PYGMALION_ASSERT(false);
				return false;
			}
		}
		template<size_t PLAYER>
		void process(const size_t maxDepth) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == this->position().movingPlayer())
				{
					bool bPassed{ true };
					constexpr const size_t n{ sizeof(m_Sets) / sizeof(testset) };
					std::uintmax_t nodes{ 0 };
					typename profiler::durationType duration{ 0 };
					for (size_t i = 0; i < n; i++)
					{
						if (m_Sets[i].depth() <= maxDepth)
						{
							bPassed &= this->template test<0>(m_Sets[i], nodes, duration);
							this->output() << std::endl;
							if (!bPassed)
								break;
						}
					}
					if (bPassed)
						this->output() << "ALL PASSED." << std::endl;
					else
						this->output() << "SOME FAILED." << std::endl;
					this->output() << std::endl;
					const profiler::speed spd(static_cast<double>(nodes), duration, "N");
					this->output() << parser::valueToString(static_cast<double>(nodes), "N") << " in " << parser::durationToString(duration) << " => " << spd << std::endl;
				}
				else
					this->template process<PLAYER + 1>(maxDepth);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual std::string help() noexcept override
		{
			return "TEST-MOVEGEN";
		}
		virtual bool onProcess(const std::string& cmd) noexcept override;
	};

}