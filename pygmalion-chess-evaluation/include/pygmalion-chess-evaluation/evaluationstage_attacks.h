namespace pygmalion::chess
{
	class evaluationstage_attacks :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_attacks, int>
	{
		friend pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_attacks, int>;
	public:
		PYGMALION_TUNABLE static inline double Attack{ 0.125 / 64.0 };
	private:
		PYGMALION_INLINE static scoreType quietChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to) noexcept
		{
			const int maxFrom{ static_cast<int>(generatorType::captureTargets(pl,pc,from).count() + generatorType::promoCaptureTargets(pl,pc,from).count()) };
			const int maxTo{ static_cast<int>(generatorType::captureTargets(pl,pc,to).count() + generatorType::promoCaptureTargets(pl,pc,to).count()) };
			const int d{ maxFrom + maxTo };
			return d * (pParameters[0]);
		}
		PYGMALION_INLINE static scoreType promotionChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const pieceType promoted) noexcept
		{
			const int maxFrom{ static_cast<int>(generatorType::captureTargets(pl,pc,from).count() + generatorType::promoCaptureTargets(pl,pc,from).count()) };
			const int maxTo{ static_cast<int>(generatorType::captureTargets(pl,promoted,to).count() + generatorType::promoCaptureTargets(pl,promoted,to).count()) };
			const int d{ maxFrom + maxTo };
			return d * (pParameters[0]);
		}
		PYGMALION_INLINE static scoreType captureChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc) noexcept
		{
			const int maxFrom{ static_cast<int>(generatorType::captureTargets(pl,pc,from).count() + generatorType::promoCaptureTargets(pl,pc,from).count()) };
			const int maxTo{ static_cast<int>(generatorType::captureTargets(pl,pc,to).count() + generatorType::promoCaptureTargets(pl,pc,to).count()) };
			const int maxVictim{ static_cast<int>(generatorType::captureTargets(vpl,vpc,to).count() + generatorType::promoCaptureTargets(vpl,vpc,to).count()) };
			const int d{ maxFrom + maxTo + maxVictim };
			return d * (pParameters[0]);
		}
		PYGMALION_INLINE static scoreType promoCaptureChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc, const pieceType promoted) noexcept
		{
			const int maxFrom{ static_cast<int>(generatorType::captureTargets(pl,pc,from).count() + generatorType::promoCaptureTargets(pl,pc,from).count()) };
			const int maxTo{ static_cast<int>(generatorType::captureTargets(pl,promoted,to).count() + generatorType::promoCaptureTargets(pl,promoted,to).count()) };
			const int maxVictim{ static_cast<int>(generatorType::captureTargets(vpl,vpc,to).count() + generatorType::promoCaptureTargets(vpl,vpc,to).count()) };
			const int d{ maxFrom + maxTo + maxVictim };
			return d * (pParameters[0]);
		}
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 1;
		}
		static parameter getParameter_Implementation(const size_t index) noexcept
		{
			return parameter(Attack, 0.0, 1.0, 0.001, "term_attack");
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static void computeData_Implementation(const generatorType::template stackType<PLAYER>& stack, int& data) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			const squaresType attackedByBlack{ stack.template squaresAttackedByPlayer<static_cast<size_t>(blackPlayer)>() };
			const squaresType attackedByWhite{ stack.template squaresAttackedByPlayer<static_cast<size_t>(whitePlayer)>() };
			const int attacks{ static_cast<int>(attackedByWhite.count()) - static_cast<int>(attackedByBlack.count()) };
			if constexpr (movingPlayer == blackPlayer)
				data = -attacks;
			else
				data = attacks;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate_Implementation(const int data, const scoreType* pParameters) noexcept
		{
			const scoreType scoreAttacks{ data * pParameters[0] };
			return scoreAttacks;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType differentiate_Implementation(const dataType, const size_t parameterIndex, const scoreType* pParameters) noexcept
		{
			PYGMALION_ASSERT(parameterIndex == 0);
			return static_cast<scoreType>(data);
		}
		static std::string name_Implementation() noexcept
		{
			return "attacks";
		}
	};
}