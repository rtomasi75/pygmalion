namespace pygmalion::chess
{
	namespace detail
	{
		class captureMovedata :
			public pygmalion::mechanics::movedataBase<board>
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			flagsType m_OldFlags;
			squareType m_From;
			squareType m_To;
			squareType m_OldEnPassantSquare;
			pieceType m_Piece;
			pieceType m_CapturedPiece;
			size_t m_ReversiblePlies{ 0 };
			constexpr static const flagsType noFlags{ flagsType::none() };
		public:
			PYGMALION_INLINE size_t reversiblePlies() const noexcept
			{
				return m_ReversiblePlies;
			}
			PYGMALION_INLINE const flagsType& oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			PYGMALION_INLINE const pieceType& piece() const noexcept
			{
				return m_Piece;
			}
			PYGMALION_INLINE const pieceType& capturedPiece() const noexcept
			{
				return m_CapturedPiece;
			}
			PYGMALION_INLINE const squareType& from() const noexcept
			{
				return m_From;
			}
			PYGMALION_INLINE const squareType& oldEnPassantSquare() const noexcept
			{
				return m_OldEnPassantSquare;
			}
			PYGMALION_INLINE const squareType& to() const noexcept
			{
				return m_To;
			}
			PYGMALION_INLINE captureMovedata(const pieceType transportedPiece, const squareType fromSquare, const squareType toSquare, const flagsType oldFlags_, const pieceType capturedPiece_, const size_t reversiblePlies_, const squareType oldEnPassantSquare_) noexcept :
				m_Piece{ transportedPiece },
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OldFlags{ oldFlags_ },
				m_CapturedPiece{ capturedPiece_ },
				m_ReversiblePlies{ reversiblePlies_ },
				m_OldEnPassantSquare{ oldEnPassantSquare_ }
			{}
			PYGMALION_INLINE captureMovedata() noexcept :
				m_OldFlags{ noFlags }
			{

			}
			PYGMALION_INLINE captureMovedata(captureMovedata&&) noexcept = default;
			PYGMALION_INLINE captureMovedata(const captureMovedata&) noexcept = default;
			PYGMALION_INLINE captureMovedata& operator=(captureMovedata&&) noexcept = default;
			PYGMALION_INLINE captureMovedata& operator=(const captureMovedata&) noexcept = default;
			PYGMALION_INLINE ~captureMovedata() noexcept = default;
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
		static squareType extractTo(const typename capturemove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<countFromBits,countToBits>())) };
			return sq;
		}
		static void encodeTo(typename capturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<countFromBits, countToBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
		static squareType extractFrom(const typename capturemove::movebitsType movebits) noexcept
		{
			const squareType sq{ squareType(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(movebits.template extractBits<0,countFromBits>())) };
			return sq;
		}
		static void encodeFrom(typename capturemove::movebitsType& movebits, const squareType sq) noexcept
		{
			movebits.template storeBits<0, countFromBits>(static_cast<typename std::make_unsigned<typename squareType::baseType>::type>(sq));
		}
	public:
		constexpr capturemove() noexcept = default;
		~capturemove() noexcept = default;
		constexpr capturemove(capturemove&&) noexcept = default;
		constexpr capturemove(const capturemove&) noexcept = default;
		constexpr capturemove& operator=(capturemove&&) noexcept
		{
			return *this;
		}
		constexpr capturemove& operator=(const capturemove&) noexcept
		{
			return *this;
		}
		PYGMALION_INLINE void doMove_Implementation(boardType& position, const typename capturemove::movebitsType moveBits, typename capturemove::movedataType& movedata, const materialTableType& materialTable) const noexcept
		{
			const squareType from{ capturemove::extractFrom(moveBits) };
			const squareType to{ capturemove::extractTo(moveBits) };
			const squareType enPassantSquare{ position.enPassantSquare() };
			const pieceType pc{ position.getPiece(from) };
			const playerType p{ position.getPlayer(from) };
			const pieceType pc2{ position.getPiece(to) };
			const playerType p2{ position.getPlayer(to) };
			const flagsType oldFlags{ position.flags() };
			const size_t reversiblePlies{ position.getReversiblePlyCount() };
			position.clearEnPassantSquare();
			position.removePiece(pc2, to, p2, materialTable);
			position.movePiece(pc, from, to, p, materialTable);
			position.setMovingPlayer(++position.movingPlayer());
			position.resetReversiblePlyCount();
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
			movedata = typename capturemove::movedataType(pc, from, to, oldFlags, pc2, reversiblePlies, enPassantSquare);
		}
		PYGMALION_INLINE void undoMove_Implementation(boardType& position, const typename capturemove::movedataType& data, const materialTableType& materialTable) const noexcept
		{
			const playerType p2{ position.movingPlayer() };
			const playerType p1{ --position.movingPlayer() };
			position.setMovingPlayer(p1);
			position.movePiece(data.piece(), data.to(), data.from(), p1, materialTable);
			position.addPiece(data.capturedPiece(), data.to(), p2, materialTable);
			position.flags() = data.oldFlags();
			position.setReversiblePlyCount(data.reversiblePlies());
			position.setEnPassantSquare(data.oldEnPassantSquare());
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
				std::string temp2{ temp.substr(cnt, temp.length() - cnt) };
				if (position.playerOccupancy(position.movingPlayer())[from])
				{
					if (boardType::parseSquare(temp2, to, cnt))
					{
						if (position.playerOccupancy(position.movingPlayer().next())[to])
						{
							moveBits = create(from, to);
							count += cnt;
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
		PYGMALION_INLINE squaresType otherOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squaresType(capturemove::extractTo(moveBits));
		}
		PYGMALION_INLINE squaresType ownOccupancyDelta_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return squaresType(capturemove::extractFrom(moveBits)) ^ squaresType(capturemove::extractTo(moveBits));
		}
		PYGMALION_INLINE squaresType pieceOccupancyDelta_Implementation(const boardType& position, const pieceType piece, const movebitsType moveBits) const noexcept
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
		PYGMALION_INLINE squareType fromSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return capturemove::extractFrom(moveBits);
		}
		PYGMALION_INLINE squareType toSquare_Implementation(const boardType& position, const movebitsType moveBits) const noexcept
		{
			return capturemove::extractTo(moveBits);
		}
	};
}