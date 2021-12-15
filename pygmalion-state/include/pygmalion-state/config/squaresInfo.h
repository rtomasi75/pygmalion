namespace pygmalion::config
{
	template<typename FILES, typename RANKS>
	class squaresInfo
	{
	private:
		static_assert(std::is_base_of<filesInfoBase, FILES>::value, "FILES must inherit filesInfo type.");
		static_assert(std::is_base_of<ranksInfoBase, RANKS>::value, "RANKS must inherit ranksInfo type.");
		const FILES m_Files;
		const RANKS m_Ranks;
	public:
		constexpr const FILES& files() const noexcept
		{
			return m_Files;
		}
		constexpr const RANKS& ranks() const noexcept
		{
			return m_Ranks;
		}
		constexpr static const inline size_t count{ FILES::count * RANKS::count };
		constexpr squaresInfo(const FILES& files, const RANKS& ranks) noexcept
		{
		}
		template<size_t FILE, size_t RANK>
		constexpr squareInfo<typename FILES::template valueType<FILE>, typename RANKS::template valueType<RANK>> square() const noexcept
		{
			return squareInfo<typename FILES::template valueType<FILE>, typename RANKS::template valueType<RANK>>(m_Files.template file<FILE>(), m_Ranks.template rank<RANK>());
		}
	private:
		template<size_t INDEX_FILE, size_t INDEX_RANK>
		bool parsePackRank(const std::string& text, size_t& pos, size_t& parsedFile, size_t& parsedRank) const noexcept
		{
			if constexpr (INDEX_RANK < RANKS::count)
			{
				if (this->template square<INDEX_FILE, INDEX_RANK>().parse(text, pos))
				{
					parsedFile = INDEX_FILE;
					parsedRank = INDEX_RANK;
					return true;
				}
				else
					return this->template parsePackRank<INDEX_FILE, INDEX_RANK + 1>(text, pos, parsedFile, parsedRank);
			}
			else
			{
				return false;
			}
		}
		template<size_t INDEX_FILE>
		bool parsePackFile(const std::string& text, size_t& pos, size_t& parsedFile, size_t& parsedRank) const noexcept
		{
			if constexpr (INDEX_FILE < FILES::count)
			{
				if (this->template parsePackRank<INDEX_FILE, 0>(text, pos, parsedFile, parsedRank))
					return true;
				else
					return this->template parsePackFile<INDEX_FILE + 1>(text, pos, parsedFile, parsedRank);
			}
			else
				return false;
		}
		template<size_t INDEX_FILE, size_t INDEX_RANK>
		std::string toShortStringPackRank(const size_t rankIndex) const noexcept
		{
			if constexpr (INDEX_RANK < RANKS::count)
			{
				if (INDEX_RANK == rankIndex)
					return static_cast<std::string>(this->template square<INDEX_FILE, INDEX_RANK>().shortName);
				else
					return this->template toShortStringPackRank<INDEX_FILE, INDEX_RANK + 1>(rankIndex);
			}
			else
			{
				PYGMALION_ASSERT(false);
				return std::string("?");
			}
		}
		template<size_t INDEX_FILE>
		std::string toShortStringPackFile(const size_t fileIndex, const size_t rankIndex) const noexcept
		{
			if constexpr (INDEX_FILE < FILES::count)
			{
				if (INDEX_FILE == fileIndex)
					return this->template toShortStringPackRank<INDEX_FILE, 0>(rankIndex);
				else
					return this->template toShortStringPackFile<INDEX_FILE + 1>(fileIndex, rankIndex);
			}
			else
			{
				PYGMALION_ASSERT(false);
				return std::string("?");
			}
		}
		template<size_t INDEX_FILE, size_t INDEX_RANK>
		std::string toLongStringPackRank(const size_t rankIndex) const noexcept
		{
			if constexpr (INDEX_RANK < RANKS::count)
			{
				if (INDEX_RANK == rankIndex)
					return static_cast<std::string>(this->template square<INDEX_FILE, INDEX_RANK>().longName);
				else
					return this->template toLongStringPackRank<INDEX_FILE, INDEX_RANK + 1>(rankIndex);
			}
			else
			{
				PYGMALION_ASSERT(false);
				return std::string("?");
			}
		}
		template<size_t INDEX_FILE>
		std::string toLongStringPackFile(const size_t fileIndex, const size_t rankIndex) const noexcept
		{
			if constexpr (INDEX_FILE < FILES::count)
			{
				if (INDEX_FILE == fileIndex)
					return this->template toLongStringPackRank<INDEX_FILE, 0>(rankIndex);
				else
					return this->template toLongStringPackFile<INDEX_FILE + 1>(fileIndex, rankIndex);
			}
			else
			{
				PYGMALION_ASSERT(false);
				return std::string("?");
			}
		}
	public:
		bool parse(const std::string& text, size_t& pos, size_t& parsedIndex) const noexcept
		{
			if constexpr (count == 0)
				return false;
			else
			{
				size_t parsedFileIndex;
				size_t parsedRankIndex;
				if (this->template parsePackFile<0>(text, pos, parsedFileIndex, parsedRankIndex))
				{
					parsedIndex = parsedRankIndex * FILES::count + parsedFileIndex;
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
				return this->template toShortStringPackFile<0>(index % FILES::count, index / FILES::count);
		}
		std::string toLongString(const size_t index) const noexcept
		{
			if (index >= count)
			{
				PYGMALION_ASSERT(false);
				return "?";
			}
			else
				return this->template toLongStringPackFile<0>(index % FILES::count, index / FILES::count);
		}
	};
}