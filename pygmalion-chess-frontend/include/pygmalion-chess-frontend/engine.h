namespace pygmalion::chess::frontend
{
	template<typename FRONT>
	class engine :
		public pygmalion::frontend::engine<FRONT>
	{
	public:
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::frontend::engine<FRONT>(input, output)
		{
			this->template addCommand<command_white<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_black<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_time<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_otim<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_rating<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_new<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
			this->template addCommand<command_result<typename pygmalion::frontend::engine<FRONT>::descriptorFrontend, typename pygmalion::frontend::engine<FRONT>::frontType>>();
		}
		virtual double timeSkew() const noexcept override
		{
			return 8.0;
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
			return "no game (frontend only)";
		}
	};
}