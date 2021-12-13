namespace pygmalion::mechanics
{
	namespace detail
	{
		template<typename BOARD>
		class captureMovedata :
			public pygmalion::mechanics::movedataBase<BOARD>
		{
		public:
			using boardType = BOARD;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			squareType m_From;
			squareType m_To;
			pieceType m_TransportedPiece;
			pieceType m_CapturedPiece;
			playerType m_OwnerTransported;
			playerType m_OwnerCaptured;
		public:
			PYGMALION_INLINE playerType ownerTransported() const noexcept
			{
				return m_OwnerTransported;
			}
			PYGMALION_INLINE playerType ownerCaptured() const noexcept
			{
				return m_OwnerCaptured;
			}
			PYGMALION_INLINE pieceType transportedPiece() const noexcept
			{
				return m_TransportedPiece;
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
			PYGMALION_INLINE captureMovedata(const pieceType transportedPiece_, const squareType fromSquare, const squareType toSquare, const playerType ownerTransported_, const pieceType capturedPiece_, const playerType ownerCaptured_) noexcept :
				m_TransportedPiece{ transportedPiece_ },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OwnerTransported{ ownerTransported_ },
				m_CapturedPiece{ capturedPiece_ },
				m_OwnerCaptured{ ownerCaptured_ }
			{}
			PYGMALION_INLINE captureMovedata() noexcept = default;
			PYGMALION_INLINE captureMovedata(captureMovedata&&) noexcept = default;
			PYGMALION_INLINE captureMovedata(const captureMovedata&) noexcept = default;
			PYGMALION_INLINE captureMovedata& operator=(captureMovedata&&) noexcept = default;
			PYGMALION_INLINE captureMovedata& operator=(const captureMovedata&) noexcept = default;
			PYGMALION_INLINE ~captureMovedata() noexcept = default;
		};
	}

	template<typename BOARD>
	class capturemove :
		public move<BOARD, 2 * BOARD::squareType::countUnsignedBits, detail::captureMovedata<BOARD>, capturemove<BOARD>>
	{
	public:
		using boardType = BOARD;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countFromBits{ squareType::countUnsignedBits };
		constexpr static const size_t countToBits{ squareType::countUnsignedBits };
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename capturemove::movedataType) << ":" << capturemove::countBits << "@capture";
			return sstr.str();
		}
	private:
		PYGMALION_INLINE static squareType extractTo(const typename capturemove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		PYGMALION_INLINE static void encodeTo(typename capturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		PYGMALION_INLINE static squareType extractFrom(const typename capturemove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		PYGMALION_INLINE static void encodeFrom(typename capturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		PYGMALION_INLINE constexpr capturemove() noexcept = default;
		PYGMALION_INLINE ~capturemove() noexcept = default;
		PYGMALION_INLINE constexpr capturemove(capturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr capturemove(const capturemove&) noexcept = default;
		PYGMALION_INLINE constexpr capturemove& operator=(capturemove&&) noexcept = default;
		PYGMALION_INLINE constexpr capturemove& operator=(const capturemove&) noexcept = default;
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename capturemove::movebitsType moveBits, typename capturemove::movedataType& movedata) const noexcept
		{
			const squareType from{ capturemove::extractFrom(moveBits) };
			const squareType to{ capturemove::extractTo(moveBits) };
			const pieceType pc{ position.getPiece(from) };
			const playerType p{ position.getPlayer(from) };
			const pieceType pc2{ position.getPiece(to) };
			const playerType p2{ position.getPlayer(to) };
			position.removePiece(pc, from, p);
			position.removePiece(pc2, to, p2);
			position.addPiece(pc, to, p);
			movedata = typename capturemove::movedataType(pc, from, to, p, pc2, p2);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename capturemove::movedataType& data) const noexcept
		{
			position.removePiece(data.transportedPiece(), data.to(), data.ownerTransported());
			position.addPiece(data.capturedPiece(), data.to(), data.ownerCaptured());
			position.addPiece(data.transportedPiece(), data.from(), data.ownerTransported());
		}
		PYGMALION_INLINE typename capturemove::movebitsType create(const squareType from, const squareType to) const noexcept
		{
			typename capturemove::movebitsType bits{ capturemove::movebitsType::zero() };
			capturemove::encodeFrom(bits, from);
			capturemove::encodeTo(bits, to);
			return bits;
		}
		bool parse_Implementation(const boardType& position, const std::string& text, typename capturemove::movebitsType& moveBits, size_t& count) const noexcept
		{
			std::string temp{ text };
			squareType from;
			squareType to;
			size_t cnt{ 0 };
			if (boardType::parseSquare(temp, from, cnt))
			{
				if (position.totalOccupancy()[from])
				{
					std::string temp2{ temp.substr(cnt,temp.length() - cnt) };
					if (temp2.length() > 0 && temp2[0] == 'x')
					{
						cnt++;
						if (boardType::parseSquare(temp.substr(cnt, temp.length() - cnt), to, cnt))
						{
							if (position.totalOccupancy()[to])
							{
								moveBits = create(from, to);
								count += cnt;
								return true;
							}
						}
					}
				}
			}
			return false;
		}
		std::string toString_Implementation(const boardType& position, const typename capturemove::movebitsType moveBits) const noexcept
		{
			const squareType from{ capturemove::extractFrom(moveBits) };
			const squareType to{ capturemove::extractTo(moveBits) };
			return boardType::squareToString(from) + "x" + boardType::squareToString(to);
		}
	};
}