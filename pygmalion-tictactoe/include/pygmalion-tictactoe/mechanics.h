namespace pygmalion::tictactoe
{
	class mechanics :
		public pygmalion::mechanics<descriptor_mechanics, mechanics>
	{
	public:
		class movedata : public pygmalion::mechanics<descriptor_mechanics, mechanics>::movedata
		{
		private:
			squareType m_TargetSquare;
		public:
			constexpr movedata(boardType& position, const playerType oldPlayer) noexcept :
				pygmalion::mechanics<descriptor_mechanics, mechanics>::movedata(position, oldPlayer),
				m_TargetSquare{ squareType::invalid }
			{

			}
			constexpr movedata(boardType& position, const moveType& mv) noexcept :
				pygmalion::mechanics<descriptor_mechanics, mechanics>::movedata(position, mv),
				m_TargetSquare{ mv.square(0) }
			{
			}
			~movedata() noexcept = default;
			constexpr squareType targetSquare() const noexcept
			{
				return m_TargetSquare;
			}
		};
		using movedataType = movedata;

		static void initializePosition_Implementation(boardType& position) noexcept
		{
			return position.clear();
		}
		static void makeMove_Implementation(boardType& position, const movedataType& md) noexcept
		{
			position.addPiece(0, md.targetSquare(), md.movingPlayer());
			position.setMovingPlayer(md.movingPlayer().next());
		}
		static void unmakeMove_Implementation(boardType& position, const movedataType& md) noexcept
		{
			position.removePiece(0, md.targetSquare(), md.movingPlayer());
			position.setMovingPlayer(md.movingPlayer());
		}
	};
}