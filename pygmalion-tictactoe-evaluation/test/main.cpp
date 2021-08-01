#include <pygmalion-tictactoe-evaluation.h>

using namespace pygmalion;
using namespace pygmalion::evaluation;
using namespace pygmalion::tictactoe;

int main(int argc, char* argv[])
{
	engine<pygmalion::tictactoe::evaluator> eng(std::cin, std::cout);
	eng.run();
	return 0;
}