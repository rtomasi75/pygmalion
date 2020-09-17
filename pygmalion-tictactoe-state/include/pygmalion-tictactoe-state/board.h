namespace pygmalion::tictactoe
{
	using descriptorState = pygmalion::descriptor_state<2, 1, 3,3, 0, 8>;

	class board :
		public pygmalion::board<descriptorState, board>
	{
	public:
		static std::string flagToString_Implementation(const flagType flag) noexcept
		{
			return "";
		}
		static bool parseFlag_Implementation(const std::string& text, flagType& flag) noexcept
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
		static bool parseRank_Implementation(const std::string& text, rankType& rank) noexcept
		{
			if (text.length() > 0)
			{
				if ((text[0] >= '1') && (text[0] < ('1' + countFiles)))
				{
					rank = text[0] - '1';
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
		static bool parseFile_Implementation(const std::string& text, fileType& file) noexcept
		{
			if (text.length() > 0)
			{
				if ((text[0] >= 'a') && (text[0] < ('a' + countFiles)))
				{
					file = text[0] - 'a';
					return true;
				}
				else if ((text[0] >= 'A') && (text[0] < ('A' + countFiles)))
				{
					file = text[0] - 'A';
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
		static bool parsePlayer_Implementation(const std::string& text, playerType& player) noexcept
		{
			if (text.length() > 0)
			{
				switch (text[0])
				{
				case 'x':
				case 'X':
				case '0':
					player = 0;
					return true;
				case 'o':
				case 'O':
				case '1':
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
		static std::string pieceToString_Implementation(const pieceType piece) noexcept
		{
			return "#";
		}
		static bool parsePiece_Implementation(const std::string& text, pieceType& piece) noexcept
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
				case '#':
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
