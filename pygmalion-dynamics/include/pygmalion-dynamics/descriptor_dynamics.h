namespace pygmalion
{
	template<typename MOTOR, size_t COUNT_MAX_GENERATED_MOVES>
	class descriptor_dynamics :
		public MOTOR::descriptorMechanics
	{
	public:
		constexpr static const size_t countMaxGeneratedMoves{ COUNT_MAX_GENERATED_MOVES };
		using motorType = MOTOR;
		using descriptorMechanics = typename MOTOR::descriptorMechanics;
		using movelistType = list<typename descriptorMechanics::movebitsType, countMaxGeneratedMoves>;
		using indexType = typename movelistType::counterType;
	};

}