namespace pygmalion::chess
{
	class propagator_sliders_hv :
		public pygmalion::dynamics::propagator<descriptor_dynamics, 7, propagator_sliders_hv, pygmalion::dynamics::ray<0, 1>, pygmalion::dynamics::ray<0, -1>, pygmalion::dynamics::ray<1, 0>, pygmalion::dynamics::ray<-1, 0>>
	{
		constexpr static const typename squaresType::bitsType m_MagicFactors[64]
		{
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4080008c20400010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc8c0200010024000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x280100020008008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x100051000210009)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x100143008000300)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2100040006480500)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4100020001000084)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8004800441a300)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x412002081004209)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x809002080400100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x801000600380)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1009001000090060)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xaa00800400820800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x200a000410080a01)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x402001408019200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2842002049009402)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1400808000a04000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1040008020084080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x808200102a0140)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10808048021000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2121010018000450)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8008808002001400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x808001001600)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10020009014b84)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1011c00180002580)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2084400540201002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x600200080100082)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc31002100100289)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1003020500080010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2210013000c0028)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4181008900460004)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x840800080004100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x201401820800083)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10600085804000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x3100108202002240)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x810420012000820)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x848804800800400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc800200800c00)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20301244000508)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x210218a042000904)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2400421808001)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x23000402000c000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x100804203620010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10600c009220030)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc001002548010010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc0002008080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x44020801040010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x89000580410002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2014400662800480)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1000201001400840)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2080200080900180)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10240900100100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x422006030140a00)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8480020080040080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20004c8010200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x5400800100194480)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x68822600110042)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400011002085)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20000a00804010a2)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x41006005100009)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2830042100c0801)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x100d003400022841)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1821110210080584)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x5040020910846))
		};
		constexpr static const typename squaresType::bitsType m_InverseMagicFactors[64]
		{
			static_cast<typename squaresType::bitsType>(UINT64_C(0x80008363400090)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4400020011004c0)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9000c2001014010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2480045000822800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x80080080024400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x200104408220003)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400084112100084)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x100004481000122)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x100080018024c002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1080200080c000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x41002002410410)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1a0803000800802)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2000600210810)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x502000200241028)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc001004890802)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8010800841800100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x140008001804129)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x88838020004005)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x94062004081b200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8008009801001)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xb01000d080011)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x824008022001480)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x100040008100102)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x220120001008044)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x806308080004008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x41000c040042000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20802200401200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa040082100100100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9480100100500)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10000c0080800200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa9400080d50)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8403288200025514)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x304008800280)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8432004401000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x820022004012)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4aa101001002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x17000431001800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x200040080800200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x300100104000802)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400a2000043)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x410800040008020)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x30024220004000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x810048020048012)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x922512842020020)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1009008010004)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8082002890020005)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1008420108040010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2008886891020004)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x180056000400840)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x481020040842200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x40128440220200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x65080280100080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1004009801048080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400100460402801)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x6000804630200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1810808044110200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x680019120804103)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400300241281)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4120820a0032)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1030100100080421)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x86004805502002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1001400022829)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x22200080400c10a)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x424208024050042))
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

	class movegen_sliders_hv :
		public pygmalion::dynamics::movegen<motor, propagator_sliders_hv>
	{
	public:
		constexpr movegen_sliders_hv() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_sliders_hv>(squaresType::all(), squaresType::all())
		{
		}
	};
}