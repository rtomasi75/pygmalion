namespace pygmalion::chess
{
	using descriptor_mechanics = pygmalion::descriptor_mechanics<combinedmoves, 10, 256>;

	class motor :
		public pygmalion::motor<descriptor_mechanics, motor>
	{
	public:
		PYGMALION_INLINE static bool isTacticalMove_Implementation(const movebitsType& movebits) noexcept
		{
			return combinedmoves::isCapture(movebits);
		}

	};
}