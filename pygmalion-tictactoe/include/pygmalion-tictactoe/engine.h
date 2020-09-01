namespace pygmalion::tictactoe
{
	class engine : public pygmalion::engine<pygmalion::tictactoe::frontend>
	{
	private:
		class command_debugPattern : public commandType
		{
		private:
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
						if ((line < 0) || (line >= patterns<descriptorBoard>::countLines))
						{
							eng.outputStream() << "invalid line: " << remainder2 << std::endl;
						}
						else
						{
							eng.outputStream() << "line " << line << ":" << std::endl;
							frontendType::dumpSquares(evaluationType::patterns().line(line), eng.outputStream());
						}
					}
					else if (token2 == "occupancy")
					{
						if (remainder2 == "white")
						{
							eng.outputStream() << "white occupancy:" << std::endl;
							frontendType::dumpSquares(eng.board().playerOccupancy(static_cast<playerType>(0)), eng.outputStream());
						}
						else	if (remainder2 == "black")

						{
							eng.outputStream() << "black occupancy:" << std::endl;
							frontendType::dumpSquares(eng.board().playerOccupancy(static_cast<playerType>(1)), eng.outputStream());
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
						eng.outputStream() << "computing move table..." << std::endl;
						movetable<descriptorGenerator> table;
						auto premask{ table.magic().premask() };
						auto factor{ premask };
						int bits;
						table.magic().find(premask, factor, bits);
						eng.outputStream() << "...done." << std::endl;
						eng.outputStream() << std::endl;
						eng.outputStream() << "static inline movetable<descriptor_generator> moveTable{ movetable<descriptor_generator>(" << parser::toString(premask) << ", " << parser::toString(factor) << ", " << static_cast<int>(bits) << ") }; " << std::endl;
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