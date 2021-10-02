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
		constexpr static const typename squaresType::bitsType m_InverseMagicFactors[64]
		{
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8000a0009101000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x5000000020002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x508000230003)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20300a000429)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1a00000802012)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x809004400444000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2808021083000040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc000020020404)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x90004008000088)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x3000600c02a200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x610002000a005520)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9840400000010004)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x480414280000010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x819048540006)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x40000300064000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10a0028044500200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8a0000006001908)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1140000112000810)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x26008030223088)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4090400141000018)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4889804205000300)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x125800000818083)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x802044080010508)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2c01102800000980)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8049800802028c0)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10044c900020001)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x410200080090230)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2000110000300110)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x600804a4a00006)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1000840040440000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa0000000440)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x6ec0911023d00000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x300500a082020000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1000004000110280)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x80022b000204000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4109001013030000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x410204900040402)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x800ca0402421100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1800804250080242)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x547024212001a400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x84a3c8080000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1010044040860004)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8000008030224000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x248010080304)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x60a0010808180004)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x64400c085504101)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2110408006000000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa420048001010006)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa2002020008200a1)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2000080021408000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc02000c000220121)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1000004088106008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10020103c2080208)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc001000046c8102)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x80a1521208120002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x800e6e000012508)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x800400090a0)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x82282000094084)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8020b600004a008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9202801c2001002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x100c10)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc008000404000658)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x200800000a00e28)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x60100514000950))
		};
	public:
		constexpr static typename squaresType::bitsType magicFactor(const size_t index) noexcept
		{
			PYGMALION_ASSERT(index >= 0);
			PYGMALION_ASSERT(index < 64);
			return m_MagicFactors[index];
		}
		constexpr static typename squaresType::bitsType inverseMagicFactor(const size_t index) noexcept
		{
			PYGMALION_ASSERT(index >= 0);
			PYGMALION_ASSERT(index < 64);
			return m_InverseMagicFactors[index];
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