namespace pygmalion
{
	template<bool HASSQUARE1, bool HASSQUARE2, int SQUAREBITS, int CHANNELCOUNT, int DATABITS>
	class moveBase
	{
	public:
		constexpr static bool hasSquare1{ HASSQUARE1 };
		constexpr static bool hasSquare2{ HASSQUARE2 };
		constexpr static int squareBits{ SQUAREBITS };
		constexpr static int square1Bits{ hasSquare1 ? squareBits : 0 };
		constexpr static int square2Bits{ hasSquare2 ? squareBits : 0 };
		constexpr static int dataBits{ DATABITS };
		constexpr static int channelCount{ CHANNELCOUNT };
		constexpr static int channelBits{ requiredUnsignedBits(channelCount) };
		constexpr static int totalBits{ square1Bits + square2Bits + channelBits + dataBits };
		using baseType = typename int_traits<requiredBitBytes(totalBits)>::UTYPE;
		using channelType = typename int_traits<requiredBitBytes(channelBits)>::UTYPE;
		using dataType = typename int_traits<requiredBitBytes(dataBits)>::UTYPE;
		using squareType = typename int_traits<requiredBitBytes(squareBits)>::UTYPE;
	private:
		constexpr static int shiftSquare1{ 0 };
		constexpr static int shiftSquare2{ square1Bits };
		constexpr static int shiftChannel{ square1Bits + square1Bits };
		constexpr static int shiftData{ square1Bits + square1Bits + channelBits };
		const static baseType maskSquare1{ ((baseType(1) << square1Bits) - 1) << shiftSquare1 };
		const static baseType maskSquare2{ ((baseType(1) << square2Bits) - 1) << shiftSquare2 };
		const static baseType maskChannel{ ((baseType(1) << channelBits) - 1) << shiftChannel };
		const static baseType encodeSquare1(const squareType square1) noexcept
		{
			return (square1 << shiftSquare1) & maskSquare1;
		}
		const static baseType encodeSquare2(const squareType square2) noexcept
		{
			return (square2 << shiftSquare2) & maskSquare2;
		}
		const static baseType encodeChannel(const channelType channel) noexcept
		{
			return (channel << shiftChannel) & maskChannel;
		}
		const static baseType encodeData(const dataType data) noexcept
		{
			return (data << shiftData) & maskData;
		}
		const static squareType decodeSquare1(const baseType bits) noexcept
		{
			return (bits & maskSquare1) >> shiftSquare1;
		}
		const static squareType decodeSquare2(const baseType bits) noexcept
		{
			return (bits & maskSquare2) >> shiftSquare2;
		}
		const static channelType decodeChannel(const baseType bits) noexcept
		{
			return (bits & maskChannel) >> shiftChannel;
		}
		const static dataType decodeData(const baseType bits) noexcept
		{
			return (bits & maskData) >> shiftData;
		}
		const static baseType maskData{ ((baseType(1) << dataBits) - 1) << shiftData };
		baseType m_Bits;
	protected:
		constexpr moveBase(const squareType square1, const squareType square2, const channelType channel, const dataType data) noexcept :
			m_Bits{ static_cast<baseType>(encodeSquare1(square1) | encodeSquare2(square2) | encodeChannel(channel) | encodeData(data)) }
		{
		}
		constexpr moveBase() noexcept :
			m_Bits{ 0 }
		{
		}
		constexpr squareType square1() const noexcept
		{
			return decodeSquare1(m_Bits);
		}
		constexpr squareType square2() const noexcept
		{
			return decodeSquare2(m_Bits);
		}
		constexpr dataType data() const noexcept
		{
			return decodeData(m_Bits);
		}
		constexpr channelType channel() const noexcept
		{
			return decodeChannel(m_Bits);
		}
		constexpr moveBase(const moveBase&) noexcept = default;
		constexpr moveBase(moveBase&&) noexcept = default;
		constexpr moveBase& operator=(const moveBase&) noexcept = default;
		constexpr moveBase& operator=(moveBase&&) noexcept = default;
		~moveBase() noexcept = default;
	public:
	};
}