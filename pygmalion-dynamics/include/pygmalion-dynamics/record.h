namespace pygmalion
{
	template<typename DESCRIPTOR_DYNAMICS, typename GENERATOR>
	class record :
		public DESCRIPTOR_DYNAMICS
	{
	public:
		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
		using generatorType = GENERATOR;
#include "include_dynamics.h"
		using contextType = typename generatorType::contextType;
	private:
		boardType m_StartPosition;
		const materialTableType& m_MaterialTable;
		std::vector<movebitsType> m_Moves;
		std::string m_Players[countPlayers];
		std::string m_Event;
		std::string m_Site;
		std::string m_Date;
		std::string m_Round;
		gamestateType m_Outcome;
		static std::string clean(const std::string& line) noexcept
		{
			std::stringstream str;
			for (size_t i = 0; i < line.length(); i++)
			{
				switch (line[i])
				{
				default:
					str << line[i];
					break;
				case '\x09':
				case '\x0a':
				case '\x0b':
				case '\x0d':
					break;
				case ';':
					return str.str();
				}
			}
			return str.str();
		}
		static bool parseTag(const std::string& text, std::string& name, std::string& value) noexcept
		{
			bool bName{ false };
			bool bValue{ false };
			size_t pos{ 0 };
			if (text.length() <= pos)
				return false;
			if (pos >= text.length())
				return false;
			if (text[pos] != '[')
				return false;
			pos++;
			name = "";
			while (pos < text.length())
			{
				if (text[pos] == '\"')
				{
					pos++;
					bName = true;
					break;
				}
				if (text[pos] != ' ')
					name += text[pos];
				pos++;
			}
			value = "";
			while (pos < text.length())
			{
				if (text[pos] == '\"')
				{
					pos++;
					bValue = true;
					break;
				}
				value += text[pos];
				pos++;
			}
			if (pos >= text.length())
				return false;
			if (text[pos] != ']')
				return false;
			return true;
		}
		template<size_t PLAYER>
		static bool parseMove(boardType& pos, historyType& history, contextType* pContext, const std::string& movetext, movebitsType& mv, const materialTableType& materialTable, const deltaType& delta) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == pos.movingPlayer())
				{
					typename generatorType::template stackType<PLAYER> stack(pos, history, pContext, materialTable, delta);
					size_t count{ 0 };
					return stack.parseSAN(movetext, mv, count);
				}
				else
					return record::template parseMove<PLAYER + 1>(pos, history, pContext, movetext, mv, materialTable, delta);
			}
			else
				return false;
		}
		static std::string cleanToken(const std::string& token) noexcept
		{
			size_t pos{ 0 };
			for (size_t i = 0; i < token.length(); i++)
			{
				if (token[i] == '.')
					pos = i + 1;
			}
			return token.substr(pos, token.length() - pos);
		}
	public:
		const boardType& startPosition() const noexcept
		{
			return m_StartPosition;
		}
		boardType position(const size_t ply) const noexcept
		{
			PYGMALION_ASSERT(ply <= m_Moves.size());
			boardType pos{ boardType(m_StartPosition) };
			for (size_t i = 0; i < ply; i++)
			{
				movedataType data;
				motorType::makeMove(pos, m_Moves[i], data, m_MaterialTable);
			}
			return pos;
		}
		PYGMALION_INLINE size_t length() const noexcept
		{
			return m_Moves.size();
		}
		const std::string& eventName() const noexcept
		{
			return m_Event;
		}
		const std::string& siteName() const noexcept
		{
			return m_Site;
		}
		const std::string& date() const noexcept
		{
			return m_Date;
		}
		const std::string& round() const noexcept
		{
			return m_Round;
		}
		const std::string& playerName(const playerType pl) const noexcept
		{
			return m_Players[pl];
		}
		gamestateType outcome() const noexcept
		{
			return m_Outcome;
		}
		record(const materialTableType& materialTable) noexcept :
			m_Event{ "" },
			m_Site{ "" },
			m_Date{ "" },
			m_Round{ "" },
			m_MaterialTable{ materialTable }
		{
			m_StartPosition.initialize(m_MaterialTable);
			for (size_t i = 0; i < countPlayers; i++)
			{
				m_Players[i] = "Player_" + parser::fromInt(i);
			}
			m_Outcome = gamestateType::open();
		}
		~record() noexcept = default;
		record(const record& other) noexcept :
			m_StartPosition{ other.m_StartPosition },
			m_MaterialTable{ other.m_MaterialTable },
			m_Moves{ other.m_Moves },
			m_Event{ other.m_Event },
			m_Site{ other.m_Site },
			m_Date{ other.m_Date },
			m_Round{ other.m_Round },
			m_Outcome{ other.m_Outcome }
		{
			for (size_t i = 0; i < countPlayers; i++)
				m_Players[i] = other.m_Players[i];
		}
		record(record&&) noexcept = default;
		record& operator=(const record& other) noexcept
		{
			m_Moves = other.m_Moves;
			for (size_t i = 0; i < countPlayers; i++)
			{
				m_Players[i] = other.m_Players[i];
			}
			m_Event = other.m_Event;
			m_Site = other.m_Site;
			m_Date = other.m_Date;
			m_Round = other.m_Round;
			m_Outcome = other.m_Outcome;
			return *this;
		}
		record& operator=(record&& other) noexcept
		{
			m_Moves = std::move(other.m_Moves);
			for (size_t i = 0; i < countPlayers; i++)
			{
				m_Players[i] = std::move(other.m_Players[i]);
			}
			m_Event = std::move(other.m_Event);
			m_Site = std::move(other.m_Site);
			m_Date = std::move(other.m_Date);
			m_Round = std::move(other.m_Round);
			m_Outcome = std::move(other.m_Outcome);
			return *this;
		}
		static bool read(std::ifstream& file, record& output, const materialTableType& materialTable, const deltaType& delta) noexcept
		{
			output = record(materialTable);
			bool bParseTags{ true };
			bool bLeadIn{ true };
			bool bSetUp{ false };
			std::string line;
			std::string fen = "";
			while (bParseTags)
			{
				if (std::getline(file, line))
				{
					const std::string cleaned{ parser::trim_copy(clean(line)) };
					if (cleaned.length() == 0)
					{
						if (!bLeadIn)
							bParseTags = false;
					}
					else
					{
						if (cleaned[0] != '%')
						{
							bLeadIn = false;
							std::string name;
							std::string value;
							if (parseTag(line, name, value))
							{
								if (name == "Event")
									output.m_Event = value;
								else if (name == "Site")
									output.m_Site = value;
								else if (name == "Date")
									output.m_Date = value;
								else if (name == "Round")
									output.m_Round = value;
								else if (name == "White")
									output.m_Players[descriptorDynamics::whitePlayer] = value;
								else if (name == "Black")
									output.m_Players[descriptorDynamics::blackPlayer] = value;
								else if (name == "Result")
								{
									if (value == "1-0")
										output.m_Outcome = gamestateType::win(descriptorDynamics::whitePlayer);
									else if (value == "0-1")
										output.m_Outcome = gamestateType::win(descriptorDynamics::blackPlayer);
									else if (value == "1/2-1/2")
										output.m_Outcome = gamestateType::draw();
									else if (value == "*")
										output.m_Outcome = gamestateType::open();
									else
										return false;
								}
								else if (name == "FEN")
								{
									fen = value;
								}
								else if (name == "SetUp")
								{
									if (value == "1")
										bSetUp = true;
								}
							}
							else
								bParseTags = false;
						}
					}
				}
				else
					return false;
			}
			if (bSetUp)
			{
				if (fen == "")
					return false;
				else
					output.m_StartPosition.setFen(fen, materialTable);
			}
			else
				output.m_StartPosition.initialize(materialTable);
			boardType pos = output.m_StartPosition;
			historyType history;
			contextType context;
			bool bLoop{ true };
			bLeadIn = true;
#if _DEBUG
			//			std::cout << output;
#endif
			bool bStopped{ false };
			while (bLoop)
			{
				std::string cleaned{ parser::trim_copy(clean(line)) };
				if (cleaned.length() == 0)
				{
					if (!bLeadIn)
						break;
				}
				while (cleaned.length() != 0)
				{
					bLeadIn = false;
					std::string token;
					std::string remainder;
					parser::parseTokenCaseSensitive(cleaned, token, remainder);
					token = parser::trim_copy(record::cleanToken(token));
					cleaned = parser::trim_copy(remainder);
					if (token == "1-0")
						return output.m_Outcome == gamestateType::win(descriptorDynamics::whitePlayer);
					else if (token == "0-1")
						return output.m_Outcome == gamestateType::win(descriptorDynamics::blackPlayer);
					else if (token == "1/2-1/2")
						return output.m_Outcome == gamestateType::draw();
					else if (token == "*")
						return output.m_Outcome == gamestateType::open();
					else
					{
						movebitsType mv;
						if ((!bStopped) && (token.length() > 0))
						{
							if (record::template parseMove<0>(pos, history, &context, token, mv, materialTable, delta))
							{
								output.m_Moves.emplace_back(std::move(mv));
								movedataType data;
								motorType::makeMove(pos, mv, data, materialTable);
							}
							else
								bStopped = true;
						}
					}
				}
				if (std::getline(file, line))
					bLoop = true;
				else
					bLoop = false;
			}
			return true;
		}
	};

	template<typename DESCRIPTOR_DYNAMICS, typename GENERATOR>
	std::ostream& operator<<(std::ostream& str, const record<DESCRIPTOR_DYNAMICS, GENERATOR>& rec) noexcept
	{
		str << "Event:    " << rec.eventName() << std::endl;
		str << "Site:     " << rec.siteName() << std::endl;
		str << "Date:     " << rec.date() << std::endl;
		str << "Round:    " << rec.round() << std::endl;
		for (size_t i = 0; i < DESCRIPTOR_DYNAMICS::countPlayers; i++)
		{
			str << "Player " << (i + 1) << ": " << rec.playerName(static_cast<typename DESCRIPTOR_DYNAMICS::playerType>(i)) << std::endl;
		}
		str << "Result:   ";
		using gamestateType = typename DESCRIPTOR_DYNAMICS::gamestateType;
		if (gamestateType::isOpen(rec.outcome()))
			str << "none";
		else
		{
			if (gamestateType::isDraw(rec.outcome()))
				str << "remis";
			else
			{
				for (size_t i = 0; i < DESCRIPTOR_DYNAMICS::countPlayers; i++)
				{
					if (gamestateType::isWin(rec.outcome(), static_cast<typename DESCRIPTOR_DYNAMICS::playerType>(i)))
					{
						str << "player " << (i + 1) << " wins";
						break;
					}
				}
			}
			str << std::endl;
		}
		str << std::endl;
		for (size_t i = 0; i <= rec.length(); i++)
		{
			str << rec.position(i).getFen() << std::endl;
		}
		return str;
	}
}