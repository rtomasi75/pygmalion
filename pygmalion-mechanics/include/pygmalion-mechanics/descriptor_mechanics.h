namespace pygmalion
{
	template<typename MOVE>
	class descriptor_mechanics :
		public MOVE::boardType::descriptorState
	{
	public:
		using moveType = MOVE;
		using movedataType = typename moveType::movedataType;
		using movebitsType = typename moveType::movebitsType;
		using boardType = typename MOVE::boardType;
		using descriptorState = typename boardType::descriptorState;
		constexpr static const size_t countMoveBits{ moveType::countBits };
	};

}