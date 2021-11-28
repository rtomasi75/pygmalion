namespace pygmalion
{
	class tuningposition
	{
	private:
		std::string m_FEN;
		double m_Score;
	public:
		const std::string& fen() const noexcept
		{
			return m_FEN;
		}
		double score() const noexcept
		{
			return m_Score;
		}
		tuningposition(const std::string& fen, const double score) noexcept :
			m_FEN{ fen },
			m_Score{ score }
		{

		}
		tuningposition() noexcept
		{
			m_FEN = "";
			m_Score = 0.0;
		}
		~tuningposition() noexcept = default;
		tuningposition(const tuningposition&) noexcept = default;
		tuningposition(tuningposition&&) noexcept = default;
		tuningposition& operator=(const tuningposition&) = default;
		tuningposition& operator=(tuningposition&&) = default;
	};

	inline std::ofstream& operator<<(std::ofstream& file, const tuningposition& tpos) noexcept
	{
		double sc{ tpos.score() };
		file.write(reinterpret_cast<char*>(&sc), sizeof(sc));
		size_t l{ tpos.fen().length() };
		file.write(reinterpret_cast<char*>(&l), sizeof(l));
		for (size_t i = 0; i < l; i++)
		{
			char c{ tpos.fen()[i] };
			file.write(&c, sizeof(char));
		}
		return file;
	}

	inline std::ifstream& operator>>(std::ifstream& file, tuningposition& tpos) noexcept
	{
		double score;
		size_t l;
		std::string fen = "";
		file.read(reinterpret_cast<char*>(&score), sizeof(score));
		file.read(reinterpret_cast<char*>(&l), sizeof(l));
		for (size_t i = 0; i < l; i++)
		{
			char c;
			file.read(&c, sizeof(char));
			fen += c;
		}
		tpos = tuningposition(fen, score);
		return file;
	}

	class tuningpositions
	{
	private:
		std::vector<tuningposition> m_Positions;
	public:
		tuningpositions() noexcept = default;
		~tuningpositions() noexcept = default;
		tuningpositions(const tuningpositions&) noexcept = default;
		tuningpositions(tuningpositions&&) noexcept = default;
		tuningpositions& operator=(const tuningpositions&) = default;
		tuningpositions& operator=(tuningpositions&&) = default;
		PYGMALION_INLINE size_t size() const noexcept
		{
			return m_Positions.size();
		}
		PYGMALION_INLINE void add(const tuningposition& tpos) noexcept
		{
			m_Positions.emplace_back(tpos);
		}
		PYGMALION_INLINE void add(tuningposition&& tpos) noexcept
		{
			m_Positions.emplace_back(std::move(tpos));
		}
		PYGMALION_INLINE const tuningposition& operator[](const size_t idx) const noexcept
		{
			return m_Positions[idx];
		}
	};

	inline std::ofstream& operator<<(std::ofstream& file, const tuningpositions& tpos) noexcept
	{
		file << tpos.size();
		for (size_t i = 0; i < tpos.size(); i++)
			file << tpos[i];
		return file;
	}

	inline std::ifstream& operator>>(std::ifstream& file, tuningpositions& tpos) noexcept
	{
		tpos = tuningpositions();
		size_t n;
		file >> n;
		tuningposition tp;
		for (size_t i = 0; i < n; i++)
		{
			file >> tp;
			tpos.add(tp);
		}
		return file;
	}
}