namespace pygmalion::chess
{
	class evaluationstage_control :
		public pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_control, int>
	{
		friend pygmalion::evaluationstage<descriptor_evaluation, evaluationstage_control, int>;
	public:
		PYGMALION_TUNABLE static inline scoreType Control{ static_cast<scoreType>(0.25 / 64.0) };
	private:
		PYGMALION_INLINE static scoreType quietChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to) noexcept
		{
			const int maxFrom{ static_cast<int>(generatorType::captureTargets(pl,pc,from).count() + generatorType::promoCaptureTargets(pl,pc,from).count()) };
			const int maxTo{ static_cast<int>(generatorType::captureTargets(pl,pc,to).count() + generatorType::promoCaptureTargets(pl,pc,to).count()) };
			const int d{ std::max(maxFrom,maxTo) };
			return d * (pParameters[0]);
		}
		PYGMALION_INLINE static scoreType promotionChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const pieceType promoted) noexcept
		{
			const int maxFrom{ static_cast<int>(generatorType::captureTargets(pl,pc,from).count() + generatorType::promoCaptureTargets(pl,pc,from).count()) };
			const int maxTo{ static_cast<int>(generatorType::captureTargets(pl,promoted,to).count() + generatorType::promoCaptureTargets(pl,promoted,to).count()) };
			const int d{ std::max(maxFrom,maxTo) };
			return d * (pParameters[0]);
		}
		PYGMALION_INLINE static scoreType captureChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc) noexcept
		{
			const int maxFrom{ static_cast<int>(generatorType::captureTargets(pl,pc,from).count() + generatorType::promoCaptureTargets(pl,pc,from).count()) };
			const int maxTo{ static_cast<int>(generatorType::captureTargets(pl,pc,to).count() + generatorType::promoCaptureTargets(pl,pc,to).count()) };
			const int maxVictim{ static_cast<int>(generatorType::captureTargets(vpl,vpc,to).count() + generatorType::promoCaptureTargets(vpl,vpc,to).count()) };
			const int d{ std::max(maxFrom,maxTo) + maxVictim };
			return d * (pParameters[0]);
		}
		PYGMALION_INLINE static scoreType promoCaptureChange_Implementation(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc, const pieceType promoted) noexcept
		{
			const int maxFrom{ static_cast<int>(generatorType::captureTargets(pl,pc,from).count() + generatorType::promoCaptureTargets(pl,pc,from).count()) };
			const int maxTo{ static_cast<int>(generatorType::captureTargets(pl,promoted,to).count() + generatorType::promoCaptureTargets(pl,promoted,to).count()) };
			const int maxVictim{ static_cast<int>(generatorType::captureTargets(vpl,vpc,to).count() + generatorType::promoCaptureTargets(vpl,vpc,to).count()) };
			const int d{ std::max(maxFrom,maxTo) + maxVictim };
			return d * (pParameters[0]);
		}
	public:
		constexpr static size_t getParameterCount_Implementation() noexcept
		{
			return 1;
		}
		static parameterType getParameter_Implementation(const size_t index) noexcept
		{
			return parameterType(Control, static_cast<scoreType>(0.0), static_cast<scoreType>(1.0), static_cast<scoreType>(0.001), "term_control");
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static void computeData_Implementation(const generatorType::template stackType<PLAYER>& stack, dataType& data) noexcept
		{
			constexpr const playerType movingPlayer{ static_cast<playerType>(PLAYER) };
			squaresType controlledByBlack;
			squaresType controlledByWhite;
			stack.control(controlledByWhite, controlledByBlack);
			const int control{ static_cast<int>(controlledByWhite.count()) - static_cast<int>(controlledByBlack.count()) };
			if constexpr (movingPlayer == blackPlayer)
				data = -control;
			else
				data = control;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate_Implementation(const dataType& data, const scoreType* pParameters) noexcept
		{
			const scoreType scoreControl{ data * pParameters[0] };
			return scoreControl;
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType differentiate_Implementation(const dataType& data, const size_t parameterIndex, const scoreType* pParameters) noexcept
		{
			PYGMALION_ASSERT(parameterIndex == 0);
			return static_cast<scoreType>(data);
		}
		static std::string name_Implementation() noexcept
		{
			return "control";
		}
	};
}