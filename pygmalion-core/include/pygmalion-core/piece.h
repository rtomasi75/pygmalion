namespace pygmalion
{
	template<int COUNT_PIECES>
	class piece : public enumeration<COUNT_PIECES, piece<COUNT_PIECES>>
	{
	public:
		constexpr piece(const piece&) noexcept = default;
		constexpr piece(piece&&) noexcept = default;
		constexpr piece() noexcept :
			enumeration<COUNT_PIECES, piece<COUNT_PIECES>>()
		{

		}
		constexpr piece(const typename enumeration<COUNT_PIECES, piece<COUNT_PIECES>>::baseType value) noexcept :
			enumeration<COUNT_PIECES, piece<COUNT_PIECES>>(value)
		{
		}
		constexpr piece(const typename enumeration<COUNT_PIECES, piece<COUNT_PIECES>>::valueType value) noexcept :
			enumeration<COUNT_PIECES, piece<COUNT_PIECES>>(value)
		{
		}
		constexpr piece<COUNT_PIECES>& operator=(piece<COUNT_PIECES>&&) noexcept = default;
		constexpr piece<COUNT_PIECES>& operator=(const piece<COUNT_PIECES>&) noexcept = default;
	};
}