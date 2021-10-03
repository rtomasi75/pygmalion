namespace pygmalion::chess
{
	namespace detail
	{
		class captureMovedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			uint_t<countFlags, false> m_OldFlags;
			squareType m_From;
			squareType m_To;
			pieceType m_Piece;
			pieceType m_CapturedPiece;
			std::uint16_t m_ReversiblePlies{ 0 };
		public:
			constexpr std::uint16_t reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			constexpr const uint_t<countFlags, false> oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr pieceType piece() const noexcept
			{
				return m_Piece;
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
			constexpr captureMovedata(const pieceType transportedPiece, const squareType fromSquare, const squareType toSquare, const uint_t<countFlags, false> oldFlags_, const pieceType capturedPiece_, const std::uint16_t reversiblePlies_) noexcept :
				m_Piece{ transportedPiece },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OldFlags{ oldFlags_ },
				m_CapturedPiece{ capturedPiece_ },
				m_ReversiblePlies{ reversiblePlies_ }
			{}
			constexpr captureMovedata() noexcept = default;
			constexpr captureMovedata(captureMovedata&&) noexcept = default;
			constexpr captureMovedata(const captureMovedata&) noexcept = default;
			constexpr captureMovedata& operator=(captureMovedata&&) noexcept = default;
			constexpr captureMovedata& operator=(const captureMovedata&) noexcept = default;
			~captureMovedata() noexcept = default;
		};
	}

	class capturemove :
		public pygmalion::mechanics::move<board, 2 * board::squareType::countUnsignedBits, detail::captureMovedata, capturemove>,
		public board::descriptorState
	{
	public:
		using boardType = board;
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
		constexpr static squareType extractTo(const typename capturemove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		constexpr static void encodeTo(typename capturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		constexpr static squareType extractFrom(const typename capturemove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		constexpr static void encodeFrom(typename capturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		constexpr capturemove() noexcept = default;
		~capturemove() noexcept = default;
		constexpr capturemove(capturemove&&) noexcept = default;
		constexpr capturemove(const capturemove&) noexcept = default;
		constexpr capturemove& operator=(capturemove&&) noexcept = default;
		constexpr capturemove& operator=(const capturemove&) noexcept = default;
		constexpr typename capturemove::movedataType doMove_Implementation(boardType& position, const typename capturemove::movebitsType moveBits) const noexcept
		{
			const squareType from{ capturemove::extractFrom(moveBits) };
			const squareType to{ capturemove::extractTo(moveBits) };
			const pieceType pc{ position.getPiece(from) };
			const playerType p{ position.getPlayer(from) };
			const pieceType pc2{ position.getPiece(to) };
			const playerType p2{ position.getPlayer(to) };
			const uint_t<countFlags, false> oldFlags{ position.extractFlagRange<0, 11>() };
			const std::uint16_t reversiblePlies{ position.cumulation().reversiblePlies() };
			position.clearEnPassantFiles();
			position.removePiece(pc, from, p);
			position.removePiece(pc2, to, p2);
			position.addPiece(pc, to, p);
			position.setMovingPlayer(++position.movingPlayer());
			position.cumulation().reversiblePlies() = 0;
			if (p == whitePlayer)
			{
				switch (pc)
				{
				case king:
					position.clearCastleRightsWhite();
					break;
				case rook:
					switch (from)
					{
					case squareA1:
						position.clearCastleRightQueensideWhite();
						break;
					case squareH1:
						position.clearCastleRightKingsideWhite();
						break;
					}
					break;
				}
				if (pc2 == rook)
				{
					switch (to)
					{
					case squareA8:
						position.clearCastleRightQueensideBlack();
						break;
					case squareH8:
						position.clearCastleRightKingsideBlack();
						break;
					}
				}
			}
			else
			{
				switch (pc)
				{
				case king:
					position.clearCastleRightsBlack();
					break;
				case rook:
					switch (from)
					{
					case squareA8:
						position.clearCastleRightQueensideBlack();
						break;
					case squareH8:
						position.clearCastleRightKingsideBlack();
						break;
					}
					break;
				}
				if (pc2 == rook)
				{
					switch (to)
					{
					case squareA1:
						position.clearCastleRightQueensideWhite();
						break;
					case squareH1:
						position.clearCastleRightKingsideWhite();
						break;
					}
				}
			}
			return typename capturemove::movedataType(pc, from, to, oldFlags, pc2, reversiblePlies);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename capturemove::movedataType& data) const noexcept
		{
			const playerType p2{ position.movingPlayer() };
			const playerType p1{ --position.movingPlayer() };
			position.setMovingPlayer(p1);
			position.removePiece(data.piece(), data.to(), p1);
			position.addPiece(data.piece(), data.from(), p1);
			position.addPiece(data.capturedPiece(), data.to(), p2);
			position.storeFlagRange<0, 11>(data.oldFlags());
			position.cumulation().reversiblePlies() = data.reversiblePlies();
		}
		constexpr typename capturemove::movebitsType create(const squareType from, const squareType to) const noexcept
		{
			typename capturemove::movebitsType bits{ capturemove::movebitsType::zero() };
			capturemove::encodeFrom(bits, from);
			capturemove::encodeTo(bits, to);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename capturemove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			squareType from;
			squareType to;
			if (boardType::parseSquare(temp, from))
			{
				if (position.playerOccupancy(position.movingPlayer())[from])
				{
					if (boardType::parseSquare(temp, to))
					{
						if (position.playerOccupancy(++position.movingPlayer())[to])
						{
							moveBits = create(from, to);
							text = temp;
							return true;
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
			return boardType::squareToString(from) + boardType::squareToString(to);
		}
		constexpr squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squaresType(capturemove::extractTo(moveBits));
		}
		constexpr squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squaresType(capturemove::extractFrom(moveBits)) ^ squaresType(capturemove::extractTo(moveBits));
		}
		constexpr squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
		{
			const squareType to{ capturemove::extractTo(moveBits) };
			const squareType from{ capturemove::extractFrom(moveBits) };
			constexpr const squaresType none{ squaresType::none() };
			squaresType delta{ none };
			if (position.pieceOccupancy(piece)[from])
			{
				delta ^= from;
				delta ^= to;
			}
			if (position.pieceOccupancy(piece)[to])
				delta ^= to;
			return delta;
		}
		constexpr squareType fromSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return capturemove::extractFrom(moveBits);
		}
		constexpr squareType toSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return capturemove::extractTo(moveBits);
		}
	};
}