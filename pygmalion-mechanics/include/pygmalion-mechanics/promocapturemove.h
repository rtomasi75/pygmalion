namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename BOARD>
		class promocaptureMovedata
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			squareType m_From;
			squareType m_To;
			pieceType m_InitialPiece;
			pieceType m_PromotedPiece;
			pieceType m_CapturedPiece;
			playerType m_OwnerPromoted;
			playerType m_OwnerCaptured;
		public:
			PYGMALION_INLINE playerType ownerPromoted() const noexcept
			{
				return m_OwnerPromoted;
			}
			PYGMALION_INLINE playerType ownerCaptured() const noexcept
			{
				return m_OwnerCaptured;
			}
			PYGMALION_INLINE pieceType promotedPiece() const noexcept
			{
				return m_PromotedPiece;
			}
			PYGMALION_INLINE pieceType initialPiece() const noexcept
			{
				return m_InitialPiece;
			}
			PYGMALION_INLINE pieceType capturedPiece() const noexcept
			{
				return m_CapturedPiece;
			}
			PYGMALION_INLINE squareType from() const noexcept
			{
				return m_From;
			}
			PYGMALION_INLINE squareType to() const noexcept
			{
				return m_To;
			}
			PYGMALION_INLINE promocaptureMovedata(const pieceType& initialPiece_, const squareType fromSquare, const squareType toSquare, const playerType ownerPromoted_, const pieceType promotedPiece_, const pieceType capturedPiece_, const playerType ownerCaptured_) noexcept :
				m_InitialPiece{ initialPiece_ },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OwnerPromoted{ ownerPromoted_ },
				m_PromotedPiece{ promotedPiece_ },
				m_CapturedPiece{ capturedPiece_ },
				m_OwnerCaptured{ ownerCaptured_ }
			{
			}
			PYGMALION_INLINE promocaptureMovedata() noexcept = default;
			PYGMALION_INLINE promocaptureMovedata(promocaptureMovedata&&) noexcept = default;
			PYGMALION_INLINE promocaptureMovedata(const promocaptureMovedata&) noexcept = default;
			PYGMALION_INLINE promocaptureMovedata& operator=(promocaptureMovedata&&) noexcept = default;
			PYGMALION_INLINE promocaptureMovedata& operator=(const promocaptureMovedata&) noexcept = default;
			PYGMALION_INLINE ~promocaptureMovedata() noexcept = default;
		};
	}

	template<typename BOARD>
	class promocapturemove :
		public move<BOARD, 2 * BOARD::squareType::countUnsignedBits + BOARD::pieceType::countUnsignedBits, detail::promocaptureMovedata<BOARD>, promocapturemove<BOARD>>
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countFromBits{ squareType::countUnsignedBits };
		constexpr static const size_t countToBits{ squareType::countUnsignedBits };
		constexpr static const size_t countPieceBits{ pieceType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename promocapturemove::movedataType) << ":" << promocapturemove::countBits << "@promocapture";
			return sstr.str();
		}
	private:
		PYGMALION_INLINE static pieceType extractPiece(const typename promocapturemove::movebitsType movebits) noexcept
		{
			const pieceType pc{ pieceType(static_cast<typename std::make_unsigned<typename pieceType::baseType>::type>(movebits.template extractBits<countFromBits + countToBits,countPieceBits>())) };
			return pc;
		}
		PYGMALION_INLINE static void encodePiece(typename promocapturemove::movebitsType& movebits, const pieceType pc) noexcept
		{
			movebits.template storeBits<countFromBits + countToBits, countPieceBits>(static_cast<typename std::make_unsigned<typename pieceType::baseType>::type>(pc));
		}
		PYGMALION_INLINE static squareType extractTo(const typename promocapturemove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		PYGMALION_INLINE static void encodeTo(typename promocapturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		PYGMALION_INLINE static squareType extractFrom(const typename promocapturemove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		constexpr static void encodeFrom(typename promocapturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		PYGMALION_INLINE constexpr promocapturemove() noexcept = default;
		PYGMALION_INLINE ~promocapturemove() noexcept = default;
		PYGMALION_INLINE constexpr promocapturemove(promocapturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr promocapturemove(const promocapturemove&) noexcept = default;
		PYGMALION_INLINE constexpr promocapturemove& operator=(promocapturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr promocapturemove& operator=(const promocapturemove&) noexcept = default;
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename promocapturemove::movebitsType moveBits, typename promocapturemove::movedataType& movedata) const noexcept
		{
			const squareType from{ promocapturemove::extractFrom(moveBits) };
			const squareType to{ promocapturemove::extractTo(moveBits) };
			const pieceType initialPiece{ position.getPiece(from) };
			const playerType ownerPromoted{ position.getPlayer(from) };
			const pieceType capturedPiece{ position.getPiece(to) };
			const playerType ownerCaptured{ position.getPlayer(to) };
			const pieceType promotedPiece{ promocapturemove::extractPiece(moveBits) };
			position.removePiece(initialPiece, from, ownerPromoted);
			position.removePiece(capturedPiece, to, ownerCaptured);
			position.addPiece(promotedPiece, to, ownerPromoted);
			movedata = typename promocapturemove::movedataType(initialPiece, from, to, ownerPromoted, promotedPiece, capturedPiece, ownerCaptured);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename promocapturemove::movedataType& data) const noexcept
		{
			position.removePiece(data.promotedPiece(), data.to(), data.ownerPromoted());
			position.addPiece(data.promotedPiece(), data.to(), data.ownerCaptured());
			position.addPiece(data.initialPiece(), data.from(), data.ownerPromoted());
		}
		PYGMALION_INLINE typename promocapturemove::movebitsType create(const squareType from, const squareType to, const pieceType piece) const noexcept
		{
			typename promocapturemove::movebitsType bits{ promocapturemove::movebitsType::zero() };
			promocapturemove::encodeFrom(bits, from);
			promocapturemove::encodeTo(bits, to);
			promocapturemove::encodePiece(bits, piece);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename promocapturemove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			squareType from;
			squareType to;
			pieceType pc;
			playerType p;
			if (boardType::parsePiece(temp, pc, p))
			{
				if ((p == position.movingPlayer()) && (temp.length() > 0) && (temp[0] == '='))
				{
					temp = temp.substr(1, temp.length() - 1);
					if (boardType::parseSquare(temp, from))
					{
						if (position.totalOccupancy()[from])
						{
							if (temp.length() > 0 && temp[0] == 'x')
							{
								temp = temp.substr(1, temp.length() - 1);
								if (boardType::parseSquare(temp, to))
								{
									if (position.totalOccupancy()[to])
									{
										moveBits = create(from, to, pc);
										text = temp;
										return true;
									}
								}
							}
						}
					}
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename promocapturemove::movebitsType moveBits) const noexcept
		{
			const squareType from{ promocapturemove::extractFrom(moveBits) };
			const squareType to{ promocapturemove::extractTo(moveBits) };
			return boardType::squareToString(from) + "x" + boardType::squareToString(to);
		}
	};
}