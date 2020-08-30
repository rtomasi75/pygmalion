namespace pygmalion::tictactoe
{

	class board : public pygmalion::board<descriptor_board>
	{
	private:
	public:
		constexpr board() noexcept :
			pygmalion::board<descriptor_board>()
		{
		}
		constexpr board(const board&) noexcept = default;
		constexpr board(board&&) noexcept = default;
		~board() = default;
		constexpr board& operator=(const board&) = default;
		constexpr board& operator=(board&&) = default;
	};

}