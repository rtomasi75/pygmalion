#include <pygmalion-tictactoe.h>

using namespace pygmalion;
using namespace pygmalion::tictactoe;

int main(int argc, char* argv[])
{
	pygmalion::tictactoe::engine eng(std::cin, std::cout);
	eng.run();
	return 0;
}