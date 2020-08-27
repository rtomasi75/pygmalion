namespace pygmalion::tictactoe
{
	class frontend : public pygmalion::frontend<search<movegen, evaluator, 9>, frontend>
	{
	private:
	public:
		static std::string subjectiveToString_Implementation(const subjectiveType& score) noexcept
		{
			return static_cast<std::string>(score);
		}
		static std::string objectiveToString_Implementation(const objectiveType& score) noexcept
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
		static std::string moveToString_Implementation(const boardType& position, const moveType mv) noexcept
		{
			int file = mv.to() % 3;
			int rank = (mv.to() - file) / 3;
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
		static bool parseMove_Implementation(const std::string str, const boardType& position, moveType& move, std::string& error) noexcept
		{
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
				move = static_cast<moveType>(rank * 3 + file);
				return true;
			}
		}
		static std::string variationToString_Implementation(const boardType& position, const variationType& variation)
		{
			boardType currentPosition{ position };
			std::stringstream sstr;
			for (int i = 0; i < variation.length(); i++)
			{
				sstr << moveToString(currentPosition, variation[i]) << " ";
				boardType::movedata md(currentPosition, variation[i]);
				currentPosition.makeMove(md);
			}
			return sstr.str();
		}
	};
}