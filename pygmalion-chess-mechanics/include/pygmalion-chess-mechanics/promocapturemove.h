namespace pygmalion::chess
{
	namespace detail
	{
		class promocaptureMovedata
		{
		public:
			using boardType = board;
			using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		private:
			squareType m_From;
			squareType m_To;
			uint_t<countFiles, false> m_OldFlags;
			pieceType m_CapturedPiece;
			playerType m_Player;
			playerType m_CapturedPlayer;
		public:
			constexpr const uint_t<countFiles, false>& oldFlags() const noexcept
			{
				return m_OldFlags;
			}
			constexpr playerType player() const noexcept
			{
				return m_Player;
			}
			constexpr squareType from() const noexcept
			{
				return m_From;
			}
			constexpr squareType to() const noexcept
			{
				return m_To;
			}
			constexpr playerType capturedPlayer() const noexcept
			{
				return m_CapturedPlayer;
			}
			constexpr pieceType capturedPiece() const noexcept
			{
				return m_CapturedPiece;
			}
			constexpr promocaptureMovedata(const squareType fromSquare, const squareType toSquare, const playerType owner, const uint_t<countFiles, false>& oldFlags_, const pieceType capturedPiece_, const playerType capturedPlayer_) noexcept :
				m_From{ fromSquare },
				m_To{ toSquare },
				m_OldFlags{ oldFlags_ },
				m_Player{ owner },
				m_CapturedPiece{ capturedPiece_ },
				m_CapturedPlayer{ capturedPlayer_ }
			{}
			constexpr promocaptureMovedata() noexcept = default;
			constexpr promocaptureMovedata(promocaptureMovedata&&) noexcept = default;
			constexpr promocaptureMovedata(const promocaptureMovedata&) noexcept = default;
			constexpr promocaptureMovedata& operator=(promocaptureMovedata&&) noexcept = default;
			constexpr promocaptureMovedata& operator=(const promocaptureMovedata&) noexcept = default;
			~promocaptureMovedata() noexcept = default;
		};
	}

	class promocapturemove :
		public pygmalion::mechanics::move<board, 2 * board::squareType::countUnsignedBits, detail::promocaptureMovedata, promocapturemove>,
		public board::descriptorState
	{
	public:
		using boardType = board;
		using descriptorState = typename boardType::descriptorState;
#include <pygmalion-state/include_state.h>
		constexpr static const size_t countFromBits{ squareType::countUnsignedBits };
		constexpr static const size_t countToBits{ squareType::countUnsignedBits };
	private:
		pieceType m_PromotedPiece;
	public:
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "" << sizeof(typename promocapturemove::movedataType) << ":" << promocapturemove::countBits << "@promocapture";
			return sstr.str();
		}
	private:
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
	protected:
		constexpr promocapturemove(const pieceType promotedPiece) noexcept :
			m_PromotedPiece{ promotedPiece }
		{

		}
		~promocapturemove() noexcept = default;
		constexpr promocapturemove(promocapturemove&&) noexcept = default;
		constexpr promocapturemove(const promocapturemove&) noexcept = default;
		constexpr promocapturemove& operator=(promocapturemove&&) noexcept = default;
		constexpr promocapturemove& operator=(const promocapturemove&) noexcept = default;
	public:
		constexpr typename promocapturemove::movedataType doMove_Implementation(boardType& position, const typename promocapturemove::movebitsType& moveBits) const noexcept
		{
			const squareType from{ promocapturemove::extractFrom(moveBits) };
			const squareType to{ promocapturemove::extractTo(moveBits) };
			const playerType p{ position.getPlayer(from) };
			const pieceType pc2{ position.getPiece(to) };
			const playerType p2{ position.getPlayer(to) };
			const uint_t<countFiles, false> oldFlags{ position.extractFlagRange<4, 11>() };
			position.clearEnPassantFiles();
			position.removePiece(pawn, from, p);
			position.removePiece(pc2, to, p2);
			position.addPiece(m_PromotedPiece, to, p);
			position.setMovingPlayer(++position.movingPlayer());
			return typename promocapturemove::movedataType(from, to, p, oldFlags, pc2, p2);
		}
		constexpr void undoMove_Implementation(boardType& position, const typename promocapturemove::movedataType& data) const noexcept
		{
			position.setMovingPlayer(--position.movingPlayer());
			position.removePiece(m_PromotedPiece, data.to(), data.player());
			position.addPiece(pawn, data.from(), data.player());
			position.addPiece(data.capturedPiece(), data.to(), data.capturedPlayer());
			position.storeFlagRange<4, 11>(data.oldFlags());
		}
		constexpr typename promocapturemove::movebitsType create(const squareType from, const squareType to) const noexcept
		{
			typename promocapturemove::movebitsType bits{ promocapturemove::movebitsType::zero() };
			promocapturemove::encodeFrom(bits, from);
			promocapturemove::encodeTo(bits, to);
			return bits;
		}
		bool parse_Implementation(const boardType& position, std::string& text, typename promocapturemove::movebitsType& moveBits) const noexcept
		{
			std::string temp{ text };
			squareType from;
			squareType to;
			if (boardType::parseSquare(temp, from))
			{
				if ((position.pieceOccupancy(pawn) & position.playerOccupancy(position.movingPlayer()))[from])
				{
					if (position.movingPlayer() == whitePlayer)
					{
						if (from.rank() == rank7)
						{
							if (boardType::parseSquare(temp, to))
							{
								if (to.rank() == rank8)
								{
									if (position.totalOccupancy()[to])
									{
										playerType p;
										pieceType pc;
										if (boardType::parsePiece(temp, pc, p))
										{
											if (pc == m_PromotedPiece)
											{
												moveBits = create(from, to);
												text = temp;
												return true;
											}
										}
									}
								}
							}
						}
					}
					else
					{
						if (from.rank() == rank2)
						{
							if (boardType::parseSquare(temp, to))
							{
								if (to.rank() == rank1)
								{
									if (position.totalOccupancy()[to])
									{
										playerType p;
										pieceType pc;
										if (boardType::parsePiece(temp, pc, p))
										{
											if (pc == m_PromotedPiece)
											{
												moveBits = create(from, to);
												text = temp;
												return true;
											}
										}
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
			return boardType::squareToString(from) + boardType::squareToString(to) + boardType::pieceToString(m_PromotedPiece, whitePlayer);
		}
	};
}