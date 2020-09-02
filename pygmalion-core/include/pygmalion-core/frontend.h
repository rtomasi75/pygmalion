namespace pygmalion
{

	template<typename DESCRIPTION_FRONTEND, typename INSTANCE>
	class frontend :
		public base_frontend<DESCRIPTION_FRONTEND>
	{
	public:
		using frontendType = INSTANCE;

		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "include_frontend.h"

		class stack :
			public base_frontend<DESCRIPTION_FRONTEND>,
			public searchType::stackType
		{
		public:
			using frontendType = INSTANCE;

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
			return frontendType::name_Implementation();
		}
		static std::string subjectiveToString(const subjectiveType& score) noexcept
		{
			return frontendType::subjectiveToString_Implementation(score);
		}
		static std::string objectiveToString(const objectiveType& score) noexcept
		{
			return frontendType::objectiveToString_Implementation(score);
		}
		template<typename stackType>
		static std::string moveToString(const stackType& stack, const moveType mv) noexcept
		{
			return frontendType::moveToString_Implementation(stack, mv);
		}
		static void dumpBoard(const boardType& board, std::ostream& str) noexcept
		{
			return frontendType::dumpBoard_Implementation(board, str);
		}
		static bool parseMove(const std::string str, const stackType& stack, moveType& move, std::string& error) noexcept
		{
			return frontendType::parseMove_Implementation(str, stack, move, error);
		}
		static std::string variationToStringFromDepth(const stackType& stack, const variationType& variation, depthType depth)
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
		static std::string variationToString(const stackType& stack, const variationType& variation)
		{
			return variationToStringFromDepth(stack, variation, 0);
		}
	};
}