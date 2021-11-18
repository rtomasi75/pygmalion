namespace pygmalion::tictactoe
{
	using descriptorState = pygmalion::descriptor_state<1, 3, 3, 0, 8, false, bool>;

	class board :
		public pygmalion::board<descriptorState, board>
	{
	public:
		static std::string name_Implementation() noexcept
		{
			std::stringstream sstr;
			sstr << "tictactoe board, " << countFiles << "x" << countRanks << " square" << (countSquares != 1 ? "s" : "") << ", " << countPlayers << " player" << (countPlayers != 1 ? "s" : "") << ", " << countPieces << " piece" << (countPieces != 1 ? "s" : "") << ", " << countFlags << " flag" << (countFlags != 1 ? "s" : "");
			return sstr.str();
		}
		static std::string flagToString_Implementation(const flagType flag) noexcept
		{
			return "";
		}
		static bool parseFlag_Implementation(const std::string& text, flagType& flag, size_t& count) noexcept
		{
			return false;
		}
		static std::string rankToString_Implementation(const rankType rank) noexcept
		{
			const char c{ static_cast<char>('1' + static_cast<char>(rank)) };
			std::string txt = "";
			txt += c;
			return txt;
		}
		static bool parseRank_Implementation(const std::string& text, rankType& rank, size_t& count) noexcept
		{
			if (text.length() > 0)
			{
				if ((text[0] >= '1') && (text[0] < ('1' + countRanks)))
				{
					rank = text[0] - '1';
					count++;
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		static std::string fileToString_Implementation(const fileType file) noexcept
		{
			const char c{ static_cast<char>('a' + static_cast<char>(file)) };
			std::string txt = "";
			txt += c;
			return txt;
		}
		static std::string cumulationToString_Implementation(const cumulationType&) noexcept
		{
			return "none";
		}
		static bool parseFile_Implementation(const std::string& text, fileType& file, size_t& count) noexcept
		{
			if (text.length() > 0)
			{
				if ((text[0] >= 'a') && (text[0] < ('a' + countFiles)))
				{
					file = text[0] - 'a';
					count++;
					return true;
				}
				else if ((text[0] >= 'A') && (text[0] < ('A' + countFiles)))
				{
					file = text[0] - 'A';
					count++;
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		static std::string playerToString_Implementation(const playerType player) noexcept
		{
			switch (player)
			{
			default:
				return "?";
			case 0:
				return "X";
			case 1:
				return "O";
			}
		}
		static bool parsePlayer_Implementation(const std::string& text, playerType& player, size_t& count) noexcept
		{
			if (text.length() > 0)
			{
				switch (text[0])
				{
				case 'x':
				case 'X':
				case '0':
					player = 0;
					count++;
					return true;
				case 'o':
				case 'O':
				case '1':
					player = 1;
					count++;
					return true;
				default:
					return false;
				}
			}
			else
				return false;
		}
		static std::string pieceToString_Implementation(const pieceType piece, const playerType player) noexcept
		{
			return (player == 0) ? "X" : "O";
		}
		static bool parsePiece_Implementation(const std::string& text, pieceType& piece, playerType& player, size_t& count) noexcept
		{
			if (text.length() > 0)
			{
				switch (text[0])
				{
				case 'x':
				case 'X':
					piece = 0;
					player = 0;
					count++;
					return true;
				case 'o':
				case 'O':
					piece = 0;
					player = 1;
					count++;
					return true;
				default:
					return false;
				}
			}
			else
				return false;
		}
		void onClear_Implementation() noexcept
		{
		}
		void onAddedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
		{
		}
		void onSetMovingPlayer_Implementation(const playerType player) noexcept
		{
		}
		void onRemovedPiece_Implementation(const pieceType piece, const squareType square, const playerType player) noexcept
		{
		}
		void onSetFlag_Implementation(const flagType flag) noexcept
		{
		}
		void onClearedFlag_Implementation(const flagType flag) noexcept
		{
		}
		void onInitialize_Implementation() noexcept
		{
		}
		static std::string flagsToString_Implementation(const flagsType flags, const playerType movingPlayer) noexcept
		{
			return "";
		}
		static bool parseFlags_Implementation(const std::string& text, flagsType& flags, size_t& count) noexcept
		{
			return true;
		}
	};
}
