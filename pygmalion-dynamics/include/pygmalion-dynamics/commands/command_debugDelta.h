namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugDelta :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
#include "../include_dynamics.h"	
	private:
		template<size_t PLAYER>
		void process(const playerType pl, const pieceType pc, const squareType sq) noexcept
		{
			if constexpr (PLAYER < countPlayers)
			{
				constexpr const playerType player{ static_cast<playerType>(PLAYER) };
				if (player == pl)
				{
					this->dumpSquares(generatorType::template attackMask<PLAYER>(pc, sq));
				}
				else
					this->template process<PLAYER + 1>(pl, pc, sq);
			}
			else
				PYGMALION_ASSERT(false);
		}
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-delta")
			{
				this->output() << std::endl;
				constexpr const typename piecemaskType::maskType n{ typename piecemaskType::maskType(1) << countPieces };
				const auto delta(this->dynamicsEngine().delta());
				for (const auto mask : piecemaskType::range)
				{
					for (const auto spl : playerType::range)
					{
						for (const auto pl : playerType::range)
						{
							this->output() << boardType::playerToString(spl) << "=>" << boardType::piecemaskToString(mask, pl) << ": " << delta.maxQuietChange(spl, pl, mask) << std::endl;
							this->output() << boardType::playerToString(spl) << "=>" << boardType::piecemaskToString(mask, pl) << "=" << boardType::piecemaskToString(generatorType::promotionResults(pl), pl) << ": " << delta.maxPromotionChange(spl, pl, mask) << std::endl;
							for (const auto mask2 : piecemaskType::range)
							{
								this->output() << boardType::playerToString(spl) << "=>" << boardType::piecemaskToString(mask, pl) << "-" << boardType::piecemaskToString(mask, pl) << ": " << delta.maxCaptureChange(spl, pl, mask, mask2) << std::endl;
							}
							for (const auto mask2 : piecemaskType::range)
							{
								this->output() << boardType::playerToString(spl) << "=>" << boardType::piecemaskToString(mask, pl) << "-" << boardType::piecemaskToString(mask, pl) << "=" << boardType::piecemaskToString(generatorType::promotionResults(pl), pl) << ": " << delta.maxPromoCaptureChange(spl, pl, mask, mask2) << std::endl;
							}
							this->output() << std::endl;
						}
					}
				}
				this->output() << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-DELTA";
		}
	};

}