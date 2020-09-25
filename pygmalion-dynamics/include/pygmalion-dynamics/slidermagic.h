namespace pygmalion::dynamics
{
	template<typename DESCRIPTOR_DYNAMICS>
	class slidermagicinfo :
		public DESCRIPTOR_DYNAMICS
	{
	public:

		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "include_dynamics.h"

	private:
		squareType m_Square;
	public:
		constexpr slidermagicinfo() noexcept :
			m_Square{ squareType::invalid }
		{
		}
		constexpr slidermagicinfo(const squareType square) noexcept :
			m_Square{ square }
		{

		}
		constexpr slidermagicinfo(const slidermagicinfo&) noexcept = default;
		constexpr slidermagicinfo(slidermagicinfo&&) noexcept = default;
		~slidermagicinfo() noexcept = default;
		constexpr slidermagicinfo& operator=(const slidermagicinfo&) noexcept = default;
		constexpr slidermagicinfo& operator=(slidermagicinfo&&) noexcept = default;
		constexpr auto square() const noexcept
		{
			return m_Square;
		}
	};

	template<typename DESCRIPTOR_DYNAMICS, typename PROPAGATOR>
	class slidermagic :
		public DESCRIPTOR_DYNAMICS,
		public pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, typename DESCRIPTOR_DYNAMICS::squaresType, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>
	{
	public:
		using propagatorType = PROPAGATOR;
		using descriptorDynamics = DESCRIPTOR_DYNAMICS;
#include "include_dynamics.h"
	private:
		using parentType = pygmalion::magictable<DESCRIPTOR_DYNAMICS::squaresType::countSquares, DESCRIPTOR_DYNAMICS::squaresType::countSquares, typename DESCRIPTOR_DYNAMICS::squaresType, slidermagicinfo<DESCRIPTOR_DYNAMICS>, slidermagic<DESCRIPTOR_DYNAMICS, PROPAGATOR>>;
		using bitsType = typename parentType::bitsType;
	public:
	private:
	public:
		void initializeValue_Implementation(squaresType& value, const slidermagicinfo<descriptorDynamics>& info, const bitsType& blockers, const bitsType& premask) const noexcept
		{
			assert(info.square().isValid());
			value = propagatorType::attacks(squaresType(info.square()), squaresType(~blockers));
		}
		static bitsType calculatePremask(const slidermagicinfo<descriptorDynamics>& info) noexcept
		{
			assert(info.square().isValid());
			return static_cast<bitsType>(propagatorType::relevant(info.square()));
		}
		slidermagic(const slidermagicinfo<descriptorDynamics>& info) noexcept :
			parentType(info)
		{
		}
		slidermagic(const slidermagicinfo<descriptorDynamics>& info, const bitsType& factor, const size_t shift) noexcept :
			parentType(info, factor, shift)
		{
		}
		slidermagic() noexcept = default;
		slidermagic(const slidermagic&) noexcept = default;
		constexpr slidermagic(slidermagic&&) noexcept = default;
		~slidermagic() noexcept = default;
		const squaresType& operator[](const squaresType& blockers) const
		{
			return slidermagic::value(static_cast<bitsType>(blockers));
		}
		slidermagic& operator=(const slidermagic&) noexcept = default;
		slidermagic& operator=(slidermagic&&) noexcept = default;
	};

}