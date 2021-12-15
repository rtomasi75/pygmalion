namespace pygmalion::config
{
	template<typename PLAYERS, typename PIECES>
	class playerpiecesInfo
	{
	private:
		static_assert(std::is_base_of<playersInfoBase, PLAYERS>::value, "PLAYERS must inherit playersInfo type.");
		static_assert(std::is_base_of<piecesInfoBase, PIECES>::value, "PIECES must inherit piecesInfo type.");
		const PLAYERS m_Players;
		const PIECES m_Pieces;
	public:
		constexpr static const inline size_t count{ PLAYERS::count * PIECES::count };
		constexpr playerpiecesInfo(const PLAYERS& players, const PIECES& pieces) noexcept 
		{
		}
		template<size_t PLAYER,size_t PIECE>
		constexpr playerpieceInfo<typename PLAYERS::template valueType<PLAYER>, typename PIECES::template valueType<PIECE>> playerpiece() const noexcept
		{
			return playerpieceInfo<typename PLAYERS::template valueType<PLAYER>, typename PIECES::template valueType<PIECE>>(m_Players.template player<PLAYER>(), m_Pieces.template piece<PIECE>());
		}
		constexpr const PLAYERS& players() const noexcept
		{
			return m_Players;
		}
		constexpr const PIECES& pieces() const noexcept
		{
			return m_Pieces;
		}
	private:
		template<size_t INDEX_PLAYER, size_t INDEX_PIECE>
		std::string toShortStringPackPiece(const size_t pieceIndex) const noexcept
		{
			if constexpr (INDEX_PIECE < PIECES::count)
			{
				if (INDEX_PIECE == pieceIndex)
					return static_cast<std::string>(this->template playerpiece<INDEX_PLAYER, INDEX_PIECE>().shortName);
				else
					return this->template toShortStringPackPiece<INDEX_PLAYER, INDEX_PIECE + 1>(pieceIndex);
			}
			else
			{
				PYGMALION_ASSERT(false);
				return std::string("?");
			}
		}
		template<size_t INDEX_PLAYER, size_t INDEX_PIECE>
		std::string toLongStringPackPiece(const size_t pieceIndex) const noexcept
		{
			if constexpr (INDEX_PIECE < PIECES::count)
			{
				if (INDEX_PIECE == pieceIndex)
					return static_cast<std::string>(this->template playerpiece<INDEX_PLAYER, INDEX_PIECE>().shortName);
				else
					return this->template toLongStringPackPiece<INDEX_PLAYER, INDEX_PIECE + 1>(pieceIndex);
			}
			else
			{
				PYGMALION_ASSERT(false);
				return std::string("?");
			}
		}
		template<size_t INDEX_PLAYER>
		std::string toShortStringPackPlayer(const size_t playerIndex, const size_t pieceIndex) const noexcept
		{
			if constexpr (INDEX_PLAYER < PLAYERS::count)
			{
				if (INDEX_PLAYER == playerIndex)
					return this->template toShortStringPackPiece<INDEX_PLAYER, 0>(pieceIndex);
				else
					return this->template toShortStringPackPlayer<INDEX_PLAYER + 1>(playerIndex, pieceIndex);
			}
			else
			{
				PYGMALION_ASSERT(false);
				return std::string("?");
			}
		}
		template<size_t INDEX_PLAYER>
		std::string toLongStringPackPlayer(const size_t playerIndex, const size_t pieceIndex) const noexcept
		{
			if constexpr (INDEX_PLAYER < PLAYERS::count)
			{
				if (INDEX_PLAYER == playerIndex)
					return this->template toLongStringPackPiece<INDEX_PLAYER, 0>(pieceIndex);
				else
					return this->template toLongStringPackPlayer<INDEX_PLAYER + 1>(playerIndex, pieceIndex);
			}
			else
			{
				PYGMALION_ASSERT(false);
				return std::string("?");
			}
		}
		template<size_t INDEX_PLAYER, size_t INDEX_PIECE>
		bool parsePackPiece(const std::string& text, size_t& pos, size_t& parsedPlayer, size_t& parsedPiece) const noexcept
		{
			if constexpr (INDEX_PIECE < PIECES::count)
			{
				if (this->template playerpiece<INDEX_PLAYER, INDEX_PIECE>().parse(text, pos))
				{
					parsedPlayer = INDEX_PLAYER;
					parsedPiece = INDEX_PIECE;
					return true;
				}
				else
					return this->template parsePackPiece<INDEX_PLAYER, INDEX_PIECE + 1>(text, pos, parsedPlayer, parsedPiece);
			}
			else
			{
				return false;
			}
		}
		template<size_t INDEX_PLAYER>
		bool parsePackPlayer(const std::string& text, size_t& pos, size_t& parsedPlayer, size_t& parsedPiece) const noexcept
		{
			if constexpr (INDEX_PLAYER < PLAYERS::count)
			{
				if (this->template parsePackPiece<INDEX_PLAYER, 0>(text, pos, parsedPlayer, parsedPiece))
					return true;
				else
					return this->template parsePackPlayer<INDEX_PLAYER + 1>(text, pos, parsedPlayer, parsedPiece);
			}
			else
				return false;
		}
	public:
		bool parse(const std::string& text, size_t& pos, size_t& parsedIndex) const noexcept
		{
			if constexpr (count == 0)
				return false;
			else
			{
				size_t parsedPlayerIndex;
				size_t parsedPieceIndex;
				if (this->template parsePackPlayer<0>(text, pos, parsedPlayerIndex, parsedPieceIndex))
				{
					parsedIndex = parsedPlayerIndex * PIECES::count + parsedPieceIndex;
					return true;
				}
				else
					return false;
			}
		}
		std::string toShortString(const size_t index) const noexcept
		{
			if (index >= count)
			{
				PYGMALION_ASSERT(false);
				return "?";
			}
			else
				return this->template toShortStringPackPlayer<0>(index / PIECES::count, index % PIECES::count);
		}
		std::string toLongString(const size_t index) const noexcept
		{
			if (index >= count)
			{
				PYGMALION_ASSERT(false);
				return "?";
			}
			else
				return this->template toLongStringPackPlayer<0>(index / PIECES::count, index % PIECES::count);
		}
	};
}