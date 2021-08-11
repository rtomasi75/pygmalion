namespace pygmalion
{
	template<typename MOVE, size_t COUNT_BITS_BLOOMFILTER, size_t COUNT_VALUES_BLOOMFILTER>
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
		constexpr static const size_t countBitsBloomfilter{ COUNT_BITS_BLOOMFILTER };
		constexpr static const size_t countValuesBloomfilter{ COUNT_VALUES_BLOOMFILTER };
		using bloomfilterType = bloomfilter<typename descriptorState::hashType, COUNT_BITS_BLOOMFILTER, COUNT_VALUES_BLOOMFILTER - 1>;
		using historyType = history<descriptor_mechanics, COUNT_BITS_BLOOMFILTER, COUNT_VALUES_BLOOMFILTER>;
	};

}