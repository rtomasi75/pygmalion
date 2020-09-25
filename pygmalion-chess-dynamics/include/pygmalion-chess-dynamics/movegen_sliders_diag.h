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
	public:
		constexpr static typename squaresType::bitsType magicFactor(const size_t index) noexcept
		{
			return m_MagicFactors[index];
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