#include <pygmalion-chess-dynamics.h>
namespace pygmalion::chess::dynamics
{
	bool command_debugMagics::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		if (token == "debug-magics")
		{
			this->output() << std::endl;
			std::string table;
			std::string remainder2;
			parser::parseToken(remainder, table, remainder2);
			if (table == "slider" || table == "s")
			{
				this->output() << "computing diag. slider magics..." << std::endl;
				this->output() << std::endl;
				this->output() << "constexpr static const typename squaresType::bitsType m_MagicFactors[64]" << std::endl;
				this->output() << "{" << std::endl;
				for (const auto sq : squareType::range)
				{
					auto& sm(propagator_sliders_diag::magic(sq));
					auto premask{ static_cast<typename squaresType::bitsType>(propagator_sliders_diag::relevant(sq)) };
					auto factor{ premask };
					size_t bits;
					sm.magic().find(premask, factor, bits);
					this->output() << "    static_cast<typename squaresType::bitsType>(UINT64_C(0x" << std::hex << static_cast<std::uintmax_t>(factor) << std::dec << "))";
					if (sq < (countSquares - 1))
						this->output() << ",";
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
				this->output() << std::endl;
				this->output() << "computing h/v slider magics..." << std::endl;
				this->output() << std::endl;
				this->output() << "constexpr static const typename squaresType::bitsType m_MagicFactors[64]" << std::endl;
				this->output() << "{" << std::endl;
				for (const auto sq : squareType::range)
				{
					auto& sm(propagator_sliders_hv::magic(sq));
					auto premask{ static_cast<typename squaresType::bitsType>(propagator_sliders_hv::relevant(sq)) };
					auto factor{ premask };
					size_t bits;
					sm.magic().find(premask, factor, bits);
					this->output() << "    static_cast<typename squaresType::bitsType>(UINT64_C(0x" << std::hex << static_cast<std::uintmax_t>(factor) << std::dec << "))";
					if (sq < (countSquares - 1))
						this->output() << ",";
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
				this->output() << std::endl;
				this->output() << "computing diag. inverse slider magics..." << std::endl;
				this->output() << std::endl;
				this->output() << "constexpr static const typename squaresType::bitsType m_InverseMagicFactors[64]" << std::endl;
				this->output() << "{" << std::endl;
				for (const auto sq : squareType::range)
				{
					auto& sm(propagator_sliders_diag::inverseMagic(sq));
					auto premask{ static_cast<typename squaresType::bitsType>(propagator_sliders_diag::inverseRelevant(sq)) };
					auto factor{ premask };
					size_t bits;
					sm.magic().find(premask, factor, bits);
					this->output() << "    static_cast<typename squaresType::bitsType>(UINT64_C(0x" << std::hex << static_cast<std::uintmax_t>(factor) << std::dec << "))";
					if (sq < (countSquares - 1))
						this->output() << ",";
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
				this->output() << std::endl;
				this->output() << "computing h/v inverse inverse slider magics..." << std::endl;
				this->output() << std::endl;
				this->output() << "constexpr static const typename squaresType::bitsType m_InverseMagicFactors[64]" << std::endl;
				this->output() << "{" << std::endl;
				for (const auto sq : squareType::range)
				{
					auto& sm(propagator_sliders_hv::inverseMagic(sq));
					auto premask{ static_cast<typename squaresType::bitsType>(propagator_sliders_hv::inverseRelevant(sq)) };
					auto factor{ premask };
					size_t bits;
					sm.magic().find(premask, factor, bits);
					this->output() << "    static_cast<typename squaresType::bitsType>(UINT64_C(0x" << std::hex << static_cast<std::uintmax_t>(factor) << std::dec << "))";
					if (sq < (countSquares - 1))
						this->output() << ",";
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
			}
			else if (table == "pawn" || table == "doublepush" || table == "p" || table == "D")
			{
				this->output() << "computing black double push magics..." << std::endl;
				this->output() << std::endl;
				this->output() << "constexpr static const typename squaresType::bitsType m_MagicFactors[64]" << std::endl;
				this->output() << "{" << std::endl;
				for (const auto sq : squareType::range)
				{
					auto& sm(propagator_pawn_doublepush_black::magic(sq));
					auto premask{ static_cast<typename squaresType::bitsType>(propagator_pawn_doublepush_black::relevant(sq)) };
					auto factor{ premask };
					size_t bits;
					sm.magic().find(premask, factor, bits);
					this->output() << "    static_cast<typename squaresType::bitsType>(UINT64_C(0x" << std::hex << static_cast<std::uintmax_t>(factor) << std::dec << "))";
					if (sq < (countSquares - 1))
						this->output() << ",";
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
				this->output() << std::endl;
				this->output() << "computing white double push magics..." << std::endl;
				this->output() << std::endl;
				this->output() << "constexpr static const typename squaresType::bitsType m_MagicFactors[64]" << std::endl;
				this->output() << "{" << std::endl;
				for (const auto sq : squareType::range)
				{
					auto& sm(propagator_pawn_doublepush_white::magic(sq));
					auto premask{ static_cast<typename squaresType::bitsType>(propagator_pawn_doublepush_white::relevant(sq)) };
					auto factor{ premask };
					size_t bits;
					sm.magic().find(premask, factor, bits);
					this->output() << "    static_cast<typename squaresType::bitsType>(UINT64_C(0x" << std::hex << static_cast<std::uintmax_t>(factor) << std::dec << "))";
					if (sq < (countSquares - 1))
						this->output() << ",";
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
				this->output() << std::endl;
				this->output() << "computing black double push inverse magics..." << std::endl;
				this->output() << std::endl;
				this->output() << "constexpr static const typename squaresType::bitsType m_InverseMagicFactors[64]" << std::endl;
				this->output() << "{" << std::endl;
				for (const auto sq : squareType::range)
				{
					auto& sm(propagator_pawn_doublepush_black::inverseMagic(sq));
					auto premask{ static_cast<typename squaresType::bitsType>(propagator_pawn_doublepush_black::inverseRelevant(sq)) };
					auto factor{ premask };
					size_t bits;
					sm.magic().find(premask, factor, bits);
					this->output() << "    static_cast<typename squaresType::bitsType>(UINT64_C(0x" << std::hex << static_cast<std::uintmax_t>(factor) << std::dec << "))";
					if (sq < (countSquares - 1))
						this->output() << ",";
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
				this->output() << std::endl;
				this->output() << "computing white double push magics..." << std::endl;
				this->output() << std::endl;
				this->output() << "constexpr static const typename squaresType::bitsType m_InverseMagicFactors[64]" << std::endl;
				this->output() << "{" << std::endl;
				for (const auto sq : squareType::range)
				{
					auto& sm(propagator_pawn_doublepush_white::inverseMagic(sq));
					auto premask{ static_cast<typename squaresType::bitsType>(propagator_pawn_doublepush_white::inverseRelevant(sq)) };
					auto factor{ premask };
					size_t bits;
					sm.magic().find(premask, factor, bits);
					this->output() << "    static_cast<typename squaresType::bitsType>(UINT64_C(0x" << std::hex << static_cast<std::uintmax_t>(factor) << std::dec << "))";
					if (sq < (countSquares - 1))
						this->output() << ",";
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
			}
			else
				this->output() << "invalid table: " << table << std::endl;
			this->output() << std::endl;
			return true;
		}
		else
			return false;
	}
}