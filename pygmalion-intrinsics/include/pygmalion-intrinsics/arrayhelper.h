
namespace pygmalion
{
	class arrayhelper
	{
	private:
		template<size_t size, typename T, size_t... indexes>
		constexpr static auto make_impl(T&& value, std::index_sequence<indexes...>&&) noexcept
		{
			return std::array<std::decay_t<T>, size>{ (static_cast<void>(indexes), value)..., std::forward<T>(value) };
		}
		template<size_t size, typename T, size_t... indexes>
		constexpr static auto make_impl(std::array<std::decay_t<T>, size>&& values, T&& value, std::index_sequence<indexes...>&&) noexcept
		{
			return std::array<std::decay_t<T>, size>{ (static_cast<void>(indexes), values[indexes])..., std::forward<T>(value) };
		}
		template<size_t SIZE, typename T, typename LAMBDA, size_t... INDEX>
		constexpr static auto generate(const LAMBDA& lambda, std::index_sequence<INDEX...>&&) noexcept
		{
			return std::array<std::decay_t<T>, SIZE>{(lambda(INDEX))...};
		}
		template<size_t SIZE, typename C, typename T, typename LAMBDA, size_t... INDEX>
		constexpr static auto transform(const std::array<T, SIZE>& values, const LAMBDA& lambda, std::index_sequence<INDEX...>&&) noexcept
		{
			return std::array<std::decay_t<C>, SIZE>{(lambda(values[INDEX], INDEX))...};
		}
		template<typename T>
		constexpr static auto make(std::integral_constant<size_t, 0>, T&&) noexcept
		{
			return std::array<std::decay_t<T>, 0>{};
		}
		template<size_t SIZE, typename T>
		constexpr static auto make(std::integral_constant<size_t, SIZE>, T&& value) noexcept
		{
			return make_impl<SIZE>(std::forward<T>(value), std::make_index_sequence<SIZE - 1>{});
		}
		template <size_t... n>
		struct ct_integers_list {
			template <size_t m>
			struct push_back
			{
				typedef ct_integers_list<n..., m> type;
			};
		};

		template <size_t max>
		struct ct_iota_1
		{
			typedef typename ct_iota_1<max - 1>::type::template push_back<max>::type type;
		};

		template <>
		struct ct_iota_1<0>
		{
			typedef ct_integers_list<> type;
		};
	public:
		template <size_t... indices, typename Tuple>
		constexpr auto tuple_subset(const Tuple& tpl, ct_integers_list<indices...>) -> decltype(std::make_tuple(std::get<indices>(tpl)...))
		{
			return std::make_tuple(std::get<indices>(tpl)...);
			// this means:
			//   make_tuple(get<indices[0]>(tpl), get<indices[1]>(tpl), ...)
		}
		constexpr static size_t requiredSignedBytes(const std::uintmax_t number) noexcept
		{
			if (number >= (UINTMAX_C(1) << 31))
				return 8;
			if (number >= (UINTMAX_C(1) << 15))
				return 4;
			if (number >= (UINTMAX_C(1) << 7))
				return 2;
			return 1;
		}		
		constexpr static size_t requiredUnsignedBits(const std::uintmax_t number) noexcept
		{
			std::uintmax_t n = 1;
			std::uintmax_t k = 0;
			while (number > n)
			{
				n *= 2;
				k++;
			}
			return k;
		}
		constexpr static size_t requiredSignedBits(const std::uintmax_t number) noexcept
		{
			return requiredUnsignedBits(number + 1);
		}
		template<size_t SIZE, typename T>
		constexpr static auto make(T&& value) noexcept
		{
			return make(std::integral_constant<size_t, SIZE>{}, std::forward<T>(value));
		}
		template<size_t SIZE, typename T>
		constexpr static auto expand(std::array<T, SIZE>&& values, T&& value) noexcept
		{
			return make_impl(std::forward<std::array<T, SIZE>>(values), std::forward<T>(value), std::make_index_sequence<SIZE>{});
		}
		template<size_t SIZE, typename T, typename LAMBDA>
		constexpr static auto generate(const LAMBDA& lambda) noexcept
		{
			return generate<SIZE, T, LAMBDA>(lambda, std::make_index_sequence<SIZE>{});
		}
		template<size_t SIZE, typename C, typename T, typename LAMBDA>
		constexpr static auto transform(const std::array<T, SIZE>& values, const LAMBDA& lambda) noexcept
		{
			return transform<SIZE, C, T, LAMBDA>(values, lambda, std::make_index_sequence<SIZE>{});
		}
		template<size_t SIZE, size_t START, size_t LENGTH, typename T, typename ENABLED = typename std::enable_if<(LENGTH + START) <= SIZE>::type>
		constexpr static T sum(const std::array<T, SIZE>& values) noexcept
		{
			if constexpr (LENGTH == 0)
				return T(0);
			if constexpr (LENGTH == 1)
				return values[START];
			if constexpr ((LENGTH % 2) == 1)
				return sum<SIZE, START, 1>(values) + sum<SIZE, START + 1, LENGTH - 1>(values);
			else
				return sum<SIZE, START, LENGTH / 2>(values) + sum<SIZE, START + LENGTH / 2, LENGTH / 2>(values);
		}
	};
}





