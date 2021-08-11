namespace pygmalion
{
	template<typename MOTOR, size_t COUNT_MAX_GENERATED_MOVES, size_t COUNT_BITS_BLOOMFILTER, size_t COUNT_VALUES_BLOOMFILTER>
	class descriptor_dynamics :
		public MOTOR::descriptorMechanics
	{
	public:
		constexpr static const size_t countMaxGeneratedMoves{ COUNT_MAX_GENERATED_MOVES };
		constexpr static const size_t countBitsBloomfilter{ COUNT_BITS_BLOOMFILTER };
		constexpr static const size_t countValuesBloomfilter{ COUNT_VALUES_BLOOMFILTER };
		using motorType = MOTOR;
		using descriptorMechanics = typename MOTOR::descriptorMechanics;
		using bloomfilterType = bloomfilter<typename descriptorMechanics::descriptorState::hashType, countBitsBloomfilter, countValuesBloomfilter - 1>;
		using movelistType = list<typename descriptorMechanics::movebitsType, countMaxGeneratedMoves>;
		using indexType = typename movelistType::counterType;
	};

}