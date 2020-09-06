
namespace detail {

	template<size_t size, typename T, size_t... indexes>
	constexpr auto make_array_n_impl(T&& value, std::index_sequence<indexes...>) noexcept
	{
		// Use the comma operator to expand the variadic pack
		// Move the last element in if possible. Order of evaluation is well-defined
		// for aggregate initialization, so there is no risk of copy-after-move
		return std::array<std::decay_t<T>, size>{ (static_cast<void>(indexes), value)..., std::forward<T>(value) };
	}
	template<size_t size, typename T, size_t... indexes>
	constexpr auto make_array_n_impl(std::array<std::decay_t<T>, size>&& values, T&& value, std::index_sequence<indexes...>) noexcept
	{
		// Use the comma operator to expand the variadic pack
		// Move the last element in if possible. Order of evaluation is well-defined
		// for aggregate initialization, so there is no risk of copy-after-move
		return std::array<std::decay_t<T>, size>{ (static_cast<void>(indexes), values[indexes])..., std::forward<T>(value) };
	}

	template<size_t SIZE, typename T, typename LAMBDA, size_t... INDEX>
	constexpr auto generate_array_n(const LAMBDA& lambda, std::index_sequence<INDEX...>) noexcept
	{
		return std::array<std::decay_t<T>, SIZE>{(lambda(INDEX))...};
	}

	template<size_t SIZE, typename C, typename T, typename LAMBDA, size_t... INDEX>
	constexpr auto transform_array_n(const std::array<T, SIZE>& values, const LAMBDA& lambda, std::index_sequence<INDEX...>) noexcept
	{
		return std::array<std::decay_t<C>, SIZE>{(lambda(values[INDEX], INDEX))...};
	}
}   // namespace detail

template<typename T>
constexpr auto make_array_n(std::integral_constant<size_t, 0>, T&&) noexcept
{
	return std::array<std::decay_t<T>, 0>{};
}

template<size_t SIZE, typename T>
constexpr auto make_array_n(std::integral_constant<size_t, SIZE>, T&& value) noexcept
{
	return detail::make_array_n_impl<SIZE>(std::forward<T>(value), std::make_index_sequence<SIZE - 1>{});
}

template<size_t SIZE, typename T>
constexpr auto make_array_n(T&& value) noexcept
{
	return make_array_n(std::integral_constant<size_t, SIZE>{}, std::forward<T>(value));
}

template<size_t SIZE, typename T>
constexpr auto expand_array_n(std::array<T, SIZE>&& values, T&& value) noexcept
{
	return detail::make_array_n_impl(std::forward<std::array<T, SIZE>>(values), std::forward<T>(value), std::make_index_sequence<SIZE>{});
}

template<size_t SIZE, typename T, typename LAMBDA>
constexpr auto generate_array_n(const LAMBDA& lambda) noexcept
{
	return detail::generate_array_n<SIZE, T, LAMBDA>(lambda, std::make_index_sequence<SIZE>{});
}

template<size_t SIZE, typename C, typename T, typename LAMBDA>
constexpr auto transform_array_n(const std::array<T, SIZE>& values, const LAMBDA& lambda) noexcept
{
	return detail::transform_array_n<SIZE, C, T, LAMBDA>(values, lambda, std::make_index_sequence<SIZE>{});
}



template<size_t SIZE, size_t START, size_t LENGTH, typename T, typename ENABLED = typename std::enable_if<(LENGTH + START) <= SIZE>::type>
constexpr T sum_array_n(const std::array<T, SIZE>& values) noexcept
{
	if constexpr (LENGTH == 0)
		return T(0);
	if constexpr (LENGTH == 1)
		return values[START];
	if constexpr ((LENGTH % 2) == 1)
		return sum_array_n<SIZE, START, 1>(values) + sum_array_n<SIZE, START + 1, LENGTH - 1>(values);
	else
		return sum_array_n<SIZE, START, LENGTH / 2>(values) + sum_array_n<SIZE, START + LENGTH / 2, LENGTH / 2>(values);
}
