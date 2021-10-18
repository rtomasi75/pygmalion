namespace pygmalion::frontend
{
#if defined(PYGMALION_UCI)
	template<typename DESCRIPTION_FRONTEND, typename FRONT>
	class command_uci :
		public pygmalion::frontend::command<DESCRIPTION_FRONTEND, FRONT>
	{
	public:
		using frontType = FRONT;
		using descriptorFrontend = DESCRIPTION_FRONTEND;
#include "../include_frontend.h"	
	protected:
		virtual bool onProcess(const std::string& cmd) noexcept override
		{
			if (cmd == "uci")
			{
#if defined(PYGMALION_WB2)
				this->front().isXBoard() = false;
				this->front().forceMode() = true;
#endif
				this->front().isUCI() = true;
				this->output() << "id name " << this->frontendEngine().version() << std::endl;
				this->output() << "id author " << this->frontendEngine().author() << std::endl;
				this->output() << "option name Hash type spin default 160 min 1 max ";
				this->output() << std::min(static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max()), ((UINT64_C(1) << std::min(static_cast<size_t>(63), countHashBits)))) / (1024 * 1024) << std::endl;
				this->output() << "option name Ponder type check default " << (this->frontendEngine().ponderEnabled() ? "true" : "false") << std::endl;
#if defined(PYGMALION_TUNE)&&(PYGMALION_TUNE==1)
				for (const pieceType pc : pieceType::range)
					this->output() << "option name Piece" << static_cast<size_t>(pc) << "_Material" << " type spin default " << static_cast<int>(static_cast<double>(boardType::materialValue(pc, descriptorFrontend::whitePlayer)) * 100.0) << " min 0 max 12000" << std::endl;
#endif
				this->output() << "uciok" << std::endl;
				return true;
			}
			else
				return false;
		}
		virtual std::string help() noexcept override
		{
			return "UCI";
		}
	};
#endif
}