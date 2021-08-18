namespace pygmalion::tictactoe
{
	class frontend :
		public pygmalion::frontend<descriptor_frontend, frontend>
	{
	private:
	public:
		static std::string name_Implementation() noexcept
		{
			return "Tic Tac Toe - a demo implmenentation ;)";
		}
		static std::string subjectiveToString_Implementation(const subjectiveType& score) noexcept
		{
			return static_cast<std::string>(score);
		}
		static std::string objectiveToString_Implementation(const scoreType& score) noexcept
		{
			return static_cast<std::string>(score);
		}
		static void dumpBoard_Implementation(const boardType& board, std::ostream& str) noexcept
		{
			str << std::endl;
			for (int i = 0; i < 3; i++)
			{
				str << "+-+-+-+" << std::endl;
				for (int j = 0; j < 3; j++)
				{
					str << "|";
					if (board.isOccupied(static_cast<squareType>(i * 3 + j)))
					{
						str << (board.isOccupied(static_cast<squareType>(i * 3 + j), static_cast<playerType>(0)) ? "X" : "O");
					}
					else
						str << " ";
				}
				str << "|";
				switch (i)
				{
				case 0:
					str << " 1";
					break;
				case 1:
					str << " 2";
					break;
				case 2:
					str << " 3";
					break;
				}
				str << std::endl;
			}
			str << "+-+-+-+" << std::endl;
			str << " A B C" << std::endl;
		}
		template<typename stackType>
		static std::string moveToString_Implementation(const stackType& stack, const moveType mv) noexcept
		{
			auto file = mv.square(0).file();
			auto rank = mv.square(0).rank();
			std::string text{ "" };
			switch (file)
			{
			default:
				assert(false);
				break;
			case 0:
				text += "a";
				break;
			case 1:
				text += "b";
				break;
			case 2:
				text += "c";
				break;
			}
			switch (rank)
			{
			default:
				assert(false);
				break;
			case 0:
				text += "1";
				break;
			case 1:
				text += "2";
				break;
			case 2:
				text += "3";
				break;
			}
			return text;
		}
		static bool parseMove_Implementation(const std::string str, const stackType& stack, moveType& move, std::string& error) noexcept
		{
			const boardType& position{ stack.position() };
			if (str.length() != 2)
			{
				error = "String representation of a move needs to be 2 chars long.";
				return false;
			}
			else
			{
				int file;
				int rank;
				switch (str[0])
				{
				default:
					error = "Invalid file: ";
					error += str[0];
					return false;
				case 'a':
				case 'A':
					file = 0;
					break;
				case 'b':
				case 'B':
					file = 1;
					break;
				case 'c':
				case 'C':
					file = 2;
					break;
				}
				switch (str[1])
				{
				default:
					error = "Invalid rank: ";
					error += str[1];
					return false;
				case '1':
					rank = 0;
					break;
				case '2':
					rank = 1;
					break;
				case '3':
					rank = 2;
					break;
				}
				move = moveType({ squareType::fromRankFile(rank, file) }, {}, 0);
				return true;
			}
		}
	};
}