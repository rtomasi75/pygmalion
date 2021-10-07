namespace pygmalion::frontend
{
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
						this->output() << "feature";
						this->output() << " sigint=0";
						this->output() << " sigterm=0";
						this->output() << " reuse=1";
						this->output() << " colors=0";
						this->output() << " nps=0";
						this->output() << " san=0";
						this->output() << " debug=0";
						this->output() << " time=0";
						this->output() << " myname=\"" << this->frontendEngine().version() << " by " << this->frontendEngine().author() << "\"";
						std::deque<std::string> variants;
						this->frontendEngine().getXBoardVariants(variants);
						if (variants.size() > 0)
						{
							this->output() << " variants=\"";
							for (size_t i = 0; i < variants.size(); i++)
							{
								this->output() << variants[i];
								if (i < (variants.size() - 1))
								{
									this->output() << ",";
								}
							}
							this->output() << "\"";
						}
						for (const auto feature : features)
						{
							this->output() << "" << feature;
						}
						this->output() << std::endl;
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

}