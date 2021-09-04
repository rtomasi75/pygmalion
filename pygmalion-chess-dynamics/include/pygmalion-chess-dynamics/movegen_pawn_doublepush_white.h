namespace pygmalion::chess
{
	class propagator_pawn_doublepush_white :
		public pygmalion::dynamics::propagator<descriptor_dynamics, 2, propagator_pawn_doublepush_white, pygmalion::dynamics::ray<0, 1>>
	{
	private:
		constexpr static const typename squaresType::bitsType m_MagicFactors[64]
		{
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9289108939c00000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x43010020000200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20500001810000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8010282440001190)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xd480090018000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x404040820200008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x224800882900c8)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4021000001104800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9800090070600)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xd1600210020000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x30060000000180c)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x880120400113002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x180080051000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x500240000a02000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8205021804040018)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xe10000180040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10a8011001500)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2040084240004205)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa0025a0800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1100040501)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400801020030)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x42400400220800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4401202054408)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1190140200600)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2109a800400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x3000100049080042)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1800208038000000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20000400100522a0)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x840288801280)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2210124000221)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa900830212000408)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1200088090100a6)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x200000ac1200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x200104a000404082)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc20006200200012)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x234001400101400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8700000000480050)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400008000151000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400004c00021002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x800a08200030340)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400008000200c02a)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8080800100004421)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1140308044002a24)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x5000085000005000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9010c88024c10800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1100109000008440)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2800000010008300)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4010151a)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8100d002000800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8040600188100000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc009004000000b04)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1050188082000000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8000848120000000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2001a09000000880)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x6002010050000800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc882100002008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x80801828200040c0)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x200a901303082048)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1842011800804000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x802000400908220)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x810806010068804)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa430a0200000000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2002084400002000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x80088008401081))
		};
	public:
		constexpr static typename squaresType::bitsType magicFactor(const size_t index) noexcept
		{
			assert(index >= 0);
			assert(index < 64);
			return m_MagicFactors[index];
		}
	};

	class movegen_pawn_doublepush_white :
		public pygmalion::dynamics::movegen<motor, propagator_pawn_doublepush_white>
	{
	private:
		constexpr static const squaresType pawnToSquares() noexcept
		{
			squaresType squares{ squaresType::none() };
			squares |= static_cast<squaresType>(static_cast<rankType>(3));
			return squares;
		}
		constexpr static const squaresType pawnFromSquares() noexcept
		{
			squaresType squares{ squaresType::none() };
			squares |= static_cast<squaresType>(static_cast<rankType>(1));
			return squares;
		}
	public:
		constexpr movegen_pawn_doublepush_white() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_pawn_doublepush_white>(pawnToSquares(), pawnFromSquares())
		{}
	};
}