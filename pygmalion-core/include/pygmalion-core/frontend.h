namespace pygmalion
{

	template<typename DESCRIPTION_FRONTEND, typename INSTANCE>
	class frontend :
		public base_frontend<DESCRIPTION_FRONTEND>
	{
	public:
		using frontType = INSTANCE;

		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "include_frontend.h"

		class stack :
			public base_frontend<DESCRIPTION_FRONTEND>,
			public searchType::stackType
		{
		public:
			using frontType = INSTANCE;

			using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "include_frontend.h"

			stack(const stack& parent, const moveType move) noexcept :
				searchType::stackType(parent, move)
			{
			}
			stack(boardType& position, const playerType oldPlayer) noexcept :
				searchType::stackType(position, oldPlayer)
			{
			}
			~stack() noexcept = default;
		};
		static void dumpSquares(const squaresType squares, std::ostream& stream) noexcept
		{
			stream << std::endl;
			for (const auto i : rankType::range)
			{
				for (const auto j : fileType::range)
				{
					const squareType sq{ (-i)& j };
					if (squares[sq])
						stream << "#";
					else
						stream << ".";
				}
				stream << std::endl;
			}
			stream << std::endl;
			stream << "population: " << static_cast<size_t>(squares.count());
			stream << std::endl;
		}
		using stackType = stack;
		static std::string name() noexcept
		{
			return frontType::name_Implementation();
		}
		static std::string subjectiveToString(const subjectiveType score) noexcept
		{
			return frontType::subjectiveToString_Implementation(score);
		}
		static std::string objectiveToString(const scoreType score) noexcept
		{
			return frontType::objectiveToString_Implementation(score);
		}
		template<typename stackType>
		static std::string moveToString(const stackType& stack, const moveType mv) noexcept
		{
			return frontType::moveToString_Implementation(stack, mv);
		}
		static void dumpBoard(const boardType& board, std::ostream& str) noexcept
		{
			return frontType::dumpBoard_Implementation(board, str);
		}
		static bool parseMove(const std::string str, const stackType& stack, moveType& move, std::string& error) noexcept
		{
			return frontType::parseMove_Implementation(str, stack, move, error);
		}
		static std::string variationToStringFromDepth(const stackType& stack, const variationType& variation, const depthType depth) noexcept
		{
			if (variation.length() > depth)
			{
				std::stringstream sstr;
				sstr << moveToString(stack, variation[depth]) << " ";
				stackType subStack(stack, variation[depth]);
				sstr << variationToStringFromDepth(subStack, variation, depth + 1);
				return sstr.str();
			}
			return "";
		}
		static std::string variationToString(const stackType& stack, const variationType& variation) noexcept
		{
			return variationToStringFromDepth(stack, variation, 0);
		}
	};
}