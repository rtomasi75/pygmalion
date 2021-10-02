namespace pygmalion::chess
{
	class propagator_sliders_diag :
		public pygmalion::dynamics::propagator<descriptor_dynamics, 7, propagator_sliders_diag, pygmalion::dynamics::ray<1, 1>, pygmalion::dynamics::ray<1, -1>, pygmalion::dynamics::ray<-1, 1>, pygmalion::dynamics::ray<-1, -1>>
	{
	private:
		constexpr static const typename squaresType::bitsType m_MagicFactors[64]
		{
			static_cast<typename squaresType::bitsType>(UINT64_C(0x310205810802040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9008022806410401)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x110008c81000002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x208094101080050)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x405a004016020)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x22820180004a8)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x402080602100812)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20114041c040400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8000140818014400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2055308420840040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x81640c00a20002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10910404840008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x108040308000238)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10020822480000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc00001c222104021)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4488002088280841)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4028500420c40402)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x444240821080200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x80201a504010202)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x801200c0c0080a8)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x101000890401001)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4040c00200422000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1100158080400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x5042000020840408)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2008402120040100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x24300021012100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8221010040044)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8112080154004009)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9020044082003001)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8208002016100400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4130024008280)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc000420224410400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10901000082200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x3308019000088208)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20040a4100c80200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x180a910800240040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8010408020820200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1002018200030800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x61010500041400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8010020004202)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x411080a344000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x111068250c02000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9220840401009200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2040060102400c00)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20e0188502401401)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10602084209100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1200802228000d2)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x204089202100048)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x3080550680000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x859040111090021)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x624010898040484)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa000080420980000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9420101002020400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x41043810c30008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x261880208004050)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x14082218c20200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x100808c20224c)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4000020100880400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x200044040c23)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x420020964208801)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x100011020200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x12000050a009010c)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x208802280050)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x3020042108012080))
		};
		constexpr static const typename squaresType::bitsType m_InverseMagicFactors[64]
		{
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2103002004042)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8018220444006014)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x6106008a000000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x11040481000090)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2024042008020020)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1012010201010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8884130304005)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x14020e026009)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2c00411001010100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x40410100201c540)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x40480c0804890020)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa024083008500)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400c2110400000c0)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4400020504220100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x410c30402024004)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x200410402840450)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x940001010a10100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4810280424088401)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x50002090204040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1008210904010280)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x104004202110100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8082810080c000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8001200188082200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x401482081100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4040011208800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x410102008022092)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2004500203110200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2000488098020040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x201001011004004)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4a0001011900)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8840c0004410c00)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x82020020250100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc104422000286000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa61000291000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xaa1084040080080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x9000020080280080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8b2418020020200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20c8201800c1009)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x3001041404050108)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc8008062010101)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x88080450000411)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8a280402000400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8100884410000202)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2800a124001800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x210422320c000602)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2400484a2801102)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2890814204100080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x18a842400202080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa006809010900080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x202e020984040000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x124408548088040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2023100042060410)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2221243102020428)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4000081001021000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4483805040001)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x3101b0129020000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4828190012040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa805208050803)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400c08600c22200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4280000208818)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2a000040082200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x320a804008218100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4009262060c0410)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1404102020e0822))
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

	class movegen_sliders_diag :
		public pygmalion::dynamics::movegen<motor, propagator_sliders_diag>
	{
	public:
		constexpr movegen_sliders_diag() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_sliders_diag>(squaresType::all(), squaresType::all())
		{
		}
	};
}