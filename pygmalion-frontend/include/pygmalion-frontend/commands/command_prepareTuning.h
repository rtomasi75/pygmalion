namespace pygmalion::frontend
{
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_prepareTuning :
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
			if (token == "prepare-tuning")
			{
				std::ifstream pgn(remainder);
				if (pgn.is_open())
				{
					this->output() << "Successfully opened file \"" << remainder << "\"." << std::endl;
					this->flushOutput();
					std::deque<recordType> records;
					std::string gamenum = "";
					bool bOk{ true };
					while (bOk)
					{
						recordType rec(this->stateEngine().materialTable());
						if (recordType::read(pgn, rec, this->stateEngine().materialTable(), this->dynamicsEngine().delta()))
						{
							records.emplace_back(rec);
							std::string temp = parser::valueToString(records.size(), " games");
							if (temp != gamenum)
							{
								gamenum = temp;
								this->output() << gamenum << std::endl;
								this->flushOutput();
							}
						}
						else
						{
							this->output() << "finished." << std::endl;
							this->flushOutput();
							bOk = false;
						}
						this->flushOutput();
					}
					std::string posnum = "";
					tuningpositions tp;
					size_t poscount{ 0 };
					for (const auto& rec : records)
					{
						if (!gamestateType::isOpen(rec.outcome()))
						{
							double score{ 0.5 };
							if (gamestateType::isWin(rec.outcome(), static_cast<playerType>(0)))
								score = 1.0;
							else if (gamestateType::isLoss(rec.outcome(), static_cast<playerType>(0)))
								score = 0.0;
							for (size_t i = 0; i <= rec.length(); i++)
							{
								const boardType pos{ rec.position(i) };
								tuningposition tpos(pos.getFen(), score);
								tp.add(std::move(tpos));
							}
							poscount += rec.length();
							std::string temp = parser::valueToString(poscount, " positions");
							if (temp != posnum)
							{
								posnum = temp;
								this->output() << posnum << std::endl;
								this->flushOutput();
							}
						}
					}
					this->output() << "writing tuning data...";
					std::ofstream outfile("tuning.data", std::ofstream::binary);
					if (outfile.is_open())
					{
						outfile << tp;
						this->output() << "done!" << std::endl;
					}
					else
					{
						this->output() << "error!" << std::endl;
					}
				}
				else
					this->output() << "Error: failed to open file \"" << remainder << "\"." << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "PREPARE-TUNING";
		}
	};
}