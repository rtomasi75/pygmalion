namespace pygmalion::chess
{

	class node :
		public pygmalion::node<descriptor_search>
	{
	public:
		constexpr node(const stackType& stack, std::atomic_bool& isRunning) noexcept :
			pygmalion::node<descriptor_search>(stack, isRunning)
		{

		}
	};
}