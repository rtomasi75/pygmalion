namespace pygmalion::chess::frontend
{
	template<typename FRONT>
	class engine :
		public pygmalion::frontend::engine<FRONT>
	{
	private:

	public:
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::frontend::engine<FRONT>(input, output)
		{
			this->template addCommand<command_white<descriptorFrontend, frontType>>();
			this->template addCommand<command_black<descriptorFrontend, frontType>>();
			this->template addCommand<command_time<descriptorFrontend, frontType>>();
			this->template addCommand<command_otim<descriptorFrontend, frontType>>();
			this->template addCommand<command_rating<descriptorFrontend, frontType>>();
			this->template addCommand<command_new<descriptorFrontend, frontType>>();
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "no game (frontend only)";
		}
	};
}