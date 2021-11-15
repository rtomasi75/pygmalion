namespace pygmalion::chess::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_debugMaterial :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include <pygmalion-frontend/include_frontend.h>
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "debug-material")
			{
				for (const auto pl : playerType::range)
				{
					for (const auto pc : pieceType::range)
					{
						this->output() << boardType::pieceToString(pc, pl) << ":" << std::endl;
						for (size_t r = countRanks; r > 0; r--)
						{
							const rankType rank{ static_cast<rankType>(r - 1) };
							for (const auto file : fileType::range)
							{
								const squareType sq{ rank & file };
								this->output() << "\t";
								this->output() << boardType::materialValueRelative(pc, sq, pl);
							}
							this->output() << std::endl;
						}
						this->output() << std::endl;
					}
				}
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "DEBUG-MATERIAL";
		}
	};
}