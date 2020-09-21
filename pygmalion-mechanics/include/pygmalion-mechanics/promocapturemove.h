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
			constexpr playerType ownerPromoted() const noexcept
			{
				return m_OwnerPromoted;
			}
			constexpr playerType ownerCaptured() const noexcept
			{
				return m_OwnerCaptured;
			}
			constexpr pieceType promotedPiece() const noexcept
			{
				return m_PromotedPiece;
			}
			constexpr pieceType initialPiece() const noexcept
			{
				return m_InitialPiece;
			}
			constexpr pieceType capturedPiece() const noexcept
			{
				return m_CapturedPiece;
			}
			constexpr squareType from() const noexcept
			{
				return m_From;
			}
			constexpr squareType to() const noexcept
			{
				return m_To;
			}
			constexpr promocaptureMovedata(const pieceType initialPiece_, const squareType fromSquare, const squareType toSquare, const playerType ownerPromoted_, const pieceType promotedPiece_, const pieceType capturedPiece_, const playerType ownerCaptured_) noexcept :
				m_InitialPiece{ initialPiece_ },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OwnerPromoted{ ownerPromoted_ },
				m_PromotedPiece{ promotedPiece_ },
				m_CapturedPiece{ capturedPiece_ },
				m_OwnerCaptured{ ownerCaptured_ }
			{
			}
			constexpr promocaptureMovedata() noexcept = default;
			constexpr promocaptureMovedata(promocaptureMovedata&&) noexcept = default;
			constexpr promocaptureMovedata(const promocaptureMovedata&) noexcept = default;
			constexpr promocaptureMovedata& operator=(promocaptureMovedata&&) noexcept = default;
			constexpr promocaptureMovedata& operator=(const promocaptureMovedata&) noexcept = default;
			~promocaptureMovedata() noexcept = default;
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
		std::string name_Implementation() const noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename promocapturemove::movedataType) << ":" << promocapturemove::countBits << "@promocapture";
			return sstr.str();
		}
	private:
		constexpr static pieceType extractPiece(const typename promocapturemove::movebitsType& movebits) noexcept
		{
			const pieceType pc{ pieceType(static_cast<typename std::make_unsigned<typename pieceType::baseType>::type>(movebits.template extractBits<countFromBits + countToBits,countPieceBits>())) };
			return pc;
		}
		constexpr static void encodePiece(typename promocapturemove::movebitsType& movebits, const pieceType pc) noexcept
		{
			movebits.template storeBits<countFromBits + countToBits, countPieceBits>(static_cast<typename std::make_unsigned<typename pieceType::baseType>::type>(pc));
		}
		constexpr static squareType extractTo(const typename promocapturemove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		constexpr static void encodeTo(typename promocapturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		constexpr static squareType extractFrom(const typename promocapturemove::movebitsType& movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		constexpr static void encodeFrom(typename promocapturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		constexpr promocapturemove() noexcept = default;
		~promocapturemove() noexcept = default;
		constexpr promocapturemove(promocapturemove&&) noexcept = default;
		constexpr promocapturemove(const promocapturemove&) noexcept = default;
		constexpr promocapturemove& operator=(promocapturemove&&) noexcept = default;
		constexpr promocapturemove& operator=(const promocapturemove&) noexcept = default;
		constexpr typename promocapturemove::movedataType doMove_Implementation(boardType& position, const typename promocapturemove::movebitsType& moveBits) const noexcept
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
			return typename promocapturemove::movedataType(initialPiece, from, to, ownerPromoted, promotedPiece, capturedPiece, ownerCaptured);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename promocapturemove::movedataType& data) const noexcept
		{
			position.removePiece(data.promotedPiece(), data.to(), data.ownerPromoted());
			position.addPiece(data.promotedPiece(), data.to(), data.ownerCaptured());
			position.addPiece(data.initialPiece(), data.from(), data.ownerPromoted());
		}
		constexpr typename promocapturemove::movebitsType create(const squareType from, const squareType to, const pieceType piece) const noexcept
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
							if (temp.length() >= 0 && temp[0] == 'x')
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
		std::string toString_Implementation(const boardType& position, const typename promocapturemove::movebitsType& moveBits) const noexcept
		{
			const squareType from{ promocapturemove::extractFrom(moveBits) };
			const squareType to{ promocapturemove::extractTo(moveBits) };
			return boardType::squareToString(from) + "x" + boardType::squareToString(to);
		}
	};
}