namespace pygmalion::state::test
{
	using descriptorState = pygmalion::descriptor_state<2, 1, 4, 4, 1, 16>;

	class board :
		public pygmalion::board<descriptorState, board>
	{
	public:
		static std::string flagToString_Implementation(const flagType flag) noexcept
		{
			return "F";
		}
		static bool parseFlag_Implementation(const std::string& text, flagType& flag, size_t& len) noexcept
		{
			if (text.length() > 0)
			{
				if (text[0] == 'F')
				{
					len = 1;
					flag = 0;
					return true;
				}
				else if (text[0] == 'f')
				{
					len = 1;
					flag = 0;
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		static std::string rankToString_Implementation(const rankType rank) noexcept
		{
			const char c{ static_cast<char>('1' + static_cast<char>(rank)) };
			std::string txt = "";
			txt += c;
			return txt;
		}
		static bool parseRank_Implementation(const std::string& text, rankType& rank, size_t& len) noexcept
		{
			if (text.length() > 0)
			{
				if ((text[0] >= '1') && (text[0] < ('1' + countFiles)))
				{
					rank = text[0] - '1';
					len = 1;
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
		static bool parseFile_Implementation(const std::string& text, fileType& file, size_t& len) noexcept
		{
			if (text.length() > 0)
			{
				if ((text[0] >= 'a') && (text[0] < ('a' + countFiles)))
				{
					file = text[0] - 'a';
					len = 1;
					return true;
				}
				else if ((text[0] >= 'A') && (text[0] < ('A' + countFiles)))
				{
					file = text[0] - 'A';
					len = 1;
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
				return "??";
			case 0:
				return "X";
			case 1:
				return "O";
			}
		}
		static bool parsePlayer_Implementation(const std::string& text, playerType& player, size_t& len) noexcept
		{
			if (text.length() > 0)
			{
				switch (text[0])
				{
				case 'x':
				case 'X':
				case '0':
					len = 1;
					player = 0;
					return true;
				case 'o':
				case 'O':
				case '1':
					len = 1;
					player = 1;
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
		static bool parsePiece_Implementation(const std::string& text, pieceType& piece, size_t& len) noexcept
		{
			if (text.length() > 0)
			{
				switch (text[0])
				{
				case 'x':
				case 'X':
				case '0':
				case 'o':
				case 'O':
					len = 1;
					piece = 0;
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
	};
}
