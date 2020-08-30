namespace pygmalion::chess
{
	class stack : public  pygmalion::stack<pygmalion::chess::movedata, descriptor_movegen>
	{
	public:
		stack(const stack& parent, const moveType mv) noexcept :
			pygmalion::stack<board, pygmalion::chess::movedata, descriptor_board, descriptor_movegen>(parent, mv)
		{
		}
		stack(boardType& position, const playerType oldPlayer) noexcept :
			pygmalion::stack<board, pygmalion::chess::movedata, descriptor_board, descriptor_movegen>(position, oldPlayer)
		{

		}
	};
}