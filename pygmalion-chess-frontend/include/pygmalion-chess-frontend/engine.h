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
		}
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