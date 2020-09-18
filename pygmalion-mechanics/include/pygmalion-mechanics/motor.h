namespace pygmalion
{
	template <typename DESCRIPTOR_MECHANICS, typename INSTANCE>
	class motor :
		public DESCRIPTOR_MECHANICS
	{
	public:

		using mechanicsType = INSTANCE;
		using descriptorMechanics = DESCRIPTOR_MECHANICS;
#include "include_mechanics.h"
		static movedataType makeMove(boardType& position, const movebitsType& movebits) noexcept
		{
			movedataType data{ moveType::doMove(position, movebits) };
			return data;
		}

		static void unmakeMove(boardType& position, const movedataType& data) noexcept
		{
			moveType::undoMove(position, data);
		}

		static bool parseMove(const boardType& position, std::string& text, movebitsType& movebits) noexcept
		{
			return moveType::parse(position, text, movebits);
		}

		static std::string moveToString(const boardType& position, const movebitsType& movebits) noexcept
		{
			return moveType::toString(position, movebits);
		}
	};
}