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
		using stackType = typename pygmalion::frontend<DESCRIPTION_FRONTEND, frontendType>::stack;

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
		static std::string moveToString(const boardType& position, const moveType mv) noexcept
		{
			return frontendType::moveToString_Implementation(position, mv);
		}
		static void dumpBoard(const boardType& board, std::ostream& str) noexcept
		{
			return frontendType::dumpBoard_Implementation(board, str);
		}
		static bool parseMove(const std::string str, const boardType& position, moveType& move, std::string& error) noexcept
		{
			return frontendType::parseMove_Implementation(str, position, move, error);
		}
		static std::string variationToString(const boardType& position, const variationType& variation)
		{
			return frontendType::variationToString_Implementation(position, variation);
		}
	};
}