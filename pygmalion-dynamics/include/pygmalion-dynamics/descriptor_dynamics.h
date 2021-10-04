namespace pygmalion
{
	template<typename MOTOR, size_t COUNT_MAX_GENERATED_MOVES, size_t MANTISSA, size_t SHIFT, size_t MAXDIST, size_t COUNT_PASSES, size_t COUNT_TACTICALPASSES, size_t COUNT_CRITICALPASSES, size_t COUNT_QUIETCRITICALPASSES, size_t COUNT_CRITICALEVASIONPASSES, size_t COUNT_TACTICALCRITICALEVASIONPASSES, size_t COUNT_WINNINGPASSES, size_t COUNT_EQUALPASSES, size_t COUNT_LOSINGPASSES, size_t COUNT_QUIETPASSES>
	class descriptor_dynamics :
		public MOTOR::descriptorMechanics
	{
	public:
		constexpr static const size_t countMovegenStages{ 10 };
		constexpr static const size_t countMaxGeneratedMoves{ COUNT_MAX_GENERATED_MOVES };
		constexpr static const inline std::array<size_t, countMovegenStages> countMovegenPasses
		{
			COUNT_PASSES,
			COUNT_TACTICALPASSES,
			COUNT_CRITICALPASSES,
			COUNT_QUIETCRITICALPASSES,
			COUNT_CRITICALEVASIONPASSES,
			COUNT_TACTICALCRITICALEVASIONPASSES,
			COUNT_WINNINGPASSES,
			COUNT_EQUALPASSES,
			COUNT_LOSINGPASSES,
			COUNT_QUIETPASSES
		};
		constexpr static const size_t movegenStage_AllMoves{ 0 };
		constexpr static const size_t movegenStage_TacticalMoves{ 1 };
		constexpr static const size_t movegenStage_CriticalMoves{ 2 };
		constexpr static const size_t movegenStage_QuietCriticalMoves{ 3 };
		constexpr static const size_t movegenStage_CriticalEvasionMoves{ 4 };
		constexpr static const size_t movegenStage_TacticalCriticalEvasionMoves{ 5 };
		constexpr static const size_t movegenStage_WinningMoves{ 6 };
		constexpr static const size_t movegenStage_EqualMoves{ 7 };
		constexpr static const size_t movegenStage_LosingMoves{ 8 };
		constexpr static const size_t movegenStage_QuietMoves{ 9 };
		constexpr static const size_t maxCountPasses{ ([]()
			{
				size_t n = 0;
				for (size_t i = 0; i < countMovegenStages; i++)
				{
					n = std::max(n, countMovegenPasses[i]);
				}
				return n;
			})() };
		using passType = uint_t < arrayhelper::requiredUnsignedBits(maxCountPasses + 1), false > ;
		using passlistType = list<passType, countMaxGeneratedMoves>;
		using stageType= uint_t < arrayhelper::requiredUnsignedBits(countMovegenStages + 1), false >;
		using stagelistType = list<stageType, countMaxGeneratedMoves>;
		using motorType = MOTOR;
		using descriptorMechanics = typename MOTOR::descriptorMechanics;
		using movelistType = list<typename descriptorMechanics::movebitsType, countMaxGeneratedMoves>;
		using indexType = typename movelistType::counterType;
		using scoreType = pygmalion::score<MANTISSA, SHIFT, MAXDIST>;
		using scorelistType = list<scoreType, countMaxGeneratedMoves>;
		constexpr static const size_t evaluationMantissa{ MANTISSA };
		constexpr static const size_t evaluationShift{ SHIFT };
		constexpr static const size_t evaluationMaxDistance{ MAXDIST };
	};

}