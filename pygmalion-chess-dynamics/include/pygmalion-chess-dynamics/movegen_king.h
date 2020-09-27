namespace pygmalion::chess
{
	class propagator_king :
		public pygmalion::dynamics::propagator<descriptor_dynamics, 1, propagator_king,  pygmalion::dynamics::ray<-1, -1>, pygmalion::dynamics::ray<-1, 0>, pygmalion::dynamics::ray<-1, 1>, pygmalion::dynamics::ray<0, -1>, pygmalion::dynamics::ray<0, 1>, pygmalion::dynamics::ray<1, -1>, pygmalion::dynamics::ray<1, 0>, pygmalion::dynamics::ray<1, 1>>
	{};

	class movegen_king :
		public pygmalion::dynamics::movegen<motor, propagator_king>
	{
	public:
		constexpr movegen_king() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_king>(squaresType::all(), squaresType::all())
		{}
	};
}