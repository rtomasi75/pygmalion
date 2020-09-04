
namespace detail {

	template<std::size_t size, typename T, std::size_t... indexes>
	constexpr auto make_array_n_impl(T&& value, std::index_sequence<indexes...>) noexcept
	{
		// Use the comma operator to expand the variadic pack
		// Move the last element in if possible. Order of evaluation is well-defined
		// for aggregate initialization, so there is no risk of copy-after-move
		return std::array<std::decay_t<T>, size>{ (static_cast<void>(indexes), value)..., std::forward<T>(value) };
	}
	template<std::size_t size, typename T, std::size_t... indexes>
	constexpr auto make_array_n_impl(std::array<std::decay_t<T>, size>&& values, T&& value, std::index_sequence<indexes...>) noexcept
	{
		// Use the comma operator to expand the variadic pack
		// Move the last element in if possible. Order of evaluation is well-defined
		// for aggregate initialization, so there is no risk of copy-after-move
		return std::array<std::decay_t<T>, size>{ (static_cast<void>(indexes), values[indexes])..., std::forward<T>(value) };
	}

}   // namespace detail

template<typename T>
constexpr auto make_array_n(std::integral_constant<std::size_t, 0>, T&&) noexcept
{
	return std::array<std::decay_t<T>, 0>{};
}

template<std::size_t size, typename T>
constexpr auto make_array_n(std::integral_constant<std::size_t, size>, T&& value) noexcept
{
	return detail::make_array_n_impl<size>(std::forward<T>(value), std::make_index_sequence<size - 1>{});
}

template<std::size_t size, typename T>
constexpr auto make_array_n(T&& value) noexcept
{
	return make_array_n(std::integral_constant<std::size_t, size>{}, std::forward<T>(value));
}

template<std::size_t size, typename T>
constexpr auto expand_array_n(std::array<T, size>&& values, T&& value) noexcept
{
	return detail::make_array_n_impl(std::forward<std::array<T, size>>(values), std::forward<T>(value), std::make_index_sequence<size>{});
}

