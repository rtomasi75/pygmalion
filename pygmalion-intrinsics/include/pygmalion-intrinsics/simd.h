namespace pygmalion
{
	template<typename A,size_t N>
	class simd
	{
	private:
		std::array<A, N> m_Value;
	public:
		constexpr simd() noexcept :
			m_Value{ arrayhelper::make<N,A>(0) }
		{

		}
	};
}