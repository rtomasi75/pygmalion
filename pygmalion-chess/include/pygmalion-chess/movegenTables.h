namespace pygmalion::chess
{
	class movegenTables
	{
	public:
		using bitsType = typename board::bitsType;
		using squareType = typename board::square;
		using playerType = typename board::player;
	private:
		bitsType m_KnightMoveMap[64];
		bitsType m_KingMoveMap[64];
		bitsType m_PawnMoveMap[2][64];
		bitsType m_PawnCaptureMap[2][64];
#if defined(PYGMALION_CPU_BMI2)&&defined(PYGMALION_CPU_X64)
		slidermagic m_SliderMagics[2][64]
		{
			{
				slidermagic(slidermagicinfo(0, false)),
				slidermagic(slidermagicinfo(1, false)),
				slidermagic(slidermagicinfo(2, false)),
				slidermagic(slidermagicinfo(3, false)),
				slidermagic(slidermagicinfo(4, false)),
				slidermagic(slidermagicinfo(5, false)),
				slidermagic(slidermagicinfo(6, false)),
				slidermagic(slidermagicinfo(7, false)),
				slidermagic(slidermagicinfo(8, false)),
				slidermagic(slidermagicinfo(9, false)),
				slidermagic(slidermagicinfo(10, false)),
				slidermagic(slidermagicinfo(11, false)),
				slidermagic(slidermagicinfo(12, false)),
				slidermagic(slidermagicinfo(13, false)),
				slidermagic(slidermagicinfo(14, false)),
				slidermagic(slidermagicinfo(15, false)),
				slidermagic(slidermagicinfo(16, false)),
				slidermagic(slidermagicinfo(17, false)),
				slidermagic(slidermagicinfo(18, false)),
				slidermagic(slidermagicinfo(19, false)),
				slidermagic(slidermagicinfo(20, false)),
				slidermagic(slidermagicinfo(21, false)),
				slidermagic(slidermagicinfo(22, false)),
				slidermagic(slidermagicinfo(23, false)),
				slidermagic(slidermagicinfo(24, false)),
				slidermagic(slidermagicinfo(25, false)),
				slidermagic(slidermagicinfo(26, false)),
				slidermagic(slidermagicinfo(27, false)),
				slidermagic(slidermagicinfo(28, false)),
				slidermagic(slidermagicinfo(29, false)),
				slidermagic(slidermagicinfo(30, false)),
				slidermagic(slidermagicinfo(31, false)),
				slidermagic(slidermagicinfo(32, false)),
				slidermagic(slidermagicinfo(33, false)),
				slidermagic(slidermagicinfo(34, false)),
				slidermagic(slidermagicinfo(35, false)),
				slidermagic(slidermagicinfo(36, false)),
				slidermagic(slidermagicinfo(37, false)),
				slidermagic(slidermagicinfo(38, false)),
				slidermagic(slidermagicinfo(39, false)),
				slidermagic(slidermagicinfo(40, false)),
				slidermagic(slidermagicinfo(41, false)),
				slidermagic(slidermagicinfo(42, false)),
				slidermagic(slidermagicinfo(43, false)),
				slidermagic(slidermagicinfo(44, false)),
				slidermagic(slidermagicinfo(45, false)),
				slidermagic(slidermagicinfo(46, false)),
				slidermagic(slidermagicinfo(47, false)),
				slidermagic(slidermagicinfo(48, false)),
				slidermagic(slidermagicinfo(49, false)),
				slidermagic(slidermagicinfo(50, false)),
				slidermagic(slidermagicinfo(51, false)),
				slidermagic(slidermagicinfo(52, false)),
				slidermagic(slidermagicinfo(53, false)),
				slidermagic(slidermagicinfo(54, false)),
				slidermagic(slidermagicinfo(55, false)),
				slidermagic(slidermagicinfo(56, false)),
				slidermagic(slidermagicinfo(57, false)),
				slidermagic(slidermagicinfo(58, false)),
				slidermagic(slidermagicinfo(59, false)),
				slidermagic(slidermagicinfo(60, false)),
				slidermagic(slidermagicinfo(61, false)),
				slidermagic(slidermagicinfo(62, false)),
				slidermagic(slidermagicinfo(63, false))
			},
			{
				slidermagic(slidermagicinfo(0, true)),
				slidermagic(slidermagicinfo(1, true)),
				slidermagic(slidermagicinfo(2, true)),
				slidermagic(slidermagicinfo(3, true)),
				slidermagic(slidermagicinfo(4, true)),
				slidermagic(slidermagicinfo(5, true)),
				slidermagic(slidermagicinfo(6, true)),
				slidermagic(slidermagicinfo(7, true)),
				slidermagic(slidermagicinfo(8, true)),
				slidermagic(slidermagicinfo(9, true)),
				slidermagic(slidermagicinfo(10, true)),
				slidermagic(slidermagicinfo(11, true)),
				slidermagic(slidermagicinfo(12, true)),
				slidermagic(slidermagicinfo(13, true)),
				slidermagic(slidermagicinfo(14, true)),
				slidermagic(slidermagicinfo(15, true)),
				slidermagic(slidermagicinfo(16, true)),
				slidermagic(slidermagicinfo(17, true)),
				slidermagic(slidermagicinfo(18, true)),
				slidermagic(slidermagicinfo(19, true)),
				slidermagic(slidermagicinfo(20, true)),
				slidermagic(slidermagicinfo(21, true)),
				slidermagic(slidermagicinfo(22, true)),
				slidermagic(slidermagicinfo(23, true)),
				slidermagic(slidermagicinfo(24, true)),
				slidermagic(slidermagicinfo(25, true)),
				slidermagic(slidermagicinfo(26, true)),
				slidermagic(slidermagicinfo(27, true)),
				slidermagic(slidermagicinfo(28, true)),
				slidermagic(slidermagicinfo(29, true)),
				slidermagic(slidermagicinfo(30, true)),
				slidermagic(slidermagicinfo(31, true)),
				slidermagic(slidermagicinfo(32, true)),
				slidermagic(slidermagicinfo(33, true)),
				slidermagic(slidermagicinfo(34, true)),
				slidermagic(slidermagicinfo(35, true)),
				slidermagic(slidermagicinfo(36, true)),
				slidermagic(slidermagicinfo(37, true)),
				slidermagic(slidermagicinfo(38, true)),
				slidermagic(slidermagicinfo(39, true)),
				slidermagic(slidermagicinfo(40, true)),
				slidermagic(slidermagicinfo(41, true)),
				slidermagic(slidermagicinfo(42, true)),
				slidermagic(slidermagicinfo(43, true)),
				slidermagic(slidermagicinfo(44, true)),
				slidermagic(slidermagicinfo(45, true)),
				slidermagic(slidermagicinfo(46, true)),
				slidermagic(slidermagicinfo(47, true)),
				slidermagic(slidermagicinfo(48, true)),
				slidermagic(slidermagicinfo(49, true)),
				slidermagic(slidermagicinfo(50, true)),
				slidermagic(slidermagicinfo(51, true)),
				slidermagic(slidermagicinfo(52, true)),
				slidermagic(slidermagicinfo(53, true)),
				slidermagic(slidermagicinfo(54, true)),
				slidermagic(slidermagicinfo(55, true)),
				slidermagic(slidermagicinfo(56, true)),
				slidermagic(slidermagicinfo(57, true)),
				slidermagic(slidermagicinfo(58, true)),
				slidermagic(slidermagicinfo(59, true)),
				slidermagic(slidermagicinfo(60, true)),
				slidermagic(slidermagicinfo(61, true)),
				slidermagic(slidermagicinfo(62, true)),
				slidermagic(slidermagicinfo(63, true))
			}
		};
#else
		slidermagic m_SliderMagics[2][64]
		{
			{
				slidermagic(slidermagicinfo(0, false), 0x8280002140001084),
				slidermagic(slidermagicinfo(1, false), 0x4180200040018250),
				slidermagic(slidermagicinfo(2, false), 0x8100082001110043),
				slidermagic(slidermagicinfo(3, false), 0x31000821004c1002),
				slidermagic(slidermagicinfo(4, false), 0x0600208450080a00),
				slidermagic(slidermagicinfo(5, false), 0x220001100200c804),
				slidermagic(slidermagicinfo(6, false), 0x84000a0081100814),
				slidermagic(slidermagicinfo(7, false), 0x0600028024020443),
				slidermagic(slidermagicinfo(8, false), 0x00968000401c2080),
				slidermagic(slidermagicinfo(9, false), 0x0c00c00050002008),
				slidermagic(slidermagicinfo(10, false), 0x0800808010002000),
				slidermagic(slidermagicinfo(11, false), 0x0402801000800800),
				slidermagic(slidermagicinfo(12, false), 0x1006800800540080),
				slidermagic(slidermagicinfo(13, false), 0x220880800c000a00),
				slidermagic(slidermagicinfo(14, false), 0x8004000a34010810),
				slidermagic(slidermagicinfo(15, false), 0x0042000100409214),
				slidermagic(slidermagicinfo(16, false), 0x101080800020c001),
				slidermagic(slidermagicinfo(17, false), 0x0040010041028020),
				slidermagic(slidermagicinfo(18, false), 0x4001010010200049),
				slidermagic(slidermagicinfo(19, false), 0x0005010020081000),
				slidermagic(slidermagicinfo(20, false), 0x2125010010080084),
				slidermagic(slidermagicinfo(21, false), 0x0009808004000a00),
				slidermagic(slidermagicinfo(22, false), 0x1000240008112250),
				slidermagic(slidermagicinfo(23, false), 0x0000020000804104),
				slidermagic(slidermagicinfo(24, false), 0x0240002180064080),
				slidermagic(slidermagicinfo(25, false), 0x10401003402000c1),
				slidermagic(slidermagicinfo(26, false), 0x5420022080300080),
				slidermagic(slidermagicinfo(27, false), 0x0002002200089440),
				slidermagic(slidermagicinfo(28, false), 0x0008000500100900),
				slidermagic(slidermagicinfo(29, false), 0x2010260080800400),
				slidermagic(slidermagicinfo(30, false), 0x0110065400450850),
				slidermagic(slidermagicinfo(31, false), 0x10800926000188c4),
				slidermagic(slidermagicinfo(32, false), 0x020280c000800024),
				slidermagic(slidermagicinfo(33, false), 0xc301406004401000),
				slidermagic(slidermagicinfo(34, false), 0x8000801000802009),
				slidermagic(slidermagicinfo(35, false), 0x0020808800801002),
				slidermagic(slidermagicinfo(36, false), 0x0008014880800400),
				slidermagic(slidermagicinfo(37, false), 0x0082000400802280),
				slidermagic(slidermagicinfo(38, false), 0x0001908204000801),
				slidermagic(slidermagicinfo(39, false), 0x0400800048800100),
				slidermagic(slidermagicinfo(40, false), 0x0080004020004001),
				slidermagic(slidermagicinfo(41, false), 0x8040081000a02000),
				slidermagic(slidermagicinfo(42, false), 0x0011002000510040),
				slidermagic(slidermagicinfo(43, false), 0x000420104202000a),
				slidermagic(slidermagicinfo(44, false), 0x00140080a8008004),
				slidermagic(slidermagicinfo(45, false), 0x0000a40002008080),
				slidermagic(slidermagicinfo(46, false), 0x0702000c89020028),
				slidermagic(slidermagicinfo(47, false), 0x00000041009e0004),
				slidermagic(slidermagicinfo(48, false), 0x0010258010400080),
				slidermagic(slidermagicinfo(49, false), 0x0000400085210100),
				slidermagic(slidermagicinfo(50, false), 0x4801004091200100),
				slidermagic(slidermagicinfo(51, false), 0x0200081000210100),
				slidermagic(slidermagicinfo(52, false), 0x0101040080880180),
				slidermagic(slidermagicinfo(53, false), 0x0042420004008080),
				slidermagic(slidermagicinfo(54, false), 0x0000111008020c00),
				slidermagic(slidermagicinfo(55, false), 0x0004824110840a00),
				slidermagic(slidermagicinfo(56, false), 0x0032002081004012),
				slidermagic(slidermagicinfo(57, false), 0x0008108040010021),
				slidermagic(slidermagicinfo(58, false), 0x0020f10042086001),
				slidermagic(slidermagicinfo(59, false), 0x8029006144981001),
				slidermagic(slidermagicinfo(60, false), 0x0102000420500882),
				slidermagic(slidermagicinfo(61, false), 0x050a004810010406),
				slidermagic(slidermagicinfo(62, false), 0x4000010600881004),
				slidermagic(slidermagicinfo(63, false), 0x0002004400810062)
			},
			{
				slidermagic(slidermagicinfo(0, true), 0x01404a020a420088),
				slidermagic(slidermagicinfo(1, true), 0x0319020802006000),
				slidermagic(slidermagicinfo(2, true), 0x0810008883002100),
				slidermagic(slidermagicinfo(3, true), 0x0854040090200880),
				slidermagic(slidermagicinfo(4, true), 0x10040c200c404078),
				slidermagic(slidermagicinfo(5, true), 0x0201110840200340),
				slidermagic(slidermagicinfo(6, true), 0x100b082210840106),
				slidermagic(slidermagicinfo(7, true), 0x8130404408884041),
				slidermagic(slidermagicinfo(8, true), 0x38012020020a0160),
				slidermagic(slidermagicinfo(9, true), 0x48000430022202a2),
				slidermagic(slidermagicinfo(10, true), 0x08020c080200c100),
				slidermagic(slidermagicinfo(11, true), 0x4840141400800e00),
				slidermagic(slidermagicinfo(12, true), 0x13200c1028004408),
				slidermagic(slidermagicinfo(13, true), 0x0100020844040a00),
				slidermagic(slidermagicinfo(14, true), 0x6048008801101000),
				slidermagic(slidermagicinfo(15, true), 0x04682310480c0c00),
				slidermagic(slidermagicinfo(16, true), 0x0020001420020212),
				slidermagic(slidermagicinfo(17, true), 0x02080b8288280280),
				slidermagic(slidermagicinfo(18, true), 0x00500012040140c8),
				slidermagic(slidermagicinfo(19, true), 0x0008110082004100),
				slidermagic(slidermagicinfo(20, true), 0x0084000880a00080),
				slidermagic(slidermagicinfo(21, true), 0x0040802048200800),
				slidermagic(slidermagicinfo(22, true), 0x80e854e209100808),
				slidermagic(slidermagicinfo(23, true), 0x00aa042082809800),
				slidermagic(slidermagicinfo(24, true), 0x1010c4004108020a),
				slidermagic(slidermagicinfo(25, true), 0x0090040508218408),
				slidermagic(slidermagicinfo(26, true), 0x1001030850024a01),
				slidermagic(slidermagicinfo(27, true), 0x0000802012020200),
				slidermagic(slidermagicinfo(28, true), 0x5001040002002111),
				slidermagic(slidermagicinfo(29, true), 0x0009110000300800),
				slidermagic(slidermagicinfo(30, true), 0x0011220004208400),
				slidermagic(slidermagicinfo(31, true), 0x2200810118b40215),
				slidermagic(slidermagicinfo(32, true), 0x0001205020a00464),
				slidermagic(slidermagicinfo(33, true), 0x0000900810c40840),
				slidermagic(slidermagicinfo(34, true), 0x80040101800c0402),
				slidermagic(slidermagicinfo(35, true), 0x0000228080480200),
				slidermagic(slidermagicinfo(36, true), 0x001002060038a008),
				slidermagic(slidermagicinfo(37, true), 0x8080c58200010100),
				slidermagic(slidermagicinfo(38, true), 0x2a02040100040080),
				slidermagic(slidermagicinfo(39, true), 0x0480810a06010180),
				slidermagic(slidermagicinfo(40, true), 0x01082422a0805810),
				slidermagic(slidermagicinfo(41, true), 0x0113080110000c04),
				slidermagic(slidermagicinfo(42, true), 0x0000a12228001000),
				slidermagic(slidermagicinfo(43, true), 0x1000002218008400),
				slidermagic(slidermagicinfo(44, true), 0x40004843040000c0),
				slidermagic(slidermagicinfo(45, true), 0xb1010208020000c0),
				slidermagic(slidermagicinfo(46, true), 0x18d2080800900100),
				slidermagic(slidermagicinfo(47, true), 0x098420a891002200),
				slidermagic(slidermagicinfo(48, true), 0x120400d828081001),
				slidermagic(slidermagicinfo(49, true), 0x0001008804428008),
				slidermagic(slidermagicinfo(50, true), 0x49001100a0900000),
				slidermagic(slidermagicinfo(51, true), 0x0090891042020012),
				slidermagic(slidermagicinfo(52, true), 0xc0040020264406d0),
				slidermagic(slidermagicinfo(53, true), 0x2100481001820028),
				slidermagic(slidermagicinfo(54, true), 0x0040160204010000),
				slidermagic(slidermagicinfo(55, true), 0x000310040100c000),
				slidermagic(slidermagicinfo(56, true), 0x5046104414202800),
				slidermagic(slidermagicinfo(57, true), 0x5481003404020807),
				slidermagic(slidermagicinfo(58, true), 0x0000020904010401),
				slidermagic(slidermagicinfo(59, true), 0x0200200980460800),
				slidermagic(slidermagicinfo(60, true), 0x00040e0210020e10),
				slidermagic(slidermagicinfo(61, true), 0x010081b010100121),
				slidermagic(slidermagicinfo(62, true), 0x0000400808018090),
				slidermagic(slidermagicinfo(63, true), 0x0808208d86004100)
			}
		};
#endif
	public:
		const slidermagic& magic(const bool diagonal, const squareType square) const noexcept
		{
			assert(square.isValid());
			return m_SliderMagics[diagonal][square];
		}
		slidermagic& magic(const bool diagonal, const squareType square) noexcept
		{
			assert(square.isValid());
			return m_SliderMagics[diagonal][square];
		}
		constexpr auto knightMoveMap(const squareType sq) const noexcept
		{
			assert(sq.isValid());
			return m_KnightMoveMap[sq];
		}
		constexpr auto kingMoveMap(const squareType sq) const noexcept
		{
			assert(sq.isValid());
			return m_KingMoveMap[sq];
		}
		void pawnMoveMap_Debug(const squareType sq, const playerType p) const noexcept;
		auto pawnMoveMap(const squareType sq, const playerType p) const noexcept
		{
			assert(sq.isValid());
			assert(p.isValid());
			return m_PawnMoveMap[p][sq];
		}
		constexpr auto pawnCaptureMap(const squareType sq, const playerType p) const noexcept
		{
			assert(sq.isValid());
			assert(p.isValid());
			return m_PawnCaptureMap[p][sq];
		}
		bitsType sliderAttackMask(const bool diagonal, const squareType square, const bitsType blockers) const noexcept
		{
			assert(square.isValid());
			return m_SliderMagics[diagonal][square][blockers];
		}
		void sliderMoveMaps(const bool diagonal, const squareType square, const bitsType blockers, const bitsType captureTargets, bitsType& moves, bitsType& captures) const noexcept
		{
			assert(square.isValid());
			const bitsType attackMask{ sliderAttackMask(diagonal,square,blockers) };
			moves |= attackMask & ~blockers;
			captures |= attackMask & captureTargets;
		}
		bitsType sliderAttacks(const bool diagonal, const squareType square, const bitsType blockers, const bitsType xrays) const noexcept
		{
			assert(square.isValid());
			const bitsType attackMask{ sliderAttackMask(diagonal,square,blockers) };
			return attackMask & xrays;
		}

		movegenTables() noexcept;
		~movegenTables() noexcept = default;
	};
}