namespace pygmalion::chess::dynamics
{
	class command_perft :
		public pygmalion::dynamics::command<descriptor_dynamics, generator>
	{
	public:
		using generatorType = generator;
		using stackType = typename generatorType::stackType;
		using descriptorDynamics = descriptor_dynamics;
#include <pygmalion-dynamics/include_dynamics.h>
	private:
		struct perftdata
		{
			std::uintmax_t Moves;
			std::uintmax_t Captures;
			std::uintmax_t EnPassant;
			std::uintmax_t DoublePushes;
			std::uintmax_t QueensideCastles;
			std::uintmax_t KingsideCastles;
			std::uintmax_t Castles;
			std::uintmax_t Checks;
			std::uintmax_t Checkmates;
			constexpr perftdata() :
				Moves{ 0 },
				Captures{ 0 },
				EnPassant{ 0 },
				DoublePushes{ 0 },
				QueensideCastles{ 0 },
				KingsideCastles{ 0 },
				Checks{ 0 },
				Checkmates{ 0 },
				Castles{ 0 }
			{}
			perftdata& operator+=(const perftdata& data) noexcept;
		};
		static void perft(const stackType& stack, const size_t depth, const size_t maxDepth, perftdata& data) noexcept;
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override;
	};

}