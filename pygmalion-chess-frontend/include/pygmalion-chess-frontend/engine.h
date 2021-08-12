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
		//	this->template addCommand<command_debugSearch<descriptorSearch, nodeType>>();
		//	this->template addCommand<command_debugPvs<descriptorSearch, nodeType>>();
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "no game (frontend only)";
		}
	};
}