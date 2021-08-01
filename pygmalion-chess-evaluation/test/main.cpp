#include <pygmalion-chess-evaluation.h>

using namespace pygmalion;
using namespace pygmalion::evaluation;
using namespace pygmalion::chess;

int main(int argc, char* argv[])
{
	engine<pygmalion::chess::evaluator> eng(std::cin, std::cout);
	eng.run();
	return 0;
}