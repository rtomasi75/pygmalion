namespace pygmalion::chess
{
	class descriptor_dynamics :
		public pygmalion::descriptor_dynamics<motor, 255, 31, 15, 1024, 15, 7, 4, 4, 1, 1>
	{
	public:
		constexpr static bool inline usePieceType{ true };
	};
}