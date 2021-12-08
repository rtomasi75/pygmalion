namespace pygmalion::dynamics
{
	template<typename DESCRIPTION_DYNAMICS, typename GENERATOR>
	class command_debugMaterialDelta :
		public pygmalion::dynamics::command<DESCRIPTION_DYNAMICS, GENERATOR>
	{
	public:
		using generatorType = GENERATOR;
		template<size_t PLAYER>
		using stackType = typename generatorType::template stackType<PLAYER>;
		using descriptorDynamics = DESCRIPTION_DYNAMICS;
#include "../include_dynamics.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-materialdelta")
			{
				this->output() << std::endl;
				const auto delta(this->dynamicsEngine().materialDelta());
				for (const auto mask : piecesType::range)
				{
					for (const auto spl : playerType::range)
					{
						for (const auto pl : playerType::range)
						{
							this->output() << boardType::playerToString(spl) << "=>" << boardType::piecesToString(mask, pl) << ": " << delta.maxQuietChange(spl, pl, mask) << std::endl;
							this->output() << boardType::playerToString(spl) << "=>" << boardType::piecesToString(mask, pl) << "=" << boardType::piecesToString(generatorType::promotionResults(pl), pl) << ": " << delta.maxPromotionChange(spl, pl, mask) << std::endl;
							for (const auto mask2 : piecesType::range)
							{
								this->output() << boardType::playerToString(spl) << "=>" << boardType::piecesToString(mask, pl) << "-" << boardType::piecesToString(mask2, pl.next()) << ": " << delta.maxCaptureChange(spl, pl, mask, mask2) << std::endl;
							}
							for (const auto mask2 : piecesType::range)
							{
								this->output() << boardType::playerToString(spl) << "=>" << boardType::piecesToString(mask, pl) << "-" << boardType::piecesToString(mask2, pl.next()) << "=" << boardType::piecesToString(generatorType::promotionResults(pl), pl) << ": " << delta.maxPromoCaptureChange(spl, pl, mask, mask2) << std::endl;
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
			return "DEBUG-MATERIALDELTA";
		}
	};

}