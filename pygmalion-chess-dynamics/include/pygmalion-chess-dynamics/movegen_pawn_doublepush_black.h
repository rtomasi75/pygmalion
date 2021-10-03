namespace pygmalion::chess
{
	class propagator_pawn_doublepush_black :
		public pygmalion::dynamics::propagator<descriptor_dynamics, 2, propagator_pawn_doublepush_black, pygmalion::dynamics::ray<0, -1>>
	{
	private:
		constexpr static const typename squaresType::bitsType m_MagicFactors[64]
		{
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10084004f012800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x40000014000100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x100040001000a)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2612200800a81000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2800000000120)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x515600000020000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x44820001400b)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x402801000020000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x28058041041200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20408000c2043001)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8000002500000501)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8100020004a)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x24044040082810)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc141209002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4040b20022030000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4080819180080b10)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4080000010038000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x48200400402080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x60201ac00000c004)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x60504040004000e0)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4080a0000008400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x84a80010400400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x64c2160000800e00)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8201200122498080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x500821002061000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2020401000420440)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10a00146802048)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x30100000000104)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x5c080000020c00)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x88141200200101)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1110284c0000008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10012002200130)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x48000000004)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2004434009008020)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x80092220ac0000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x103001000340a20)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x811020808300208)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8400080c800210c1)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x800010230400500)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2080900010214)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2c00000080004400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1000862070000226)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1000000062201280)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x23c4202011100001)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1140009000052)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x15000204042204)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x828002008000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x28200087403c41)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x290000a08608)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1002000200440000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8100000424a00008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2008c0010145601)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x842000080c002c)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4000010620c0880)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x20200600e8400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1081001230010800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x6620a40004008008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8a000a080c4040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x101a28230a2050)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x80106900041040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8000400000a08840)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8020025470018590)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x500142601002a4)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2088200005008912))
		};
		constexpr static const typename squaresType::bitsType m_InverseMagicFactors[64]
		{
			static_cast<typename squaresType::bitsType>(UINT64_C(0x480129041000010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4048081001300880)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x420450400020a00)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc114004000000008)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1088001050080900)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4000805000b04)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4052600404300200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1000040080000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc0800004018000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x11a548800000200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x200020008010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4044108200011800)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x40480808004820)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x104048030800031)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x600111020c8)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x140101001000a401)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400009042000010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x430408c000100098)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x46000000281)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x402211000085000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8004880048010)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x802080160c081000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8040000200004044)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2000410050800a)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x802188080004061)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8000000040000000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8200020008210)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4400042011006040)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x28820060c0040d0)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400b01060e0002)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x200848a02018000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2023000110)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2105000000808000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x28000f00404200)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10002081220080)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2100100484308402)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x160000880101)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2194002ad0308)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x3010004200123000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10a0014008450000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x5010004804208480)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x3020000520004009)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x35002000002424)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10880a2000001000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x18240c410808)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc8430080010400)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8248033000340)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4000100000a0054c)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xa60001000c04)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x800020000802524)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x4000088000008030)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x400e0000492801)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0xc000c01050000a0)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x3048600010200100)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x140301002c)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x600800008700)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x40040a0400e0014)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x180040080410214)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x8a0112020)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2202080ac1000000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x2040020400002018)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x800600000222a62)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x1145c000042000)),
			static_cast<typename squaresType::bitsType>(UINT64_C(0x10000204002008))
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

	class movegen_pawn_doublepush_black :
		public pygmalion::dynamics::movegen<motor, propagator_pawn_doublepush_black>
	{
	private:
		constexpr static const squaresType pawnToSquares() noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType squares{ none };
			squares |= static_cast<squaresType>(static_cast<rankType>(countRanks - 4));
			return squares;
		}
		constexpr static const squaresType pawnFromSquares() noexcept
		{
			constexpr const squaresType none{ squaresType::none() };
			squaresType squares{ none };
			squares |= static_cast<squaresType>(static_cast<rankType>(countRanks - 2));
			return squares;
		}
	public:
		constexpr movegen_pawn_doublepush_black() noexcept :
			pygmalion::dynamics::movegen<motor, propagator_pawn_doublepush_black>(pawnToSquares(), pawnFromSquares())
		{}
	};
}