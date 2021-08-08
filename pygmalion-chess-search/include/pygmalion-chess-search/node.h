namespace pygmalion::chess
{

	class node :
		public pygmalion::node<descriptor_search>
	{
	public:
		constexpr node(const stackType& stack) noexcept :
			pygmalion::node<descriptor_search>(stack)
		{

		}
	};
}