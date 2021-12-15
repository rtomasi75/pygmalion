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
	public:
		template<size_t INDEX>
		constexpr const typename enumerationInfo<PIECES...>::template valueType<INDEX>& piece() const noexcept
		{
			return this->template value<INDEX>();
		}
	};
}