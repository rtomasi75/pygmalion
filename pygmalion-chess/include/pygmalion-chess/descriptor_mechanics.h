namespace pygmalion::chess
{
	class descriptor_mechanics :
		public pygmalion::descriptor_mechanics<board, 2, 1, 5>
	{
	public:
		constexpr static const moveflagbitType capture{ 0 };
		constexpr static const moveflagbitType doublePush{ 1 };
		constexpr static const moveflagbitType captureEnPassant{ 2 };
		constexpr static const moveflagbitType castle{ 3 };
		constexpr static const moveflagbitType promotion{ 4 };

		constexpr static const int square_from{ 0 };
		constexpr static const int square_to{ 1 };
		constexpr static const int piece_promotion{ 0 };

		constexpr static uint8_t DrawingDistance{ 100 };
	};
}
