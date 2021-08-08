namespace pygmalion::search
{
	template<typename NODE>
	class engine :
		public pygmalion::evaluation::engine<typename NODE::evaluatorType>,
		public NODE::descriptorSearch
	{
	public:
		using nodeType = NODE;
		using descriptorSearch = typename NODE::descriptorSearch;
#include "include_search.h"
	private:
	public:
		engine() noexcept = delete;
		engine(const engine&) = delete;
		engine(engine&&) = delete;
		engine(std::istream& input, std::ostream& output) noexcept :
			pygmalion::evaluation::engine<typename NODE::evaluatorType>(input, output)
		{
			this->template addCommand<command_debugSearch<descriptorSearch, nodeType>>();
			this->template addCommand<command_debugPvs<descriptorSearch, nodeType>>();
		}
		virtual ~engine() noexcept = default;
		virtual std::string version() const noexcept override
		{
			return "no game (search only)";
		}
	};
}