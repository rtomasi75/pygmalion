namespace pygmalion::chess
{
	template<typename DESCRIPTION_GENERATOR>
	class generatorTables :
		public base_generator<DESCRIPTION_GENERATOR>
	{
	public:

		using descriptorGenerator = DESCRIPTION_GENERATOR;
#include "pygmalion-core/include_generator.h"

	private:
		squaresType m_KnightMoveMap[64];
		squaresType m_KingMoveMap[64];
		squaresType m_PawnMoveMap[2][64];
		squaresType m_PawnCaptureMap[2][64];
#if defined(PYGMALION_CPU_BMI2)&&defined(PYGMALION_CPU_X64)
		slidermagic<descriptorGenerator> m_SliderMagics[2][64]
		{
			{
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(0, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(1, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(2, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(3, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(4, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(5, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(6, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(7, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(8, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(9, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(10, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(11, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(12, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(13, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(14, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(15, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(16, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(17, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(18, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(19, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(20, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(21, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(22, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(23, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(24, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(25, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(26, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(27, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(28, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(29, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(30, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(31, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(32, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(33, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(34, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(35, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(36, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(37, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(38, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(39, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(40, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(41, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(42, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(43, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(44, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(45, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(46, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(47, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(48, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(49, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(50, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(51, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(52, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(53, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(54, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(55, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(56, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(57, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(58, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(59, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(60, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(61, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(62, false)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(63, false))
			},
			{
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(0, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(1, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(2, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(3, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(4, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(5, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(6, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(7, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(8, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(9, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(10, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(11, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(12, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(13, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(14, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(15, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(16, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(17, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(18, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(19, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(20, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(21, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(22, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(23, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(24, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(25, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(26, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(27, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(28, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(29, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(30, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(31, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(32, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(33, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(34, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(35, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(36, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(37, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(38, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(39, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(40, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(41, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(42, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(43, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(44, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(45, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(46, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(47, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(48, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(49, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(50, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(51, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(52, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(53, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(54, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(55, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(56, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(57, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(58, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(59, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(60, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(61, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(62, true)),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(63, true))
			}
		};
#else
		slidermagic<descriptorGenerator> m_SliderMagics[2][64]
		{
			{
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(0, false), 0x8280002140001084),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(1, false), 0x4180200040018250),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(2, false), 0x8100082001110043),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(3, false), 0x31000821004c1002),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(4, false), 0x0600208450080a00),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(5, false), 0x220001100200c804),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(6, false), 0x84000a0081100814),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(7, false), 0x0600028024020443),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(8, false), 0x00968000401c2080),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(9, false), 0x0c00c00050002008),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(10, false), 0x0800808010002000),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(11, false), 0x0402801000800800),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(12, false), 0x1006800800540080),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(13, false), 0x220880800c000a00),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(14, false), 0x8004000a34010810),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(15, false), 0x0042000100409214),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(16, false), 0x101080800020c001),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(17, false), 0x0040010041028020),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(18, false), 0x4001010010200049),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(19, false), 0x0005010020081000),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(20, false), 0x2125010010080084),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(21, false), 0x0009808004000a00),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(22, false), 0x1000240008112250),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(23, false), 0x0000020000804104),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(24, false), 0x0240002180064080),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(25, false), 0x10401003402000c1),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(26, false), 0x5420022080300080),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(27, false), 0x0002002200089440),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(28, false), 0x0008000500100900),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(29, false), 0x2010260080800400),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(30, false), 0x0110065400450850),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(31, false), 0x10800926000188c4),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(32, false), 0x020280c000800024),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(33, false), 0xc301406004401000),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(34, false), 0x8000801000802009),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(35, false), 0x0020808800801002),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(36, false), 0x0008014880800400),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(37, false), 0x0082000400802280),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(38, false), 0x0001908204000801),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(39, false), 0x0400800048800100),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(40, false), 0x0080004020004001),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(41, false), 0x8040081000a02000),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(42, false), 0x0011002000510040),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(43, false), 0x000420104202000a),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(44, false), 0x00140080a8008004),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(45, false), 0x0000a40002008080),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(46, false), 0x0702000c89020028),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(47, false), 0x00000041009e0004),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(48, false), 0x0010258010400080),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(49, false), 0x0000400085210100),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(50, false), 0x4801004091200100),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(51, false), 0x0200081000210100),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(52, false), 0x0101040080880180),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(53, false), 0x0042420004008080),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(54, false), 0x0000111008020c00),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(55, false), 0x0004824110840a00),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(56, false), 0x0032002081004012),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(57, false), 0x0008108040010021),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(58, false), 0x0020f10042086001),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(59, false), 0x8029006144981001),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(60, false), 0x0102000420500882),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(61, false), 0x050a004810010406),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(62, false), 0x4000010600881004),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(63, false), 0x0002004400810062)
			},
			{
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(0, true), 0x01404a020a420088),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(1, true), 0x0319020802006000),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(2, true), 0x0810008883002100),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(3, true), 0x0854040090200880),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(4, true), 0x10040c200c404078),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(5, true), 0x0201110840200340),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(6, true), 0x100b082210840106),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(7, true), 0x8130404408884041),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(8, true), 0x38012020020a0160),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(9, true), 0x48000430022202a2),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(10, true), 0x08020c080200c100),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(11, true), 0x4840141400800e00),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(12, true), 0x13200c1028004408),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(13, true), 0x0100020844040a00),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(14, true), 0x6048008801101000),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(15, true), 0x04682310480c0c00),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(16, true), 0x0020001420020212),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(17, true), 0x02080b8288280280),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(18, true), 0x00500012040140c8),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(19, true), 0x0008110082004100),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(20, true), 0x0084000880a00080),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(21, true), 0x0040802048200800),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(22, true), 0x80e854e209100808),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(23, true), 0x00aa042082809800),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(24, true), 0x1010c4004108020a),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(25, true), 0x0090040508218408),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(26, true), 0x1001030850024a01),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(27, true), 0x0000802012020200),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(28, true), 0x5001040002002111),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(29, true), 0x0009110000300800),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(30, true), 0x0011220004208400),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(31, true), 0x2200810118b40215),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(32, true), 0x0001205020a00464),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(33, true), 0x0000900810c40840),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(34, true), 0x80040101800c0402),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(35, true), 0x0000228080480200),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(36, true), 0x001002060038a008),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(37, true), 0x8080c58200010100),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(38, true), 0x2a02040100040080),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(39, true), 0x0480810a06010180),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(40, true), 0x01082422a0805810),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(41, true), 0x0113080110000c04),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(42, true), 0x0000a12228001000),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(43, true), 0x1000002218008400),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(44, true), 0x40004843040000c0),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(45, true), 0xb1010208020000c0),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(46, true), 0x18d2080800900100),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(47, true), 0x098420a891002200),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(48, true), 0x120400d828081001),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(49, true), 0x0001008804428008),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(50, true), 0x49001100a0900000),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(51, true), 0x0090891042020012),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(52, true), 0xc0040020264406d0),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(53, true), 0x2100481001820028),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(54, true), 0x0040160204010000),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(55, true), 0x000310040100c000),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(56, true), 0x5046104414202800),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(57, true), 0x5481003404020807),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(58, true), 0x0000020904010401),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(59, true), 0x0200200980460800),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(60, true), 0x00040e0210020e10),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(61, true), 0x010081b010100121),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(62, true), 0x0000400808018090),
				slidermagic<descriptorGenerator>(slidermagicinfo<descriptorGenerator>(63, true), 0x0808208d86004100)
			}
		};
#endif
		static squaresType pawnMoveMap_untabled(const playerType side, const squareType square, const bool bCapture) noexcept
		{
			assert(side.isValid());
			assert(square.isValid());
			const squaresType piecemask{ squaresType::setMask(square) };
			squaresType movemap{ squaresType::empty() };
			if (side == whitePlayer)
			{
				if (bCapture)
				{
					movemap |= boardType::upLeft(piecemask & boardType::notRank1);
					movemap |= boardType::upRight(piecemask & boardType::notRank1);
				}
				else
					movemap |= boardType::up(piecemask & boardType::notRank1);
			}
			else
			{
				if (bCapture)
				{
					movemap |= boardType::downLeft(piecemask & boardType::notRank8);
					movemap |= boardType::downRight(piecemask & boardType::notRank8);
				}
				else
					movemap |= boardType::down(piecemask & boardType::notRank8);
			}
			return movemap;
		}

		static squaresType knightMoveMap_untabled(const squareType square) noexcept
		{
			assert(square.isValid());
			const squaresType piecemask{ squaresType::setMask(square) };
			squaresType map{ squaresType::empty() };
			map |= boardType::upLeftLeft(piecemask);
			map |= boardType::upRightRight(piecemask);
			map |= boardType::downLeftLeft(piecemask);
			map |= boardType::downRightRight(piecemask);
			map |= boardType::upUpLeft(piecemask);
			map |= boardType::upUpRight(piecemask);
			map |= boardType::downDownLeft(piecemask);
			map |= boardType::downDownRight(piecemask);
			return map;
		}

		static squaresType kingMoveMap_untabled(const squareType square) noexcept
		{
			assert(square.isValid());
			const squaresType piecemask{ squaresType::setMask(square) };
			squaresType map{ squaresType::empty() };
			map |= boardType::up(piecemask);
			map |= boardType::down(piecemask);
			map |= boardType::left(piecemask);
			map |= boardType::right(piecemask);
			map |= boardType::upLeft(piecemask);
			map |= boardType::upRight(piecemask);
			map |= boardType::downLeft(piecemask);
			map |= boardType::downRight(piecemask);
			return map;
		}

		static squaresType sliderAttacks_untabled(const squareType square, const squaresType blockers, const bool bDiag) noexcept
		{
			assert(square.isValid());
			squaresType result;
			const rankType{ square.rank() };
			const fileType{ square.file() };
			rankType r;
			fileType f;
			if (bDiag)
			{
				for (r = rank + 1, f = file + 1; (r < 8) && (f < 8); r++, f++)
				{
					const squareType sq{ squareType::fromRankFile(r, f) };
					result.setBit(sq);
					if (blockers[sq])
						break;
				}
				for (r = rank + 1, f = file - 1; (r < 8) && (f >= 0); r++, f--)
				{
					const squareType sq{ squareType::fromRankFile(r, f) };
					result.setBit(sq);
					if (blockers[sq])
						break;
				}
				for (r = rank - 1, f = file + 1; (r >= 0) && (f < 8); r--, f++)
				{
					const squareType sq{ squareType::fromRankFile(r, f) };
					result.setBit(sq);
					if (blockers[sq])
						break;
				}
				for (r = rank - 1, f = file - 1; (r >= 0) && (f >= 0); r--, f--)
				{
					const squareType sq{ squareType::fromRankFile(r, f) };
					result.setBit(sq);
					if (blockers[sq])
						break;
				}
			}
			else
			{
				for (r = rank + 1; r < 8; r++)
				{
					const squareType sq{ squareType::fromRankFile(r, file) };
					result.setBit(sq);
					if (blockers[sq])
						break;
				}
				for (r = rank - 1; r >= 0; r--)
				{
					const squareType sq{ squareType::fromRankFile(r, file) };
					result.setBit(sq);
					if (blockers[sq])
						break;
				}
				for (f = file + 1; f < 8; f++)
				{
					const squareType sq{ squareType::fromRankFile(rank, f) };
					result.setBit(sq);
					if (blockers[sq])
						break;
				}
				for (f = file - 1; f >= 0; f--)
				{
					const squareType sq{ squareType::fromRankFile(rank, f) };
					result.setBit(sq);
					if (blockers[sq])
						break;
				}
			}
			return result;
		}

		static void sliderMoveMaps_untabled(const bool bDiag, const squareType square, const squaresType occupy, const squaresType capturetargets, squaresType& moves, squaresType& caps) noexcept
		{
			assert(square.isValid());
			bitsType attmask = sliderAttacks_untabled(square, occupy, bDiag);
			moves |= attmask & ~occupy;
			caps |= attmask & capturetargets;
		}

	public:
		generatorTables() noexcept
		{
			for (const auto sq : squareType::range)
			{
				m_KnightMoveMap[sq] = knightMoveMap_untabled(sq);
				m_KingMoveMap[sq] = kingMoveMap_untabled(sq);
				for (const auto p : playerType::range)
				{
					m_PawnMoveMap[p][sq] = pawnMoveMap_untabled(p, sq, false);
					m_PawnCaptureMap[p][sq] = pawnMoveMap_untabled(p, sq, true);
				}
			}
		}
		const slidermagic<descriptorGenerator>& magic(const bool diagonal, const squareType square) const noexcept
		{
			assert(square.isValid());
			return m_SliderMagics[diagonal][square];
		}
		slidermagic<descriptorGenerator>& magic(const bool diagonal, const squareType square) noexcept
		{
			assert(square.isValid());
			return m_SliderMagics[diagonal][square];
		}
		constexpr squaresType knightMoveMap(const squareType sq) const noexcept
		{
			assert(sq.isValid());
			return m_KnightMoveMap[sq];
		}
		constexpr squaresType kingMoveMap(const squareType sq) const noexcept
		{
			assert(sq.isValid());
			return m_KingMoveMap[sq];
		}
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
		squaresType sliderAttackMask(const bool diagonal, const squareType square, const squaresType blockers) const noexcept
		{
			assert(square.isValid());
			return m_SliderMagics[diagonal][square][blockers];
		}
		void sliderMoveMaps(const bool diagonal, const squareType square, const squaresType blockers, const squaresType captureTargets, squaresType& moves, squaresType& captures) const noexcept
		{
			assert(square.isValid());
			const bitsType attackMask{ sliderAttackMask(diagonal,square,blockers) };
			moves |= attackMask & ~blockers;
			captures |= attackMask & captureTargets;
		}
		squaresType sliderAttacks(const bool diagonal, const squareType square, const squaresType blockers, const squaresType xrays) const noexcept
		{
			assert(square.isValid());
			const bitsType attackMask{ sliderAttackMask(diagonal,square,blockers) };
			return attackMask & xrays;
		}
		~generatorTables() noexcept = default;
	};
}