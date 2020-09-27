namespace pygmalion::chess
{
	class propagator_knight :
		public pygmalion::dynamics::propagator<descriptor_dynamics, 1, propagator_knight, pygmalion::dynamics::ray<2, 1>, pygmalion::dynamics::ray<1, 2>, pygmalion::dynamics::ray<-2, 1>, pygmalion::dynamics::ray<-1, 2>, pygmalion::dynamics::ray<2, -1>, pygmalion::dynamics::ray<1, -2>, pygmalion::dynamics::ray<-2, -1>, pygmalion::dynamics::ray<-1, -2>>
	{};

	class movegen_knight :
		public pygmalion::dynamics::movegen<motor, propagator_knight>
	{
	public:
		constexpr movegen_knight() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_knight>(squaresType::all(), squaresType::all())
		{}
	};
}