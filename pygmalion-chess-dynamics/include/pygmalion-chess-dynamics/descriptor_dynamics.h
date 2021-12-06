namespace pygmalion::chess
{
	class descriptor_dynamics :
		public pygmalion::descriptor_dynamics<motor, 255>
	{
	public:
		constexpr static bool inline usePieceType{ false };
		constexpr static unsigned int maxTopismDistance{ 4};
	};
}