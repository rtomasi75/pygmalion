#include <pygmalion-chess-evaluation.h>
namespace pygmalion::chess::evaluation
{
	bool command_generatePST::onProcess(const std::string& cmd) noexcept
	{
		std::string token;
		std::string remainder;
		parser::parseToken(cmd, token, remainder);
		using positionType = pawnlookupPosition<descriptorDynamics>;
		using positionList = list<positionType, 9>;
		if (token == "generate-pst")
		{
			std::string token2;
			std::string remainder2;
			parser::parseToken(remainder, token2, remainder2);
			if (token2 != "")
			{
				const auto millipawns{ parser::parseInt(token2) };
				const double scale{ static_cast<double>(millipawns) * 0.001 };
				double pst[countSquares];
				for (int i = 0; i < countSquares; i++)
					pst[i] = 0.0;
				// King
				for (const auto sq : squareType::range)
				{
					pst[sq] = generatorType::movegenKing.attacks(sq, squaresType::all()).count();
				}
				double m{ std::numeric_limits<double>::max() };
				double M{ std::numeric_limits<double>::min() };
				for (int i = 0; i < countSquares; i++)
				{
					if (m > pst[i])
						m = pst[i];
					if (M < pst[i])
						M = pst[i];
				}
				double med{ 0.5 * (m + M) };
				for (int i = 0; i < countSquares; i++)
				{
					pst[i] -= med;
					pst[i] *= scale;
				}
				this->output() << "PYGMALION_TUNABLE static inline double m_PST_King[" << countSquares << "]" << std::endl;
				this->output() << "{" << std::endl;
				for (int i = 0; i < 8; i++)
				{
					this->output() << "\t";
					for (int j = 0; j < 8; j++)
					{
						this->output() << pst[i * 8 + j] << ", ";
					}
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
				// Knight
				for (const auto sq : squareType::range)
				{
					pst[sq] = generatorType::movegenKnight.attacks(sq, squaresType::all()).count();
				}
				m = std::numeric_limits<double>::max();
				M = std::numeric_limits<double>::min();
				for (int i = 0; i < countSquares; i++)
				{
					if (m > pst[i])
						m = pst[i];
					if (M < pst[i])
						M = pst[i];
				}
				med = 0.5 * (m + M);
				for (int i = 0; i < countSquares; i++)
				{
					pst[i] -= med;
					pst[i] *= scale;
				}
				this->output() << "PYGMALION_TUNABLE static inline double m_PST_Knight[" << countSquares << "]" << std::endl;
				this->output() << "{" << std::endl;
				for (int i = 0; i < 8; i++)
				{
					this->output() << "\t";
					for (int j = 0; j < 8; j++)
					{
						this->output() << pst[i * 8 + j] << ", ";
					}
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
				// Bishop
				for (const auto sq : squareType::range)
				{
					pst[sq] = generatorType::movegenSlidersDiag.attacks(sq, squaresType::all()).count();
				}
				m = std::numeric_limits<double>::max();
				M = std::numeric_limits<double>::min();
				for (int i = 0; i < countSquares; i++)
				{
					if (m > pst[i])
						m = pst[i];
					if (M < pst[i])
						M = pst[i];
				}
				med = 0.5 * (m + M);
				for (int i = 0; i < countSquares; i++)
				{
					pst[i] -= med;
					pst[i] *= scale;
				}
				this->output() << "PYGMALION_TUNABLE static inline double m_PST_Bishop[" << countSquares << "]" << std::endl;
				this->output() << "{" << std::endl;
				for (int i = 0; i < 8; i++)
				{
					this->output() << "\t";
					for (int j = 0; j < 8; j++)
					{
						this->output() << pst[i * 8 + j] << ", ";
					}
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
				// Rook
				for (const auto sq : squareType::range)
				{
					pst[sq] = generatorType::movegenSlidersHV.attacks(sq, squaresType::all()).count();
				}
				m = std::numeric_limits<double>::max();
				M = std::numeric_limits<double>::min();
				for (int i = 0; i < countSquares; i++)
				{
					if (m > pst[i])
						m = pst[i];
					if (M < pst[i])
						M = pst[i];
				}
				med = 0.5 * (m + M);
				for (int i = 0; i < countSquares; i++)
				{
					pst[i] -= med;
					pst[i] *= scale;
				}
				this->output() << "PYGMALION_TUNABLE static inline double m_PST_Rook[" << countSquares << "]" << std::endl;
				this->output() << "{" << std::endl;
				for (int i = 0; i < 8; i++)
				{
					this->output() << "\t";
					for (int j = 0; j < 8; j++)
					{
						this->output() << pst[i * 8 + j] << ", ";
					}
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
				// Queen
				for (const auto sq : squareType::range)
				{
					pst[sq] = (generatorType::movegenSlidersHV.attacks(sq, squaresType::all()) | generatorType::movegenSlidersDiag.attacks(sq, squaresType::all())).count();
				}
				m = std::numeric_limits<double>::max();
				M = std::numeric_limits<double>::min();
				for (int i = 0; i < countSquares; i++)
				{
					if (m > pst[i])
						m = pst[i];
					if (M < pst[i])
						M = pst[i];
				}
				med = 0.5 * (m + M);
				for (int i = 0; i < countSquares; i++)
				{
					pst[i] -= med;
					pst[i] *= scale;
				}
				this->output() << "PYGMALION_TUNABLE static inline double m_PST_Queen[" << countSquares << "]" << std::endl;
				this->output() << "{" << std::endl;
				for (int i = 0; i < 8; i++)
				{
					this->output() << "\t";
					for (int j = 0; j < 8; j++)
					{
						this->output() << pst[i * 8 + j] << ", ";
					}
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
				// Pawn
				for (const auto sq : squareType::range)
				{
					if ((sq.rank() > 0) && (sq.rank() < 8))
						pst[sq] = sq.rank() + (generatorType::movegenPawnCaptureWhite.attacks(sq, squaresType::all()) | generatorType::movegenPawnPromoCaptureWhite.attacks(sq, squaresType::all())).count();
					else
						pst[sq] = 0.0;
				}
				m = std::numeric_limits<double>::max();
				M = std::numeric_limits<double>::min();
				for (int i = 0; i < countSquares; i++)
				{
					const squareType sq{ static_cast<squareType>(i) };
					if ((sq.rank() > 0) && (sq.rank() < 7))
					{
						if (m > pst[i])
							m = pst[i];
						if (M < pst[i])
							M = pst[i];
					}
				}
				med = 0.5 * (m + M);
				for (int i = 0; i < countSquares; i++)
				{
					pst[i] -= med;
					pst[i] *= scale;
				}
				this->output() << "PYGMALION_TUNABLE static inline double m_PST_Pawn[" << countSquares << "]" << std::endl;
				this->output() << "{" << std::endl;
				for (int i = 0; i < 8; i++)
				{
					this->output() << "\t";
					for (int j = 0; j < 8; j++)
					{
						const squareType sq{ static_cast<squareType>(i * 8 + j) };
						if ((sq.rank() > 0) && (sq.rank() < 7))
							this->output() << pst[i * 8 + j] << ", ";
						else
							this->output() << 0.0 << ", ";
					}
					this->output() << std::endl;
				}
				this->output() << "};" << std::endl;
			}
			else
			{
				this->output() << "Invalid score: " << token2 << std::endl;
			}
			return true;
		}
		else
			return false;
	}
}