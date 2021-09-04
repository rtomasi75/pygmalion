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
	public:
		constexpr static typename squaresType::bitsType magicFactor(const size_t index) noexcept
		{
			assert(index >= 0);
			assert(index < 64);
			return m_MagicFactors[index];
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