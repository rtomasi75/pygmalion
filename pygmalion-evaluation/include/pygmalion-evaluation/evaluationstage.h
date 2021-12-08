namespace pygmalion
{
	template<typename DESCRIPTION_EVALUATION, typename INSTANCE, typename DATATYPE>
	class evaluationstage :
		public DESCRIPTION_EVALUATION
	{
	public:
		using instanceType = INSTANCE;
		using dataType = DATATYPE;
		using descriptorEvaluation = DESCRIPTION_EVALUATION;
#include "include_evaluation.h"	
	protected:
		PYGMALION_INLINE static scoreType quietChange(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to) noexcept
		{
			return instanceType::quietChange_Implementation(pParameters, spl, pl, pc, from, to);
		}
		PYGMALION_INLINE static scoreType promotionChange(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const pieceType promoted) noexcept
		{
			return instanceType::promotionChange_Implementation(pParameters, spl, pl, pc, from, to, promoted);
		}
		PYGMALION_INLINE static scoreType captureChange(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc) noexcept
		{
			return instanceType::captureChange_Implementation(pParameters, spl, pl, pc, from, to, vpl, vpc);
		}
		PYGMALION_INLINE static scoreType promoCaptureChange(const scoreType* pParameters, const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc, const pieceType promoted) noexcept
		{
			return instanceType::promoCaptureChange_Implementation(pParameters, spl, pl, pc, from, to, vpl, vpc, promoted);
		}
	public:
		constexpr static size_t getParameterCount() noexcept
		{
			return instanceType::getParameterCount_Implementation();
		}
		static parameter getParameter(const size_t index) noexcept
		{
			return instanceType::getParameter_Implementation(index);
		}
		static void computeDelta(const scoreType* pParameters, deltaType& delta) noexcept
		{
			const auto lambdaQuiet
			{
				[pParameters](const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to)
				{
					return quietChange(pParameters, spl, pl, pc, from, to);
				}
			};
			const auto lambdaPromotion
			{
				[pParameters](const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const pieceType promoted)
				{
					return promotionChange(pParameters, spl, pl, pc, from, to, promoted);
				}
			};
			const auto lambdaCapture
			{
				[pParameters](const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc)
				{
					return captureChange(pParameters, spl, pl, pc, from, to, vpl, vpc);
				}
			};
			const auto lambdaPromoCapture
			{
				[pParameters](const playerType spl, const playerType pl, const pieceType pc, const squareType from, const squareType to, const playerType vpl, const pieceType vpc, const pieceType promoted)
				{
					return promoCaptureChange(pParameters, spl, pl, pc, from, to, vpl, vpc, promoted);
				}
			};
			generatorType::computeDelta(delta, lambdaQuiet, lambdaCapture, lambdaPromotion, lambdaPromoCapture);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static void computeData(const typename generatorType::template stackType<PLAYER>& stack, dataType& data) noexcept
		{
			instanceType::template computeData_Implementation<PLAYER>(stack, data);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType evaluate(const dataType& data, const scoreType* pParameters) noexcept
		{
			return instanceType::template evaluate_Implementation<PLAYER>(data, pParameters);
		}
		template<size_t PLAYER>
		PYGMALION_INLINE static scoreType differentiate(const dataType, const size_t parameterIndex, const scoreType* pParameters) noexcept
		{
			return instanceType::template differentiate_Implementation<PLAYER>(data, parameterIndex, pParameters);
		}
		static std::string name() noexcept
		{
			return instanceType::name_Implementation();
		}
	};
}