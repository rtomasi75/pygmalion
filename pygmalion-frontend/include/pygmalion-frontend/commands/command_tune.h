namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_tune :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include <pygmalion-frontend/include_frontend.h>
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			std::string token;
			std::string remainder;
			parser::parseToken(cmd, token, remainder);
			if (token == "tune")
			{
				std::ifstream data("tuning.data");
				if (data.is_open())
				{
					this->output() << "Successfully opened tuning data file..." << std::endl;
					this->flushOutput();
					tuningpositions tp;
					this->output() << "reading tuning data...";
					data >> tp;
					this->output() << "done!" << std::endl;
					this->flushOutput();
					double K = 1.0;
					const double deltaK{ 0.000001 };
					this->output() << "K=" << K << "=>";
					this->flushOutput();
					double sc = this->frontendEngine().tuningError(tp, K);
					this->output() << " " << sc << std::endl;
				}
				else
					this->output() << "Error: failed to open tuning data file..." << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "TUNE";
		}
	};
}