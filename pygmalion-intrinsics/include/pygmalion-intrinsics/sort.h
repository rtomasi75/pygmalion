namespace pygmalion
{
	namespace detail
	{
		template<typename VALUE, typename SCORE>
		class sortTraits
		{
		public:
			constexpr static const bool inline isGeneric{ true };
		};

		template<>
		class sortTraits<std::uint8_t, std::int8_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint16_t, std::int8_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint32_t, std::int8_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint64_t, std::int8_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint8_t, std::int16_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint16_t, std::int16_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint32_t, std::int16_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint64_t, std::int16_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint8_t, std::int32_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint16_t, std::int32_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint32_t, std::int32_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint64_t, std::int32_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint8_t, std::int64_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint16_t, std::int64_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint32_t, std::int64_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};
		template<>
		class sortTraits<std::uint64_t, std::int64_t>
		{
		public:
			constexpr static const bool inline isGeneric{ false };
		};


		template<typename VALUE, typename SCORE>
		class compare
		{
		private:
			static void sort_N1(VALUE* pValues, SCORE* pScores) noexcept
			{
			}
			static void sort_N2(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar<0, 1>(pValues, pScores); // FIRST 1-Lane
			}
			static void sort_N3(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar<1, 2>(pValues, pScores);
				scalar<0, 2>(pValues, pScores);
				scalar<0, 1>(pValues, pScores);
			}
			static void sort_N4(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<0, 1, 2, 3>(pValues, pScores); // FIRST 2-Lane
				vector2<0, 2, 1, 3>(pValues, pScores);
				scalar<1, 2>(pValues, pScores);
			}
			static void sort_N5(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<0, 4, 1, 3>(pValues, pScores);
				scalar<0, 2>(pValues, pScores);
				vector2<2, 4, 0, 1>(pValues, pScores);
				vector2<2, 3, 1, 4>(pValues, pScores);
				vector2<1, 2, 3, 4>(pValues, pScores);
			}
			static void sort_N6(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<0, 4, 1, 5>(pValues, pScores);
				vector2<0, 2, 1, 3>(pValues, pScores);
				vector3<2, 4, 3, 5, 0, 1>(pValues, pScores); // FIRST 3-Lane
				vector2<2, 3, 4, 5>(pValues, pScores);
				scalar<1, 4>(pValues, pScores);
				vector2<1, 2, 3, 4 >(pValues, pScores);
			}
			static void sort_N7(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector3<0, 4, 1, 5, 2, 6>(pValues, pScores);
				vector3<0, 2, 1, 3, 4, 6>(pValues, pScores);
				vector3<2, 4, 3, 5, 0, 1>(pValues, pScores);
				vector2<2, 3, 4, 5>(pValues, pScores);
				vector2<1, 4, 3, 6>(pValues, pScores);
				vector3<1, 2, 3, 4, 5, 6>(pValues, pScores);
			}
			static void sort_N8(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores); // FIRST 4-Lane
				vector4<0, 2, 1, 3, 4, 6, 5, 7>(pValues, pScores);
				vector4<2, 4, 3, 5, 0, 1, 6, 7>(pValues, pScores);
				vector2<2, 3, 4, 5>(pValues, pScores);
				vector2<1, 4, 3, 6>(pValues, pScores);
				vector3<1, 2, 3, 4, 5, 6>(pValues, pScores);
			}
			static void sort_N9(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<0, 8, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector3<0, 4, 1, 3, 5, 7>(pValues, pScores);
				vector3<4, 8, 0, 2, 3, 5>(pValues, pScores);
				vector3<4, 6, 2, 8, 0, 1>(pValues, pScores);
				vector2<2, 4, 6, 8>(pValues, pScores);
				vector4<2, 3, 4, 5, 6, 7, 1, 8>(pValues, pScores);
				vector3<1, 4, 3, 6, 5, 8>(pValues, pScores);
				vector4<1, 2, 3, 4, 5, 6, 7, 8>(pValues, pScores);
			}
			static void sort_N10(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector5<4, 9, 3, 8, 2, 7, 1, 6, 0, 5>(pValues, pScores); // FIRST 5-Lane
				vector4<1, 4, 6, 9, 0, 3, 5, 8>(pValues, pScores);
				vector3<0, 2, 3, 6, 7, 9>(pValues, pScores);
				vector4<0, 1, 2, 4, 5, 7, 8, 9>(pValues, pScores);
				vector4<1, 2, 4, 6, 7, 8, 3, 5>(pValues, pScores);
				vector4<2, 5, 6, 8, 1, 3, 4, 7>(pValues, pScores);
				vector2<2, 3, 6, 7>(pValues, pScores);
				vector2<3, 4, 5, 6>(pValues, pScores);
				scalar<4, 5>(pValues, pScores);
			}
			static void sort_N11(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector5<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>(pValues, pScores);
				vector5<1, 3, 5, 7, 0, 2, 4, 6, 8, 10>(pValues, pScores);
				vector5<1, 2, 5, 6, 9, 10, 0, 4, 3, 7>(pValues, pScores);
				vector3<1, 5, 6, 10, 4, 8>(pValues, pScores);
				vector4<5, 9, 2, 6, 0, 4, 3, 8>(pValues, pScores);
				vector4<1, 5, 6, 10, 2, 3, 8, 9>(pValues, pScores);
				vector4<1, 4, 7, 10, 3, 5, 6, 8>(pValues, pScores);
				vector3<2, 4, 7, 9, 5, 6>(pValues, pScores);
				vector2<3, 4, 7, 8>(pValues, pScores);
			}
			static void sort_N12(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector6<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11>(pValues, pScores); // FIRST 6-Lane
				vector6<1, 3, 5, 7, 9, 11, 0, 2, 4, 6, 8, 10>(pValues, pScores);
				vector5<1, 2, 5, 6, 9, 10, 0, 4, 7, 11>(pValues, pScores);
				vector4<1, 5, 6, 10, 3, 7, 4, 8>(pValues, pScores);
				vector5<5, 9, 2, 6, 0, 4, 7, 11, 3, 8>(pValues, pScores);
				vector4<1, 5, 6, 10, 2, 3, 8, 9>(pValues, pScores);
				vector4<1, 4, 7, 10, 3, 5, 6, 8>(pValues, pScores);
				vector3<2, 4, 7, 9, 5, 6>(pValues, pScores);
				vector2<3, 4, 7, 8>(pValues, pScores);
			}
			static void sort_N13(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector6<1, 7, 9, 11, 3, 4, 5, 8, 0, 12, 2, 6>(pValues, pScores);
				vector6<0, 1, 2, 3, 4, 6, 8, 11, 7, 12, 5, 9>(pValues, pScores);
				vector5<0, 2, 3, 7, 10, 11, 1, 4, 6, 12>(pValues, pScores);
				vector4<7, 8, 11, 12, 4, 9, 6, 10>(pValues, pScores);
				vector5<3, 4, 5, 6, 8, 9, 10, 11, 1, 7>(pValues, pScores);
				vector6<2, 6, 9, 11, 1, 3, 4, 7, 8, 10, 0, 5>(pValues, pScores);
				vector3<2, 5, 6, 8, 9, 10>(pValues, pScores);
				vector4<1, 2, 3, 5, 7, 8, 4, 6>(pValues, pScores);
				vector4<2, 3, 4, 5, 6, 7, 8, 9>(pValues, pScores);
				vector2<3, 4, 5, 6>(pValues, pScores);
			}
			static void sort_N14(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector7<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13>(pValues, pScores); // FIRST 7-Lane
				vector6<0, 2, 4, 6, 8, 10, 1, 3, 5, 7, 9, 11>(pValues, pScores);
				vector6<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 3, 7>(pValues, pScores);
				vector6<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13>(pValues, pScores);
				vector6<5, 10, 6, 9, 3, 12, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				vector5<1, 4, 7, 13, 2, 8, 5, 6, 9, 10>(pValues, pScores);
				vector4<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				vector4<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				vector5<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				vector2<6, 7, 8, 9>(pValues, pScores);
			}
			static void sort_N15(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector7<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13>(pValues, pScores);
				vector7<0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11>(pValues, pScores);
				vector7<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7>(pValues, pScores);
				vector7<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14>(pValues, pScores);
				vector7<5, 10, 6, 9, 3, 12, 13, 14, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				vector6<1, 4, 7, 13, 2, 8, 11, 14, 5, 6, 9, 10>(pValues, pScores);
				vector4<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				vector4<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				vector5<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				vector2<6, 7, 8, 9>(pValues, pScores);
			}
			static void sort_N16(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>(pValues, pScores); // FIRST 8-Lane
				vector8<0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15>(pValues, pScores);
				vector8<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15>(pValues, pScores);
				vector8<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector7<5, 10, 6, 9, 3, 12, 13, 14, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				vector6<1, 4, 7, 13, 2, 8, 11, 14, 5, 6, 9, 10>(pValues, pScores);
				vector4<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				vector4<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				vector5<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				vector2<6, 7, 8, 9>(pValues, pScores);
			}
			static void sort_N17(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector7<0, 8, 1, 5, 2, 6, 3, 7, 9, 13, 10, 14, 11, 15>(pValues, pScores);
				vector7<8, 16, 0, 4, 5, 9, 6, 10, 7, 11, 1, 3, 13, 15>(pValues, pScores);
				vector5<8, 12, 4, 16, 0, 2, 5, 7, 9, 11>(pValues, pScores);
				vector5<4, 8, 12, 16, 3, 9, 7, 13, 0, 1>(pValues, pScores);
				vector7<4, 6, 8, 10, 12, 14, 2, 16, 3, 5, 7, 9, 11, 13>(pValues, pScores);
				vector3<2, 8, 6, 12, 10, 16>(pValues, pScores);
				vector4<2, 4, 6, 8, 10, 12, 14, 16>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 16>(pValues, pScores);
				vector5<1, 8, 3, 10, 5, 12, 7, 14, 9, 16>(pValues, pScores);
				vector7<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16>(pValues, pScores);
				vector8<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16>(pValues, pScores);
			}
			static void sort_N18(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector6<0, 8, 1, 9, 2, 6, 3, 7, 10, 14, 11, 15>(pValues, pScores);
				vector6<8, 16, 9, 17, 0, 4, 1, 5, 6, 10, 7, 11>(pValues, pScores);
				vector6<8, 12, 9, 13, 4, 16, 5, 17, 0, 2, 1, 3>(pValues, pScores);
				vector5<4, 8, 5, 9, 12, 16, 13, 17, 0, 1>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 2, 16, 3, 17>(pValues, pScores);
				vector6<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17>(pValues, pScores);
				vector8<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				vector4<1, 16, 3, 10, 5, 12, 7, 14>(pValues, pScores);
				vector5<1, 8, 9, 16, 3, 6, 7, 10, 11, 14>(pValues, pScores);
				vector4<1, 4, 5, 8, 9, 12, 13, 16>(pValues, pScores);
				vector8<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16>(pValues, pScores);
			}
			static void sort_N19(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector5<0, 8, 1, 9, 2, 10, 3, 7, 11, 15>(pValues, pScores);
				vector7<8, 16, 9, 17, 10, 18, 0, 4, 1, 5, 2, 6, 7, 11>(pValues, pScores);
				vector8<8, 12, 9, 13, 10, 14, 4, 16, 5, 17, 6, 18, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 8, 5, 9, 6, 10, 12, 16, 13, 17, 14, 18, 0, 1>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 3, 17>(pValues, pScores);
				vector5<2, 16, 3, 9, 6, 12, 7, 13, 11, 17>(pValues, pScores);
				vector6<2, 8, 10, 16, 3, 5, 7, 9, 11, 13, 15, 17>(pValues, pScores);
				vector4<2, 4, 6, 8, 10, 12, 14, 16>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 12, 7, 14>(pValues, pScores);
				vector4<1, 8, 3, 10, 9, 16, 11, 18>(pValues, pScores);
				vector8<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18>(pValues, pScores);
				vector9<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18>(pValues, pScores); // FIRST 9-Lane
			}
			static void sort_N20(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector4<0, 8, 1, 9, 2, 10, 3, 11>(pValues, pScores);
				vector8<8, 16, 9, 17, 10, 18, 11, 19, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 4, 16, 5, 17, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores); // FIRST 10-Lane
				vector9<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector5<2, 16, 3, 17, 6, 12, 7, 13, 18, 19>(pValues, pScores);
				vector4<2, 8, 3, 9, 10, 16, 11, 17>(pValues, pScores);
				vector8<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 12, 7, 14>(pValues, pScores);
				vector4<1, 8, 3, 10, 9, 16, 11, 18>(pValues, pScores);
				vector8<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18>(pValues, pScores);
				vector9<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18>(pValues, pScores);
			}
			static void sort_N21(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector5<0, 8, 1, 9, 2, 10, 3, 11, 4, 12>(pValues, pScores);
				vector9<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 5, 17, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				vector8<4, 16, 5, 9, 6, 10, 7, 11, 13, 17, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				vector6<4, 8, 12, 16, 5, 7, 9, 11, 13, 15, 17, 19>(pValues, pScores);
				vector6<4, 6, 8, 10, 12, 14, 16, 18, 3, 17, 7, 13>(pValues, pScores);
				vector4<2, 16, 6, 20, 3, 9, 11, 17>(pValues, pScores);
				vector8<2, 8, 6, 12, 10, 16, 14, 20, 3, 5, 7, 9, 11, 13, 15, 17>(pValues, pScores);
				vector5<2, 4, 6, 8, 10, 12, 14, 16, 18, 20>(pValues, pScores);
				vector9<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 14>(pValues, pScores);
				vector6<1, 8, 3, 10, 5, 12, 9, 16, 11, 18, 13, 20>(pValues, pScores);
				vector9<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20>(pValues, pScores);
				vector10<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20>(pValues, pScores);
			}
			static void sort_N22(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 14, 7, 15>(pValues, pScores);
				vector6<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13>(pValues, pScores);
				vector10<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 10, 7, 11, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				vector4<4, 8, 5, 9, 12, 16, 13, 17>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector4<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				vector8<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				vector10<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				vector10<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 14>(pValues, pScores);
				vector6<1, 8, 3, 10, 5, 12, 9, 16, 11, 18, 13, 20>(pValues, pScores);
				vector9<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20>(pValues, pScores);
				vector10<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20>(pValues, pScores);
			}
			static void sort_N23(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 15>(pValues, pScores);
				vector7<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14>(pValues, pScores);
				vector11<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores); // FIRST 11-Lane
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 11, 15, 19, 20, 22, 0, 1>(pValues, pScores);
				vector6<4, 8, 5, 9, 6, 10, 12, 16, 13, 17, 14, 18>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector4<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				vector8<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				vector10<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				vector10<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 22>(pValues, pScores);
				vector8<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22>(pValues, pScores);
				vector10<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22>(pValues, pScores);
				vector11<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22>(pValues, pScores);
			}
			static void sort_N24(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23>(pValues, pScores);
				vector8<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores); // FIRST 12-Lane
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 19, 20, 22, 21, 23, 0, 1>(pValues, pScores);
				vector9<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 22, 23>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector4<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				vector8<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				vector10<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				vector10<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 22>(pValues, pScores);
				vector8<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22>(pValues, pScores);
				vector10<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22>(pValues, pScores);
				vector11<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22>(pValues, pScores);
			}
			static void sort_N25(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector9<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24>(pValues, pScores);
				vector9<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 21, 23, 0, 1>(pValues, pScores);
				vector9<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24>(pValues, pScores);
				vector9<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22>(pValues, pScores);
				vector5<2, 16, 3, 17, 6, 20, 7, 21, 10, 24>(pValues, pScores);
				vector9<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24>(pValues, pScores);
				vector11<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24>(pValues, pScores);
				vector11<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23>(pValues, pScores);
				vector5<1, 16, 3, 18, 5, 20, 7, 22, 9, 24>(pValues, pScores);
				vector9<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24>(pValues, pScores);
				vector11<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24>(pValues, pScores);
				vector12<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24>(pValues, pScores);
			}
			static void sort_N26(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector10<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25>(pValues, pScores);
				vector10<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 0, 1>(pValues, pScores);
				vector10<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25>(pValues, pScores);
				vector10<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23>(pValues, pScores);
				vector6<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25>(pValues, pScores);
				vector10<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				vector12<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				vector12<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				vector5<1, 16, 3, 18, 5, 20, 7, 22, 9, 24>(pValues, pScores);
				vector9<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24>(pValues, pScores);
				vector11<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24>(pValues, pScores);
				vector12<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24>(pValues, pScores);
			}
			static void sort_N27(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector11<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26>(pValues, pScores);
				vector11<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector8<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 0, 1>(pValues, pScores);
				vector11<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26>(pValues, pScores);
				vector11<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26>(pValues, pScores);
				vector6<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25>(pValues, pScores);
				vector10<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				vector12<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				vector12<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				vector6<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26>(pValues, pScores);
				vector10<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26>(pValues, pScores);
				vector12<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26>(pValues, pScores);
				vector13<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26>(pValues, pScores); // FIRST 13-Lane
			}
			static void sort_N28(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector12<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27>(pValues, pScores);
				vector12<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector7<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 26, 27>(pValues, pScores);
				vector10<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				vector12<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				vector12<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				vector6<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26>(pValues, pScores);
				vector10<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26>(pValues, pScores);
				vector12<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26>(pValues, pScores);
				vector13<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26>(pValues, pScores);
			}
			static void sort_N29(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector13<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28>(pValues, pScores);
				vector13<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28>(pValues, pScores);
				vector13<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector7<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28>(pValues, pScores);
				vector11<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28>(pValues, pScores);
				vector13<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28>(pValues, pScores);
				vector13<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27>(pValues, pScores);
				vector7<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28>(pValues, pScores);
				vector11<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28>(pValues, pScores);
				vector13<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28>(pValues, pScores);
				vector14<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28>(pValues, pScores); // FIRST 14-Lane
			}
			static void sort_N30(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector14<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29>(pValues, pScores);
				vector14<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29>(pValues, pScores);
				vector14<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector8<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				vector12<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				vector14<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				vector14<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				vector7<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28>(pValues, pScores);
				vector11<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28>(pValues, pScores);
				vector13<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28>(pValues, pScores);
				vector14<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28>(pValues, pScores);
			}
			static void sort_N31(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector15<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30>(pValues, pScores); // FIRST 15-Lane
				vector15<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29, 22, 30>(pValues, pScores);
				vector15<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29, 26, 30>(pValues, pScores);
				vector11<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3, 28, 30>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector8<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				vector12<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				vector14<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				vector14<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				vector8<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28, 15, 30>(pValues, pScores);
				vector12<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28, 23, 30>(pValues, pScores);
				vector14<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28, 27, 30>(pValues, pScores);
				vector15<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30>(pValues, pScores);
			}
			static void sort_N32(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector16<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30, 15, 31>(pValues, pScores); // FIRST 16-Lane
				vector16<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29, 22, 30, 23, 31>(pValues, pScores);
				vector16<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29, 26, 30, 27, 31>(pValues, pScores);
				vector12<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3, 28, 30, 29, 31>(pValues, pScores);
				vector10<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1, 30, 31>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector8<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				vector12<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				vector14<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				vector14<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				vector8<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28, 15, 30>(pValues, pScores);
				vector12<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28, 23, 30>(pValues, pScores);
				vector14<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28, 27, 30>(pValues, pScores);
				vector15<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30>(pValues, pScores);
			}
			constexpr static size_t sort_tail() noexcept
			{
				return 3;
			}
		public:
			PYGMALION_INLINE static void quickSort(const int low, const int high, VALUE* pValues, SCORE* pScores) noexcept
			{
				const int pi{ partition(low, high, pValues, pScores) };
				sortValues(&pValues[low], &pScores[low], pi - low);
				sortValues(&pValues[pi + 1], &pScores[pi + 1], high - pi);
			}
			PYGMALION_INLINE static int partition(const int low, const int high, VALUE* pValues, SCORE* pScores) noexcept
			{
				const SCORE pivotScore{ pScores[high] };
				int i{ low - 1 };
				for (int j = low; j <= high - 1; j++)
				{
					if (pScores[j] >= pivotScore)
					{
						i++;
						std::swap(pValues[i], pValues[j]);
						std::swap(pScores[i], pScores[j]);
					}
				}
				i++;
				std::swap(pValues[i], pValues[high]);
				std::swap(pScores[i], pScores[high]);
				return i;
			}
			static void sortValues(VALUE* pValues, SCORE* pScores, const size_t length) noexcept
			{
				constexpr const auto tail{ sort_tail() };
				if (length <= tail)
				{
					switch (length)
					{
					case 0:
						return;
					case 1:
						return;
					case 2:
						sort_N2(pValues, pScores);
						return;
					case 3:
						sort_N3(pValues, pScores);
						return;
					case 4:
						sort_N4(pValues, pScores);
						return;
					case 5:
						sort_N5(pValues, pScores);
						return;
					case 6:
						sort_N6(pValues, pScores);
						return;
					case 7:
						sort_N7(pValues, pScores);
						return;
					case 8:
						sort_N8(pValues, pScores);
						return;
					case 9:
						sort_N9(pValues, pScores);
						return;
					case 10:
						sort_N10(pValues, pScores);
						return;
					case 11:
						sort_N11(pValues, pScores);
						return;
					case 12:
						sort_N12(pValues, pScores);
						return;
					case 13:
						sort_N13(pValues, pScores);
						return;
					case 14:
						sort_N14(pValues, pScores);
						return;
					case 15:
						sort_N15(pValues, pScores);
						return;
					case 16:
						sort_N16(pValues, pScores);
						return;
					case 17:
						sort_N17(pValues, pScores);
						return;
					case 18:
						sort_N18(pValues, pScores);
						return;
					case 19:
						sort_N19(pValues, pScores);
						return;
					case 20:
						sort_N20(pValues, pScores);
						return;
					case 21:
						sort_N21(pValues, pScores);
						return;
					case 22:
						sort_N22(pValues, pScores);
						return;
					case 23:
						sort_N23(pValues, pScores);
						return;
					case 24:
						sort_N24(pValues, pScores);
						return;
					case 25:
						sort_N25(pValues, pScores);
						return;
					case 26:
						sort_N26(pValues, pScores);
						return;
					case 27:
						sort_N27(pValues, pScores);
						return;
					case 28:
						sort_N28(pValues, pScores);
						return;
					case 29:
						sort_N29(pValues, pScores);
						return;
					case 30:
						sort_N30(pValues, pScores);
						return;
					case 31:
						sort_N31(pValues, pScores);
						return;
					case 32:
						sort_N32(pValues, pScores);
						return;
					default:
						PYGMALION_UNREACHABLE;
						return;
					}
				}
				else
				{
					quickSort(0, length - 1, pValues, pScores);
				}
			}
			template<size_t IDX1, size_t IDX2>
			PYGMALION_INLINE static void scalar(VALUE* pValues, SCORE* pScores) noexcept
			{
				if (pScores[IDX1] < pScores[IDX2])
				{
					std::swap(pValues[IDX1], pValues[IDX2]);
					std::swap(pScores[IDX1], pScores[IDX2]);
				}
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			PYGMALION_INLINE static void vector2(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar<IDX1a, IDX2a>(pValues, pScores);
				scalar<IDX1b, IDX2b>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			PYGMALION_INLINE static void vector3(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				scalar<IDX1c, IDX2c>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			PYGMALION_INLINE static void vector4(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				vector2<IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			PYGMALION_INLINE static void vector5(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				scalar<IDX1e, IDX2e>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			PYGMALION_INLINE static void vector6(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector2<IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			PYGMALION_INLINE static void vector7(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector3<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			PYGMALION_INLINE static void vector8(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector4<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j>
			PYGMALION_INLINE static void vector9(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				scalar<IDX1j, IDX2j>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k>
			PYGMALION_INLINE static void vector10(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector2<IDX1j, IDX2j, IDX1k, IDX2k>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l>
			PYGMALION_INLINE static void vector11(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector3<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m>
			PYGMALION_INLINE static void vector12(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector4<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n>
			PYGMALION_INLINE static void vector13(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector5<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o>
			PYGMALION_INLINE static void vector14(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector6<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p>
			static void vector15(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector7<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p, size_t IDX1q, size_t IDX2q>
			PYGMALION_INLINE static void vector16(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector8<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p, IDX1q, IDX2q>(pValues, pScores);
			}
		};

		template<>
		class compare<std::uint16_t, std::int16_t>
		{
		public:
			using VALUE = std::uint16_t;
			using SCORE = std::int16_t;
		private:
			static void sort_N0(VALUE* pValues, SCORE* pScores) noexcept
			{
			}
			static void sort_N1(VALUE* pValues, SCORE* pScores) noexcept
			{
			}
			static void sort_N2(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar<0, 1>(pValues, pScores); // FIRST 1-Lane
			}
			static void sort_N3(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar<1, 2>(pValues, pScores);
				scalar<0, 2>(pValues, pScores);
				scalar<0, 1>(pValues, pScores);
			}
			static void sort_N4(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<0, 1, 2, 3>(pValues, pScores); // FIRST 2-Lane
				vector2<0, 2, 1, 3>(pValues, pScores);
				scalar<1, 2>(pValues, pScores);
			}
			static void sort_N5(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<0, 4, 1, 3>(pValues, pScores);
				scalar<0, 2>(pValues, pScores);
				vector2<2, 4, 0, 1>(pValues, pScores);
				vector2<2, 3, 1, 4>(pValues, pScores);
				vector2<1, 2, 3, 4>(pValues, pScores);
			}
			static void sort_N6(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<0, 4, 1, 5>(pValues, pScores);
				vector2<0, 2, 1, 3>(pValues, pScores);
				vector3<2, 4, 3, 5, 0, 1>(pValues, pScores); // FIRST 3-Lane
				vector2<2, 3, 4, 5>(pValues, pScores);
				scalar<1, 4>(pValues, pScores);
				vector2<1, 2, 3, 4 >(pValues, pScores);
			}
			static void sort_N7(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector3<0, 4, 1, 5, 2, 6>(pValues, pScores);
				vector3<0, 2, 1, 3, 4, 6>(pValues, pScores);
				vector3<2, 4, 3, 5, 0, 1>(pValues, pScores);
				vector2<2, 3, 4, 5>(pValues, pScores);
				vector2<1, 4, 3, 6>(pValues, pScores);
				vector3<1, 2, 3, 4, 5, 6>(pValues, pScores);
			}
			static void sort_N8(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores); // FIRST 4-Lane
				vector4<0, 2, 1, 3, 4, 6, 5, 7>(pValues, pScores);
				vector4<2, 4, 3, 5, 0, 1, 6, 7>(pValues, pScores);
				vector2<2, 3, 4, 5>(pValues, pScores);
				vector2<1, 4, 3, 6>(pValues, pScores);
				vector3<1, 2, 3, 4, 5, 6>(pValues, pScores);
			}
			static void sort_N9(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<0, 8, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector3<0, 4, 1, 3, 5, 7>(pValues, pScores);
				vector3<4, 8, 0, 2, 3, 5>(pValues, pScores);
				vector3<4, 6, 2, 8, 0, 1>(pValues, pScores);
				vector2<2, 4, 6, 8>(pValues, pScores);
				vector4<2, 3, 4, 5, 6, 7, 1, 8>(pValues, pScores);
				vector3<1, 4, 3, 6, 5, 8>(pValues, pScores);
				vector4<1, 2, 3, 4, 5, 6, 7, 8>(pValues, pScores);
			}
			static void sort_N10(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector5<4, 9, 3, 8, 2, 7, 1, 6, 0, 5>(pValues, pScores); // FIRST 5-Lane
				vector4<1, 4, 6, 9, 0, 3, 5, 8>(pValues, pScores);
				vector3<0, 2, 3, 6, 7, 9>(pValues, pScores);
				vector4<0, 1, 2, 4, 5, 7, 8, 9>(pValues, pScores);
				vector4<1, 2, 4, 6, 7, 8, 3, 5>(pValues, pScores);
				vector4<2, 5, 6, 8, 1, 3, 4, 7>(pValues, pScores);
				vector2<2, 3, 6, 7>(pValues, pScores);
				vector2<3, 4, 5, 6>(pValues, pScores);
				scalar<4, 5>(pValues, pScores);
			}
			static void sort_N11(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector5<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>(pValues, pScores);
				vector5<1, 3, 5, 7, 0, 2, 4, 6, 8, 10>(pValues, pScores);
				vector5<1, 2, 5, 6, 9, 10, 0, 4, 3, 7>(pValues, pScores);
				vector3<1, 5, 6, 10, 4, 8>(pValues, pScores);
				vector4<5, 9, 2, 6, 0, 4, 3, 8>(pValues, pScores);
				vector4<1, 5, 6, 10, 2, 3, 8, 9>(pValues, pScores);
				vector4<1, 4, 7, 10, 3, 5, 6, 8>(pValues, pScores);
				vector3<2, 4, 7, 9, 5, 6>(pValues, pScores);
				vector2<3, 4, 7, 8>(pValues, pScores);
			}
			static void sort_N12(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector6<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11>(pValues, pScores); // FIRST 6-Lane
				vector6<1, 3, 5, 7, 9, 11, 0, 2, 4, 6, 8, 10>(pValues, pScores);
				vector5<1, 2, 5, 6, 9, 10, 0, 4, 7, 11>(pValues, pScores);
				vector4<1, 5, 6, 10, 3, 7, 4, 8>(pValues, pScores);
				vector5<5, 9, 2, 6, 0, 4, 7, 11, 3, 8>(pValues, pScores);
				vector4<1, 5, 6, 10, 2, 3, 8, 9>(pValues, pScores);
				vector4<1, 4, 7, 10, 3, 5, 6, 8>(pValues, pScores);
				vector3<2, 4, 7, 9, 5, 6>(pValues, pScores);
				vector2<3, 4, 7, 8>(pValues, pScores);
			}
			static void sort_N13(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector6<1, 7, 9, 11, 3, 4, 5, 8, 0, 12, 2, 6>(pValues, pScores);
				vector6<0, 1, 2, 3, 4, 6, 8, 11, 7, 12, 5, 9>(pValues, pScores);
				vector5<0, 2, 3, 7, 10, 11, 1, 4, 6, 12>(pValues, pScores);
				vector4<7, 8, 11, 12, 4, 9, 6, 10>(pValues, pScores);
				vector5<3, 4, 5, 6, 8, 9, 10, 11, 1, 7>(pValues, pScores);
				vector6<2, 6, 9, 11, 1, 3, 4, 7, 8, 10, 0, 5>(pValues, pScores);
				vector3<2, 5, 6, 8, 9, 10>(pValues, pScores);
				vector4<1, 2, 3, 5, 7, 8, 4, 6>(pValues, pScores);
				vector4<2, 3, 4, 5, 6, 7, 8, 9>(pValues, pScores);
				vector2<3, 4, 5, 6>(pValues, pScores);
			}
			static void sort_N14(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector7<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13>(pValues, pScores); // FIRST 7-Lane
				vector6<0, 2, 4, 6, 8, 10, 1, 3, 5, 7, 9, 11>(pValues, pScores);
				vector6<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 3, 7>(pValues, pScores);
				vector6<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13>(pValues, pScores);
				vector6<5, 10, 6, 9, 3, 12, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				vector5<1, 4, 7, 13, 2, 8, 5, 6, 9, 10>(pValues, pScores);
				vector4<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				vector4<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				vector5<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				vector2<6, 7, 8, 9>(pValues, pScores);
			}
			static void sort_N15(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector7<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13>(pValues, pScores);
				vector7<0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11>(pValues, pScores);
				vector7<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7>(pValues, pScores);
				vector7<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14>(pValues, pScores);
				vector7<5, 10, 6, 9, 3, 12, 13, 14, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				vector6<1, 4, 7, 13, 2, 8, 11, 14, 5, 6, 9, 10>(pValues, pScores);
				vector4<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				vector4<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				vector5<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				vector2<6, 7, 8, 9>(pValues, pScores);
			}
			static void sort_N16(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>(pValues, pScores); // FIRST 8-Lane
				vector8<0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15>(pValues, pScores);
				vector8<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15>(pValues, pScores);
				vector8<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector7<5, 10, 6, 9, 3, 12, 13, 14, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				vector6<1, 4, 7, 13, 2, 8, 11, 14, 5, 6, 9, 10>(pValues, pScores);
				vector4<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				vector4<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				vector5<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				vector2<6, 7, 8, 9>(pValues, pScores);
			}
			static void sort_N17(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector7<0, 8, 1, 5, 2, 6, 3, 7, 9, 13, 10, 14, 11, 15>(pValues, pScores);
				vector7<8, 16, 0, 4, 5, 9, 6, 10, 7, 11, 1, 3, 13, 15>(pValues, pScores);
				vector5<8, 12, 4, 16, 0, 2, 5, 7, 9, 11>(pValues, pScores);
				vector5<4, 8, 12, 16, 3, 9, 7, 13, 0, 1>(pValues, pScores);
				vector7<4, 6, 8, 10, 12, 14, 2, 16, 3, 5, 7, 9, 11, 13>(pValues, pScores);
				vector3<2, 8, 6, 12, 10, 16>(pValues, pScores);
				vector4<2, 4, 6, 8, 10, 12, 14, 16>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 16>(pValues, pScores);
				vector5<1, 8, 3, 10, 5, 12, 7, 14, 9, 16>(pValues, pScores);
				vector7<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16>(pValues, pScores);
				vector8<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16>(pValues, pScores);
			}
			static void sort_N18(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector6<0, 8, 1, 9, 2, 6, 3, 7, 10, 14, 11, 15>(pValues, pScores);
				vector6<8, 16, 9, 17, 0, 4, 1, 5, 6, 10, 7, 11>(pValues, pScores);
				vector6<8, 12, 9, 13, 4, 16, 5, 17, 0, 2, 1, 3>(pValues, pScores);
				vector5<4, 8, 5, 9, 12, 16, 13, 17, 0, 1>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 2, 16, 3, 17>(pValues, pScores);
				vector6<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17>(pValues, pScores);
				vector8<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				vector4<1, 16, 3, 10, 5, 12, 7, 14>(pValues, pScores);
				vector5<1, 8, 9, 16, 3, 6, 7, 10, 11, 14>(pValues, pScores);
				vector4<1, 4, 5, 8, 9, 12, 13, 16>(pValues, pScores);
				vector8<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16>(pValues, pScores);
			}
			static void sort_N19(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector5<0, 8, 1, 9, 2, 10, 3, 7, 11, 15>(pValues, pScores);
				vector7<8, 16, 9, 17, 10, 18, 0, 4, 1, 5, 2, 6, 7, 11>(pValues, pScores);
				vector8<8, 12, 9, 13, 10, 14, 4, 16, 5, 17, 6, 18, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 8, 5, 9, 6, 10, 12, 16, 13, 17, 14, 18, 0, 1>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 3, 17>(pValues, pScores);
				vector5<2, 16, 3, 9, 6, 12, 7, 13, 11, 17>(pValues, pScores);
				vector6<2, 8, 10, 16, 3, 5, 7, 9, 11, 13, 15, 17>(pValues, pScores);
				vector4<2, 4, 6, 8, 10, 12, 14, 16>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 12, 7, 14>(pValues, pScores);
				vector4<1, 8, 3, 10, 9, 16, 11, 18>(pValues, pScores);
				vector8<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18>(pValues, pScores);
				vector9<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18>(pValues, pScores); // FIRST 9-Lane
			}
			static void sort_N20(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector4<0, 8, 1, 9, 2, 10, 3, 11>(pValues, pScores);
				vector8<8, 16, 9, 17, 10, 18, 11, 19, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 4, 16, 5, 17, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores); // FIRST 10-Lane
				vector9<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector5<2, 16, 3, 17, 6, 12, 7, 13, 18, 19>(pValues, pScores);
				vector4<2, 8, 3, 9, 10, 16, 11, 17>(pValues, pScores);
				vector8<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 12, 7, 14>(pValues, pScores);
				vector4<1, 8, 3, 10, 9, 16, 11, 18>(pValues, pScores);
				vector8<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18>(pValues, pScores);
				vector9<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18>(pValues, pScores);
			}
			static void sort_N21(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector5<0, 8, 1, 9, 2, 10, 3, 11, 4, 12>(pValues, pScores);
				vector9<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 5, 17, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				vector8<4, 16, 5, 9, 6, 10, 7, 11, 13, 17, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				vector6<4, 8, 12, 16, 5, 7, 9, 11, 13, 15, 17, 19>(pValues, pScores);
				vector6<4, 6, 8, 10, 12, 14, 16, 18, 3, 17, 7, 13>(pValues, pScores);
				vector4<2, 16, 6, 20, 3, 9, 11, 17>(pValues, pScores);
				vector8<2, 8, 6, 12, 10, 16, 14, 20, 3, 5, 7, 9, 11, 13, 15, 17>(pValues, pScores);
				vector5<2, 4, 6, 8, 10, 12, 14, 16, 18, 20>(pValues, pScores);
				vector9<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 14>(pValues, pScores);
				vector6<1, 8, 3, 10, 5, 12, 9, 16, 11, 18, 13, 20>(pValues, pScores);
				vector9<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20>(pValues, pScores);
				vector10<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20>(pValues, pScores);
			}
			static void sort_N22(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 14, 7, 15>(pValues, pScores);
				vector6<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13>(pValues, pScores);
				vector10<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 10, 7, 11, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				vector4<4, 8, 5, 9, 12, 16, 13, 17>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector4<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				vector8<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				vector10<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				vector10<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 14>(pValues, pScores);
				vector6<1, 8, 3, 10, 5, 12, 9, 16, 11, 18, 13, 20>(pValues, pScores);
				vector9<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20>(pValues, pScores);
				vector10<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20>(pValues, pScores);
			}
			static void sort_N23(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 15>(pValues, pScores);
				vector7<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14>(pValues, pScores);
				vector11<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores); // FIRST 11-Lane
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 11, 15, 19, 20, 22, 0, 1>(pValues, pScores);
				vector6<4, 8, 5, 9, 6, 10, 12, 16, 13, 17, 14, 18>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector4<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				vector8<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				vector10<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				vector10<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 22>(pValues, pScores);
				vector8<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22>(pValues, pScores);
				vector10<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22>(pValues, pScores);
				vector11<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22>(pValues, pScores);
			}
			static void sort_N24(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23>(pValues, pScores);
				vector8<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores); // FIRST 12-Lane
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 19, 20, 22, 21, 23, 0, 1>(pValues, pScores);
				vector9<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 22, 23>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector4<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				vector8<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				vector10<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				vector10<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 22>(pValues, pScores);
				vector8<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22>(pValues, pScores);
				vector10<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22>(pValues, pScores);
				vector11<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22>(pValues, pScores);
			}
			static void sort_N25(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector9<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24>(pValues, pScores);
				vector9<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 21, 23, 0, 1>(pValues, pScores);
				vector9<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24>(pValues, pScores);
				vector9<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22>(pValues, pScores);
				vector5<2, 16, 3, 17, 6, 20, 7, 21, 10, 24>(pValues, pScores);
				vector9<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24>(pValues, pScores);
				vector11<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24>(pValues, pScores);
				vector11<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23>(pValues, pScores);
				vector5<1, 16, 3, 18, 5, 20, 7, 22, 9, 24>(pValues, pScores);
				vector9<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24>(pValues, pScores);
				vector11<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24>(pValues, pScores);
				vector12<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24>(pValues, pScores);
			}
			static void sort_N26(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector10<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25>(pValues, pScores);
				vector10<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 0, 1>(pValues, pScores);
				vector10<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25>(pValues, pScores);
				vector10<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23>(pValues, pScores);
				vector6<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25>(pValues, pScores);
				vector10<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				vector12<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				vector12<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				vector5<1, 16, 3, 18, 5, 20, 7, 22, 9, 24>(pValues, pScores);
				vector9<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24>(pValues, pScores);
				vector11<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24>(pValues, pScores);
				vector12<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24>(pValues, pScores);
			}
			static void sort_N27(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector11<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26>(pValues, pScores);
				vector11<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector8<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 0, 1>(pValues, pScores);
				vector11<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26>(pValues, pScores);
				vector11<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26>(pValues, pScores);
				vector6<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25>(pValues, pScores);
				vector10<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				vector12<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				vector12<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				vector6<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26>(pValues, pScores);
				vector10<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26>(pValues, pScores);
				vector12<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26>(pValues, pScores);
				vector13<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26>(pValues, pScores); // FIRST 13-Lane
			}
			static void sort_N28(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector12<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27>(pValues, pScores);
				vector12<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector7<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 26, 27>(pValues, pScores);
				vector10<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				vector12<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				vector12<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				vector6<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26>(pValues, pScores);
				vector10<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26>(pValues, pScores);
				vector12<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26>(pValues, pScores);
				vector13<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26>(pValues, pScores);
			}
			static void sort_N29(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector13<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28>(pValues, pScores);
				vector13<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28>(pValues, pScores);
				vector13<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector7<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28>(pValues, pScores);
				vector11<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28>(pValues, pScores);
				vector13<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28>(pValues, pScores);
				vector13<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27>(pValues, pScores);
				vector7<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28>(pValues, pScores);
				vector11<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28>(pValues, pScores);
				vector13<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28>(pValues, pScores);
				vector14<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28>(pValues, pScores); // FIRST 14-Lane
			}
			static void sort_N30(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector14<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29>(pValues, pScores);
				vector14<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29>(pValues, pScores);
				vector14<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector8<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				vector12<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				vector14<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				vector14<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				vector7<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28>(pValues, pScores);
				vector11<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28>(pValues, pScores);
				vector13<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28>(pValues, pScores);
				vector14<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28>(pValues, pScores);
			}
			static void sort_N31(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector15<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30>(pValues, pScores); // FIRST 15-Lane
				vector15<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29, 22, 30>(pValues, pScores);
				vector15<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29, 26, 30>(pValues, pScores);
				vector11<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3, 28, 30>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector8<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				vector12<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				vector14<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				vector14<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				vector8<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28, 15, 30>(pValues, pScores);
				vector12<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28, 23, 30>(pValues, pScores);
				vector14<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28, 27, 30>(pValues, pScores);
				vector15<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30>(pValues, pScores);
			}
			static void sort_N32(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector16<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30, 15, 31>(pValues, pScores); // FIRST 16-Lane
				vector16<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29, 22, 30, 23, 31>(pValues, pScores);
				vector16<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29, 26, 30, 27, 31>(pValues, pScores);
				vector12<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3, 28, 30, 29, 31>(pValues, pScores);
				vector10<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1, 30, 31>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector8<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				vector12<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				vector14<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				vector14<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				vector8<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28, 15, 30>(pValues, pScores);
				vector12<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28, 23, 30>(pValues, pScores);
				vector14<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28, 27, 30>(pValues, pScores);
				vector15<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30>(pValues, pScores);
			}
			typedef void SORTFUNC(VALUE* pValues, SCORE* pScores);
			constexpr static inline SORTFUNC* m_SortFunction[]
			{
				&sort_N0,
				&sort_N1,
				&sort_N2,
				&sort_N3,
				&sort_N4,
				&sort_N5,
#if defined(PYGMALION_CPU_SSE2)
				&sort_N6,
				&sort_N7,
				&sort_N8,
				&sort_N9,
				&sort_N10,
				&sort_N11,
				&sort_N12,
				&sort_N13,
				&sort_N14,
				&sort_N15,
				&sort_N16,
				&sort_N17,
				&sort_N18,
				&sort_N19,
				&sort_N20,
				&sort_N21,
				&sort_N22,
				&sort_N23,
				&sort_N24,
				&sort_N25,
				&sort_N26,
				&sort_N27,
				&sort_N28,
				&sort_N29,
				&sort_N30,
				&sort_N31,
				&sort_N32,
#endif
			};
			constexpr static size_t sort_tail() noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::flags::SSE2))
					return 32;
#endif
				return 5;
			}
		public:
			PYGMALION_INLINE static void quickSort(const int low, const int high, VALUE* pValues, SCORE* pScores) noexcept
			{
				const int pi{ partition(low, high, pValues, pScores) };
				sortValues(&pValues[low], &pScores[low], pi - low);
				sortValues(&pValues[pi + 1], &pScores[pi + 1], high - pi);
			}
			PYGMALION_INLINE static int partition(const int low, const int high, VALUE* pValues, SCORE* pScores) noexcept
			{
				const SCORE pivotScore{ pScores[high] };
				int i{ low - 1 };
				for (int j = low; j <= high - 1; j++)
				{
#if defined(PYGMALION_CPU_SSE2)
					if constexpr (cpu::supports(cpu::flags::SSE2))
					{
						const std::int32_t comparision{ static_cast<std::int32_t>(pScores[j] >= pivotScore) };
						i += comparision;
						const std::uint32_t negated{ static_cast<std::uint32_t>(-comparision) };
						const std::uint64_t mask{ static_cast<std::uint64_t>(negated & UINT32_C(0xffff)) };
						std::uint64_t interleaved1{ static_cast<std::uint64_t>(pValues[i]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[i])) << 16) };
						std::uint64_t interleaved2{ static_cast<std::uint64_t>(pValues[j]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[j])) << 16) };
						const __m128i operand1{ _mm_cvtsi64_si128(interleaved1) };
						const __m128i operand2{ _mm_cvtsi64_si128(interleaved2) };
						const __m128i maskVector{ _mm_shufflelo_epi16(_mm_cvtsi64_si128(mask), 0b00000000) };
						const __m128i delta{ _mm_and_si128(_mm_xor_si128(operand1, operand2), maskVector) };
						const __m128i result1{ _mm_xor_si128(operand1, delta) };
						const __m128i result2{ _mm_xor_si128(operand2, delta) };
						interleaved1 = _mm_cvtsi128_si64(result1);
						interleaved2 = _mm_cvtsi128_si64(result2);
						pValues[i] = static_cast<std::uint16_t>(interleaved1 & UINT64_C(0xffff));
						pScores[i] = static_cast<std::int16_t>(interleaved1 >> 16);
						pValues[j] = static_cast<std::uint16_t>(interleaved2 & UINT64_C(0xffff));
						pScores[j] = static_cast<std::int16_t>(interleaved2 >> 16);
					}
					else
#endif
					{
						const std::int32_t comparision{ static_cast<std::int32_t>(pScores[j] >= pivotScore) };
						i += comparision;
						const std::uint32_t negated{ static_cast<std::uint32_t>(-comparision) };
						const std::uint16_t mask{ static_cast<std::uint16_t>(negated & UINT32_C(0xffff)) };
						const std::uint16_t deltaScores{ static_cast<std::uint16_t>((reinterpret_cast<std::uint16_t*>(pScores)[i] ^ reinterpret_cast<std::uint16_t*>(pScores)[j]) & mask) };
						const std::uint16_t deltaValues{ static_cast<std::uint16_t>((pValues[i] ^ pValues[j]) & mask) };
						pValues[i] ^= deltaValues;
						pValues[j] ^= deltaValues;
						reinterpret_cast<std::uint16_t*>(pScores)[i] ^= deltaScores;
						reinterpret_cast<std::uint16_t*>(pScores)[j] ^= deltaScores;
					}
				}
				i++;
				std::swap(pValues[i], pValues[high]);
				std::swap(pScores[i], pScores[high]);
				return i;
			}
			static void sortValues(VALUE* pValues, SCORE* pScores, const size_t length) noexcept
			{
				constexpr const auto tail{ sort_tail() };
				if (length <= tail)
				{
					(*(m_SortFunction[length]))(pValues, pScores);
				}
				else
				{
					quickSort(0, length - 1, pValues, pScores);
				}
			}
			template<size_t IDX1, size_t IDX2>
			PYGMALION_INLINE static void scalar_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				const std::int32_t comparision{ static_cast<std::int32_t>(pScores[IDX1] < pScores[IDX2]) };
				const std::uint32_t negated{ static_cast<std::uint32_t>(-comparision) };
				const std::uint16_t mask{ static_cast<std::uint16_t>(negated & UINT32_C(0xffff)) };
				const std::uint16_t deltaScores{ static_cast<std::uint16_t>((reinterpret_cast<std::uint16_t*>(pScores)[IDX1] ^ reinterpret_cast<std::uint16_t*>(pScores)[IDX2]) & mask) };
				const std::uint16_t deltaValues{ static_cast<std::uint16_t>((pValues[IDX1] ^ pValues[IDX2]) & mask) };
				pValues[IDX1] ^= deltaValues;
				pValues[IDX2] ^= deltaValues;
				reinterpret_cast<std::uint16_t*>(pScores)[IDX1] ^= deltaScores;
				reinterpret_cast<std::uint16_t*>(pScores)[IDX2] ^= deltaScores;
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			PYGMALION_INLINE static void vector2_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar<IDX1a, IDX2a>(pValues, pScores);
				scalar<IDX1b, IDX2b>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			PYGMALION_INLINE static void vector3_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				scalar<IDX1c, IDX2c>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			PYGMALION_INLINE static void vector4_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				vector2<IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			PYGMALION_INLINE static void vector5_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				scalar<IDX1e, IDX2e>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			PYGMALION_INLINE static void vector6_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector2<IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			PYGMALION_INLINE static void vector7_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector3<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			PYGMALION_INLINE static void vector8_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector4<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j>
			PYGMALION_INLINE static void vector9_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				scalar<IDX1j, IDX2j>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k>
			PYGMALION_INLINE static void vector10_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector2<IDX1j, IDX2j, IDX1k, IDX2k>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l>
			PYGMALION_INLINE static void vector11_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector3<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m>
			PYGMALION_INLINE static void vector12_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector4<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n>
			PYGMALION_INLINE static void vector13_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector5<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o>
			PYGMALION_INLINE static void vector14_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector6<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p>
			PYGMALION_INLINE static void vector15_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector7<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p, size_t IDX1q, size_t IDX2q>
			PYGMALION_INLINE static void vector16_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector8<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p, IDX1q, IDX2q>(pValues, pScores);
			}
#if defined(PYGMALION_CPU_SSE2)
			template<size_t IDX1, size_t IDX2>
			PYGMALION_INLINE static void scalar_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t interleaved1{ static_cast<std::uint64_t>(pValues[IDX1]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1])) << 16) };
				std::uint64_t interleaved2{ static_cast<std::uint64_t>(pValues[IDX2]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2])) << 16) };
				const __m128i operand1{ _mm_cvtsi64_si128(interleaved1) };
				const __m128i operand2{ _mm_cvtsi64_si128(interleaved2) };
				const __m128i mask{ _mm_shufflelo_epi16(_mm_cmpgt_epi16(operand2, operand1), 0b00000101) };
				const __m128i delta{ _mm_and_si128(_mm_xor_si128(operand1, operand2), mask) };
				const __m128i result1{ _mm_xor_si128(operand1, delta) };
				const __m128i result2{ _mm_xor_si128(operand2, delta) };
				interleaved1 = _mm_cvtsi128_si64(result1);
				interleaved2 = _mm_cvtsi128_si64(result2);
				pValues[IDX1] = static_cast<std::uint16_t>(interleaved1 & UINT64_C(0xffff));
				pScores[IDX1] = static_cast<std::int16_t>(interleaved1 >> 16);
				pValues[IDX2] = static_cast<std::uint16_t>(interleaved2 & UINT64_C(0xffff));
				pScores[IDX2] = static_cast<std::int16_t>(interleaved2 >> 16);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			PYGMALION_INLINE static void vector2_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t interleaved1{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) << 16) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 48) };
				std::uint64_t interleaved2{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) << 16) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 48) };
				const __m128i operand1{ _mm_cvtsi64_si128(interleaved1) };
				const __m128i operand2{ _mm_cvtsi64_si128(interleaved2) };
				const __m128i mask{ _mm_shufflelo_epi16(_mm_cmpgt_epi16(operand2, operand1), 0b11110101) };
				const __m128i delta{ _mm_and_si128(_mm_xor_si128(operand1, operand2), mask) };
				const __m128i result1{ _mm_xor_si128(operand1, delta) };
				const __m128i result2{ _mm_xor_si128(operand2, delta) };
				interleaved1 = _mm_cvtsi128_si64(result1);
				interleaved2 = _mm_cvtsi128_si64(result2);
				pValues[IDX1a] = static_cast<std::uint16_t>(interleaved1 & UINT64_C(0xffff));
				pScores[IDX1a] = static_cast<std::int16_t>((interleaved1 >> 16) & UINT64_C(0xffff));
				pValues[IDX2a] = static_cast<std::uint16_t>(interleaved2 & UINT64_C(0xffff));
				pScores[IDX2a] = static_cast<std::int16_t>((interleaved2 >> 16) & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((interleaved1 >> 32) & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>(interleaved1 >> 48);
				pValues[IDX2b] = static_cast<std::uint16_t>((interleaved2 >> 32) & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>(interleaved2 >> 48);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			PYGMALION_INLINE static void vector3_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t interleaved1low{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) << 16) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 48) };
				std::uint64_t interleaved1high{ static_cast<std::uint64_t>(pValues[IDX1c]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 16) };
				std::uint64_t interleaved2low{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) << 16) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 48) };
				std::uint64_t interleaved2high{ static_cast<std::uint64_t>(pValues[IDX2c]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 16) };
				const __m128i operand1{ _mm_set_epi64x(interleaved1high, interleaved1low) };
				const __m128i operand2{ _mm_set_epi64x(interleaved2high, interleaved2low) };
				const __m128i comparision{ _mm_cmpgt_epi16(operand2, operand1) };
				const __m128i mask{ _mm_shufflehi_epi16(_mm_shufflelo_epi16(comparision, 0b11110101), 0b11110101) };
				const __m128i delta{ _mm_and_si128(_mm_xor_si128(operand1, operand2), mask) };
				const __m128i result1{ _mm_xor_si128(operand1, delta) };
				const __m128i result2{ _mm_xor_si128(operand2, delta) };
				interleaved1low = _mm_cvtsi128_si64(result1);
				interleaved1high = _mm_cvtsi128_si64(_mm_shuffle_epi32(result1, 0b00001110));
				interleaved2low = _mm_cvtsi128_si64(result2);
				interleaved2high = _mm_cvtsi128_si64(_mm_shuffle_epi32(result2, 0b00001110));
				pValues[IDX1a] = static_cast<std::uint16_t>(interleaved1low & UINT64_C(0xffff));
				pScores[IDX1a] = static_cast<std::int16_t>((interleaved1low >> 16) & UINT64_C(0xffff));
				pValues[IDX2a] = static_cast<std::uint16_t>(interleaved2low & UINT64_C(0xffff));
				pScores[IDX2a] = static_cast<std::int16_t>((interleaved2low >> 16) & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((interleaved1low >> 32) & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>(interleaved1low >> 48);
				pValues[IDX2b] = static_cast<std::uint16_t>((interleaved2low >> 32) & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>(interleaved2low >> 48);
				pValues[IDX1c] = static_cast<std::uint16_t>(interleaved1high & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>(interleaved1high >> 16);
				pValues[IDX2c] = static_cast<std::uint16_t>(interleaved2high & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>(interleaved2high >> 16);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			PYGMALION_INLINE static void vector4_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{

				std::uint64_t interleaved1low{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) << 16) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 48) };
				std::uint64_t interleaved1high{ static_cast<std::uint64_t>(pValues[IDX1c]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 16) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1d])) << 48) };
				std::uint64_t interleaved2low{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) << 16) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 48) };
				std::uint64_t interleaved2high{ static_cast<std::uint64_t>(pValues[IDX2c]) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 16) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2d])) << 48) };
				const __m128i operand1{ _mm_set_epi64x(interleaved1high, interleaved1low) };
				const __m128i operand2{ _mm_set_epi64x(interleaved2high, interleaved2low) };
				const __m128i comparision{ _mm_cmpgt_epi16(operand2, operand1) };
				const __m128i mask{ _mm_shufflehi_epi16(_mm_shufflelo_epi16(comparision, 0b11110101), 0b11110101) };
				const __m128i delta{ _mm_and_si128(_mm_xor_si128(operand1, operand2), mask) };
				const __m128i result1{ _mm_xor_si128(operand1, delta) };
				const __m128i result2{ _mm_xor_si128(operand2, delta) };
				interleaved1low = _mm_cvtsi128_si64(result1);
				interleaved1high = _mm_cvtsi128_si64(_mm_shuffle_epi32(result1, 0b00001110));
				interleaved2low = _mm_cvtsi128_si64(result2);
				interleaved2high = _mm_cvtsi128_si64(_mm_shuffle_epi32(result2, 0b00001110));
				pValues[IDX1a] = static_cast<std::uint16_t>(interleaved1low & UINT64_C(0xffff));
				pScores[IDX1a] = static_cast<std::int16_t>((interleaved1low >> 16) & UINT64_C(0xffff));
				pValues[IDX2a] = static_cast<std::uint16_t>(interleaved2low & UINT64_C(0xffff));
				pScores[IDX2a] = static_cast<std::int16_t>((interleaved2low >> 16) & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((interleaved1low >> 32) & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>(interleaved1low >> 48);
				pValues[IDX2b] = static_cast<std::uint16_t>((interleaved2low >> 32) & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>(interleaved2low >> 48);
				pValues[IDX1c] = static_cast<std::uint16_t>(interleaved1high & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>((interleaved1high >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>(interleaved2high & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>((interleaved2high >> 16) & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>((interleaved1high >> 32) & UINT64_C(0xffff));
				pScores[IDX1d] = static_cast<std::int16_t>(interleaved1high >> 48);
				pValues[IDX2d] = static_cast<std::uint16_t>((interleaved2high >> 32) & UINT64_C(0xffff));
				pScores[IDX2d] = static_cast<std::int16_t>(interleaved2high >> 48);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			PYGMALION_INLINE static void vector5_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1low{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) };
				std::uint64_t score1high{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) };
				std::uint64_t score2low{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) };
				std::uint64_t score2high{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) };
				std::uint64_t value1low{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) };
				std::uint64_t value1high{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) };
				std::uint64_t value2low{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) };
				std::uint64_t value2high{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) };
				const __m128i score1{ _mm_set_epi64x(score1high, score1low) };
				const __m128i score2{ _mm_set_epi64x(score2high, score2low) };
				const __m128i value1{ _mm_set_epi64x(value1high, value1low) };
				const __m128i value2{ _mm_set_epi64x(value2high, value2low) };
				const __m128i comparision{ _mm_cmpgt_epi16(score2, score1) };
				const __m128i deltaScore{ _mm_and_si128(_mm_xor_si128(score1, score2), comparision) };
				const __m128i resultScore1{ _mm_xor_si128(score1, deltaScore) };
				const __m128i resultScore2{ _mm_xor_si128(score2, deltaScore) };
				const __m128i deltaValue{ _mm_and_si128(_mm_xor_si128(value1, value2), comparision) };
				const __m128i resultValue1{ _mm_xor_si128(value1, deltaValue) };
				const __m128i resultValue2{ _mm_xor_si128(value2, deltaValue) };
				score1low = _mm_cvtsi128_si64(resultScore1);
				score1high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1, 0b00001110));
				score2low = _mm_cvtsi128_si64(resultScore2);
				score2high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2, 0b00001110));
				value1low = _mm_cvtsi128_si64(resultValue1);
				value1high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1, 0b00001110));
				value2low = _mm_cvtsi128_si64(resultValue2);
				value2high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2, 0b00001110));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1low & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1low >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>(value1low >> 32);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1high & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1high >> 16) & UINT64_C(0xffff));
				pValues[IDX2a] = static_cast<std::uint16_t>(value2low & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>(value2low >> 16);
				pValues[IDX2c] = static_cast<std::uint16_t>(value2low >> 32);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2high & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>(value2high >> 16);
				pScores[IDX1a] = static_cast<std::int16_t>(score1low & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1low >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>(score1low >> 32);
				pScores[IDX1e] = static_cast<std::int16_t>(score1high & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>(score1high >> 16);
				pScores[IDX2a] = static_cast<std::int16_t>(score2low & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2low >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>(score2low >> 32);
				pScores[IDX2e] = static_cast<std::int16_t>(score2high & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>(score2high >> 16);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			PYGMALION_INLINE static void vector6_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1low{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) };
				std::uint64_t score1high{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1g])) << 32) };
				std::uint64_t score2low{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) };
				std::uint64_t score2high{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2g])) << 32) };
				std::uint64_t value1low{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) };
				std::uint64_t value1high{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1g]) << 32) };
				std::uint64_t value2low{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) };
				std::uint64_t value2high{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2g]) << 32) };
				const __m128i score1{ _mm_set_epi64x(score1high, score1low) };
				const __m128i score2{ _mm_set_epi64x(score2high, score2low) };
				const __m128i value1{ _mm_set_epi64x(value1high, value1low) };
				const __m128i value2{ _mm_set_epi64x(value2high, value2low) };
				const __m128i comparision{ _mm_cmpgt_epi16(score2, score1) };
				const __m128i deltaScore{ _mm_and_si128(_mm_xor_si128(score1, score2), comparision) };
				const __m128i resultScore1{ _mm_xor_si128(score1, deltaScore) };
				const __m128i resultScore2{ _mm_xor_si128(score2, deltaScore) };
				const __m128i deltaValue{ _mm_and_si128(_mm_xor_si128(value1, value2), comparision) };
				const __m128i resultValue1{ _mm_xor_si128(value1, deltaValue) };
				const __m128i resultValue2{ _mm_xor_si128(value2, deltaValue) };
				score1low = _mm_cvtsi128_si64(resultScore1);
				score1high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1, 0b00001110));
				score2low = _mm_cvtsi128_si64(resultScore2);
				score2high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2, 0b00001110));
				value1low = _mm_cvtsi128_si64(resultValue1);
				value1high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1, 0b00001110));
				value2low = _mm_cvtsi128_si64(resultValue2);
				value2high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2, 0b00001110));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1low & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1low >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>(value1low >> 32);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1high & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1high >> 16) & UINT64_C(0xffff));
				pValues[IDX1g] = static_cast<std::uint16_t>(value1high >> 32);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2low & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>((value2low >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>(value2low >> 32);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2high & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>((value2high >> 16) & UINT64_C(0xffff));
				pValues[IDX2g] = static_cast<std::uint16_t>(value2high >> 32);
				pScores[IDX1a] = static_cast<std::int16_t>(score1low & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1low >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>(score1low >> 32);
				pScores[IDX1e] = static_cast<std::int16_t>(score1high & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>((score1high >> 16) & UINT64_C(0xffff));
				pScores[IDX1g] = static_cast<std::int16_t>(score1high >> 32);
				pScores[IDX2a] = static_cast<std::int16_t>(score2low & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2low >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>(score2low >> 32);
				pScores[IDX2e] = static_cast<std::int16_t>(score2high & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>((score2high >> 16) & UINT64_C(0xffff));
				pScores[IDX2g] = static_cast<std::int16_t>(score2high >> 32);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			PYGMALION_INLINE static void vector7_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1low{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1d])) << 48) };
				std::uint64_t score1high{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1g])) << 32) };
				std::uint64_t score2low{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2d])) << 48) };
				std::uint64_t score2high{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2g])) << 32) };
				std::uint64_t value1low{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 48) };
				std::uint64_t value1high{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1g]) << 32) };
				std::uint64_t value2low{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 48) };
				std::uint64_t value2high{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2g]) << 32) };
				const __m128i score1{ _mm_set_epi64x(score1high, score1low) };
				const __m128i score2{ _mm_set_epi64x(score2high, score2low) };
				const __m128i value1{ _mm_set_epi64x(value1high, value1low) };
				const __m128i value2{ _mm_set_epi64x(value2high, value2low) };
				const __m128i comparision{ _mm_cmpgt_epi16(score2, score1) };
				const __m128i deltaScore{ _mm_and_si128(_mm_xor_si128(score1, score2), comparision) };
				const __m128i resultScore1{ _mm_xor_si128(score1, deltaScore) };
				const __m128i resultScore2{ _mm_xor_si128(score2, deltaScore) };
				const __m128i deltaValue{ _mm_and_si128(_mm_xor_si128(value1, value2), comparision) };
				const __m128i resultValue1{ _mm_xor_si128(value1, deltaValue) };
				const __m128i resultValue2{ _mm_xor_si128(value2, deltaValue) };
				score1low = _mm_cvtsi128_si64(resultScore1);
				score1high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1, 0b00001110));
				score2low = _mm_cvtsi128_si64(resultScore2);
				score2high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2, 0b00001110));
				value1low = _mm_cvtsi128_si64(resultValue1);
				value1high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1, 0b00001110));
				value2low = _mm_cvtsi128_si64(resultValue2);
				value2high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2, 0b00001110));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1low & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1low >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>((value1low >> 32) & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1low >> 48);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1high & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1high >> 16) & UINT64_C(0xffff));
				pValues[IDX1g] = static_cast<std::uint16_t>(value1high >> 32);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2low & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>((value2low >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>((value2low >> 32) & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2low >> 48);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2high & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>((value2high >> 16) & UINT64_C(0xffff));
				pValues[IDX2g] = static_cast<std::uint16_t>(value2high >> 32);
				pScores[IDX1a] = static_cast<std::int16_t>(score1low & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1low >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>((score1low >> 32) & UINT64_C(0xffff));
				pScores[IDX1d] = static_cast<std::int16_t>(score1low >> 48);
				pScores[IDX1e] = static_cast<std::int16_t>(score1high & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>((score1high >> 16) & UINT64_C(0xffff));
				pScores[IDX1g] = static_cast<std::int16_t>(score1high >> 32);
				pScores[IDX2a] = static_cast<std::int16_t>(score2low & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2low >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>((score2low >> 32) & UINT64_C(0xffff));
				pScores[IDX2d] = static_cast<std::int16_t>(score2low >> 48);
				pScores[IDX2e] = static_cast<std::int16_t>(score2high & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>((score2high >> 16) & UINT64_C(0xffff));
				pScores[IDX2g] = static_cast<std::int16_t>(score2high >> 32);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			PYGMALION_INLINE static void vector8_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1low{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1d])) << 48) };
				std::uint64_t score1high{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1h])) << 48) };
				std::uint64_t score2low{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2d])) << 48) };
				std::uint64_t score2high{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2h])) << 48) };
				std::uint64_t value1low{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 48) };
				std::uint64_t value1high{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1h]) << 48) };
				std::uint64_t value2low{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 48) };
				std::uint64_t value2high{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2h]) << 48) };
				const __m128i score1{ _mm_set_epi64x(score1high, score1low) };
				const __m128i score2{ _mm_set_epi64x(score2high, score2low) };
				const __m128i value1{ _mm_set_epi64x(value1high, value1low) };
				const __m128i value2{ _mm_set_epi64x(value2high, value2low) };
				const __m128i comparision{ _mm_cmpgt_epi16(score2, score1) };
				const __m128i deltaScore{ _mm_and_si128(_mm_xor_si128(score1, score2), comparision) };
				const __m128i resultScore1{ _mm_xor_si128(score1, deltaScore) };
				const __m128i resultScore2{ _mm_xor_si128(score2, deltaScore) };
				const __m128i deltaValue{ _mm_and_si128(_mm_xor_si128(value1, value2), comparision) };
				const __m128i resultValue1{ _mm_xor_si128(value1, deltaValue) };
				const __m128i resultValue2{ _mm_xor_si128(value2, deltaValue) };
				score1low = _mm_cvtsi128_si64(resultScore1);
				score1high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1, 0b00001110));
				score2low = _mm_cvtsi128_si64(resultScore2);
				score2high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2, 0b00001110));
				value1low = _mm_cvtsi128_si64(resultValue1);
				value1high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1, 0b00001110));
				value2low = _mm_cvtsi128_si64(resultValue2);
				value2high = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2, 0b00001110));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1low & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1low >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>((value1low >> 32) & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1low >> 48);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1high & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1high >> 16) & UINT64_C(0xffff));
				pValues[IDX1g] = static_cast<std::uint16_t>((value1high >> 32) & UINT64_C(0xffff));
				pValues[IDX1h] = static_cast<std::uint16_t>(value1high >> 48);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2low & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>((value2low >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>((value2low >> 32) & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2low >> 48);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2high & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>((value2high >> 16) & UINT64_C(0xffff));
				pValues[IDX2g] = static_cast<std::uint16_t>((value2high >> 32) & UINT64_C(0xffff));
				pValues[IDX2h] = static_cast<std::uint16_t>(value2high >> 48);
				pScores[IDX1a] = static_cast<std::int16_t>(score1low & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1low >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>((score1low >> 32) & UINT64_C(0xffff));
				pScores[IDX1d] = static_cast<std::int16_t>(score1low >> 48);
				pScores[IDX1e] = static_cast<std::int16_t>(score1high & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>((score1high >> 16) & UINT64_C(0xffff));
				pScores[IDX1g] = static_cast<std::int16_t>((score1high >> 32) & UINT64_C(0xffff));
				pScores[IDX1h] = static_cast<std::int16_t>(score1high >> 48);
				pScores[IDX2a] = static_cast<std::int16_t>(score2low & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2low >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>((score2low >> 32) & UINT64_C(0xffff));
				pScores[IDX2d] = static_cast<std::int16_t>(score2low >> 48);
				pScores[IDX2e] = static_cast<std::int16_t>(score2high & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>((score2high >> 16) & UINT64_C(0xffff));
				pScores[IDX2g] = static_cast<std::int16_t>((score2high >> 32) & UINT64_C(0xffff));
				pScores[IDX2h] = static_cast<std::int16_t>(score2high >> 48);
			}
#endif
#if defined(PYGMALION_CPU_AVX2)
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1i, size_t IDX2i>
			PYGMALION_INLINE static void vector9_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1d])) << 48) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1h])) << 48) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2d])) << 48) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2h])) << 48) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 48) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1h]) << 48) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 48) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2h]) << 48) };
				const __m128i score1low{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score2low{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i value1low{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value2low{ _mm_set_epi64x(value2highA, value2lowA) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1i])) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2i])) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1i]) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2i]) };
				const __m128i score1high{ _mm_set1_epi64x(score1lowB) };
				const __m128i score2high{ _mm_set1_epi64x(score2lowB) };
				const __m128i value1high{ _mm_set1_epi64x(value1lowB) };
				const __m128i value2high{ _mm_set1_epi64x(value2lowB) };
				const __m256i score1{ _mm256_set_m128i(score1high, score1low) };
				const __m256i score2{ _mm256_set_m128i(score2high, score2low) };
				const __m256i value1{ _mm256_set_m128i(value1high, value1low) };
				const __m256i value2{ _mm256_set_m128i(value2high, value2low) };
				const __m256i comparision{ _mm256_cmpgt_epi16(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1low);
				score1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1low, 0b00001110));
				score2lowA = _mm_cvtsi128_si64(resultScore2low);
				score2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2low, 0b00001110));
				value1lowA = _mm_cvtsi128_si64(resultValue1low);
				value1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1low, 0b00001110));
				value2lowA = _mm_cvtsi128_si64(resultValue2low);
				value2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2low, 0b00001110));
				score1lowB = _mm_cvtsi128_si64(resultScore1high);
				score2lowB = _mm_cvtsi128_si64(resultScore2high);
				value1lowB = _mm_cvtsi128_si64(resultValue1high);
				value2lowB = _mm_cvtsi128_si64(resultValue2high);
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>((value1lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1lowA >> 48);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1highA >> 16) & UINT64_C(0xffff));
				pValues[IDX1g] = static_cast<std::uint16_t>((value1highA >> 32) & UINT64_C(0xffff));
				pValues[IDX1h] = static_cast<std::uint16_t>(value1highA >> 48);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>((value2lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>((value2lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2lowA >> 48);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>((value2highA >> 16) & UINT64_C(0xffff));
				pValues[IDX2g] = static_cast<std::uint16_t>((value2highA >> 32) & UINT64_C(0xffff));
				pValues[IDX2h] = static_cast<std::uint16_t>(value2highA >> 48);
				pScores[IDX1a] = static_cast<std::int16_t>(score1lowA & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>((score1lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX1d] = static_cast<std::int16_t>(score1lowA >> 48);
				pScores[IDX1e] = static_cast<std::int16_t>(score1highA & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>((score1highA >> 16) & UINT64_C(0xffff));
				pScores[IDX1g] = static_cast<std::int16_t>((score1highA >> 32) & UINT64_C(0xffff));
				pScores[IDX1h] = static_cast<std::int16_t>(score1highA >> 48);
				pScores[IDX2a] = static_cast<std::int16_t>(score2lowA & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>((score2lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX2d] = static_cast<std::int16_t>(score2lowA >> 48);
				pScores[IDX2e] = static_cast<std::int16_t>(score2highA & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>((score2highA >> 16) & UINT64_C(0xffff));
				pScores[IDX2g] = static_cast<std::int16_t>((score2highA >> 32) & UINT64_C(0xffff));
				pScores[IDX2h] = static_cast<std::int16_t>(score2highA >> 48);
				pValues[IDX1i] = static_cast<std::uint16_t>(value1lowB);
				pValues[IDX2i] = static_cast<std::uint16_t>(value2lowB);
				pScores[IDX1i] = static_cast<std::int16_t>(score1lowB);
				pScores[IDX2i] = static_cast<std::int16_t>(score2lowB);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1i, size_t IDX2i, size_t IDX1j, size_t IDX2j>
			PYGMALION_INLINE static void vector10_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1d])) << 48) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1h])) << 48) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2d])) << 48) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2h])) << 48) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 48) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1h]) << 48) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 48) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2h]) << 48) };
				const __m128i score1low{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score2low{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i value1low{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value2low{ _mm_set_epi64x(value2highA, value2lowA) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1j])) << 16) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2j])) << 16) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1i]) | (static_cast<std::uint64_t>(pValues[IDX1j]) << 16) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2i]) | (static_cast<std::uint64_t>(pValues[IDX2j]) << 16) };
				const __m128i score1high{ _mm_set1_epi64x(score1lowB) };
				const __m128i score2high{ _mm_set1_epi64x(score2lowB) };
				const __m128i value1high{ _mm_set1_epi64x(value1lowB) };
				const __m128i value2high{ _mm_set1_epi64x(value2lowB) };
				const __m256i score1{ _mm256_set_m128i(score1high, score1low) };
				const __m256i score2{ _mm256_set_m128i(score2high, score2low) };
				const __m256i value1{ _mm256_set_m128i(value1high, value1low) };
				const __m256i value2{ _mm256_set_m128i(value2high, value2low) };
				const __m256i comparision{ _mm256_cmpgt_epi16(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1low);
				score1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1low, 0b00001110));
				score2lowA = _mm_cvtsi128_si64(resultScore2low);
				score2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2low, 0b00001110));
				value1lowA = _mm_cvtsi128_si64(resultValue1low);
				value1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1low, 0b00001110));
				value2lowA = _mm_cvtsi128_si64(resultValue2low);
				value2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2low, 0b00001110));
				score1lowB = _mm_cvtsi128_si64(resultScore1high);
				score2lowB = _mm_cvtsi128_si64(resultScore2high);
				value1lowB = _mm_cvtsi128_si64(resultValue1high);
				value2lowB = _mm_cvtsi128_si64(resultValue2high);
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>((value1lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1lowA >> 48);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1highA >> 16) & UINT64_C(0xffff));
				pValues[IDX1g] = static_cast<std::uint16_t>((value1highA >> 32) & UINT64_C(0xffff));
				pValues[IDX1h] = static_cast<std::uint16_t>(value1highA >> 48);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>((value2lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>((value2lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2lowA >> 48);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>((value2highA >> 16) & UINT64_C(0xffff));
				pValues[IDX2g] = static_cast<std::uint16_t>((value2highA >> 32) & UINT64_C(0xffff));
				pValues[IDX2h] = static_cast<std::uint16_t>(value2highA >> 48);
				pScores[IDX1a] = static_cast<std::int16_t>(score1lowA & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>((score1lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX1d] = static_cast<std::int16_t>(score1lowA >> 48);
				pScores[IDX1e] = static_cast<std::int16_t>(score1highA & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>((score1highA >> 16) & UINT64_C(0xffff));
				pScores[IDX1g] = static_cast<std::int16_t>((score1highA >> 32) & UINT64_C(0xffff));
				pScores[IDX1h] = static_cast<std::int16_t>(score1highA >> 48);
				pScores[IDX2a] = static_cast<std::int16_t>(score2lowA & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>((score2lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX2d] = static_cast<std::int16_t>(score2lowA >> 48);
				pScores[IDX2e] = static_cast<std::int16_t>(score2highA & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>((score2highA >> 16) & UINT64_C(0xffff));
				pScores[IDX2g] = static_cast<std::int16_t>((score2highA >> 32) & UINT64_C(0xffff));
				pScores[IDX2h] = static_cast<std::int16_t>(score2highA >> 48);
				pValues[IDX1i] = static_cast<std::uint16_t>(value1lowB & UINT64_C(0xffff));
				pValues[IDX1j] = static_cast<std::uint16_t>(value1lowB >> 16);
				pValues[IDX2i] = static_cast<std::uint16_t>(value2lowB & UINT64_C(0xffff));
				pValues[IDX2j] = static_cast<std::uint16_t>(value2lowB >> 16);
				pScores[IDX1i] = static_cast<std::int16_t>(score1lowB & UINT64_C(0xffff));
				pScores[IDX1j] = static_cast<std::int16_t>(score1lowB >> 16);
				pScores[IDX2i] = static_cast<std::int16_t>(score2lowB & UINT64_C(0xffff));
				pScores[IDX2j] = static_cast<std::int16_t>(score2lowB >> 16);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1i, size_t IDX2i, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k>
			PYGMALION_INLINE static void vector11_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1d])) << 48) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1h])) << 48) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2d])) << 48) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2h])) << 48) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 48) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1h]) << 48) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 48) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2h]) << 48) };
				const __m128i score1low{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score2low{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i value1low{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value2low{ _mm_set_epi64x(value2highA, value2lowA) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1k])) << 32) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2k])) << 32) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1i]) | (static_cast<std::uint64_t>(pValues[IDX1j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1k]) << 32) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2i]) | (static_cast<std::uint64_t>(pValues[IDX2j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2k]) << 32) };
				const __m128i score1high{ _mm_set1_epi64x(score1lowB) };
				const __m128i score2high{ _mm_set1_epi64x(score2lowB) };
				const __m128i value1high{ _mm_set1_epi64x(value1lowB) };
				const __m128i value2high{ _mm_set1_epi64x(value2lowB) };
				const __m256i score1{ _mm256_set_m128i(score1high, score1low) };
				const __m256i score2{ _mm256_set_m128i(score2high, score2low) };
				const __m256i value1{ _mm256_set_m128i(value1high, value1low) };
				const __m256i value2{ _mm256_set_m128i(value2high, value2low) };
				const __m256i comparision{ _mm256_cmpgt_epi16(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1low);
				score1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1low, 0b00001110));
				score2lowA = _mm_cvtsi128_si64(resultScore2low);
				score2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2low, 0b00001110));
				value1lowA = _mm_cvtsi128_si64(resultValue1low);
				value1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1low, 0b00001110));
				value2lowA = _mm_cvtsi128_si64(resultValue2low);
				value2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2low, 0b00001110));
				score1lowB = _mm_cvtsi128_si64(resultScore1high);
				score2lowB = _mm_cvtsi128_si64(resultScore2high);
				value1lowB = _mm_cvtsi128_si64(resultValue1high);
				value2lowB = _mm_cvtsi128_si64(resultValue2high);
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>((value1lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1lowA >> 48);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1highA >> 16) & UINT64_C(0xffff));
				pValues[IDX1g] = static_cast<std::uint16_t>((value1highA >> 32) & UINT64_C(0xffff));
				pValues[IDX1h] = static_cast<std::uint16_t>(value1highA >> 48);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>((value2lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>((value2lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2lowA >> 48);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>((value2highA >> 16) & UINT64_C(0xffff));
				pValues[IDX2g] = static_cast<std::uint16_t>((value2highA >> 32) & UINT64_C(0xffff));
				pValues[IDX2h] = static_cast<std::uint16_t>(value2highA >> 48);
				pScores[IDX1a] = static_cast<std::int16_t>(score1lowA & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>((score1lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX1d] = static_cast<std::int16_t>(score1lowA >> 48);
				pScores[IDX1e] = static_cast<std::int16_t>(score1highA & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>((score1highA >> 16) & UINT64_C(0xffff));
				pScores[IDX1g] = static_cast<std::int16_t>((score1highA >> 32) & UINT64_C(0xffff));
				pScores[IDX1h] = static_cast<std::int16_t>(score1highA >> 48);
				pScores[IDX2a] = static_cast<std::int16_t>(score2lowA & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>((score2lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX2d] = static_cast<std::int16_t>(score2lowA >> 48);
				pScores[IDX2e] = static_cast<std::int16_t>(score2highA & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>((score2highA >> 16) & UINT64_C(0xffff));
				pScores[IDX2g] = static_cast<std::int16_t>((score2highA >> 32) & UINT64_C(0xffff));
				pScores[IDX2h] = static_cast<std::int16_t>(score2highA >> 48);
				pValues[IDX1i] = static_cast<std::uint16_t>(value1lowB & UINT64_C(0xffff));
				pValues[IDX1j] = static_cast<std::uint16_t>((value1lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX1k] = static_cast<std::uint16_t>(value1lowB >> 32);
				pValues[IDX2i] = static_cast<std::uint16_t>(value2lowB & UINT64_C(0xffff));
				pValues[IDX2j] = static_cast<std::uint16_t>((value2lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX2k] = static_cast<std::uint16_t>(value2lowB >> 32);
				pScores[IDX1i] = static_cast<std::int16_t>(score1lowB & UINT64_C(0xffff));
				pScores[IDX1j] = static_cast<std::int16_t>((score1lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX1k] = static_cast<std::int16_t>(score1lowB >> 32);
				pScores[IDX2i] = static_cast<std::int16_t>(score2lowB & UINT64_C(0xffff));
				pScores[IDX2j] = static_cast<std::int16_t>((score2lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX2k] = static_cast<std::int16_t>(score2lowB >> 32);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1i, size_t IDX2i, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l>
			PYGMALION_INLINE static void vector12_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1d])) << 48) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1h])) << 48) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2d])) << 48) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2h])) << 48) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 48) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1h]) << 48) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 48) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2h]) << 48) };
				const __m128i score1low{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score2low{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i value1low{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value2low{ _mm_set_epi64x(value2highA, value2lowA) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1k])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1l])) << 48) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2k])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2l])) << 48) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1i]) | (static_cast<std::uint64_t>(pValues[IDX1j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1k]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1l]) << 48) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2i]) | (static_cast<std::uint64_t>(pValues[IDX2j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2k]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2l]) << 48) };
				const __m128i score1high{ _mm_set1_epi64x(score1lowB) };
				const __m128i score2high{ _mm_set1_epi64x(score2lowB) };
				const __m128i value1high{ _mm_set1_epi64x(value1lowB) };
				const __m128i value2high{ _mm_set1_epi64x(value2lowB) };
				const __m256i score1{ _mm256_set_m128i(score1high, score1low) };
				const __m256i score2{ _mm256_set_m128i(score2high, score2low) };
				const __m256i value1{ _mm256_set_m128i(value1high, value1low) };
				const __m256i value2{ _mm256_set_m128i(value2high, value2low) };
				const __m256i comparision{ _mm256_cmpgt_epi16(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1low);
				score1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1low, 0b00001110));
				score2lowA = _mm_cvtsi128_si64(resultScore2low);
				score2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2low, 0b00001110));
				value1lowA = _mm_cvtsi128_si64(resultValue1low);
				value1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1low, 0b00001110));
				value2lowA = _mm_cvtsi128_si64(resultValue2low);
				value2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2low, 0b00001110));
				score1lowB = _mm_cvtsi128_si64(resultScore1high);
				score2lowB = _mm_cvtsi128_si64(resultScore2high);
				value1lowB = _mm_cvtsi128_si64(resultValue1high);
				value2lowB = _mm_cvtsi128_si64(resultValue2high);
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>((value1lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1lowA >> 48);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1highA >> 16) & UINT64_C(0xffff));
				pValues[IDX1g] = static_cast<std::uint16_t>((value1highA >> 32) & UINT64_C(0xffff));
				pValues[IDX1h] = static_cast<std::uint16_t>(value1highA >> 48);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>((value2lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>((value2lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2lowA >> 48);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>((value2highA >> 16) & UINT64_C(0xffff));
				pValues[IDX2g] = static_cast<std::uint16_t>((value2highA >> 32) & UINT64_C(0xffff));
				pValues[IDX2h] = static_cast<std::uint16_t>(value2highA >> 48);
				pScores[IDX1a] = static_cast<std::int16_t>(score1lowA & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>((score1lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX1d] = static_cast<std::int16_t>(score1lowA >> 48);
				pScores[IDX1e] = static_cast<std::int16_t>(score1highA & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>((score1highA >> 16) & UINT64_C(0xffff));
				pScores[IDX1g] = static_cast<std::int16_t>((score1highA >> 32) & UINT64_C(0xffff));
				pScores[IDX1h] = static_cast<std::int16_t>(score1highA >> 48);
				pScores[IDX2a] = static_cast<std::int16_t>(score2lowA & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>((score2lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX2d] = static_cast<std::int16_t>(score2lowA >> 48);
				pScores[IDX2e] = static_cast<std::int16_t>(score2highA & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>((score2highA >> 16) & UINT64_C(0xffff));
				pScores[IDX2g] = static_cast<std::int16_t>((score2highA >> 32) & UINT64_C(0xffff));
				pScores[IDX2h] = static_cast<std::int16_t>(score2highA >> 48);
				pValues[IDX1i] = static_cast<std::uint16_t>(value1lowB & UINT64_C(0xffff));
				pValues[IDX1j] = static_cast<std::uint16_t>((value1lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX1k] = static_cast<std::uint16_t>((value1lowB >> 32) & UINT64_C(0xffff));
				pValues[IDX1l] = static_cast<std::uint16_t>(value1lowB >> 48);
				pValues[IDX2i] = static_cast<std::uint16_t>(value2lowB & UINT64_C(0xffff));
				pValues[IDX2j] = static_cast<std::uint16_t>((value2lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX2k] = static_cast<std::uint16_t>((value2lowB >> 32) & UINT64_C(0xffff));
				pValues[IDX2l] = static_cast<std::uint16_t>(value2lowB >> 48);
				pScores[IDX1i] = static_cast<std::int16_t>(score1lowB & UINT64_C(0xffff));
				pScores[IDX1j] = static_cast<std::int16_t>((score1lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX1k] = static_cast<std::int16_t>((score1lowB >> 32) & UINT64_C(0xffff));
				pScores[IDX1l] = static_cast<std::int16_t>(score1lowB >> 48);
				pScores[IDX2i] = static_cast<std::int16_t>(score2lowB & UINT64_C(0xffff));
				pScores[IDX2j] = static_cast<std::int16_t>((score2lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX2k] = static_cast<std::int16_t>((score2lowB >> 32) & UINT64_C(0xffff));
				pScores[IDX2l] = static_cast<std::int16_t>(score2lowB >> 48);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1i, size_t IDX2i, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m>
			PYGMALION_INLINE static void vector13_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1d])) << 48) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1h])) << 48) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2d])) << 48) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2h])) << 48) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 48) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1h]) << 48) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 48) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2h]) << 48) };
				const __m128i score1low{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score2low{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i value1low{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value2low{ _mm_set_epi64x(value2highA, value2lowA) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1k])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1l])) << 48) };
				std::uint64_t score1highB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1m])) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2k])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2l])) << 48) };
				std::uint64_t score2highB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2m])) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1i]) | (static_cast<std::uint64_t>(pValues[IDX1j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1k]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1l]) << 48) };
				std::uint64_t value1highB{ static_cast<std::uint64_t>(pValues[IDX1m]) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2i]) | (static_cast<std::uint64_t>(pValues[IDX2j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2k]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2l]) << 48) };
				std::uint64_t value2highB{ static_cast<std::uint64_t>(pValues[IDX2m]) };
				const __m128i score1high{ _mm_set_epi64x(score1highB, score1lowB) };
				const __m128i score2high{ _mm_set_epi64x(score2highB, score2lowB) };
				const __m128i value1high{ _mm_set_epi64x(value1highB, value1lowB) };
				const __m128i value2high{ _mm_set_epi64x(value2highB, value2lowB) };
				const __m256i score1{ _mm256_set_m128i(score1high, score1low) };
				const __m256i score2{ _mm256_set_m128i(score2high, score2low) };
				const __m256i value1{ _mm256_set_m128i(value1high, value1low) };
				const __m256i value2{ _mm256_set_m128i(value2high, value2low) };
				const __m256i comparision{ _mm256_cmpgt_epi16(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1low);
				score1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1low, 0b00001110));
				score2lowA = _mm_cvtsi128_si64(resultScore2low);
				score2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2low, 0b00001110));
				value1lowA = _mm_cvtsi128_si64(resultValue1low);
				value1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1low, 0b00001110));
				value2lowA = _mm_cvtsi128_si64(resultValue2low);
				value2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2low, 0b00001110));
				score1lowB = _mm_cvtsi128_si64(resultScore1high);
				score1highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1high, 0b00001110));
				score2lowB = _mm_cvtsi128_si64(resultScore2high);
				score2highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2high, 0b00001110));
				value1lowB = _mm_cvtsi128_si64(resultValue1high);
				value1highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1high, 0b00001110));
				value2lowB = _mm_cvtsi128_si64(resultValue2high);
				value2highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2high, 0b00001110));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>((value1lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1lowA >> 48);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1highA >> 16) & UINT64_C(0xffff));
				pValues[IDX1g] = static_cast<std::uint16_t>((value1highA >> 32) & UINT64_C(0xffff));
				pValues[IDX1h] = static_cast<std::uint16_t>(value1highA >> 48);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>((value2lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>((value2lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2lowA >> 48);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>((value2highA >> 16) & UINT64_C(0xffff));
				pValues[IDX2g] = static_cast<std::uint16_t>((value2highA >> 32) & UINT64_C(0xffff));
				pValues[IDX2h] = static_cast<std::uint16_t>(value2highA >> 48);
				pScores[IDX1a] = static_cast<std::int16_t>(score1lowA & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>((score1lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX1d] = static_cast<std::int16_t>(score1lowA >> 48);
				pScores[IDX1e] = static_cast<std::int16_t>(score1highA & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>((score1highA >> 16) & UINT64_C(0xffff));
				pScores[IDX1g] = static_cast<std::int16_t>((score1highA >> 32) & UINT64_C(0xffff));
				pScores[IDX1h] = static_cast<std::int16_t>(score1highA >> 48);
				pScores[IDX2a] = static_cast<std::int16_t>(score2lowA & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>((score2lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX2d] = static_cast<std::int16_t>(score2lowA >> 48);
				pScores[IDX2e] = static_cast<std::int16_t>(score2highA & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>((score2highA >> 16) & UINT64_C(0xffff));
				pScores[IDX2g] = static_cast<std::int16_t>((score2highA >> 32) & UINT64_C(0xffff));
				pScores[IDX2h] = static_cast<std::int16_t>(score2highA >> 48);
				pValues[IDX1i] = static_cast<std::uint16_t>(value1lowB & UINT64_C(0xffff));
				pValues[IDX1j] = static_cast<std::uint16_t>((value1lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX1k] = static_cast<std::uint16_t>((value1lowB >> 32) & UINT64_C(0xffff));
				pValues[IDX1l] = static_cast<std::uint16_t>(value1lowB >> 48);
				pValues[IDX1m] = static_cast<std::uint16_t>(value1highB);
				pValues[IDX2i] = static_cast<std::uint16_t>(value2lowB & UINT64_C(0xffff));
				pValues[IDX2j] = static_cast<std::uint16_t>((value2lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX2k] = static_cast<std::uint16_t>((value2lowB >> 32) & UINT64_C(0xffff));
				pValues[IDX2l] = static_cast<std::uint16_t>(value2lowB >> 48);
				pValues[IDX2m] = static_cast<std::uint16_t>(value2highB);
				pScores[IDX1i] = static_cast<std::int16_t>(score1lowB & UINT64_C(0xffff));
				pScores[IDX1j] = static_cast<std::int16_t>((score1lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX1k] = static_cast<std::int16_t>((score1lowB >> 32) & UINT64_C(0xffff));
				pScores[IDX1l] = static_cast<std::int16_t>(score1lowB >> 48);
				pScores[IDX1m] = static_cast<std::int16_t>(score1highB);
				pScores[IDX2i] = static_cast<std::int16_t>(score2lowB & UINT64_C(0xffff));
				pScores[IDX2j] = static_cast<std::int16_t>((score2lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX2k] = static_cast<std::int16_t>((score2lowB >> 32) & UINT64_C(0xffff));
				pScores[IDX2l] = static_cast<std::int16_t>(score2lowB >> 48);
				pScores[IDX2m] = static_cast<std::int16_t>(score2highB);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1i, size_t IDX2i, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n>
			PYGMALION_INLINE static void vector14_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1d])) << 48) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1h])) << 48) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2d])) << 48) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2h])) << 48) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 48) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1h]) << 48) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 48) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2h]) << 48) };
				const __m128i score1low{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score2low{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i value1low{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value2low{ _mm_set_epi64x(value2highA, value2lowA) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1k])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1l])) << 48) };
				std::uint64_t score1highB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1m])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1n])) << 16) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2k])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2l])) << 48) };
				std::uint64_t score2highB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2m])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2n])) << 16) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1i]) | (static_cast<std::uint64_t>(pValues[IDX1j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1k]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1l]) << 48) };
				std::uint64_t value1highB{ static_cast<std::uint64_t>(pValues[IDX1m]) | (static_cast<std::uint64_t>(pValues[IDX1n]) << 16) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2i]) | (static_cast<std::uint64_t>(pValues[IDX2j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2k]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2l]) << 48) };
				std::uint64_t value2highB{ static_cast<std::uint64_t>(pValues[IDX2m]) | (static_cast<std::uint64_t>(pValues[IDX2n]) << 16) };
				const __m128i score1high{ _mm_set_epi64x(score1highB, score1lowB) };
				const __m128i score2high{ _mm_set_epi64x(score2highB, score2lowB) };
				const __m128i value1high{ _mm_set_epi64x(value1highB, value1lowB) };
				const __m128i value2high{ _mm_set_epi64x(value2highB, value2lowB) };
				const __m256i score1{ _mm256_set_m128i(score1high, score1low) };
				const __m256i score2{ _mm256_set_m128i(score2high, score2low) };
				const __m256i value1{ _mm256_set_m128i(value1high, value1low) };
				const __m256i value2{ _mm256_set_m128i(value2high, value2low) };
				const __m256i comparision{ _mm256_cmpgt_epi16(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1low);
				score1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1low, 0b00001110));
				score2lowA = _mm_cvtsi128_si64(resultScore2low);
				score2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2low, 0b00001110));
				value1lowA = _mm_cvtsi128_si64(resultValue1low);
				value1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1low, 0b00001110));
				value2lowA = _mm_cvtsi128_si64(resultValue2low);
				value2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2low, 0b00001110));
				score1lowB = _mm_cvtsi128_si64(resultScore1high);
				score1highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1high, 0b00001110));
				score2lowB = _mm_cvtsi128_si64(resultScore2high);
				score2highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2high, 0b00001110));
				value1lowB = _mm_cvtsi128_si64(resultValue1high);
				value1highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1high, 0b00001110));
				value2lowB = _mm_cvtsi128_si64(resultValue2high);
				value2highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2high, 0b00001110));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>((value1lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1lowA >> 48);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1highA >> 16) & UINT64_C(0xffff));
				pValues[IDX1g] = static_cast<std::uint16_t>((value1highA >> 32) & UINT64_C(0xffff));
				pValues[IDX1h] = static_cast<std::uint16_t>(value1highA >> 48);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>((value2lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>((value2lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2lowA >> 48);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>((value2highA >> 16) & UINT64_C(0xffff));
				pValues[IDX2g] = static_cast<std::uint16_t>((value2highA >> 32) & UINT64_C(0xffff));
				pValues[IDX2h] = static_cast<std::uint16_t>(value2highA >> 48);
				pScores[IDX1a] = static_cast<std::int16_t>(score1lowA & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>((score1lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX1d] = static_cast<std::int16_t>(score1lowA >> 48);
				pScores[IDX1e] = static_cast<std::int16_t>(score1highA & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>((score1highA >> 16) & UINT64_C(0xffff));
				pScores[IDX1g] = static_cast<std::int16_t>((score1highA >> 32) & UINT64_C(0xffff));
				pScores[IDX1h] = static_cast<std::int16_t>(score1highA >> 48);
				pScores[IDX2a] = static_cast<std::int16_t>(score2lowA & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>((score2lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX2d] = static_cast<std::int16_t>(score2lowA >> 48);
				pScores[IDX2e] = static_cast<std::int16_t>(score2highA & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>((score2highA >> 16) & UINT64_C(0xffff));
				pScores[IDX2g] = static_cast<std::int16_t>((score2highA >> 32) & UINT64_C(0xffff));
				pScores[IDX2h] = static_cast<std::int16_t>(score2highA >> 48);
				pValues[IDX1i] = static_cast<std::uint16_t>(value1lowB & UINT64_C(0xffff));
				pValues[IDX1j] = static_cast<std::uint16_t>((value1lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX1k] = static_cast<std::uint16_t>((value1lowB >> 32) & UINT64_C(0xffff));
				pValues[IDX1l] = static_cast<std::uint16_t>(value1lowB >> 48);
				pValues[IDX1m] = static_cast<std::uint16_t>(value1highB & UINT64_C(0xffff));
				pValues[IDX1n] = static_cast<std::uint16_t>(value1highB >> 16);
				pValues[IDX2i] = static_cast<std::uint16_t>(value2lowB & UINT64_C(0xffff));
				pValues[IDX2j] = static_cast<std::uint16_t>((value2lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX2k] = static_cast<std::uint16_t>((value2lowB >> 32) & UINT64_C(0xffff));
				pValues[IDX2l] = static_cast<std::uint16_t>(value2lowB >> 48);
				pValues[IDX2m] = static_cast<std::uint16_t>(value2highB & UINT64_C(0xffff));
				pValues[IDX2n] = static_cast<std::uint16_t>(value2highB >> 16);
				pScores[IDX1i] = static_cast<std::int16_t>(score1lowB & UINT64_C(0xffff));
				pScores[IDX1j] = static_cast<std::int16_t>((score1lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX1k] = static_cast<std::int16_t>((score1lowB >> 32) & UINT64_C(0xffff));
				pScores[IDX1l] = static_cast<std::int16_t>(score1lowB >> 48);
				pScores[IDX1m] = static_cast<std::int16_t>(score1highB & UINT64_C(0xffff));
				pScores[IDX1n] = static_cast<std::int16_t>(score1highB >> 16);
				pScores[IDX2i] = static_cast<std::int16_t>(score2lowB & UINT64_C(0xffff));
				pScores[IDX2j] = static_cast<std::int16_t>((score2lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX2k] = static_cast<std::int16_t>((score2lowB >> 32) & UINT64_C(0xffff));
				pScores[IDX2l] = static_cast<std::int16_t>(score2lowB >> 48);
				pScores[IDX2m] = static_cast<std::int16_t>(score2highB & UINT64_C(0xffff));
				pScores[IDX2n] = static_cast<std::int16_t>(score2highB >> 16);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1i, size_t IDX2i, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o>
			PYGMALION_INLINE static void vector15_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1d])) << 48) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1h])) << 48) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2d])) << 48) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2h])) << 48) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 48) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1h]) << 48) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 48) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2h]) << 48) };
				const __m128i score1low{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score2low{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i value1low{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value2low{ _mm_set_epi64x(value2highA, value2lowA) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1k])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1l])) << 48) };
				std::uint64_t score1highB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1m])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1n])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1o])) << 32) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2k])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2l])) << 48) };
				std::uint64_t score2highB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2m])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2n])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2o])) << 32) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1i]) | (static_cast<std::uint64_t>(pValues[IDX1j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1k]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1l]) << 48) };
				std::uint64_t value1highB{ static_cast<std::uint64_t>(pValues[IDX1m]) | (static_cast<std::uint64_t>(pValues[IDX1n]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1o]) << 32) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2i]) | (static_cast<std::uint64_t>(pValues[IDX2j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2k]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2l]) << 48) };
				std::uint64_t value2highB{ static_cast<std::uint64_t>(pValues[IDX2m]) | (static_cast<std::uint64_t>(pValues[IDX2n]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2o]) << 32) };
				const __m128i score1high{ _mm_set_epi64x(score1highB, score1lowB) };
				const __m128i score2high{ _mm_set_epi64x(score2highB, score2lowB) };
				const __m128i value1high{ _mm_set_epi64x(value1highB, value1lowB) };
				const __m128i value2high{ _mm_set_epi64x(value2highB, value2lowB) };
				const __m256i score1{ _mm256_set_m128i(score1high, score1low) };
				const __m256i score2{ _mm256_set_m128i(score2high, score2low) };
				const __m256i value1{ _mm256_set_m128i(value1high, value1low) };
				const __m256i value2{ _mm256_set_m128i(value2high, value2low) };
				const __m256i comparision{ _mm256_cmpgt_epi16(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1low);
				score1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1low, 0b00001110));
				score2lowA = _mm_cvtsi128_si64(resultScore2low);
				score2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2low, 0b00001110));
				value1lowA = _mm_cvtsi128_si64(resultValue1low);
				value1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1low, 0b00001110));
				value2lowA = _mm_cvtsi128_si64(resultValue2low);
				value2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2low, 0b00001110));
				score1lowB = _mm_cvtsi128_si64(resultScore1high);
				score1highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1high, 0b00001110));
				score2lowB = _mm_cvtsi128_si64(resultScore2high);
				score2highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2high, 0b00001110));
				value1lowB = _mm_cvtsi128_si64(resultValue1high);
				value1highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1high, 0b00001110));
				value2lowB = _mm_cvtsi128_si64(resultValue2high);
				value2highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2high, 0b00001110));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>((value1lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1lowA >> 48);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1highA >> 16) & UINT64_C(0xffff));
				pValues[IDX1g] = static_cast<std::uint16_t>((value1highA >> 32) & UINT64_C(0xffff));
				pValues[IDX1h] = static_cast<std::uint16_t>(value1highA >> 48);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>((value2lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>((value2lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2lowA >> 48);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>((value2highA >> 16) & UINT64_C(0xffff));
				pValues[IDX2g] = static_cast<std::uint16_t>((value2highA >> 32) & UINT64_C(0xffff));
				pValues[IDX2h] = static_cast<std::uint16_t>(value2highA >> 48);
				pScores[IDX1a] = static_cast<std::int16_t>(score1lowA & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>((score1lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX1d] = static_cast<std::int16_t>(score1lowA >> 48);
				pScores[IDX1e] = static_cast<std::int16_t>(score1highA & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>((score1highA >> 16) & UINT64_C(0xffff));
				pScores[IDX1g] = static_cast<std::int16_t>((score1highA >> 32) & UINT64_C(0xffff));
				pScores[IDX1h] = static_cast<std::int16_t>(score1highA >> 48);
				pScores[IDX2a] = static_cast<std::int16_t>(score2lowA & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>((score2lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX2d] = static_cast<std::int16_t>(score2lowA >> 48);
				pScores[IDX2e] = static_cast<std::int16_t>(score2highA & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>((score2highA >> 16) & UINT64_C(0xffff));
				pScores[IDX2g] = static_cast<std::int16_t>((score2highA >> 32) & UINT64_C(0xffff));
				pScores[IDX2h] = static_cast<std::int16_t>(score2highA >> 48);
				pValues[IDX1i] = static_cast<std::uint16_t>(value1lowB & UINT64_C(0xffff));
				pValues[IDX1j] = static_cast<std::uint16_t>((value1lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX1k] = static_cast<std::uint16_t>((value1lowB >> 32) & UINT64_C(0xffff));
				pValues[IDX1l] = static_cast<std::uint16_t>(value1lowB >> 48);
				pValues[IDX1m] = static_cast<std::uint16_t>(value1highB & UINT64_C(0xffff));
				pValues[IDX1n] = static_cast<std::uint16_t>((value1highB >> 16) & UINT64_C(0xffff));
				pValues[IDX1o] = static_cast<std::uint16_t>(value1highB >> 32);
				pValues[IDX2i] = static_cast<std::uint16_t>(value2lowB & UINT64_C(0xffff));
				pValues[IDX2j] = static_cast<std::uint16_t>((value2lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX2k] = static_cast<std::uint16_t>((value2lowB >> 32) & UINT64_C(0xffff));
				pValues[IDX2l] = static_cast<std::uint16_t>(value2lowB >> 48);
				pValues[IDX2m] = static_cast<std::uint16_t>(value2highB & UINT64_C(0xffff));
				pValues[IDX2n] = static_cast<std::uint16_t>((value2highB >> 16) & UINT64_C(0xffff));
				pValues[IDX2o] = static_cast<std::uint16_t>(value2highB >> 32);
				pScores[IDX1i] = static_cast<std::int16_t>(score1lowB & UINT64_C(0xffff));
				pScores[IDX1j] = static_cast<std::int16_t>((score1lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX1k] = static_cast<std::int16_t>((score1lowB >> 32) & UINT64_C(0xffff));
				pScores[IDX1l] = static_cast<std::int16_t>(score1lowB >> 48);
				pScores[IDX1m] = static_cast<std::int16_t>(score1highB & UINT64_C(0xffff));
				pScores[IDX1n] = static_cast<std::int16_t>((score1highB >> 16) & UINT64_C(0xffff));
				pScores[IDX1o] = static_cast<std::int16_t>(score1highB >> 32);
				pScores[IDX2i] = static_cast<std::int16_t>(score2lowB & UINT64_C(0xffff));
				pScores[IDX2j] = static_cast<std::int16_t>((score2lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX2k] = static_cast<std::int16_t>((score2lowB >> 32) & UINT64_C(0xffff));
				pScores[IDX2l] = static_cast<std::int16_t>(score2lowB >> 48);
				pScores[IDX2m] = static_cast<std::int16_t>(score2highB & UINT64_C(0xffff));
				pScores[IDX2n] = static_cast<std::int16_t>((score2highB >> 16) & UINT64_C(0xffff));
				pScores[IDX2o] = static_cast<std::int16_t>(score2highB >> 32);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1i, size_t IDX2i, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p>
			PYGMALION_INLINE static void vector16_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1d])) << 48) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1h])) << 48) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2b])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2c])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2d])) << 48) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2f])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2g])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2h])) << 48) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 48) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1h]) << 48) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2c]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 48) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2g]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2h]) << 48) };
				const __m128i score1low{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score2low{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i value1low{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value2low{ _mm_set_epi64x(value2highA, value2lowA) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1k])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1l])) << 48) };
				std::uint64_t score1highB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1m])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1n])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1o])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX1p])) << 48) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2i])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2j])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2k])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2l])) << 48) };
				std::uint64_t score2highB{ static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2m])) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2n])) << 16) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2o])) << 32) | (static_cast<std::uint64_t>(static_cast<std::uint16_t>(pScores[IDX2p])) << 48) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1i]) | (static_cast<std::uint64_t>(pValues[IDX1j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1k]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1l]) << 48) };
				std::uint64_t value1highB{ static_cast<std::uint64_t>(pValues[IDX1m]) | (static_cast<std::uint64_t>(pValues[IDX1n]) << 16) | (static_cast<std::uint64_t>(pValues[IDX1o]) << 32) | (static_cast<std::uint64_t>(pValues[IDX1p]) << 48) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2i]) | (static_cast<std::uint64_t>(pValues[IDX2j]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2k]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2l]) << 48) };
				std::uint64_t value2highB{ static_cast<std::uint64_t>(pValues[IDX2m]) | (static_cast<std::uint64_t>(pValues[IDX2n]) << 16) | (static_cast<std::uint64_t>(pValues[IDX2o]) << 32) | (static_cast<std::uint64_t>(pValues[IDX2p]) << 48) };
				const __m128i score1high{ _mm_set_epi64x(score1highB, score1lowB) };
				const __m128i score2high{ _mm_set_epi64x(score2highB, score2lowB) };
				const __m128i value1high{ _mm_set_epi64x(value1highB, value1lowB) };
				const __m128i value2high{ _mm_set_epi64x(value2highB, value2lowB) };
				const __m256i score1{ _mm256_set_m128i(score1high, score1low) };
				const __m256i score2{ _mm256_set_m128i(score2high, score2low) };
				const __m256i value1{ _mm256_set_m128i(value1high, value1low) };
				const __m256i value2{ _mm256_set_m128i(value2high, value2low) };
				const __m256i comparision{ _mm256_cmpgt_epi16(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1low{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1high{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2low{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2high{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1low{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1high{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2low{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2high{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1low);
				score1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1low, 0b00001110));
				score2lowA = _mm_cvtsi128_si64(resultScore2low);
				score2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2low, 0b00001110));
				value1lowA = _mm_cvtsi128_si64(resultValue1low);
				value1highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1low, 0b00001110));
				value2lowA = _mm_cvtsi128_si64(resultValue2low);
				value2highA = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2low, 0b00001110));
				score1lowB = _mm_cvtsi128_si64(resultScore1high);
				score1highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore1high, 0b00001110));
				score2lowB = _mm_cvtsi128_si64(resultScore2high);
				score2highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultScore2high, 0b00001110));
				value1lowB = _mm_cvtsi128_si64(resultValue1high);
				value1highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue1high, 0b00001110));
				value2lowB = _mm_cvtsi128_si64(resultValue2high);
				value2highB = _mm_cvtsi128_si64(_mm_shuffle_epi32(resultValue2high, 0b00001110));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>((value1lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX1c] = static_cast<std::uint16_t>((value1lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1lowA >> 48);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>((value1highA >> 16) & UINT64_C(0xffff));
				pValues[IDX1g] = static_cast<std::uint16_t>((value1highA >> 32) & UINT64_C(0xffff));
				pValues[IDX1h] = static_cast<std::uint16_t>(value1highA >> 48);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>((value2lowA >> 16) & UINT64_C(0xffff));
				pValues[IDX2c] = static_cast<std::uint16_t>((value2lowA >> 32) & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2lowA >> 48);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>((value2highA >> 16) & UINT64_C(0xffff));
				pValues[IDX2g] = static_cast<std::uint16_t>((value2highA >> 32) & UINT64_C(0xffff));
				pValues[IDX2h] = static_cast<std::uint16_t>(value2highA >> 48);
				pScores[IDX1a] = static_cast<std::int16_t>(score1lowA & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int16_t>((score1lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX1c] = static_cast<std::int16_t>((score1lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX1d] = static_cast<std::int16_t>(score1lowA >> 48);
				pScores[IDX1e] = static_cast<std::int16_t>(score1highA & UINT64_C(0xffff));
				pScores[IDX1f] = static_cast<std::int16_t>((score1highA >> 16) & UINT64_C(0xffff));
				pScores[IDX1g] = static_cast<std::int16_t>((score1highA >> 32) & UINT64_C(0xffff));
				pScores[IDX1h] = static_cast<std::int16_t>(score1highA >> 48);
				pScores[IDX2a] = static_cast<std::int16_t>(score2lowA & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int16_t>((score2lowA >> 16) & UINT64_C(0xffff));
				pScores[IDX2c] = static_cast<std::int16_t>((score2lowA >> 32) & UINT64_C(0xffff));
				pScores[IDX2d] = static_cast<std::int16_t>(score2lowA >> 48);
				pScores[IDX2e] = static_cast<std::int16_t>(score2highA & UINT64_C(0xffff));
				pScores[IDX2f] = static_cast<std::int16_t>((score2highA >> 16) & UINT64_C(0xffff));
				pScores[IDX2g] = static_cast<std::int16_t>((score2highA >> 32) & UINT64_C(0xffff));
				pScores[IDX2h] = static_cast<std::int16_t>(score2highA >> 48);
				pValues[IDX1i] = static_cast<std::uint16_t>(value1lowB & UINT64_C(0xffff));
				pValues[IDX1j] = static_cast<std::uint16_t>((value1lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX1k] = static_cast<std::uint16_t>((value1lowB >> 32) & UINT64_C(0xffff));
				pValues[IDX1l] = static_cast<std::uint16_t>(value1lowB >> 48);
				pValues[IDX1m] = static_cast<std::uint16_t>(value1highB & UINT64_C(0xffff));
				pValues[IDX1n] = static_cast<std::uint16_t>((value1highB >> 16) & UINT64_C(0xffff));
				pValues[IDX1o] = static_cast<std::uint16_t>((value1highB >> 32) & UINT64_C(0xffff));
				pValues[IDX1p] = static_cast<std::uint16_t>(value1highB >> 48);
				pValues[IDX2i] = static_cast<std::uint16_t>(value2lowB & UINT64_C(0xffff));
				pValues[IDX2j] = static_cast<std::uint16_t>((value2lowB >> 16) & UINT64_C(0xffff));
				pValues[IDX2k] = static_cast<std::uint16_t>((value2lowB >> 32) & UINT64_C(0xffff));
				pValues[IDX2l] = static_cast<std::uint16_t>(value2lowB >> 48);
				pValues[IDX2m] = static_cast<std::uint16_t>(value2highB & UINT64_C(0xffff));
				pValues[IDX2n] = static_cast<std::uint16_t>((value2highB >> 16) & UINT64_C(0xffff));
				pValues[IDX2o] = static_cast<std::uint16_t>((value2highB >> 32) & UINT64_C(0xffff));
				pValues[IDX2p] = static_cast<std::uint16_t>(value2highB >> 48);
				pScores[IDX1i] = static_cast<std::int16_t>(score1lowB & UINT64_C(0xffff));
				pScores[IDX1j] = static_cast<std::int16_t>((score1lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX1k] = static_cast<std::int16_t>((score1lowB >> 32) & UINT64_C(0xffff));
				pScores[IDX1l] = static_cast<std::int16_t>(score1lowB >> 48);
				pScores[IDX1m] = static_cast<std::int16_t>(score1highB & UINT64_C(0xffff));
				pScores[IDX1n] = static_cast<std::int16_t>((score1highB >> 16) & UINT64_C(0xffff));
				pScores[IDX1o] = static_cast<std::int16_t>((score1highB >> 32) & UINT64_C(0xffff));
				pScores[IDX1p] = static_cast<std::int16_t>(score1highB >> 48);
				pScores[IDX2i] = static_cast<std::int16_t>(score2lowB & UINT64_C(0xffff));
				pScores[IDX2j] = static_cast<std::int16_t>((score2lowB >> 16) & UINT64_C(0xffff));
				pScores[IDX2k] = static_cast<std::int16_t>((score2lowB >> 32) & UINT64_C(0xffff));
				pScores[IDX2l] = static_cast<std::int16_t>(score2lowB >> 48);
				pScores[IDX2m] = static_cast<std::int16_t>(score2highB & UINT64_C(0xffff));
				pScores[IDX2n] = static_cast<std::int16_t>((score2highB >> 16) & UINT64_C(0xffff));
				pScores[IDX2o] = static_cast<std::int16_t>((score2highB >> 32) & UINT64_C(0xffff));
				pScores[IDX2p] = static_cast<std::int16_t>(score2highB >> 48);
			}
#endif
		public:
			template<size_t IDX1, size_t IDX2>
			PYGMALION_INLINE static void scalar(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					scalar_SSE2<IDX1, IDX2>(pValues, pScores);
				else
#endif
					scalar_Vanilla<IDX1, IDX2>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			PYGMALION_INLINE static void vector2(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector2_SSE2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				else
#endif
					vector2_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			PYGMALION_INLINE static void vector3(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector3_SSE2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
				else
#endif
					vector3_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			PYGMALION_INLINE static void vector4(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector4_SSE2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				else
#endif
					vector4_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			PYGMALION_INLINE static void vector5(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector5_SSE2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
				else
#endif
					vector5_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			PYGMALION_INLINE static void vector6(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector6_SSE2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
				else
#endif
					vector6_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			PYGMALION_INLINE static void vector7(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector7_SSE2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
				else
#endif
					vector7_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			PYGMALION_INLINE static void vector8(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector8_SSE2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				else
#endif
					vector8_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j>
			PYGMALION_INLINE static void vector9(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector9_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j>(pValues, pScores);
								else
				#endif*/
				vector9_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k>
			PYGMALION_INLINE static void vector10(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector10_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k>(pValues, pScores);
								else
				#endif*/
				vector10_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l>
			PYGMALION_INLINE static void vector11(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector11_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l>(pValues, pScores);
								else
				#endif*/
				vector11_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m>
			PYGMALION_INLINE static void vector12(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector12_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m>(pValues, pScores);
								else
				#endif*/
				vector12_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n>
			PYGMALION_INLINE static void vector13(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector13_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n>(pValues, pScores);
								else
				#endif*/
				vector13_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o>
			PYGMALION_INLINE static void vector14(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector14_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o>(pValues, pScores);
								else
				#endif*/
				vector14_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p>
			PYGMALION_INLINE static void vector15(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector15_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p>(pValues, pScores);
								else
				#endif*/
				vector15_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p, size_t IDX1q, size_t IDX2q>
			PYGMALION_INLINE static void vector16(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector16_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p, IDX1q, IDX2q>(pValues, pScores);
								else
				#endif*/
				vector16_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p, IDX1q, IDX2q>(pValues, pScores);
			}
		};

		template<>
		class compare<std::uint16_t, std::int32_t>
		{
		public:
			using VALUE = std::uint16_t;
			using SCORE = std::int32_t;
		private:
			template<size_t IDX1, size_t IDX2>
			PYGMALION_INLINE static void scalar_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				const std::int64_t comparision{ static_cast<std::int64_t>(pScores[IDX1] < pScores[IDX2]) };
				const std::uint64_t negated{ static_cast<std::uint64_t>(-comparision) };
				const std::uint16_t maskValue{ static_cast<std::uint16_t>(negated & UINT64_C(0xffff)) };
				const std::uint32_t maskScore{ static_cast<std::uint32_t>(negated & UINT64_C(0xffffffff)) };
				const std::uint32_t deltaScores{ static_cast<std::uint32_t>((reinterpret_cast<std::uint32_t*>(pScores)[IDX1] ^ reinterpret_cast<std::uint32_t*>(pScores)[IDX2]) & maskScore) };
				const std::uint16_t deltaValues{ static_cast<std::uint16_t>((pValues[IDX1] ^ pValues[IDX2]) & maskValue) };
				pValues[IDX1] ^= deltaValues;
				pValues[IDX2] ^= deltaValues;
				reinterpret_cast<std::uint32_t*>(pScores)[IDX1] ^= deltaScores;
				reinterpret_cast<std::uint32_t*>(pScores)[IDX2] ^= deltaScores;
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			PYGMALION_INLINE static void vector2_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar<IDX1a, IDX2a>(pValues, pScores);
				scalar<IDX1b, IDX2b>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			PYGMALION_INLINE static void vector3_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				scalar<IDX1c, IDX2c>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			PYGMALION_INLINE static void vector4_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				vector2<IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			PYGMALION_INLINE static void vector5_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector3<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
				vector2<IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			PYGMALION_INLINE static void vector6_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector3<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
				vector3<IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			PYGMALION_INLINE static void vector7_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector3<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			PYGMALION_INLINE static void vector8_Vanilla(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				vector4<IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
			}
#if defined(PYGMALION_CPU_SSE2)
			template<size_t IDX1, size_t IDX2>
			PYGMALION_INLINE static void scalar_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t interleaved1{ static_cast<std::uint64_t>(pValues[IDX1]) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1])) << 32) };
				std::uint64_t interleaved2{ static_cast<std::uint64_t>(pValues[IDX2]) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2])) << 32) };
				const __m128i operand1{ _mm_cvtsi64_si128(interleaved1) };
				const __m128i operand2{ _mm_cvtsi64_si128(interleaved2) };
				const __m128i mask{ _mm_shuffle_epi32(_mm_cmpgt_epi32(operand2, operand1), 0b00000101) };
				const __m128i delta{ _mm_and_si128(_mm_xor_si128(operand1, operand2), mask) };
				const __m128i result1{ _mm_xor_si128(operand1, delta) };
				const __m128i result2{ _mm_xor_si128(operand2, delta) };
				interleaved1 = _mm_cvtsi128_si64(result1);
				interleaved2 = _mm_cvtsi128_si64(result2);
				pValues[IDX1] = static_cast<std::uint16_t>(interleaved1 & UINT64_C(0xffff));
				pScores[IDX1] = static_cast<std::int32_t>(interleaved1 >> 32);
				pValues[IDX2] = static_cast<std::uint16_t>(interleaved2 & UINT64_C(0xffff));
				pScores[IDX2] = static_cast<std::int32_t>(interleaved2 >> 32);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			PYGMALION_INLINE static void vector2_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t interleaved1low{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1a])) << 32) };
				std::uint64_t interleaved1high{ static_cast<std::uint64_t>(pValues[IDX1b]) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1b])) << 32) };
				std::uint64_t interleaved2low{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2a])) << 32) };
				std::uint64_t interleaved2high{ static_cast<std::uint64_t>(pValues[IDX2b]) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2b])) << 32) };
				const __m128i operand1{ _mm_set_epi64x(interleaved1high,interleaved1low) };
				const __m128i operand2{ _mm_set_epi64x(interleaved2high,interleaved2low) };
				const __m128i mask{ _mm_shuffle_epi32(_mm_cmpgt_epi32(operand2, operand1), 0b11110101) };
				const __m128i delta{ _mm_and_si128(_mm_xor_si128(operand1, operand2), mask) };
				const __m128i result1{ _mm_xor_si128(operand1, delta) };
				const __m128i result2{ _mm_xor_si128(operand2, delta) };
				interleaved1low = _mm_cvtsi128_si64(result1);
				interleaved1high = _mm_cvtsi128_si64(_mm_srli_si128(result1, 8));
				interleaved2low = _mm_cvtsi128_si64(result2);
				interleaved2high = _mm_cvtsi128_si64(_mm_srli_si128(result2, 8));
				pValues[IDX1a] = static_cast<std::uint16_t>(interleaved1low & UINT64_C(0xffff));
				pScores[IDX1a] = static_cast<std::int32_t>(interleaved1low >> 32);
				pValues[IDX2a] = static_cast<std::uint16_t>(interleaved2low & UINT64_C(0xffff));
				pScores[IDX2a] = static_cast<std::int32_t>(interleaved2low >> 32);
				pValues[IDX1b] = static_cast<std::uint16_t>(interleaved1high & UINT64_C(0xffff));
				pScores[IDX1b] = static_cast<std::int32_t>(interleaved1high >> 32);
				pValues[IDX2b] = static_cast<std::uint16_t>(interleaved2high & UINT64_C(0xffff));
				pScores[IDX2b] = static_cast<std::int32_t>(interleaved2high >> 32);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			PYGMALION_INLINE static void vector3_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1low{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1b])) << 32) };
				std::uint64_t score1high{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1c])) };
				std::uint64_t score2low{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2b])) << 32) };
				std::uint64_t score2high{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2c])) };
				std::uint64_t value1low{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 32) };
				std::uint64_t value1high{ static_cast<std::uint64_t>(pValues[IDX1c]) };
				std::uint64_t value2low{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 32) };
				std::uint64_t value2high{ static_cast<std::uint64_t>(pValues[IDX2c]) };
				const __m128i score1{ _mm_set_epi64x(score1high, score1low) };
				const __m128i score2{ _mm_set_epi64x(score2high, score2low) };
				const __m128i value1{ _mm_set_epi64x(value1high, value1low) };
				const __m128i value2{ _mm_set_epi64x(value2high, value2low) };
				const __m128i comparision{ _mm_cmpgt_epi32(score2, score1) };
				const __m128i deltaScore{ _mm_and_si128(_mm_xor_si128(score1, score2), comparision) };
				const __m128i resultScore1{ _mm_xor_si128(score1, deltaScore) };
				const __m128i resultScore2{ _mm_xor_si128(score2, deltaScore) };
				const __m128i deltaValue{ _mm_and_si128(_mm_xor_si128(value1, value2), comparision) };
				const __m128i resultValue1{ _mm_xor_si128(value1, deltaValue) };
				const __m128i resultValue2{ _mm_xor_si128(value2, deltaValue) };
				score1low = _mm_cvtsi128_si64(resultScore1);
				score1high = _mm_cvtsi128_si64(_mm_srli_si128(resultScore1, 8));
				score2low = _mm_cvtsi128_si64(resultScore2);
				score2high = _mm_cvtsi128_si64(_mm_srli_si128(resultScore2, 8));
				value1low = _mm_cvtsi128_si64(resultValue1);
				value1high = _mm_cvtsi128_si64(_mm_srli_si128(resultValue1, 8));
				value2low = _mm_cvtsi128_si64(resultValue2);
				value2high = _mm_cvtsi128_si64(_mm_srli_si128(resultValue2, 8));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1low & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>(value1low >> 32);
				pValues[IDX1c] = static_cast<std::uint16_t>(value1high);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2low & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>(value2low >> 32);
				pValues[IDX2c] = static_cast<std::uint16_t>(value2high);
				pScores[IDX1a] = static_cast<std::int32_t>(score1low & UINT64_C(0xffffffff));
				pScores[IDX1b] = static_cast<std::int32_t>(score1low >> 32);
				pScores[IDX1c] = static_cast<std::int32_t>(score1high);
				pScores[IDX2a] = static_cast<std::int32_t>(score2low & UINT64_C(0xffffffff));
				pScores[IDX2b] = static_cast<std::int32_t>(score2low >> 32);
				pScores[IDX2c] = static_cast<std::int32_t>(score2high);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			PYGMALION_INLINE static void vector4_SSE2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1low{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1b])) << 32) };
				std::uint64_t score1high{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1c])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1d])) << 32) };
				std::uint64_t score2low{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2b])) << 32) };
				std::uint64_t score2high{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2c])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2d])) << 32) };
				std::uint64_t value1low{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 32) };
				std::uint64_t value1high{ static_cast<std::uint64_t>(pValues[IDX1c]) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 32) };
				std::uint64_t value2low{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 32) };
				std::uint64_t value2high{ static_cast<std::uint64_t>(pValues[IDX2c]) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 32) };
				const __m128i score1{ _mm_set_epi64x(score1high, score1low) };
				const __m128i score2{ _mm_set_epi64x(score2high, score2low) };
				const __m128i value1{ _mm_set_epi64x(value1high, value1low) };
				const __m128i value2{ _mm_set_epi64x(value2high, value2low) };
				const __m128i comparision{ _mm_cmpgt_epi32(score2, score1) };
				const __m128i deltaScore{ _mm_and_si128(_mm_xor_si128(score1, score2), comparision) };
				const __m128i resultScore1{ _mm_xor_si128(score1, deltaScore) };
				const __m128i resultScore2{ _mm_xor_si128(score2, deltaScore) };
				const __m128i deltaValue{ _mm_and_si128(_mm_xor_si128(value1, value2), comparision) };
				const __m128i resultValue1{ _mm_xor_si128(value1, deltaValue) };
				const __m128i resultValue2{ _mm_xor_si128(value2, deltaValue) };
				score1low = _mm_cvtsi128_si64(resultScore1);
				score1high = _mm_cvtsi128_si64(_mm_srli_si128(resultScore1, 8));
				score2low = _mm_cvtsi128_si64(resultScore2);
				score2high = _mm_cvtsi128_si64(_mm_srli_si128(resultScore2, 8));
				value1low = _mm_cvtsi128_si64(resultValue1);
				value1high = _mm_cvtsi128_si64(_mm_srli_si128(resultValue1, 8));
				value2low = _mm_cvtsi128_si64(resultValue2);
				value2high = _mm_cvtsi128_si64(_mm_srli_si128(resultValue2, 8));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1low & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>(value1low >> 32);
				pValues[IDX1c] = static_cast<std::uint16_t>(value1high & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1high >> 32);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2low & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>(value2low >> 32);
				pValues[IDX2c] = static_cast<std::uint16_t>(value2high & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2high >> 32);
				pScores[IDX1a] = static_cast<std::int32_t>(score1low & UINT64_C(0xffffffff));
				pScores[IDX1b] = static_cast<std::int32_t>(score1low >> 32);
				pScores[IDX1c] = static_cast<std::int32_t>(score1high & UINT64_C(0xffffffff));
				pScores[IDX1d] = static_cast<std::int32_t>(score1high >> 32);
				pScores[IDX2a] = static_cast<std::int32_t>(score2low & UINT64_C(0xffffffff));
				pScores[IDX2b] = static_cast<std::int32_t>(score2low >> 32);
				pScores[IDX2c] = static_cast<std::int32_t>(score2high & UINT64_C(0xffffffff));
				pScores[IDX2d] = static_cast<std::int32_t>(score2high >> 32);
			}
#endif
#if defined PYGMALION_CPU_AVX2
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			PYGMALION_INLINE static void vector5_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1b])) << 32) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1c])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1d])) << 32) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2b])) << 32) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2c])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2d])) << 32) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1e])) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2e])) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 32) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1c]) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 32) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 32) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2c]) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 32) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1e]) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2e]) };
				const __m128i score1A{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score1B{ _mm_set1_epi64x(score1lowB) };
				const __m128i score2A{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i score2B{ _mm_set1_epi64x(score2lowB) };
				const __m128i value1A{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value1B{ _mm_set1_epi64x(value1lowB) };
				const __m128i value2A{ _mm_set_epi64x(value2highA, value2lowA) };
				const __m128i value2B{ _mm_set1_epi64x(value2lowB) };
				const __m256i score1{ _mm256_inserti128_si256(_mm256_castsi128_si256(score1A),score1B, 1) };
				const __m256i score2{ _mm256_inserti128_si256(_mm256_castsi128_si256(score2A),score2B, 1) };
				const __m256i value1{ _mm256_inserti128_si256(_mm256_castsi128_si256(value1A),value1B, 1) };
				const __m256i value2{ _mm256_inserti128_si256(_mm256_castsi128_si256(value2A),value2B, 1) };
				const __m256i comparision{ _mm256_cmpgt_epi32(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1A{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1B{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2A{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2B{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1A{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1B{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2A{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2B{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1A);
				score1highA = _mm_cvtsi128_si64(_mm_srli_si128(resultScore1A, 8));
				score2lowA = _mm_cvtsi128_si64(resultScore2A);
				score2highA = _mm_cvtsi128_si64(_mm_srli_si128(resultScore2A, 8));
				score1lowB = _mm_cvtsi128_si64(resultScore1B);
				score2lowB = _mm_cvtsi128_si64(resultScore2B);
				value1lowA = _mm_cvtsi128_si64(resultValue1A);
				value1highA = _mm_cvtsi128_si64(_mm_srli_si128(resultValue1A, 8));
				value2lowA = _mm_cvtsi128_si64(resultValue2A);
				value2highA = _mm_cvtsi128_si64(_mm_srli_si128(resultValue2A, 8));
				value1lowB = _mm_cvtsi128_si64(resultValue1B);
				value2lowB = _mm_cvtsi128_si64(resultValue2B);
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>(value1lowA >> 32);
				pValues[IDX1c] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1highA >> 32);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1lowB);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>(value2lowA >> 32);
				pValues[IDX2c] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2highA >> 32);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2lowB);
				pScores[IDX1a] = static_cast<std::int32_t>(score1lowA & UINT64_C(0xffffffff));
				pScores[IDX1b] = static_cast<std::int32_t>(score1lowA >> 32);
				pScores[IDX1c] = static_cast<std::int32_t>(score1highA & UINT64_C(0xffffffff));
				pScores[IDX1d] = static_cast<std::int32_t>(score1highA >> 32);
				pScores[IDX1e] = static_cast<std::int32_t>(score1lowB);
				pScores[IDX2a] = static_cast<std::int32_t>(score2lowA & UINT64_C(0xffffffff));
				pScores[IDX2b] = static_cast<std::int32_t>(score2lowA >> 32);
				pScores[IDX2c] = static_cast<std::int32_t>(score2highA & UINT64_C(0xffffffff));
				pScores[IDX2d] = static_cast<std::int32_t>(score2highA >> 32);
				pScores[IDX2e] = static_cast<std::int32_t>(score2lowB);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			PYGMALION_INLINE static void vector6_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1b])) << 32) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1c])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1d])) << 32) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2b])) << 32) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2c])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2d])) << 32) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1f])) << 32) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2f])) << 32) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 32) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1c]) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 32) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 32) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2c]) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 32) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 32) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 32) };
				const __m128i score1A{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score1B{ _mm_set1_epi64x(score1lowB) };
				const __m128i score2A{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i score2B{ _mm_set1_epi64x(score2lowB) };
				const __m128i value1A{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value1B{ _mm_set1_epi64x(value1lowB) };
				const __m128i value2A{ _mm_set_epi64x(value2highA, value2lowA) };
				const __m128i value2B{ _mm_set1_epi64x(value2lowB) };
				const __m256i score1{ _mm256_inserti128_si256(_mm256_castsi128_si256(score1A),score1B, 1) };
				const __m256i score2{ _mm256_inserti128_si256(_mm256_castsi128_si256(score2A),score2B, 1) };
				const __m256i value1{ _mm256_inserti128_si256(_mm256_castsi128_si256(value1A),value1B, 1) };
				const __m256i value2{ _mm256_inserti128_si256(_mm256_castsi128_si256(value2A),value2B, 1) };
				const __m256i comparision{ _mm256_cmpgt_epi32(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1A{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1B{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2A{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2B{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1A{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1B{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2A{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2B{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1A);
				score1highA = _mm_cvtsi128_si64(_mm_srli_si128(resultScore1A, 8));
				score2lowA = _mm_cvtsi128_si64(resultScore2A);
				score2highA = _mm_cvtsi128_si64(_mm_srli_si128(resultScore2A, 8));
				score1lowB = _mm_cvtsi128_si64(resultScore1B);
				score2lowB = _mm_cvtsi128_si64(resultScore2B);
				value1lowA = _mm_cvtsi128_si64(resultValue1A);
				value1highA = _mm_cvtsi128_si64(_mm_srli_si128(resultValue1A, 8));
				value2lowA = _mm_cvtsi128_si64(resultValue2A);
				value2highA = _mm_cvtsi128_si64(_mm_srli_si128(resultValue2A, 8));
				value1lowB = _mm_cvtsi128_si64(resultValue1B);
				value2lowB = _mm_cvtsi128_si64(resultValue2B);
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>(value1lowA >> 32);
				pValues[IDX1c] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1highA >> 32);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1lowB & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>(value1lowB >> 32);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>(value2lowA >> 32);
				pValues[IDX2c] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2highA >> 32);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2lowB & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>(value2lowB >> 32);
				pScores[IDX1a] = static_cast<std::int32_t>(score1lowA & UINT64_C(0xffffffff));
				pScores[IDX1b] = static_cast<std::int32_t>(score1lowA >> 32);
				pScores[IDX1c] = static_cast<std::int32_t>(score1highA & UINT64_C(0xffffffff));
				pScores[IDX1d] = static_cast<std::int32_t>(score1highA >> 32);
				pScores[IDX1e] = static_cast<std::int32_t>(score1lowB & UINT64_C(0xffffffff));
				pScores[IDX1f] = static_cast<std::int32_t>(score1lowB >> 32);
				pScores[IDX2a] = static_cast<std::int32_t>(score2lowA & UINT64_C(0xffffffff));
				pScores[IDX2b] = static_cast<std::int32_t>(score2lowA >> 32);
				pScores[IDX2c] = static_cast<std::int32_t>(score2highA & UINT64_C(0xffffffff));
				pScores[IDX2d] = static_cast<std::int32_t>(score2highA >> 32);
				pScores[IDX2e] = static_cast<std::int32_t>(score2lowB & UINT64_C(0xffffffff));
				pScores[IDX2f] = static_cast<std::int32_t>(score2lowB >> 32);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			PYGMALION_INLINE static void vector7_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1b])) << 32) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1c])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1d])) << 32) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2b])) << 32) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2c])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2d])) << 32) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1f])) << 32) };
				std::uint64_t score1highB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1g])) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2f])) << 32) };
				std::uint64_t score2highB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2g])) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 32) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1c]) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 32) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 32) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2c]) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 32) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 32) };
				std::uint64_t value1highB{ static_cast<std::uint64_t>(pValues[IDX1g]) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 32) };
				std::uint64_t value2highB{ static_cast<std::uint64_t>(pValues[IDX2g]) };
				const __m128i score1A{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score1B{ _mm_set_epi64x(score1highB, score1lowB) };
				const __m128i score2A{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i score2B{ _mm_set_epi64x(score2highB, score2lowB) };
				const __m128i value1A{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value1B{ _mm_set_epi64x(value1highB, value1lowB) };
				const __m128i value2A{ _mm_set_epi64x(value2highA, value2lowA) };
				const __m128i value2B{ _mm_set_epi64x(value2highB, value2lowB) };
				const __m256i score1{ _mm256_inserti128_si256(_mm256_castsi128_si256(score1A),score1B, 1) };
				const __m256i score2{ _mm256_inserti128_si256(_mm256_castsi128_si256(score2A),score2B, 1) };
				const __m256i value1{ _mm256_inserti128_si256(_mm256_castsi128_si256(value1A),value1B, 1) };
				const __m256i value2{ _mm256_inserti128_si256(_mm256_castsi128_si256(value2A),value2B, 1) };
				const __m256i comparision{ _mm256_cmpgt_epi32(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1A{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1B{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2A{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2B{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1A{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1B{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2A{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2B{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1A);
				score1highA = _mm_cvtsi128_si64(_mm_srli_si128(resultScore1A, 8));
				score2lowA = _mm_cvtsi128_si64(resultScore2A);
				score2highA = _mm_cvtsi128_si64(_mm_srli_si128(resultScore2A, 8));
				score1lowB = _mm_cvtsi128_si64(resultScore1B);
				score1highB = _mm_cvtsi128_si64(_mm_srli_si128(resultScore1B, 8));
				score2lowB = _mm_cvtsi128_si64(resultScore2B);
				score2highB = _mm_cvtsi128_si64(_mm_srli_si128(resultScore2B, 8));
				value1lowA = _mm_cvtsi128_si64(resultValue1A);
				value1highA = _mm_cvtsi128_si64(_mm_srli_si128(resultValue1A, 8));
				value2lowA = _mm_cvtsi128_si64(resultValue2A);
				value2highA = _mm_cvtsi128_si64(_mm_srli_si128(resultValue2A, 8));
				value1lowB = _mm_cvtsi128_si64(resultValue1B);
				value1highB = _mm_cvtsi128_si64(_mm_srli_si128(resultValue1B, 8));
				value2lowB = _mm_cvtsi128_si64(resultValue2B);
				value2highB = _mm_cvtsi128_si64(_mm_srli_si128(resultValue2B, 8));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>(value1lowA >> 32);
				pValues[IDX1c] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1highA >> 32);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1lowB & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>(value1lowB >> 32);
				pValues[IDX1g] = static_cast<std::uint16_t>(value1highB);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>(value2lowA >> 32);
				pValues[IDX2c] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2highA >> 32);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2lowB & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>(value2lowB >> 32);
				pValues[IDX2g] = static_cast<std::uint16_t>(value2highB);
				pScores[IDX1a] = static_cast<std::int32_t>(score1lowA & UINT64_C(0xffffffff));
				pScores[IDX1b] = static_cast<std::int32_t>(score1lowA >> 32);
				pScores[IDX1c] = static_cast<std::int32_t>(score1highA & UINT64_C(0xffffffff));
				pScores[IDX1d] = static_cast<std::int32_t>(score1highA >> 32);
				pScores[IDX1e] = static_cast<std::int32_t>(score1lowB & UINT64_C(0xffffffff));
				pScores[IDX1f] = static_cast<std::int32_t>(score1lowB >> 32);
				pScores[IDX1g] = static_cast<std::int32_t>(score1highB);
				pScores[IDX2a] = static_cast<std::int32_t>(score2lowA & UINT64_C(0xffffffff));
				pScores[IDX2b] = static_cast<std::int32_t>(score2lowA >> 32);
				pScores[IDX2c] = static_cast<std::int32_t>(score2highA & UINT64_C(0xffffffff));
				pScores[IDX2d] = static_cast<std::int32_t>(score2highA >> 32);
				pScores[IDX2e] = static_cast<std::int32_t>(score2lowB & UINT64_C(0xffffffff));
				pScores[IDX2f] = static_cast<std::int32_t>(score2lowB >> 32);
				pScores[IDX2g] = static_cast<std::int32_t>(score2highB);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			PYGMALION_INLINE static void vector8_AVX2(VALUE* pValues, SCORE* pScores) noexcept
			{
				std::uint64_t score1lowA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1b])) << 32) };
				std::uint64_t score1highA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1c])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1d])) << 32) };
				std::uint64_t score2lowA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2a])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2b])) << 32) };
				std::uint64_t score2highA{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2c])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2d])) << 32) };
				std::uint64_t score1lowB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1e])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1f])) << 32) };
				std::uint64_t score1highB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1g])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX1h])) << 32) };
				std::uint64_t score2lowB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2e])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2f])) << 32) };
				std::uint64_t score2highB{ static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2g])) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[IDX2h])) << 32) };
				std::uint64_t value1lowA{ static_cast<std::uint64_t>(pValues[IDX1a]) | (static_cast<std::uint64_t>(pValues[IDX1b]) << 32) };
				std::uint64_t value1highA{ static_cast<std::uint64_t>(pValues[IDX1c]) | (static_cast<std::uint64_t>(pValues[IDX1d]) << 32) };
				std::uint64_t value2lowA{ static_cast<std::uint64_t>(pValues[IDX2a]) | (static_cast<std::uint64_t>(pValues[IDX2b]) << 32) };
				std::uint64_t value2highA{ static_cast<std::uint64_t>(pValues[IDX2c]) | (static_cast<std::uint64_t>(pValues[IDX2d]) << 32) };
				std::uint64_t value1lowB{ static_cast<std::uint64_t>(pValues[IDX1e]) | (static_cast<std::uint64_t>(pValues[IDX1f]) << 32) };
				std::uint64_t value1highB{ static_cast<std::uint64_t>(pValues[IDX1g]) | (static_cast<std::uint64_t>(pValues[IDX1h]) << 32) };
				std::uint64_t value2lowB{ static_cast<std::uint64_t>(pValues[IDX2e]) | (static_cast<std::uint64_t>(pValues[IDX2f]) << 32) };
				std::uint64_t value2highB{ static_cast<std::uint64_t>(pValues[IDX2g]) | (static_cast<std::uint64_t>(pValues[IDX2h]) << 32) };
				const __m128i score1A{ _mm_set_epi64x(score1highA, score1lowA) };
				const __m128i score1B{ _mm_set_epi64x(score1highB, score1lowB) };
				const __m128i score2A{ _mm_set_epi64x(score2highA, score2lowA) };
				const __m128i score2B{ _mm_set_epi64x(score2highB, score2lowB) };
				const __m128i value1A{ _mm_set_epi64x(value1highA, value1lowA) };
				const __m128i value1B{ _mm_set_epi64x(value1highB, value1lowB) };
				const __m128i value2A{ _mm_set_epi64x(value2highA, value2lowA) };
				const __m128i value2B{ _mm_set_epi64x(value2highB, value2lowB) };
				const __m256i score1{ _mm256_inserti128_si256(_mm256_castsi128_si256(score1A),score1B, 1) };
				const __m256i score2{ _mm256_inserti128_si256(_mm256_castsi128_si256(score2A),score2B, 1) };
				const __m256i value1{ _mm256_inserti128_si256(_mm256_castsi128_si256(value1A),value1B, 1) };
				const __m256i value2{ _mm256_inserti128_si256(_mm256_castsi128_si256(value2A),value2B, 1) };
				const __m256i comparision{ _mm256_cmpgt_epi32(score2, score1) };
				const __m256i deltaScore{ _mm256_and_si256(_mm256_xor_si256(score1, score2), comparision) };
				const __m256i resultScore1{ _mm256_xor_si256(score1, deltaScore) };
				const __m256i resultScore2{ _mm256_xor_si256(score2, deltaScore) };
				const __m256i deltaValue{ _mm256_and_si256(_mm256_xor_si256(value1, value2), comparision) };
				const __m256i resultValue1{ _mm256_xor_si256(value1, deltaValue) };
				const __m256i resultValue2{ _mm256_xor_si256(value2, deltaValue) };
				const __m128i resultScore1A{ _mm256_extracti128_si256(resultScore1, 0) };
				const __m128i resultScore1B{ _mm256_extracti128_si256(resultScore1, 1) };
				const __m128i resultScore2A{ _mm256_extracti128_si256(resultScore2, 0) };
				const __m128i resultScore2B{ _mm256_extracti128_si256(resultScore2, 1) };
				const __m128i resultValue1A{ _mm256_extracti128_si256(resultValue1, 0) };
				const __m128i resultValue1B{ _mm256_extracti128_si256(resultValue1, 1) };
				const __m128i resultValue2A{ _mm256_extracti128_si256(resultValue2, 0) };
				const __m128i resultValue2B{ _mm256_extracti128_si256(resultValue2, 1) };
				score1lowA = _mm_cvtsi128_si64(resultScore1A);
				score1highA = _mm_cvtsi128_si64(_mm_srli_si128(resultScore1A, 8));
				score2lowA = _mm_cvtsi128_si64(resultScore2A);
				score2highA = _mm_cvtsi128_si64(_mm_srli_si128(resultScore2A, 8));
				score1lowB = _mm_cvtsi128_si64(resultScore1B);
				score1highB = _mm_cvtsi128_si64(_mm_srli_si128(resultScore1B, 8));
				score2lowB = _mm_cvtsi128_si64(resultScore2B);
				score2highB = _mm_cvtsi128_si64(_mm_srli_si128(resultScore2B, 8));
				value1lowA = _mm_cvtsi128_si64(resultValue1A);
				value1highA = _mm_cvtsi128_si64(_mm_srli_si128(resultValue1A, 8));
				value2lowA = _mm_cvtsi128_si64(resultValue2A);
				value2highA = _mm_cvtsi128_si64(_mm_srli_si128(resultValue2A, 8));
				value1lowB = _mm_cvtsi128_si64(resultValue1B);
				value1highB = _mm_cvtsi128_si64(_mm_srli_si128(resultValue1B, 8));
				value2lowB = _mm_cvtsi128_si64(resultValue2B);
				value2highB = _mm_cvtsi128_si64(_mm_srli_si128(resultValue2B, 8));
				pValues[IDX1a] = static_cast<std::uint16_t>(value1lowA & UINT64_C(0xffff));
				pValues[IDX1b] = static_cast<std::uint16_t>(value1lowA >> 32);
				pValues[IDX1c] = static_cast<std::uint16_t>(value1highA & UINT64_C(0xffff));
				pValues[IDX1d] = static_cast<std::uint16_t>(value1highA >> 32);
				pValues[IDX1e] = static_cast<std::uint16_t>(value1lowB & UINT64_C(0xffff));
				pValues[IDX1f] = static_cast<std::uint16_t>(value1lowB >> 32);
				pValues[IDX1g] = static_cast<std::uint16_t>(value1highB & UINT64_C(0xffff));
				pValues[IDX1h] = static_cast<std::uint16_t>(value1highB >> 32);
				pValues[IDX2a] = static_cast<std::uint16_t>(value2lowA & UINT64_C(0xffff));
				pValues[IDX2b] = static_cast<std::uint16_t>(value2lowA >> 32);
				pValues[IDX2c] = static_cast<std::uint16_t>(value2highA & UINT64_C(0xffff));
				pValues[IDX2d] = static_cast<std::uint16_t>(value2highA >> 32);
				pValues[IDX2e] = static_cast<std::uint16_t>(value2lowB & UINT64_C(0xffff));
				pValues[IDX2f] = static_cast<std::uint16_t>(value2lowB >> 32);
				pValues[IDX2g] = static_cast<std::uint16_t>(value2highB & UINT64_C(0xffff));
				pValues[IDX2h] = static_cast<std::uint16_t>(value2highB >> 32);
				pScores[IDX1a] = static_cast<std::int32_t>(score1lowA & UINT64_C(0xffffffff));
				pScores[IDX1b] = static_cast<std::int32_t>(score1lowA >> 32);
				pScores[IDX1c] = static_cast<std::int32_t>(score1highA & UINT64_C(0xffffffff));
				pScores[IDX1d] = static_cast<std::int32_t>(score1highA >> 32);
				pScores[IDX1e] = static_cast<std::int32_t>(score1lowB & UINT64_C(0xffffffff));
				pScores[IDX1f] = static_cast<std::int32_t>(score1lowB >> 32);
				pScores[IDX1g] = static_cast<std::int32_t>(score1highB & UINT64_C(0xffffffff));
				pScores[IDX1h] = static_cast<std::int32_t>(score1highB >> 32);
				pScores[IDX2a] = static_cast<std::int32_t>(score2lowA & UINT64_C(0xffffffff));
				pScores[IDX2b] = static_cast<std::int32_t>(score2lowA >> 32);
				pScores[IDX2c] = static_cast<std::int32_t>(score2highA & UINT64_C(0xffffffff));
				pScores[IDX2d] = static_cast<std::int32_t>(score2highA >> 32);
				pScores[IDX2e] = static_cast<std::int32_t>(score2lowB & UINT64_C(0xffffffff));
				pScores[IDX2f] = static_cast<std::int32_t>(score2lowB >> 32);
				pScores[IDX2g] = static_cast<std::int32_t>(score2highB & UINT64_C(0xffffffff));
				pScores[IDX2h] = static_cast<std::int32_t>(score2highB >> 32);
			}
#endif
			static void sort_N0(VALUE* pValues, SCORE* pScores) noexcept
			{
			}
			static void sort_N1(VALUE* pValues, SCORE* pScores) noexcept
			{
			}
			static void sort_N2(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar<0, 1>(pValues, pScores); // FIRST 1-Lane
			}
			static void sort_N3(VALUE* pValues, SCORE* pScores) noexcept
			{
				scalar<1, 2>(pValues, pScores);
				scalar<0, 2>(pValues, pScores);
				scalar<0, 1>(pValues, pScores);
			}
			static void sort_N4(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<0, 1, 2, 3>(pValues, pScores); // FIRST 2-Lane
				vector2<0, 2, 1, 3>(pValues, pScores);
				scalar<1, 2>(pValues, pScores);
			}
			static void sort_N5(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<0, 4, 1, 3>(pValues, pScores);
				scalar<0, 2>(pValues, pScores);
				vector2<2, 4, 0, 1>(pValues, pScores);
				vector2<2, 3, 1, 4>(pValues, pScores);
				vector2<1, 2, 3, 4>(pValues, pScores);
			}
			static void sort_N6(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector2<0, 4, 1, 5>(pValues, pScores);
				vector2<0, 2, 1, 3>(pValues, pScores);
				vector3<2, 4, 3, 5, 0, 1>(pValues, pScores); // FIRST 3-Lane
				vector2<2, 3, 4, 5>(pValues, pScores);
				scalar<1, 4>(pValues, pScores);
				vector2<1, 2, 3, 4 >(pValues, pScores);
			}
			static void sort_N7(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector3<0, 4, 1, 5, 2, 6>(pValues, pScores);
				vector3<0, 2, 1, 3, 4, 6>(pValues, pScores);
				vector3<2, 4, 3, 5, 0, 1>(pValues, pScores);
				vector2<2, 3, 4, 5>(pValues, pScores);
				vector2<1, 4, 3, 6>(pValues, pScores);
				vector3<1, 2, 3, 4, 5, 6>(pValues, pScores);
			}
			static void sort_N8(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores); // FIRST 4-Lane
				vector4<0, 2, 1, 3, 4, 6, 5, 7>(pValues, pScores);
				vector4<2, 4, 3, 5, 0, 1, 6, 7>(pValues, pScores);
				vector2<2, 3, 4, 5>(pValues, pScores);
				vector2<1, 4, 3, 6>(pValues, pScores);
				vector3<1, 2, 3, 4, 5, 6>(pValues, pScores);
			}
			static void sort_N9(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector4<0, 8, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector3<0, 4, 1, 3, 5, 7>(pValues, pScores);
				vector3<4, 8, 0, 2, 3, 5>(pValues, pScores);
				vector3<4, 6, 2, 8, 0, 1>(pValues, pScores);
				vector2<2, 4, 6, 8>(pValues, pScores);
				vector4<2, 3, 4, 5, 6, 7, 1, 8>(pValues, pScores);
				vector3<1, 4, 3, 6, 5, 8>(pValues, pScores);
				vector4<1, 2, 3, 4, 5, 6, 7, 8>(pValues, pScores);
			}
			static void sort_N10(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector5<4, 9, 3, 8, 2, 7, 1, 6, 0, 5>(pValues, pScores); // FIRST 5-Lane
				vector4<1, 4, 6, 9, 0, 3, 5, 8>(pValues, pScores);
				vector3<0, 2, 3, 6, 7, 9>(pValues, pScores);
				vector4<0, 1, 2, 4, 5, 7, 8, 9>(pValues, pScores);
				vector4<1, 2, 4, 6, 7, 8, 3, 5>(pValues, pScores);
				vector4<2, 5, 6, 8, 1, 3, 4, 7>(pValues, pScores);
				vector2<2, 3, 6, 7>(pValues, pScores);
				vector2<3, 4, 5, 6>(pValues, pScores);
				scalar<4, 5>(pValues, pScores);
			}
			static void sort_N11(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector5<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>(pValues, pScores);
				vector5<1, 3, 5, 7, 0, 2, 4, 6, 8, 10>(pValues, pScores);
				vector5<1, 2, 5, 6, 9, 10, 0, 4, 3, 7>(pValues, pScores);
				vector3<1, 5, 6, 10, 4, 8>(pValues, pScores);
				vector4<5, 9, 2, 6, 0, 4, 3, 8>(pValues, pScores);
				vector4<1, 5, 6, 10, 2, 3, 8, 9>(pValues, pScores);
				vector4<1, 4, 7, 10, 3, 5, 6, 8>(pValues, pScores);
				vector3<2, 4, 7, 9, 5, 6>(pValues, pScores);
				vector2<3, 4, 7, 8>(pValues, pScores);
			}
			static void sort_N12(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector6<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11>(pValues, pScores); // FIRST 6-Lane
				vector6<1, 3, 5, 7, 9, 11, 0, 2, 4, 6, 8, 10>(pValues, pScores);
				vector5<1, 2, 5, 6, 9, 10, 0, 4, 7, 11>(pValues, pScores);
				vector4<1, 5, 6, 10, 3, 7, 4, 8>(pValues, pScores);
				vector5<5, 9, 2, 6, 0, 4, 7, 11, 3, 8>(pValues, pScores);
				vector4<1, 5, 6, 10, 2, 3, 8, 9>(pValues, pScores);
				vector4<1, 4, 7, 10, 3, 5, 6, 8>(pValues, pScores);
				vector3<2, 4, 7, 9, 5, 6>(pValues, pScores);
				vector2<3, 4, 7, 8>(pValues, pScores);
			}
			static void sort_N13(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector6<1, 7, 9, 11, 3, 4, 5, 8, 0, 12, 2, 6>(pValues, pScores);
				vector6<0, 1, 2, 3, 4, 6, 8, 11, 7, 12, 5, 9>(pValues, pScores);
				vector5<0, 2, 3, 7, 10, 11, 1, 4, 6, 12>(pValues, pScores);
				vector4<7, 8, 11, 12, 4, 9, 6, 10>(pValues, pScores);
				vector5<3, 4, 5, 6, 8, 9, 10, 11, 1, 7>(pValues, pScores);
				vector6<2, 6, 9, 11, 1, 3, 4, 7, 8, 10, 0, 5>(pValues, pScores);
				vector3<2, 5, 6, 8, 9, 10>(pValues, pScores);
				vector4<1, 2, 3, 5, 7, 8, 4, 6>(pValues, pScores);
				vector4<2, 3, 4, 5, 6, 7, 8, 9>(pValues, pScores);
				vector2<3, 4, 5, 6>(pValues, pScores);
			}
			static void sort_N14(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector7<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13>(pValues, pScores); // FIRST 7-Lane
				vector6<0, 2, 4, 6, 8, 10, 1, 3, 5, 7, 9, 11>(pValues, pScores);
				vector6<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 3, 7>(pValues, pScores);
				vector6<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13>(pValues, pScores);
				vector6<5, 10, 6, 9, 3, 12, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				vector5<1, 4, 7, 13, 2, 8, 5, 6, 9, 10>(pValues, pScores);
				vector4<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				vector4<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				vector5<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				vector2<6, 7, 8, 9>(pValues, pScores);
			}
			static void sort_N15(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector7<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13>(pValues, pScores);
				vector7<0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11>(pValues, pScores);
				vector7<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7>(pValues, pScores);
				vector7<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14>(pValues, pScores);
				vector7<5, 10, 6, 9, 3, 12, 13, 14, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				vector6<1, 4, 7, 13, 2, 8, 11, 14, 5, 6, 9, 10>(pValues, pScores);
				vector4<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				vector4<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				vector5<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				vector2<6, 7, 8, 9>(pValues, pScores);
			}
			static void sort_N16(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>(pValues, pScores); // FIRST 8-Lane
				vector8<0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15>(pValues, pScores);
				vector8<0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15>(pValues, pScores);
				vector8<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector7<5, 10, 6, 9, 3, 12, 13, 14, 7, 11, 1, 2, 4, 8>(pValues, pScores);
				vector6<1, 4, 7, 13, 2, 8, 11, 14, 5, 6, 9, 10>(pValues, pScores);
				vector4<2, 4, 11, 13, 3, 8, 7, 12>(pValues, pScores);
				vector4<6, 8, 10, 12, 3, 5, 7, 9>(pValues, pScores);
				vector5<3, 4, 5, 6, 7, 8, 9, 10, 11, 12>(pValues, pScores);
				vector2<6, 7, 8, 9>(pValues, pScores);
			}
			static void sort_N17(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector7<0, 8, 1, 5, 2, 6, 3, 7, 9, 13, 10, 14, 11, 15>(pValues, pScores);
				vector7<8, 16, 0, 4, 5, 9, 6, 10, 7, 11, 1, 3, 13, 15>(pValues, pScores);
				vector5<8, 12, 4, 16, 0, 2, 5, 7, 9, 11>(pValues, pScores);
				vector5<4, 8, 12, 16, 3, 9, 7, 13, 0, 1>(pValues, pScores);
				vector7<4, 6, 8, 10, 12, 14, 2, 16, 3, 5, 7, 9, 11, 13>(pValues, pScores);
				vector3<2, 8, 6, 12, 10, 16>(pValues, pScores);
				vector4<2, 4, 6, 8, 10, 12, 14, 16>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 16>(pValues, pScores);
				vector5<1, 8, 3, 10, 5, 12, 7, 14, 9, 16>(pValues, pScores);
				vector7<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16>(pValues, pScores);
				vector8<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16>(pValues, pScores);
			}
			static void sort_N18(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector6<0, 8, 1, 9, 2, 6, 3, 7, 10, 14, 11, 15>(pValues, pScores);
				vector6<8, 16, 9, 17, 0, 4, 1, 5, 6, 10, 7, 11>(pValues, pScores);
				vector6<8, 12, 9, 13, 4, 16, 5, 17, 0, 2, 1, 3>(pValues, pScores);
				vector5<4, 8, 5, 9, 12, 16, 13, 17, 0, 1>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 2, 16, 3, 17>(pValues, pScores);
				vector6<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17>(pValues, pScores);
				vector8<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				vector4<1, 16, 3, 10, 5, 12, 7, 14>(pValues, pScores);
				vector5<1, 8, 9, 16, 3, 6, 7, 10, 11, 14>(pValues, pScores);
				vector4<1, 4, 5, 8, 9, 12, 13, 16>(pValues, pScores);
				vector8<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16>(pValues, pScores);
			}
			static void sort_N19(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector5<0, 8, 1, 9, 2, 10, 3, 7, 11, 15>(pValues, pScores);
				vector7<8, 16, 9, 17, 10, 18, 0, 4, 1, 5, 2, 6, 7, 11>(pValues, pScores);
				vector8<8, 12, 9, 13, 10, 14, 4, 16, 5, 17, 6, 18, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 8, 5, 9, 6, 10, 12, 16, 13, 17, 14, 18, 0, 1>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 3, 17>(pValues, pScores);
				vector5<2, 16, 3, 9, 6, 12, 7, 13, 11, 17>(pValues, pScores);
				vector6<2, 8, 10, 16, 3, 5, 7, 9, 11, 13, 15, 17>(pValues, pScores);
				vector4<2, 4, 6, 8, 10, 12, 14, 16>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 12, 7, 14>(pValues, pScores);
				vector4<1, 8, 3, 10, 9, 16, 11, 18>(pValues, pScores);
				vector8<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18>(pValues, pScores);
				vector9<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18>(pValues, pScores); // FIRST 9-Lane
			}
			static void sort_N20(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector4<0, 8, 1, 9, 2, 10, 3, 11>(pValues, pScores);
				vector8<8, 16, 9, 17, 10, 18, 11, 19, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 4, 16, 5, 17, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores); // FIRST 10-Lane
				vector9<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector5<2, 16, 3, 17, 6, 12, 7, 13, 18, 19>(pValues, pScores);
				vector4<2, 8, 3, 9, 10, 16, 11, 17>(pValues, pScores);
				vector8<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17>(pValues, pScores);
				vector8<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 12, 7, 14>(pValues, pScores);
				vector4<1, 8, 3, 10, 9, 16, 11, 18>(pValues, pScores);
				vector8<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18>(pValues, pScores);
				vector9<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18>(pValues, pScores);
			}
			static void sort_N21(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector5<0, 8, 1, 9, 2, 10, 3, 11, 4, 12>(pValues, pScores);
				vector9<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 5, 17, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				vector8<4, 16, 5, 9, 6, 10, 7, 11, 13, 17, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				vector6<4, 8, 12, 16, 5, 7, 9, 11, 13, 15, 17, 19>(pValues, pScores);
				vector6<4, 6, 8, 10, 12, 14, 16, 18, 3, 17, 7, 13>(pValues, pScores);
				vector4<2, 16, 6, 20, 3, 9, 11, 17>(pValues, pScores);
				vector8<2, 8, 6, 12, 10, 16, 14, 20, 3, 5, 7, 9, 11, 13, 15, 17>(pValues, pScores);
				vector5<2, 4, 6, 8, 10, 12, 14, 16, 18, 20>(pValues, pScores);
				vector9<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 14>(pValues, pScores);
				vector6<1, 8, 3, 10, 5, 12, 9, 16, 11, 18, 13, 20>(pValues, pScores);
				vector9<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20>(pValues, pScores);
				vector10<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20>(pValues, pScores);
			}
			static void sort_N22(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 14, 7, 15>(pValues, pScores);
				vector6<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13>(pValues, pScores);
				vector10<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 6, 18, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 10, 7, 11, 14, 18, 15, 19, 0, 1>(pValues, pScores);
				vector4<4, 8, 5, 9, 12, 16, 13, 17>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector4<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				vector8<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				vector10<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				vector10<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 14>(pValues, pScores);
				vector6<1, 8, 3, 10, 5, 12, 9, 16, 11, 18, 13, 20>(pValues, pScores);
				vector9<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20>(pValues, pScores);
				vector10<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20>(pValues, pScores);
			}
			static void sort_N23(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 15>(pValues, pScores);
				vector7<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14>(pValues, pScores);
				vector11<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores); // FIRST 11-Lane
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 7, 19, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 11, 15, 19, 20, 22, 0, 1>(pValues, pScores);
				vector6<4, 8, 5, 9, 6, 10, 12, 16, 13, 17, 14, 18>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector4<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				vector8<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				vector10<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				vector10<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 22>(pValues, pScores);
				vector8<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22>(pValues, pScores);
				vector10<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22>(pValues, pScores);
				vector11<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22>(pValues, pScores);
			}
			static void sort_N24(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23>(pValues, pScores);
				vector8<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores); // FIRST 12-Lane
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 19, 20, 22, 21, 23, 0, 1>(pValues, pScores);
				vector9<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 22, 23>(pValues, pScores);
				vector8<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19>(pValues, pScores);
				vector4<2, 16, 3, 17, 6, 20, 7, 21>(pValues, pScores);
				vector8<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21>(pValues, pScores);
				vector10<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21>(pValues, pScores);
				vector10<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21>(pValues, pScores);
				vector4<1, 16, 3, 18, 5, 20, 7, 22>(pValues, pScores);
				vector8<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22>(pValues, pScores);
				vector10<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22>(pValues, pScores);
				vector11<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22>(pValues, pScores);
			}
			static void sort_N25(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector9<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24>(pValues, pScores);
				vector9<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 21, 23, 0, 1>(pValues, pScores);
				vector9<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24>(pValues, pScores);
				vector9<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22>(pValues, pScores);
				vector5<2, 16, 3, 17, 6, 20, 7, 21, 10, 24>(pValues, pScores);
				vector9<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24>(pValues, pScores);
				vector11<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24>(pValues, pScores);
				vector11<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23>(pValues, pScores);
				vector5<1, 16, 3, 18, 5, 20, 7, 22, 9, 24>(pValues, pScores);
				vector9<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24>(pValues, pScores);
				vector11<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24>(pValues, pScores);
				vector12<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24>(pValues, pScores);
			}
			static void sort_N26(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector10<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25>(pValues, pScores);
				vector10<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector7<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 0, 1>(pValues, pScores);
				vector10<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25>(pValues, pScores);
				vector10<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23>(pValues, pScores);
				vector6<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25>(pValues, pScores);
				vector10<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				vector12<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				vector12<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				vector5<1, 16, 3, 18, 5, 20, 7, 22, 9, 24>(pValues, pScores);
				vector9<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24>(pValues, pScores);
				vector11<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24>(pValues, pScores);
				vector12<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24>(pValues, pScores);
			}
			static void sort_N27(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector11<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26>(pValues, pScores);
				vector11<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector8<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 0, 1>(pValues, pScores);
				vector11<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26>(pValues, pScores);
				vector11<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26>(pValues, pScores);
				vector6<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25>(pValues, pScores);
				vector10<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				vector12<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				vector12<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				vector6<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26>(pValues, pScores);
				vector10<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26>(pValues, pScores);
				vector12<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26>(pValues, pScores);
				vector13<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26>(pValues, pScores); // FIRST 13-Lane
			}
			static void sort_N28(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector12<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27>(pValues, pScores);
				vector12<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27>(pValues, pScores);
				vector12<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector7<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 26, 27>(pValues, pScores);
				vector10<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25>(pValues, pScores);
				vector12<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25>(pValues, pScores);
				vector12<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25>(pValues, pScores);
				vector6<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26>(pValues, pScores);
				vector10<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26>(pValues, pScores);
				vector12<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26>(pValues, pScores);
				vector13<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26>(pValues, pScores);
			}
			static void sort_N29(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector13<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28>(pValues, pScores);
				vector13<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28>(pValues, pScores);
				vector13<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector7<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28>(pValues, pScores);
				vector11<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28>(pValues, pScores);
				vector13<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28>(pValues, pScores);
				vector13<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27>(pValues, pScores);
				vector7<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28>(pValues, pScores);
				vector11<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28>(pValues, pScores);
				vector13<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28>(pValues, pScores);
				vector14<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28>(pValues, pScores); // FIRST 14-Lane
			}
			static void sort_N30(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector14<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29>(pValues, pScores);
				vector14<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29>(pValues, pScores);
				vector14<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29>(pValues, pScores);
				vector10<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector8<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				vector12<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				vector14<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				vector14<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				vector7<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28>(pValues, pScores);
				vector11<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28>(pValues, pScores);
				vector13<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28>(pValues, pScores);
				vector14<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28>(pValues, pScores);
			}
			static void sort_N31(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector15<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30>(pValues, pScores); // FIRST 15-Lane
				vector15<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29, 22, 30>(pValues, pScores);
				vector15<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29, 26, 30>(pValues, pScores);
				vector11<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3, 28, 30>(pValues, pScores);
				vector9<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector8<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				vector12<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				vector14<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				vector14<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				vector8<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28, 15, 30>(pValues, pScores);
				vector12<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28, 23, 30>(pValues, pScores);
				vector14<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28, 27, 30>(pValues, pScores);
				vector15<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30>(pValues, pScores);
			}
			static void sort_N32(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector16<0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30, 15, 31>(pValues, pScores); // FIRST 16-Lane
				vector16<0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29, 22, 30, 23, 31>(pValues, pScores);
				vector16<8, 16, 9, 17, 10, 18, 11, 19, 12, 20, 13, 21, 14, 22, 15, 23, 0, 4, 1, 5, 2, 6, 3, 7, 24, 28, 25, 29, 26, 30, 27, 31>(pValues, pScores);
				vector12<8, 12, 9, 13, 10, 14, 11, 15, 16, 20, 17, 21, 18, 22, 19, 23, 0, 2, 1, 3, 28, 30, 29, 31>(pValues, pScores);
				vector10<4, 16, 5, 17, 6, 18, 7, 19, 12, 24, 13, 25, 14, 26, 15, 27, 0, 1, 30, 31>(pValues, pScores);
				vector12<4, 8, 5, 9, 6, 10, 7, 11, 12, 16, 13, 17, 14, 18, 15, 19, 20, 24, 21, 25, 22, 26, 23, 27>(pValues, pScores);
				vector12<4, 6, 5, 7, 8, 10, 9, 11, 12, 14, 13, 15, 16, 18, 17, 19, 20, 22, 21, 23, 24, 26, 25, 27>(pValues, pScores);
				vector8<2, 16, 3, 17, 6, 20, 7, 21, 10, 24, 11, 25, 14, 28, 15, 29>(pValues, pScores);
				vector12<2, 8, 3, 9, 6, 12, 7, 13, 10, 16, 11, 17, 14, 20, 15, 21, 18, 24, 19, 25, 22, 28, 23, 29>(pValues, pScores);
				vector14<2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11, 13, 14, 16, 15, 17, 18, 20, 19, 21, 22, 24, 23, 25, 26, 28, 27, 29>(pValues, pScores);
				vector14<2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29>(pValues, pScores);
				vector8<1, 16, 3, 18, 5, 20, 7, 22, 9, 24, 11, 26, 13, 28, 15, 30>(pValues, pScores);
				vector12<1, 8, 3, 10, 5, 12, 7, 14, 9, 16, 11, 18, 13, 20, 15, 22, 17, 24, 19, 26, 21, 28, 23, 30>(pValues, pScores);
				vector14<1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17, 20, 19, 22, 21, 24, 23, 26, 25, 28, 27, 30>(pValues, pScores);
				vector15<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30>(pValues, pScores);
			}
			typedef void SORTFUNC(VALUE* pValues, SCORE* pScores);
			constexpr static inline SORTFUNC* m_SortFunction[]
			{
				&sort_N0,
				&sort_N1,
				&sort_N2,
				&sort_N3,
				&sort_N4,
				&sort_N5,
#if defined(PYGMALION_CPU_SSE2)
				&sort_N6,
				&sort_N7,
				&sort_N8,
				&sort_N9,
				&sort_N10,
				&sort_N11,
				&sort_N12,
				&sort_N13,
				&sort_N14,
				&sort_N15,
				&sort_N16,
				&sort_N17,
				&sort_N18,
				&sort_N19,
				&sort_N20,
				&sort_N21,
				&sort_N22,
				&sort_N23,
				&sort_N24,
				&sort_N25,
				&sort_N26,
				&sort_N27,
				&sort_N28,
				&sort_N29,
				&sort_N30,
				&sort_N31,
				&sort_N32,
#endif
			};
			constexpr static size_t sort_tail() noexcept
			{
#if defined(PYGMALION_CPU_AVX2)
				if constexpr (cpu::supports(cpu::flags::AVX2))
					return 32;
				else
#endif
				{
#if defined(PYGMALION_CPU_SSE2)
					if constexpr (cpu::supports(cpu::flags::SSE2))
						return 32;
					else
#endif
						return 5;
				}
			}
		public:
			PYGMALION_INLINE static void quickSort(const int low, const int high, VALUE* pValues, SCORE* pScores) noexcept
			{
				const int pi{ partition(low, high, pValues, pScores) };
				sortValues(&pValues[low], &pScores[low], pi - low);
				sortValues(&pValues[pi + 1], &pScores[pi + 1], high - pi);
			}
			PYGMALION_INLINE static int partition(const int low, const int high, VALUE* pValues, SCORE* pScores) noexcept
			{
				const SCORE pivotScore{ pScores[high] };
				int i{ low - 1 };
				for (int j = low; j <= high - 1; j++)
				{
#if defined(PYGMALION_CPU_SSE2)
					if constexpr (cpu::supports(cpu::flags::SSE2))
					{
						const std::int64_t comparision{ static_cast<std::int64_t>(pScores[j] >= pivotScore) };
						i += comparision;
						const std::uint64_t negated{ static_cast<std::uint64_t>(-comparision) };
						const std::uint64_t mask{ static_cast<std::uint64_t>(negated & UINT64_C(0xffffffff)) };
						std::uint64_t interleaved1{ static_cast<std::uint64_t>(pValues[i]) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[i])) << 16) };
						std::uint64_t interleaved2{ static_cast<std::uint64_t>(pValues[j]) | (static_cast<std::uint64_t>(static_cast<std::uint32_t>(pScores[j])) << 16) };
						const __m128i operand1{ _mm_cvtsi64_si128(interleaved1) };
						const __m128i operand2{ _mm_cvtsi64_si128(interleaved2) };
						const __m128i maskVector{ _mm_shufflelo_epi16(_mm_cvtsi64_si128(mask), 0b00000000) };
						const __m128i delta{ _mm_and_si128(_mm_xor_si128(operand1, operand2), maskVector) };
						const __m128i result1{ _mm_xor_si128(operand1, delta) };
						const __m128i result2{ _mm_xor_si128(operand2, delta) };
						interleaved1 = _mm_cvtsi128_si64(result1);
						interleaved2 = _mm_cvtsi128_si64(result2);
						pValues[i] = static_cast<std::uint16_t>(interleaved1 & UINT64_C(0xffff));
						pScores[i] = static_cast<std::int32_t>(interleaved1 >> 16);
						pValues[j] = static_cast<std::uint16_t>(interleaved2 & UINT64_C(0xffff));
						pScores[j] = static_cast<std::int32_t>(interleaved2 >> 16);
					}
					else
#endif
					{
						const std::int64_t comparision{ static_cast<std::int64_t>(pScores[j] >= pivotScore) };
						i += comparision;
						const std::uint64_t negated{ static_cast<std::uint64_t>(-comparision) };
						const std::uint16_t maskValue{ static_cast<std::uint16_t>(negated & UINT64_C(0xffff)) };
						const std::uint32_t maskScore{ static_cast<std::uint32_t>(negated & UINT64_C(0xffffffff)) };
						const std::uint32_t deltaScores{ static_cast<std::uint32_t>((reinterpret_cast<std::uint32_t*>(pScores)[i] ^ reinterpret_cast<std::uint32_t*>(pScores)[j]) & maskScore) };
						const std::uint16_t deltaValues{ static_cast<std::uint16_t>((pValues[i] ^ pValues[j]) & maskValue) };
						pValues[i] ^= deltaValues;
						pValues[j] ^= deltaValues;
						reinterpret_cast<std::uint32_t*>(pScores)[i] ^= deltaScores;
						reinterpret_cast<std::uint32_t*>(pScores)[j] ^= deltaScores;
					}
				}
				i++;
				std::swap(pValues[i], pValues[high]);
				std::swap(pScores[i], pScores[high]);
				return i;
			}
			static void sortValues(VALUE* pValues, SCORE* pScores, const size_t length) noexcept
			{
				constexpr const auto tail{ sort_tail() };
				if (length <= tail)
				{
					(*(m_SortFunction[length]))(pValues, pScores);
				}
				else
				{
					quickSort(0, length - 1, pValues, pScores);
				}
			}
			template<size_t IDX1, size_t IDX2>
			PYGMALION_INLINE static void scalar(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					scalar_SSE2<IDX1, IDX2>(pValues, pScores);
				else
				#endif*/
				scalar_Vanilla<IDX1, IDX2>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b>
			PYGMALION_INLINE static void vector2(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector2_SSE2<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
				else
#endif
					vector2_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c>
			PYGMALION_INLINE static void vector3(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector3_SSE2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
				else
#endif
					vector3_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d>
			PYGMALION_INLINE static void vector4(VALUE* pValues, SCORE* pScores) noexcept
			{
#if defined(PYGMALION_CPU_SSE2)
				if constexpr (cpu::supports(cpu::SSE2))
					vector4_SSE2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
				else
#endif
					vector4_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e>
			PYGMALION_INLINE static void vector5(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector5_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
								else
				#endif*/
				vector5_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f>
			PYGMALION_INLINE static void vector6(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector6_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
								else
				#endif*/
				vector6_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g>
			PYGMALION_INLINE static void vector7(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector7_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
								else
				#endif*/
				vector7_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h>
			PYGMALION_INLINE static void vector8(VALUE* pValues, SCORE* pScores) noexcept
			{
				/*#if defined(PYGMALION_CPU_AVX2)
								if constexpr (cpu::supports(cpu::AVX2))
									vector8_AVX2<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
								else
				#endif*/
				vector8_Vanilla<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j>
			PYGMALION_INLINE static void vector9(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector5<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
				vector4<IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k>
			PYGMALION_INLINE static void vector10(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector5<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e>(pValues, pScores);
				vector5<IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l>
			PYGMALION_INLINE static void vector11(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector6<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
				vector5<IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m>
			PYGMALION_INLINE static void vector12(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector6<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f>(pValues, pScores);
				vector6<IDX1g, IDX2g, IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n>
			PYGMALION_INLINE static void vector13(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector7<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
				vector6<IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o>
			PYGMALION_INLINE static void vector14(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector7<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g>(pValues, pScores);
				vector7<IDX1h, IDX2h, IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p>
			PYGMALION_INLINE static void vector15(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector7<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p>(pValues, pScores);
			}
			template<size_t IDX1a, size_t IDX2a, size_t IDX1b, size_t IDX2b, size_t IDX1c, size_t IDX2c, size_t IDX1d, size_t IDX2d, size_t IDX1e, size_t IDX2e, size_t IDX1f, size_t IDX2f, size_t IDX1g, size_t IDX2g, size_t IDX1h, size_t IDX2h, size_t IDX1j, size_t IDX2j, size_t IDX1k, size_t IDX2k, size_t IDX1l, size_t IDX2l, size_t IDX1m, size_t IDX2m, size_t IDX1n, size_t IDX2n, size_t IDX1o, size_t IDX2o, size_t IDX1p, size_t IDX2p, size_t IDX1q, size_t IDX2q>
			PYGMALION_INLINE static void vector16(VALUE* pValues, SCORE* pScores) noexcept
			{
				vector8<IDX1a, IDX2a, IDX1b, IDX2b, IDX1c, IDX2c, IDX1d, IDX2d, IDX1e, IDX2e, IDX1f, IDX2f, IDX1g, IDX2g, IDX1h, IDX2h>(pValues, pScores);
				vector8<IDX1j, IDX2j, IDX1k, IDX2k, IDX1l, IDX2l, IDX1m, IDX2m, IDX1n, IDX2n, IDX1o, IDX2o, IDX1p, IDX2p, IDX1q, IDX2q>(pValues, pScores);
			}
		};

	}


	template<typename VALUE, typename SCORE>
	class sort
	{
	public:
		PYGMALION_INLINE static void sortValues(VALUE* pValues, SCORE* pScores, const size_t length) noexcept
		{
			if constexpr (sizeof(VALUE) == sizeof(std::uint8_t) && sizeof(SCORE) == sizeof(std::int8_t))
				detail::compare<std::uint8_t, std::int8_t>::sortValues(reinterpret_cast<std::uint8_t*>(pValues), reinterpret_cast<std::int8_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint8_t) && sizeof(SCORE) == sizeof(std::int16_t))
				detail::compare<std::uint8_t, std::int16_t>::sortValues(reinterpret_cast<std::uint8_t*>(pValues), reinterpret_cast<std::int16_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint8_t) && sizeof(SCORE) == sizeof(std::int32_t))
				detail::compare<std::uint8_t, std::int32_t>::sortValues(reinterpret_cast<std::uint8_t*>(pValues), reinterpret_cast<std::int32_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint8_t) && sizeof(SCORE) == sizeof(std::int64_t))
				detail::compare<std::uint8_t, std::int64_t>::sortValues(reinterpret_cast<std::uint8_t*>(pValues), reinterpret_cast<std::int64_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint16_t) && sizeof(SCORE) == sizeof(std::int8_t))
				detail::compare<std::uint16_t, std::int8_t>::sortValues(reinterpret_cast<std::uint16_t*>(pValues), reinterpret_cast<std::int8_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint16_t) && sizeof(SCORE) == sizeof(std::int16_t))
				detail::compare<std::uint16_t, std::int16_t>::sortValues(reinterpret_cast<std::uint16_t*>(pValues), reinterpret_cast<std::int16_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint16_t) && sizeof(SCORE) == sizeof(std::int32_t))
				detail::compare<std::uint16_t, std::int32_t>::sortValues(reinterpret_cast<std::uint16_t*>(pValues), reinterpret_cast<std::int32_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint16_t) && sizeof(SCORE) == sizeof(std::int64_t))
				detail::compare<std::uint16_t, std::int64_t>::sortValues(reinterpret_cast<std::uint16_t*>(pValues), reinterpret_cast<std::int64_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint32_t) && sizeof(SCORE) == sizeof(std::int8_t))
				detail::compare<std::uint32_t, std::int8_t>::sortValues(reinterpret_cast<std::uint32_t*>(pValues), reinterpret_cast<std::int8_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint32_t) && sizeof(SCORE) == sizeof(std::int16_t))
				detail::compare<std::uint32_t, std::int16_t>::sortValues(reinterpret_cast<std::uint32_t*>(pValues), reinterpret_cast<std::int16_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint32_t) && sizeof(SCORE) == sizeof(std::int32_t))
				detail::compare<std::uint32_t, std::int32_t>::sortValues(reinterpret_cast<std::uint32_t*>(pValues), reinterpret_cast<std::int32_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint32_t) && sizeof(SCORE) == sizeof(std::int64_t))
				detail::compare<std::uint32_t, std::int64_t>::sortValues(reinterpret_cast<std::uint32_t*>(pValues), reinterpret_cast<std::int64_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint64_t) && sizeof(SCORE) == sizeof(std::int8_t))
				detail::compare<std::uint64_t, std::int8_t>::sortValues(reinterpret_cast<std::uint64_t*>(pValues), reinterpret_cast<std::int8_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint64_t) && sizeof(SCORE) == sizeof(std::int16_t))
				detail::compare<std::uint64_t, std::int16_t>::sortValues(reinterpret_cast<std::uint64_t*>(pValues), reinterpret_cast<std::int16_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint64_t) && sizeof(SCORE) == sizeof(std::int32_t))
				detail::compare<std::uint64_t, std::int32_t>::sortValues(reinterpret_cast<std::uint64_t*>(pValues), reinterpret_cast<std::int32_t*>(pScores), length);
			else if constexpr (sizeof(VALUE) == sizeof(std::uint64_t) && sizeof(SCORE) == sizeof(std::int64_t))
				detail::compare<std::uint64_t, std::int64_t>::sortValues(reinterpret_cast<std::uint64_t*>(pValues), reinterpret_cast<std::int64_t*>(pScores), length);
			else
				detail::compare<VALUE, SCORE>::sortValues(pValues, pScores, length);
		}
	};
}