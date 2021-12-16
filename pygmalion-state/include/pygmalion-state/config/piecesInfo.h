namespace pygmalion::config
{
	class piecesInfoBase
	{
		template<typename... PIECES>
		friend class piecesInfo;
	private:
		piecesInfoBase() noexcept = default;
	};

	template<typename... PIECES>
	class piecesInfo :
		public enumerationInfo<PIECES...>,
		public piecesInfoBase
	{
	private:
		template<bool...> struct bool_pack;
		template<bool... bs>
		using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;
		static_assert(all_true<std::is_base_of<pieceInfo, PIECES>::value...>::value, "PIECES... must inherit pieceInfo type.");
	public:
		constexpr piecesInfo(const PIECES&... pieces) noexcept :
			enumerationInfo<PIECES...>(pieces...)
		{
		}
	private:
		template <size_t INDEX_PIECE>
		constexpr size_t countRoyalPiecesPack() const noexcept
		{
			if constexpr (INDEX_PIECE < sizeof...(PIECES))
			{
				if (this->template piece<INDEX_PIECE>().isRoyal)
					return 1 + this->template countRoyalPiecesPack<INDEX_PIECE + 1>();
				else
					return this->template countRoyalPiecesPack<INDEX_PIECE + 1>();
			}
			else
				return 0;
		}
		template <size_t INDEX_PIECE>
		constexpr size_t countStructuralPiecesPack() const noexcept
		{
			if constexpr (INDEX_PIECE < sizeof...(PIECES))
			{
				if (this->template piece<INDEX_PIECE>().isStructural)
					return 1 + this->template countStructuralPiecesPack<INDEX_PIECE + 1>();
				else
					return this->template countStructuralPiecesPack<INDEX_PIECE + 1>();
			}
			else
				return 0;
		}
		template <size_t INDEX_PIECE>
		constexpr size_t indexStructuralPiecePack(size_t structuralIndex, size_t counter) const noexcept
		{
			if constexpr (INDEX_PIECE < sizeof...(PIECES))
			{
				if (this->template piece<INDEX_PIECE>().isStructural)
				{
					if (counter == structuralIndex)
						return INDEX_PIECE;
					else
						return this->template indexStructuralPiecePack<INDEX_PIECE + 1>(structuralIndex, counter + 1);
				}
				else
					return this->template indexStructuralPiecePack<INDEX_PIECE + 1>(structuralIndex, counter);
			}
			else
				return 0;
		}
		template <size_t INDEX_PIECE>
		constexpr size_t indexRoyalPiecePack(size_t structuralIndex, size_t counter) const noexcept
		{
			if constexpr (INDEX_PIECE < sizeof...(PIECES))
			{
				if (this->template piece<INDEX_PIECE>().isRoyal)
				{
					if (counter == structuralIndex)
						return INDEX_PIECE;
					else
						return this->template indexRoyalPiecePack<INDEX_PIECE + 1>(structuralIndex, counter + 1);
				}
				else
					return this->template indexRoyalPiecePack<INDEX_PIECE + 1>(structuralIndex, counter);
			}
			else
				return 0;
		}
		template <size_t INDEX_PIECE>
		constexpr size_t isRoyalPack(size_t pieceIndex) const noexcept
		{
			if constexpr (INDEX_PIECE < sizeof...(PIECES))
			{
				if (INDEX_PIECE == pieceIndex)
					return this->template piece<INDEX_PIECE>().isRoyal;
				else
					return this->template isRoyalPack<INDEX_PIECE + 1>(pieceIndex);
			}
			else
				return false;
		}
		template <size_t INDEX_PIECE>
		constexpr size_t isStructuralPack(size_t pieceIndex) const noexcept
		{
			if constexpr (INDEX_PIECE < sizeof...(PIECES))
			{
				if (INDEX_PIECE == pieceIndex)
					return this->template piece<INDEX_PIECE>().isStructural;
				else
					return this->template isRoyalPack<INDEX_PIECE + 1>(pieceIndex);
			}
			else
				return false;
		}
	public:
		constexpr size_t countRoyalPieces() const noexcept
		{
			if constexpr (sizeof...(PIECES) == 0)
				return 0;
			else
				return this->template countRoyalPiecesPack<0>();
		}
		constexpr size_t countStructuralPieces() const noexcept
		{
			if constexpr (sizeof...(PIECES) == 0)
				return 0;
			else
				return this->template countStructuralPiecesPack<0>();
		}
		constexpr size_t indexStructuralPiece(const size_t structuralIndex) const noexcept
		{
			static_assert(sizeof...(PIECES) != 0);
			return this->template indexStructuralPiecePack<0>(structuralIndex, 0);
		}
		constexpr size_t indexRoyalPiece(const size_t royalIndex) const noexcept
		{
			static_assert(sizeof...(PIECES) != 0);
			return this->template indexRoyalPiecePack<0>(royalIndex, 0);
		}
		template<size_t INDEX>
		constexpr const typename enumerationInfo<PIECES...>::template valueType<INDEX>& piece() const noexcept
		{
			return this->template value<INDEX>();
		}
		constexpr bool isRoyalPiece(const size_t pieceIndex) const noexcept
		{
			if constexpr (sizeof...(PIECES) == 0)
				return false;
			else
				return this->template isRoyalPack<0>(pieceIndex);
		}
		constexpr bool isStructuralPiece(const size_t pieceIndex) const noexcept
		{
			if constexpr (sizeof...(PIECES) == 0)
				return false;
			else
				return this->template isRoyalPack<0>(pieceIndex);
		}
	};
}