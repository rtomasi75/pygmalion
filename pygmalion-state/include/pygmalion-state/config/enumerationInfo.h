namespace pygmalion::config
{
	template<typename... VALUES>
	class enumerationInfo
	{
	private:
		template<bool...> struct bool_pack;
		template<bool... bs>
		using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;
		static_assert(all_true<std::is_base_of<valueInfo, VALUES>::value...>::value, "VALUES... must inherit valueInfo type.");
		std::tuple<VALUES...> m_Values;
	public:
		template<size_t INDEX>
		using valueType = typename std::tuple_element<INDEX, std::tuple<VALUES...>>::type;
		constexpr static const inline size_t count{ sizeof...(VALUES) };
	private:
		template<size_t INDEX>
		constexpr void setIndices() noexcept
		{
			if constexpr (INDEX < sizeof...(VALUES))
			{
				std::get<INDEX>(m_Values).m_Index = INDEX;
				this->template setIndices<INDEX + 1>();
			}
		}
		template<size_t INDEX>
		bool parsePack(const std::string& text, size_t& pos, size_t& parsedIndex) const noexcept
		{
			if (this->template value<INDEX>().parse(text, pos))
			{
				parsedIndex = INDEX;
				return true;
			}
			else
			{
				if constexpr ((INDEX + 1) < count)
					return this->parsePack<INDEX + 1>(text, pos, parsedIndex);
				else
					return false;
			}
		}
		template<size_t INDEX, typename VALUE, typename... VALUES2>
		std::string toShortStringPack(const size_t index) const noexcept
		{
			if (index == INDEX)
				return static_cast<std::string>(this->template value<INDEX>().shortName);
			else
			{
				if constexpr (sizeof...(VALUES2) > 0)
					return this->toShortStringPack<INDEX + 1, VALUES2...>(index);
				else
				{
					PYGMALION_ASSERT(false);
					return std::string("?");
				}
			}
		}
		template<size_t INDEX, typename VALUE, typename... VALUES2>
		std::string toLongStringPack(const size_t index) const noexcept
		{
			if (index == INDEX)
				return static_cast<std::string>(this->template value<INDEX>().longName);
			else
			{
				if constexpr (sizeof...(VALUES2) > 0)
					return this->toLongStringPack<INDEX + 1, VALUES2...>(index);
				else
				{
					PYGMALION_ASSERT(false);
					return std::string("?");
				}
			}
		}
	protected:
		constexpr enumerationInfo(const VALUES&... values) noexcept :
			m_Values{ std::tuple<VALUES...>(values...) }
		{
			this->template setIndices<0>();
		}
	public:
		template<size_t INDEX>
		constexpr const valueType<INDEX>& value() const noexcept
		{
			return std::get<INDEX>(m_Values);
		}
		bool parse(const std::string& text, size_t& pos, size_t& parsedIndex) const noexcept
		{
			if constexpr (count == 0)
				return false;
			else
				return this->template parsePack<0>(text, pos, parsedIndex);
		}
		std::string toShortString(const size_t index) const noexcept
		{
			if constexpr (sizeof...(VALUES) == 0)
			{
				PYGMALION_ASSERT(false);
				return "?";
			}
			else
				return this->template toShortStringPack<0, VALUES...>(index);
		}
		std::string toLongString(const size_t index) const noexcept
		{
			if constexpr (sizeof...(VALUES) == 0)
			{
				PYGMALION_ASSERT(false);
				return "?";
			}
			else
				return this->template toLongStringPack<0, VALUES...>(index);
		}
	};
}