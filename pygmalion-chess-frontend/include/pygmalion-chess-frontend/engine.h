namespace pygmalion::chess::frontend
{
	template<typename FRONT>
	class engine :
		public pygmalion::frontend::engine<FRONT>
	{
	protected:
		virtual void writeInvalidCommand(const std::string command) noexcept override
		{
#if defined(PYGMALION_WB2)
			this->outputStream() << "Error (Invalid Command): " << command << std::endl;
#endif
		}
	public:
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::frontend::engine<FRONT>(input, output)
		{
#if defined(PYGMALION_WB2)
			this->template addCommand<command_white<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_black<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_time<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_otim<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_rating<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_new<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_result<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_memory<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
#endif
			this->template addCommand<command_debugMaterial<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
		}
#if defined(PYGMALION_UCI)
		virtual bool handleOptions(const std::string& token, const std::string& remainder) noexcept override
		{
#if defined(PYGMALION_TUNE)&&(PYGMALION_TUNE==1)
			std::string remainder2;
			std::string remainder3;
			std::string token2;
			for (const auto pc : pygmalion::frontend::engine<FRONT>::pieceType::range)
			{
				parser::parseToken(remainder, token2, remainder2);
				if (token2 == "name")
				{
					remainder3 = remainder2;
					parser::parseToken(remainder3, token2, remainder2);
					const std::string pattern{ "piece" + parser::fromInt(static_cast<size_t>(pc)) + "_material" };
					if (token2 == pattern)
					{
						remainder3 = remainder2;
						parser::parseToken(remainder3, token2, remainder2);
						if (token2 == "value")
						{
							remainder3 = remainder2;
							parser::parseToken(remainder3, token2, remainder2);
							pygmalion::frontend::engine<FRONT>::boardType::setMaterial(pc, static_cast<double>(parser::parseInt(token2)) / 100.0);
							this->heuristics().transpositionTable().clear();
							return true;
						}
					}
				}
			}
#endif
			return pygmalion::frontend::engine<FRONT>::handleOptions(token, remainder);
		}
#endif
#if defined(PYGMALION_WB2)
		virtual bool handleOptionsWB(const std::string& token, const std::string& remainder) noexcept override
		{
#if defined(PYGMALION_TUNE)&&(PYGMALION_TUNE==1)
			std::string remainder2;
			std::string remainder3;
			std::string token2;
			for (const auto pc : pygmalion::frontend::engine<FRONT>::pieceType::range)
			{
				const std::string pattern{ "piece" + parser::fromInt(static_cast<size_t>(pc)) + "_material" };
				if ((remainder.length() >= pattern.length()) && (parser::toLower(remainder.substr(0, pattern.length())) == pattern))
				{
					remainder2 = remainder.substr(pattern.length(), remainder.length() - pattern.length());
					parser::trim(remainder2);
					if ((remainder2.length() > 0) && (remainder2[0] == '='))
					{
						remainder3 = remainder2.substr(1, remainder2.length() - 1);
						parser::trim(remainder3);
						const auto value{ parser::parseInt(remainder3) };
						pygmalion::frontend::engine<FRONT>::boardType::setMaterial(pc, static_cast<double>(value) / 100.0);
						this->outputStream() << std::endl;
						return true;
					}
				}
			}
#endif
			return pygmalion::frontend::engine<FRONT>::handleOptionsWB(token, remainder);
		}
#endif
		virtual double timeSkew() const noexcept override
		{
			return 8.0;
		}
		virtual void resizeHashTables(const size_t sizeInBytes) noexcept override
		{
			std::int64_t sizeTT = (3 * sizeInBytes) / 4;
			std::int64_t sizePT = (sizeInBytes) / 4;
			this->heuristics().transpositionTable().resize(sizeTT);
			engine::generatorType::pawnTable().resize(sizePT);
		}
		virtual int expectedGameLength() const noexcept override
		{
			return 60;
		}
		virtual int minimumExpectedGameLength() const noexcept override
		{
			return 20;
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "Pygmalion ver. 0.1 alpha";
		}
		virtual std::string author() const noexcept override
		{
			return "Roland Tomasi";
		}
		virtual void getXBoardVariants(std::deque<std::string>& variants) const noexcept override
		{
			variants.emplace_back(std::string("normal"));
		}

	};
}