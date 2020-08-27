namespace pygmalion::tictactoe
{
	class engine : public pygmalion::engine<pygmalion::tictactoe::frontend>
	{
	private:
		class command_debugPattern : public commandType
		{
		private:
			static void dumpPattern(const typename boardType::bitsType& pattern, std::ostream& stream) noexcept
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						int idx = i * 3 + j;
						stream << (pattern.checkBit(idx) ? "#" : ".");
					}
					stream << std::endl;
				}
				stream << "population = " << static_cast<size_t>(pattern.populationCount());
				stream << std::endl;
			}
		protected:
			virtual bool onProcess(engineType& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-pattern")
				{
					eng.outputStream() << std::endl;
					std::string token2;
					std::string remainder2;
					parser::parseToken(remainder, token2, remainder2);
					if (token2 == "line")
					{
						int line = parser::parseInt(remainder2);
						if ((line < 0) || (line >= patterns::lineCount))
						{
							eng.outputStream() << "invalid line: " << remainder2 << std::endl;
						}
						else
						{
							eng.outputStream() << "line " << line << ":" << std::endl;
							dumpPattern(patterns::line(line), eng.outputStream());
						}
					}
					else if (token2 == "occupancy")
					{
						if (remainder2 == "white")
						{
							eng.outputStream() << "white occupancy:" << std::endl;
							dumpPattern(eng.board().playerOccupancy(static_cast<playerType>(0)), eng.outputStream());
						}
						else	if (remainder2 == "black")

						{
							eng.outputStream() << "black occupancy:" << std::endl;
							dumpPattern(eng.board().playerOccupancy(static_cast<playerType>(1)), eng.outputStream());
						}
						else
						{
							eng.outputStream() << "invalid player: " << remainder2 << std::endl;
						}
					}
					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
		class command_debugMagic : public commandType
		{
		private:
		protected:
			virtual bool onProcess(engineType& eng, const std::string& cmd) const noexcept override
			{
				std::string token;
				std::string remainder;
				parser::parseToken(cmd, token, remainder);
				if (token == "debug-magic")
				{
					eng.outputStream() << std::endl;
					std::string table;
					std::string remainder2;
					parser::parseToken(remainder, table, remainder2);
					if (table == "moves" || table == "move" || table == "m")
					{
#if !defined(PYGMALION_CPU_BMI2)
						eng.outputStream() << "refreshing move magics..." << std::endl;
						movegen::magic() = movemagic(movemagicinfo());
						eng.outputStream() << "...done." << std::endl;
						eng.outputStream() << std::endl;
						eng.outputStream() << "movemagic movegen::m_Magic{ movemagic(movemagicinfo(), " << parser::toString(movegen::magic().factor()) << ") }; " << std::endl;
#else
						eng.outputStream() << "(no magics used)" << std::endl;
#endif
					}
					else
						eng.outputStream() << "invalid table: " << table << std::endl;

					eng.outputStream() << std::endl;
					return true;
				}
				else
					return false;
			}
		};
	public:
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::engine<pygmalion::tictactoe::frontend>(input, output)
		{
			addCommand<command_debugPattern>();
			addCommand<command_debugMagic>();
		}

	};
}