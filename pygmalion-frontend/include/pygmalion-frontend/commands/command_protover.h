namespace pygmalion::frontend
{
#if defined(PYGMALION_WB2)
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_protover :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if ((this->front().isXBoard()) && (token == "protover"))
			{
				int version = parser::parseInt(remainder);
				this->front().protocolVersion() = version;
				std::deque<std::string> features;
				if (version > 1)
				{
					this->frontendEngine().getXBoardFeatures(features);
					if (features.size() > 0)
					{
						this->output() << "feature done=0" << std::endl;
						this->output() << "feature sigint=0" << std::endl;
						this->output() << "feature sigterm=0" << std::endl;
						this->output() << "feature reuse=1" << std::endl;
						this->output() << "feature colors=0" << std::endl;
						this->output() << "feature nps=0" << std::endl;
						this->output() << "feature san=0" << std::endl;
						this->output() << "feature debug=0" << std::endl;
						this->output() << "feature time=1" << std::endl;
						this->output() << "feature myname=\"" << this->frontendEngine().version() << "\"" << std::endl;
						std::deque<std::string> variants;
						this->frontendEngine().getXBoardVariants(variants);
						if (variants.size() > 0)
						{
							this->output() << "feature variants=\"";
							for (size_t i = 0; i < variants.size(); i++)
							{
								this->output() << variants[i];
								if (i < (variants.size() - 1))
								{
									this->output() << ",";
								}
							}
							this->output() << "\"" << std::endl;;
						}
						for (const auto feature : features)
						{
							this->output() << "feature " << feature << std::endl;
						}
#if defined(PYGMALION_TUNE)&&(PYGMALION_TUNE==1)
						for (const pieceType pc : pieceType::range)
							this->output() << "feature option option=\"Piece" << static_cast<size_t>(pc) << "_Material" << " -spin " << static_cast<int>(static_cast<double>(boardType::materialValue(pc, descriptorFrontend::whitePlayer)) * 100.0) << " 0 20000\"" << std::endl;
#endif
						this->output() << "feature done=1" << std::endl;
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
			return "PROTOVER";
		}
	};
#endif
}